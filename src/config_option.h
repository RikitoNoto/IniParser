#ifndef _CONFIG_OPTION_H
#define _CONFIG_OPTION_H

#include "config_common.h"
#include <stdlib.h>
#include <string.h>

typedef struct _ConfigOption
{
    config_no_in_section_t no;                      /** line no of this option in this section */
    char* title;                                    /** option title */
    config_string_size_t title_size;                /** title size */
    char* value;                                    /** option value */
    config_string_size_t value_size;                /** value size */
    char* comment;                                  /** option comment */
    config_string_size_t comment_size;              /** comment size */
};
/**
 * @struct ConfigOption
 * @brief A option structure in a section.
 * @details
 * This structure express a option in a section.
*/

ConfigOption* createConfigOption(char* title, config_string_size_t title_size, char* value, config_string_size_t value_size, char* comment, config_string_size_t comment_size);
int freeConfigOption(ConfigOption* op);
#endif // _CONFIG_OPTION_H