#include "common.h"
#include "file.h"
#include "buffer.h"
#include "string.h"

#define MAX_LENGTH 32

void initialize();
void alter_frame();

int main(){
    char op;
    int page_id, frame_id;
    char buf[MAX_LENGTH];
    int i = 0;

    initialize();
    while(fgets(buf, MAX_LENGTH, trf) != NULL){
        //int i;
        //for(i=0;i<500000;i++){
        //if(fgets(buf, MAX_LENGTH, trf) != NULL){
        //buf[strlen(buf) -1 ] = '\0';
        op = buf[0];
        page_id = atoi(buf+2);
        printf("%d:%d\n", i++, page_id);
        //printf("before fix_page\n");
        frame_id = fix_page(page_id);
        //the page is in memory
        if(ftop[frame_id] == page_id){
            //printf("the page is in memory\n");
            if(op == '1'){
                //printf("Writing page %d\n", page_id);
                write_page(dbf, page_id, &buffer[frame_id]);
                cost_lru += 1;
                cost_plain += 2;
            } else if(op == '0'){
                //print_frame(&buffer[frame_id]);
                //    printf("Reading page %d\n", page_id);
                cost_plain += 1;
            }
        } else {
            //the page is in the disk
            ftop[frame_id] = page_id;
            if(op == '0'){
                //   printf("Reading page %d\n", page_id);
                read_page(dbf, page_id, &buffer[frame_id]);
                cost_plain += 1;
                cost_lru += 1;
            } else if(op == '1') {
                //  printf("Writing page %d\n", page_id);
                read_page(dbf, page_id, &buffer[frame_id]);
                write_page(dbf, page_id, &buffer[frame_id]);
                cost_plain += 2;
                cost_lru += 2;
            }
        }
    }
    printf("I/O times using nothing: %d\n", cost_plain);
    printf("I/O times using lru: %d\n", cost_lru);
    close_file(trf);
    return 1;
    }

    void initialize(){
        int i, j;
        int ret;
        unsigned char temp[50];

        trf = fopen(TRF_NAME, "rt");
        dbf = fopen(DBF_NAME, "rb+");

        cost_plain = 0;
        cost_lru = 0;

        for(i=0;i<BUF_SIZE;i++){
            ptof[i] = NULL;
            ftop[i] = -1;
            for(j=0;j<FRAME_SIZE;j++){
                buffer[i].field[j] = 0;
            }
        }
    }
