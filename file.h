#ifndef FILE_H
#define FILE_H

#include "common.h"
extern FILE *dbf;
extern FILE *trf;

FILE* open_file(char *filename);
int close_file(FILE *fp);

int read_page(FILE *fp, int page_id, struct frame *frm);
int write_page(FILE *fp, int page_id, struct frame *frm);

int seek(FILE* fp, int page_id);

void inc_page_num();
int get_page_num();

int set_use(int page_id, int use_bit);
int get_use(int page_id);

#endif
