/*
 * Initialize the database file
 */

#include "init.h"
#include "file.h"

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

    int i, j, k;

    srand((unsigned int)time(NULL));
    dbf = open_file(DBF_NAME);
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
        printf("index %d\n", i);
         fwrite(page_id+i, sizeof(int), 1, dbf);
         fwrite(page_offset+i, sizeof(int), 1, dbf);
    }

    //initialize the pages
    for(i=0;i<PAGE_NUM;i++){
        printf("page %d\n", i);
        fseek(dbf, DIR_SIZE + PAGE_SIZE * page_offset[i], SEEK_SET);
        for(j=0;j<PAGE_SIZE/sizeof(int);j++){
            fwrite(page_id+i, sizeof(int), 1, dbf);
        }
    }
    close_file(dbf);
    return 0;
}

int main(){
     init_dbf();
     return 0;
}
