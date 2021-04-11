#ifndef _TEST_CONFIG_SECTION_H
#define _TEST_CONFIG_SECTION_H

#include "config_test.h"
#include "../src/config_section.h"

static void searchSectionTitleTest();
config_bool _searchSectionTitleTest(char* correct, char* line, config_string_size_t line_size);
static void createConfigSectionFromLineTest();
static config_bool _createConfigSectionFromLineTest(char* line, config_string_size_t line_size, ConfigSection* correct);
static void appEndOptionFromLineTest();
static config_bool _appEndOptionFromLineTest(ConfigSection* section, char* line, config_string_size_t line_size, ConfigSection* correct);
#endif // _TEST_CONFIG_SECTION_H