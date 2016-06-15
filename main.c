#include "common.h"
#include "file.h"
#include "buffer.h"
#include "string.h"

#define MAX_LENGTH 32

int main(){
    int op, page_id;
    char buf[MAX_LENGTH];

    trf = fopen(TRF_NAME, "rt");
    //while(fgets(buf, MAX_LENGTH, trf) != NULL){
    if(fgets(buf, MAX_LENGTH, trf) != NULL){
        //buf[strlen(buf) -1 ] = '\0';
        printf("length = %ld\n", strlen(buf));
        buf[strlen(buf)-1] = '\0';
        for(int i=0;i<MAX_LENGTH;i++){
            printf("%x \n", buf[i]);
        }
    }
    close_file(trf);
    return 1;
}
