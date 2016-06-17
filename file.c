#include "file.h"
#include "buffer.h"

FILE *dbf = NULL;
FILE *trf = NULL;
FILE *open_file(char* filename){
    FILE *fp = fopen(filename, "wr");
    if(!fp){
        printf("file open error : %s\n", filename);
        exit(0);
    }
    return fp;
}

int close_file(FILE* fp){
    if(fclose(fp)){
        printf("file close error!\n");
        exit(0);
    }
    return 1;
}

int read_page(FILE *fp, int page_id, struct frame *frm){
    seek(fp, page_id);
    fread(frm->field, sizeof(char), FRAME_SIZE, fp);
   // print_frame(frm);
    return 1;
}
/*
 * simulate writing a page
 */
void alter_frame(struct frame *frm){
    int i;
    for(i=0;i<FRAME_SIZE;i+=2){
        frm->field[i] += 1;
    }
}

int write_page(FILE *fp, int page_id, struct frame *frm){
    alter_frame(frm);
    //print_frame(frm);
    fwrite(frm->field, sizeof(char), FRAME_SIZE, fp);
    return 1;
}

int seek(FILE *fp, int page_id){
    int i, item_id, offset;
    for(i=0;i<PAGE_NUM;i++){
         fseek(fp, ITEM_SIZE*i, SEEK_SET);
         fread(&item_id, sizeof(int), 1, fp);
         if(item_id == page_id){
             fread(&offset, sizeof(int), 1, fp);
             fseek(fp, DIR_SIZE + offset * PAGE_NUM, SEEK_SET);
             break;
         }
    }
    return 1;
}

//TODO
int get_page_num(){
    return 1;
}

//TODO
int set_use(int page_id, int use_bit){
    return 1;
}

//TODO
int get_use(int page_id){
    return 1;
}


