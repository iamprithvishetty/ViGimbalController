#ifndef DATA_ACCESS_H_
#define DATA_ACCESS_H_

#include "user_data.h"

// data accessor structure
typedef struct{
    
    char message[32];
    
    enum {
        INTEGER,
        FLOATING,
    }type;
    union {
        float *data_float;
        int *data_int;
    };
    union {
        float data_float_min;
        int data_int_min;
    };
    union {
        float data_float_max;
        int data_int_max;
    };

}data_access;

extern data_access user_conf_data[];
extern const int length_user_conf_data;

#endif