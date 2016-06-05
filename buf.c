#include "buf.h"

struct *frame buffer[BUF_SIZE];
struct BCB ptof[BUF_SIZE];
int ftop[BUF_SIZE];

/*
 * @hash page_id into frame_id
 */
int hash(int page_id);

/*
 * @get the frame_id of this page regardless of whether it is in buffer
 * @increase the count
 * @return frame_id
 */
int fix_page(int page_id);

/*
 * TODO
 * @do not know what it is for
 */
int fix_new_page();

/*
 * @reduce the fix count of the page
 */
int unfix_page(int page_id);

/*
 * @calculate the number of free frames in the buffer
 * @return 0 ~ BUF_SIZE-1
 */
int free_frame_num();

/*
 * @decide which frame to be replaced
 * @return the frame_id
 */
int select_victim();

/*
 * @called when select_victim needs to replace a frame
 * @delete the BCB of the page
 */
int remove_BCB(BCB *bcb, int page_id);

/*
 * TODO
 */
void remove_lru_element(int frame_id);

/*
 * @set the dirty bit as 1 for the frame
 */
void set_dirty(int frame_id);

/*
 * @set the dirty bit as 0 for the frame
 */
void unset_dirty(int frame_id);

/*
 * @write all pages in the buffer that has been modified
 * @called when the system is shutdown
 */
void write_dirty();

/*
 * @print the content of the frame
 */
void print_frame(int frame_id);


