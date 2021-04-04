#ifndef _TEST_CONFIG_OPTION_H
#define _TEST_CONFIG_OPTION_H

#include "config_test.h"
#include "../src/config_option.h"
#include <string.h>


static void createConfigOptionFromLineTest();
static config_test_bool _createConfigOptionFromLineTest(char* line, ConfigOption* correct);
static void searchOptionTitleFromLineTest();
static config_bool _searchOptionTitleFromLineTest(char* correct, char* line);
static void searchOptionValueFromLineTest();
static config_bool _searchOptionValueFromLineTest(char* correct, char* line);
static config_string_size_t getStringSizeForTest(char* str);
static void printConfigOption(ConfigOption* op, char* prefix, char* suffix);

#endif // _TEST_CONFIG_OPTION_H