/*
 * Initialize the database file
 */

#include "init.h"

//two arrays to store the ids and offsets of all pages
int page_id[ITEM_NUM];
int page_offset[ITEM_NUM];

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
    fp = fopen("../data.dbf", "w+");
    if(!fp){
        printf("the file doesn't exist!\n");
    }
    //init the directory page
    for(i=0;i<ITEM_NUM;i++){
        //the i-th record is for the i-th page
        page_id[i] = i;
        //the i-th page stays at offset i
        page_offset[i] = i;
    }
    printf("before shuffle\n");
    //shuffle the records and their offsets
    for(i=0;i<ITEM_NUM/2;i++){
        j = rand() % ITEM_NUM;
        k = rand() % ITEM_NUM;
        exchange(page_id, j, k);
    }
    for(i=0;i<ITEM_NUM/2;i++){
        j = rand() % ITEM_NUM;
        k = rand() % ITEM_NUM;
        exchange(page_offset, j, k);
    }
    printf("before fwrite\n");
    for(i=0;i<ITEM_NUM;i++){
         fwrite(page_id+i, sizeof(int), 1, fp);
         fwrite(page_offset+i, sizeof(int), 1, fp);
    }
    fclose(fp);
    return 0;
}

int main(){
     init_dbf();
     return 0;
}
