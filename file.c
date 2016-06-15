#include "file.h"

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
    return 1;
}

int write_page(FILE *fp, int page_id, struct frame *frm){
    seek(fp, page_id);
    fwrite(frm->field, sizeof(char), FRAME_SIZE, fp);
    return 1;
}

int seek(FILE *fp, int page_id){
    int offset = page_id * PAGE_SIZE + DIR_SIZE;
    if(fseek(fp, offset, SEEK_SET)){
        printf("fseek error\n");
        exit(0);
    }
    return 1;
}

//TODO
int inc_page_num(int page_id){
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
