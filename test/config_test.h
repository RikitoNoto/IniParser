#ifndef _TEST_CONFIG_TEST_H
#define _TEST_CONFIG_TEST_H

#include "../src/config_common.h"
#define CONFIG_TEST_TRUE 1
#define CONFIG_TEST_FALSE 0
typedef unsigned char config_test_bool;

#define COLOR_RESET "\033[0m"
#define COLOR_GREEN "\033[32m"
#define COLOR_RED "\033[31m"
#define COLOR_CYAN "\033[36m"

config_string_size_t getStringSizeForTest(char* str);

#endif // _TEST_CONFIG_TEST_H