#ifndef _CONFIG_OPTION_H
#define _CONFIG_OPTION_H

#define CONFIG_OPTION_TEST 0

#include "config_common.h"
#include "config_comment.h"

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

#endif // _CONFIG_OPTION_H