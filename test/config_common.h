#ifndef _TEST_CONFIG_COMMON_H
#define _TEST_CONFIG_COMMON_H

#include <stdlib.h>
#include "../src/config_common.h"
#define TEST_TRUE 1
#define TEST_FALSE 0

#define COLOR_RESET "\033[0m"
#define COLOR_GREEN "\033[32m"
#define COLOR_RED "\033[31m"
#define COLOR_CYAN "\033[36m"


static void deleteIndentTest(char** corrects, char** lines, config_string_size_t* sizes);

static int _deleteIndentTest(char* correct, char* line, config_string_size_t size);
static int _mallocConfigTest(size_t size);
static int _reallocConfigTest(void *ptr, size_t size);
static int _raiseConfigErrorTest(char* cause, char* fmt, ...);


#endif // _TEST_CONFIG_COMMON_H