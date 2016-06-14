#ifndef COMMON_H
#define COMMON_H

#define FRAME_SIZE  4096
#define PAGE_SIZE   4096
#define BUF_SIZE    1024
#define PAGE_NUM    500000          //Formated as: (page_id, offset)
#define ITEM_SIZE   8
#define DIR_SIZE    500000 * 8
#define DBF_FILE    "data.dbf"
#define TRF_NAME    "trace.txt"

struct frame {
    char field[FRAME_SIZE];
};



#endif
