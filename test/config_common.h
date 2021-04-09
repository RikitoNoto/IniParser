#ifndef _TEST_CONFIG_COMMON_H
#define _TEST_CONFIG_COMMON_H

#include "config_test.h"
#include <stdlib.h>
#include <string.h>


static void deleteIndentTest();

static int _deleteIndentTest(char* correct, char* line, config_string_size_t size);

static void searchStringFromLineTest();
static config_bool _searchStringFromLineTest(const ConfigStringInfo* line, ConfigStringInfo* end_chars, ConfigStringInfo* correct);
static config_bool configStringInfoCmp(const ConfigStringInfo* info1, const ConfigStringInfo* info2);

#endif // _TEST_CONFIG_COMMON_H