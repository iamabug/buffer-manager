#include "common.h"
#include "buffer.h"
#include "file.h"

//buffer
struct frame buffer[BUF_SIZE];
//hash table page_id -> frame_id
struct BCB *ptof[BUF_SIZE];
//hash table frame_id -> page_id
int ftop[BUF_SIZE];
//lru always points to the victim page
struct node *lru, *mru;

int hash(int page_id){
    return (page_id % BUF_SIZE);
}

int fix_page(int page_id){
    int h, victim_id;
    struct BCB *bcb;
    h = hash(page_id);
    bcb = ptof[h];

    //already in memory
    while(bcb){
        //if the page is used again
        //move it to the end of lru list
        if(bcb->page_id == page_id){
            struct node* p = lru;
            if(p->frame_id == bcb->frame_id){
                 lru = p->next;
                 mru->next = p;
                 mru = p;
                 mru->next = NULL;
            }
            while(p->next){
                if(p->next->frame_id == bcb->frame_id){
                    struct node *pn = p->next;
                    if(!pn->next){
                        //do nothing because it is already in the right place
                        return 1;
                    }
                    //move the node to mru spot
                    p->next = p->next->next;
                    mru->next = pn;
                    mru = pn;
                    mru->next = NULL;
                    p = p->next;
                }
            }
            return bcb->frame_id;
        }
        bcb = bcb->next;
    }

    //the page in the disk
    victim_id = select_victim();

    //insert new BCB
    bcb = (struct BCB *)malloc(sizeof(struct BCB));
    bcb->page_id = page_id;
    bcb->frame_id = victim_id;
    bcb->dirty = 0;
    bcb->next = ptof[h];
    ptof[h] = bcb;

    //delete old BCB
    int old_page_id = ftop[victim_id];
    h = hash(old_page_id);
    bcb = ptof[h];
    if(bcb->page_id == old_page_id){
        ptof[h] = bcb->next;
    } else {
        while(bcb->next){
            if(bcb->next->page_id == old_page_id){
                bcb->next = bcb->next->next;
            }
        }
    }

    //delete old ftop
    ftop[victim_id] = page_id;
    read_page(dbf, page_id, &buffer[victim_id]);
    return victim_id;
}

int fix_new_page();

int unfix_page(int page_id);

int free_frame_num();


int select_victim(){
    int i;
    //situation 1: no frame is replaced
    for(i=0;i<BUF_SIZE;i++){
        //the first 1024 frames must go here
        if(ftop[i] == -1){
            if(!lru){
                lru = (struct node *)malloc(sizeof(struct node));
                lru->frame_id = i;
                lru->next = NULL;
                mru = lru;
            } else {
                struct node *p = (struct node *)malloc(sizeof(struct node));
                p->frame_id = i;
                mru->next = p;
                mru = p;
                mru->next = NULL;
            }
            return i;
        }
    }
    //situation 2:a frame is replaced to disk
    //update the lru list
    int id = lru->frame_id;
    lru = lru->next;
    struct node *p = (struct node *)malloc(sizeof(struct node));
    p->frame_id = id;
    mru->next = p;
    mru = p;
    mru->next = NULL;
    return id;
}

/*
 * @called when select_victim needs to replace a frame
 * @delete the BCB of the page
 */
int remove_BCB(struct BCB *bcb, int page_id);

/*
 * TODO
 */
void remove_lru_element(int frame_id);

/*
 * @set the dirty bit as 1 for the frame
 */
void set_dirty(int frame_id);

/*
 * @set the dirty bit as 0 for the frame
 */
void unset_dirty(int frame_id);

/*
 * @write all pages in the buffer that has been modified
 * @called when the system is shutdown
 */
void write_dirty();

/*
 * @print the content of the frame
 */
void print_frame(int frame_id);


