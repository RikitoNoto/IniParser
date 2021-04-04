#include "config_test.h"

config_string_size_t getStringSizeForTest(char* str)
{
    config_string_size_t size = 0;
    while(CONFIG_TEST_TRUE)
    {
        if(str[size] == '\0')
        {
            size++;
            break;
        }
        size++;
    }
    return size;
}