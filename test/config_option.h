#ifndef _TEST_CONFIG_OPTION_H
#define _TEST_CONFIG_OPTION_H

#include "config_test.h"
#include "../src/config_option.c"
#include <string.h>

static void searchOptionTitleFromLineTest();
static int _searchOptionTitleFromLineTest(char* correct, char* line);
static void searchOptionValueFromLineTest();
static int _searchOptionValueFromLineTest(char* correct, char* line);

#endif // _TEST_CONFIG_OPTION_H