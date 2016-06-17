#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>

#define FRAME_SIZE  4096
#define PAGE_SIZE   FRAME_SIZE
#define BUF_SIZE    1024
#define PAGE_NUM    50000          //Formated as: (page_id, offset)
#define ITEM_SIZE   8
#define DIR_SIZE    PAGE_NUM * ITEM_SIZE
#define DBF_NAME    "data.dbf"
#define TRF_NAME    "trace.txt"

struct frame {
    char field[FRAME_SIZE];
};

struct node {
    int frame_id;
    struct node *next;
};
#endif
