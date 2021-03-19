#ifndef _CONFIG_SECTION_H
#define _CONFIG_SECTION_H

#include "config_common.h"


struct _ConfigSection
{
    char* title;                                    /** section title that is surrounded '[]' */
    config_string_size_t title_size;                /** title size */
    char* comment;                                  /** comment to title(character after ']') */
    config_string_size_t comment_size;              /** comment size */
    ConfigComment** comments;                       /** comment array in this section */
    config_array_count_t comments_count;            /** comment array size */
    ConfigOption** options;                         /** option array in this section */
    config_array_count_t options_count;             /** option array size */
};
/**
 * @struct ConfigSection
 * @brief A section structure in a ini file.
 * @details
 * This structure express a section.
 * This structure has multiple ConfigOption structures and ConfigComment structures.
 * A order of comments and options is expressed by a "no" member that each structure has.
*/

#endif // _CONFIG_SECTION_H