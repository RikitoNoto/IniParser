#ifndef _TEST_CONFIG_COMMON_H
#define _TEST_CONFIG_COMMON_H

#include "config_test.h"
#include <stdlib.h>
#include <string.h>


static void deleteIndentTest(char** corrects, char** lines, config_string_size_t* sizes);

static int _deleteIndentTest(char* correct, char* line, config_string_size_t size);
static int _mallocConfigTest(size_t size);
static int _reallocConfigTest(void *ptr, size_t size);
static int _raiseConfigErrorTest(char* cause, char* fmt, ...);


#endif // _TEST_CONFIG_COMMON_H