#include <stdio.h>

int main(){
    int temp [50], i;
    FILE *fp = fopen("../data.dbf", "rb");
    if(!fp)
        printf("file open error!\n");
    int ret = fseek(fp, 0, SEEK_SET);
    if(ret)
        perror("fseek");
    ret = fread(temp, sizeof(int), 50, fp);
    if(ret)
        perror("fread");
    for(i=0;i<50;i++){
        printf("%x\n", temp[i]);
    }
    fclose(fp);
    return 0;
}
