#ifndef __CONFIG_OPTION_H
#define __CONFIG_OPTION_H

#define CONFIG_OPTION_TEST 0

#include "config_option.h"
#include "_config_common.h"
#include "_config_comment.h"
#include <stdlib.h>
#include <string.h>

ConfigOption* createConfigOption(config_no_in_section_t no, char* title, config_string_size_t title_size, char* value, config_string_size_t value_size, char* comment, config_string_size_t comment_size);
ConfigOption* createConfigOptionFromLine(config_no_in_section_t no, char* _line, config_string_size_t line_size);
config_bool configOptionCmp(const ConfigOption* config_option1, const ConfigOption* config_option2);
void freeConfigOption(ConfigOption* op);

#if CONFIG_OPTION_STATIC

static char* searchOptionTitleFromLine(char* line, config_string_size_t line_size, config_string_size_t* title_size, char** value_start_point);
static char* searchOptionValueFromLine(char* line, config_string_size_t line_size, config_string_size_t* value_size, char** comment_start_point);

#endif


#ifdef CONFIG_OPTION_TEST
char* _searchOptionTitleFromLine(char* line, config_string_size_t line_size, config_string_size_t* title_size, char** value_start_point);
char* _searchOptionValueFromLine(char* line, config_string_size_t line_size, config_string_size_t* value_size, char** comment_start_point);

#endif

#endif // __CONFIG_OPTION_H