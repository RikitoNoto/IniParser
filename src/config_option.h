#ifndef _CONFIG_OPTION_H
#define _CONFIG_OPTION_H

#define CONFIG_OPTION_TEST 0

#include "config_common.h"
#include <stdlib.h>
#include <string.h>

/**
 * @struct ConfigOption
 * @brief A option structure in a section.
 * @details
 * This structure express a option in a section.
*/
struct _ConfigOption
{
    config_no_in_section_t no;                      /** line no of this option in this section */
    char* title;                                    /** option title */
    config_string_size_t title_size;                /** title size */
    char* value;                                    /** option value */
    config_string_size_t value_size;                /** value size */
    char* comment;                                  /** option comment */
    config_string_size_t comment_size;              /** comment size */
};

ConfigOption* createConfigOption(config_no_in_section_t no, char* title, config_string_size_t title_size, char* value, config_string_size_t value_size, char* comment, config_string_size_t comment_size);
ConfigOption* createConfigOptionFromLine(config_no_in_section_t no, char* _line, config_string_size_t line_size);
config_bool configOptionCmp(const ConfigOption* config_option1, const ConfigOption* config_option2, config_bool comment_check);
void freeConfigOption(ConfigOption* op);

#if CONFIG_OPTION_STATIC

static char* searchOptionTitleFromLine(char* line, config_string_size_t line_size, config_string_size_t* title_size, char** value_start_point);
static char* searchOptionValueFromLine(char* line, config_string_size_t line_size, config_string_size_t* value_size, char** comment_start_point);
static char* searchOptionCommentFromLine(char* line, config_string_size_t line_size, config_string_size_t* comment_size);

#endif


#ifdef CONFIG_OPTION_TEST
char* _searchOptionTitleFromLine(char* line, config_string_size_t line_size, config_string_size_t* title_size, char** value_start_point);
char* _searchOptionValueFromLine(char* line, config_string_size_t line_size, config_string_size_t* value_size, char** comment_start_point);

#endif

#endif // _CONFIG_OPTION_H