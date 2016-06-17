#include <stdio.h>

int main(){
    int temp [50], i;
    FILE *fp = fopen("../data.dbf", "rb");
    if(!fp)
        printf("file open error!\n");
    int ret = fseek(fp, 0, SEEK_SET);
    ret = fread(temp, 50, 1, fp);
    for(i=0;i<50;i++){
        printf("%x\n", temp[i]);
    }
    printf("==================\n");
    //ret = fseek(fp, 500000*8+4096*8550, SEEK_SET);
    //ret = fread(temp, sizeof(int), 50, fp);
    //for(i=0;i<50;i++){
    //    printf("%x\n", temp[i]);
    //}
    fclose(fp);
    return 0;
}
