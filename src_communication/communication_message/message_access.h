#ifndef MESSAGE_ACCESS_H_
#define MESSAGE_ACCESS_H_

#include "stdint.h"

// data accessor structure
typedef struct{
    
    char start[2];
    char command_seperator;
    char return_seperator;
    char set_seperator;

}message_decoder;

void process(char *incoming_data, uint8_t len_data, message_decoder *decoder);
void return_data(char *parameter);
void set_data(char *parameter, float value);

#endif