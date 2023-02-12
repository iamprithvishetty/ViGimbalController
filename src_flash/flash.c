#include "stdint.h"
#include "hal.h"
#include "data_access.h"
#include "flash.h"
#include <stdlib.h>

extern void print(const char *fmt, ...);

/*
 * Writes at_command data onto flash starting from start_page to end_page
 */
void write_data_flash(uint8_t start_page, uint8_t end_page){

    // Return if page is valid and if end page is greater than start page
    if(start_page < 0 || start_page > 127 || end_page < 0 || end_page >127 || end_page<start_page){
        print("Invalid Page No\n");
        return;
    }

    // Return if at_command data has occupies more space than allocated
    if((end_page - start_page + 1)*1024 < 4*length_user_conf_data){
        print("Less space\n");
        return;
    }
    
    // Erase the pages
    for(uint8_t start = start_page; start <= end_page; start++){

        efl_lld_start_erase(&EFLD1, 0x400*start_page);

    }

    // Dynamic memory allocated for at_command data split into 4 1byte data
    uint8_t *data_user = (uint8_t *)malloc(sizeof(uint8_t)*4*length_user_conf_data);

    // To convert float to byte in order to store
    union {
        float value;
        unsigned char byte_value[4];
    } float_byte;

    // Store 4byte data into 4 1byte data for int and float sequentially
    for(int params = 0; params<length_user_conf_data; params++){

        if(user_conf_data[params].type == INTEGER) {

            data_user[params*4 + 0] = (uint8_t)(*user_conf_data[params].data_int >> 0);
            data_user[params*4 + 1] = (uint8_t)(*user_conf_data[params].data_int >> 8);
            data_user[params*4 + 2] = (uint8_t)(*user_conf_data[params].data_int >> 16);
            data_user[params*4 + 3] = (uint8_t)(*user_conf_data[params].data_int >> 24);

            #if USE_DEBUG
                print("%d\n",*user_conf_data[params].data_int);
            #endif
        
        }
        else{
            
            float_byte.value = *user_conf_data[params].data_float;

            data_user[params*4 + 0] = float_byte.byte_value[0];
            data_user[params*4 + 1] = float_byte.byte_value[1];
            data_user[params*4 + 2] = float_byte.byte_value[2];
            data_user[params*4 + 3] = float_byte.byte_value[3];

            #if USE_DEBUG
                print("%f\n",*user_conf_data[params].data_float);
            #endif

        }

    }

    // Perform Unlock Sequence
    efl_lld_start(&EFLD1);
    // Write the data onto flash memory
    efl_lld_program(&EFLD1, 0x400*start_page, 4*length_user_conf_data, data_user);
    // Perform Lock
    efl_lld_stop(&EFLD1);

    // Free the dynamically allocated data 
    free(data_user);

}

/*
 * Reads data from flash and stores in at_command
 */
void read_data_flash(uint8_t start_page){

    // Return if page is invalid
    if(start_page < 0 || start_page > 127){
        print("Invalid Page No\n");
        return;
    }

    // Dynamic memory allocated for at_command data split into 4 1byte data
    uint8_t *data_user = (uint8_t *)malloc(sizeof(uint8_t)*4*length_user_conf_data);

    // Read the data from flash memory
    efl_lld_read(&EFLD1, 0x400*start_page, 4*length_user_conf_data, data_user);

    // To convert float to byte in order to store
    union {
        float value;
        unsigned char byte_value[4];
    } float_byte;

    // Merge 4 1byte data to 1 4byte data and store in at_command
    for(int params = 0; params<length_user_conf_data; params++){

        if(user_conf_data[params].type == INTEGER) {

            *user_conf_data[params].data_int = ((uint32_t)data_user[params*4 + 0]) | ((uint32_t)data_user[params*4 + 1]<<8) | ((uint32_t)data_user[params*4 + 2]<<16) | ((uint32_t)data_user[params*4 + 3]<<24);
            
            #if USE_DEBUG
                print("%d\n",((uint32_t)data_user[params*4 + 0]) | ((uint32_t)data_user[params*4 + 1]<<8) | ((uint32_t)data_user[params*4 + 2]<<16) | ((uint32_t)data_user[params*4 + 3]<<24));
            #endif

        }
        else{
            
            float_byte.byte_value[0] = data_user[params*4 + 0];
            float_byte.byte_value[1] = data_user[params*4 + 1];
            float_byte.byte_value[2] = data_user[params*4 + 2];
            float_byte.byte_value[3] = data_user[params*4 + 3];

            *user_conf_data[params].data_float = float_byte.value;

            #if USE_DEBUG
                print("%f\n", float_byte.value);
            #endif
        }

    }

    // Free the dynamically allocated memory
    free(data_user);

}