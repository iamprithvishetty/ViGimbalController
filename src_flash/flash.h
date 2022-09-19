#ifndef FLASH_H_
#define FLASH_H_

#define PAGE_START 127
#define PAGE_END   127

void write_data_flash(uint8_t start_page, uint8_t end_page);
void read_data_flash(uint8_t start_page);

#endif