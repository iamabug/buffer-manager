/*
 * Initialize the database file
 */

#include "init.h"

//two arrays to store the ids and offsets of all pages
int page_id[PAGE_NUM];
int page_offset[PAGE_NUM];

//exchange arr[j] and arr[k]
void exchange(int arr[], int j, int k){
    arr[j] ^= arr[k];
    arr[k] ^= arr[j];
    arr[j] ^= arr[k];
    return;
}

int init_dbf(){

    FILE *fp;
    int i, j, k;

    srand((unsigned int)time(NULL));
    open_file(DBF_FILE);
    //init the directory page
    for(i=0;i<PAGE_NUM;i++){
        //the i-th record is for the i-th page
        page_id[i] = i;
        //the i-th page stays at offset i
        page_offset[i] = i;
    }

    //shuffle the records and their offsets
    for(i=0;i<PAGE_NUM/2;i++){
        j = rand() % PAGE_NUM;
        k = rand() % PAGE_NUM;
        exchange(page_id, j, k);
    }

    for(i=0;i<PAGE_NUM/2;i++){
        j = rand() % PAGE_NUM;
        k = rand() % PAGE_NUM;
        exchange(page_offset, j, k);
    }

    //write (page_id, offset) tuples to file
    for(i=0;i<PAGE_NUM;i++){
         fwrite(page_id+i, sizeof(int), 1, fp);
         fwrite(page_offset+i, sizeof(int), 1, fp);
    }

    printf("before write pages\n");
    //initialize the pages
    for(i=0;i<PAGE_NUM;i++){
        for(j=0;j<PAGE_SIZE;j++){
            seek(fp, page_id[i]);
            fwrite(page_id+i, sizeof(int), PAGE_SIZE/sizeof(int), fp);
        }
    }
    close_file(fp);
    return 0;
}

int main(){
     init_dbf();
     return 0;
}
