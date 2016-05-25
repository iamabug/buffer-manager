#ifndef FILE_H
#define FILE_H

#include "common.h"

extern FILE* dbf;
extern FILE* trf;

FILE* open_file(char* filename);
int close_file(FILE* fp);

int read_page(int page_id, Frame *frm);
int write_page(int page_id, Frame *frm);

int seek(int page_id);

int inc_page_num();
int get_page_num();

int set_use(int page_id, int use_bit);
int get_use(int page_id);

#endif
