#include "message_access.h"
#include "message_access.h"

#include "data_access.h"
#include "math_utils.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

extern void print(const char *fmt, ...);

/*
 * process the incoming user message
 */
void process(char *message, uint8_t len_message, message_decoder *decoder){


    if(len_message>=3){
        // check if the message start is in the right format
        if(message[0] == decoder->start[0] && message[1] == decoder->start[1] && message[2] == decoder->set_seperator){
            
            // message check to skip the first three characters
            uint8_t message_check = 3;
            // to check if user wants the data
            bool is_return = false;
            // to check if user wants to set the data
            bool is_set = false;

            // check if message has return or set seperator
            while( message_check < len_message){
                
                if(message[message_check] == decoder->return_seperator){
                    is_return = true;
                    break;
                }
                else if(message[message_check] == decoder->set_seperator){
                    is_set = true;
                    break;
                }
                // To keep a check of where '?' or '=' was found
                message_check++;

            }

            // if user wants the data
            if(is_return == true){
                
                // length of the parameter
                uint8_t len_of_command = (message_check-3)+1;
                // create dynamic array for parameter
                char *parameter = (char *)malloc(sizeof(char)*len_of_command);
                // save the parameter from the message
                for(uint8_t count=0; count<(len_of_command-1); count++){
                    parameter[count] = message[count+3];
                }
                // last value set to null
                parameter[len_of_command-1] = '\0';
                // processing the parameter
                return_data(parameter);
                // free the dynamically allocated memory
                free(parameter);

            }

            else if(is_set == true){
                
                // length of the parameter
                uint8_t len_of_command = (message_check-3)+1;
                // create dynamic array for parameter
                char *parameter = (char *)malloc(sizeof(char)*len_of_command);
                // save the parameter from the message
                for(uint8_t count=0; count<(len_of_command-1); count++){
                    parameter[count] = message[count+3];
                }
                // last value set to null   
                parameter[len_of_command-1] = '\0';

                // length of the value
                uint8_t len_of_value = (len_message-1) - message_check + 1;
                // create dynamic array based on length
                char *value = (char *)malloc(sizeof(char)*(len_of_value));
                // keeping a check if value is valid at every step
                bool valid_value = false;
                // processing and saving the value here
                float param_value = 0;
                // to keep a check where number was found
                int mul_count = 0;
                // to keep a check if value is negative
                int negative = 1;
                // to keep a check where '.' was found
                int div_count = 0;
                // logic for getting the value
                for(uint8_t count = 0; count < len_of_value-1; count++){
                    
                    // keep a check if the value is negative or not
                    if(count==len_of_value-2 && message[message_check+((len_of_value-2)-count)+1]=='-'){
                        negative = -1;
                    }
                    // check if the message[message_check+((len_of_value-2)-count)+1] value lies between ASCII value [48,57] both inclusive 
                    else if((message[message_check+((len_of_value-2)-count)+1]>='0' && message[message_check+count+1]<='9'))
                    {
                        param_value +=  (message[message_check+((len_of_value-2)-count)+1]-48)*pow(10,(mul_count));
                        mul_count++;
                        valid_value = true;
                    }
                    // check if the message[message_check+((len_of_value-2)-count)+1] is equal to ASCII value 46 i.e '.' for dividing param_value
                    else if(message[message_check+((len_of_value-2)-count)+1] == '.'){
                        div_count = mul_count;
                        valid_value = true;
                    }
                    // invalid value received
                    else{
                        print("invalid value\n");
                        valid_value = false;
                        break;
                    }
                }
                
                // if valid value then calculate the final param_value to be set
                if(valid_value){
                    // calculate the final param_value
                    param_value = negative*(param_value/pow(10,div_count));

                    // process and set the value if valid parameter
                    set_data(parameter,param_value);
                }

                // free dynamically allocated array value and parameter
                free(value);
                free(parameter);

            }

            else{
                print("invalid cmd\n");
            }

        }
        else{
            print("invalid cmd\n");
        }
    }

    else{

        if(len_message == 2){
            if(message[0] == decoder->start[0] && message[1] == decoder->start[1]){
                print("ok\n");
            }
        }
        else {
            print("invalid cmd\n");
        }

    }

}

/*
 * process the parameter and return value if the parameter exists
 */
void return_data(char *parameter){

    // checking all the commands
    for(int params = 0; params<(int)(sizeof(user_conf_data)/sizeof(user_conf_data[0])); params++) {

        // if parameter is matched
        if(!strcmp(parameter, user_conf_data[params].message)) {
            
            // If data is in INTEGER
            if(user_conf_data[params].type == INTEGER){
                print("%d\n",*user_conf_data[params].data_int);
                return;
            }
            // If data is in FLOAT
            else{
                print("%f\n",*user_conf_data[params].data_float);
                return;
            }
        }
    }
    print("invalid cmd\n");

}

void set_data(char *parameter, float value){

    // checking all the commands
    for(int params = 0; params<(int)(sizeof(user_conf_data)/sizeof(user_conf_data[0])); params++) {
        
        // if parameter is matched
        if(!strcmp(parameter, user_conf_data[params].message)) {

            // if data is INTEGER and min and max are not qual to 0
            if(user_conf_data[params].type == INTEGER && !(user_conf_data[params].data_int_min == 0 && user_conf_data[params].data_int_max == 0)){

                // set the new value and also constrain 
                *user_conf_data[params].data_int = constrain((int)value,user_conf_data[params].data_int_min,user_conf_data[params].data_int_max);
                print("ok value set to %d\n",*user_conf_data[params].data_int);
                return;

            }
            // if data is FLOATING and min and max are not qual to 0
            else if(!(user_conf_data[params].data_float_min == 0 && user_conf_data[params].data_float_max == 0)){

                // set the new value and also constrain 
                *user_conf_data[params].data_float = constrain(value,user_conf_data[params].data_float_min,user_conf_data[params].data_float_max);
                print("ok value set to %f\n",*user_conf_data[params].data_float);
                return;
                
            }
            // if min and max both are 0
            else{
                print("cmd data can only be read\n");
                return;
            }
        }
    }

    print("invalid cmd\n");
}