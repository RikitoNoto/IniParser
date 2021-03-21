#ifndef _TEST_CONFIG_OPTION_H
#define _TEST_CONFIG_OPTION_H

#include "config_test.h"
#include "../src/config_option.c"
#include <string.h>

static void searchOptionTitleFromLineTest(char** corrects, char** lines, config_string_size_t* sizes);
static int _searchOptionTitleFromLineTest(char* correct, char* line);

#endif // _TEST_CONFIG_OPTION_H