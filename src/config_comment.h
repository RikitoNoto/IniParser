#ifndef _CONFIG_COMMENT_H
#define _CONFIG_COMMENT_H

#include "config_common.h"


#define CONFIG_COMMENT_CHARACTERS ";"

/**
 * @struct ConfigComment
 * @brief A comment structure in a line of a section.
 * @details
 * This structure express a line comment.
*/
struct _ConfigComment
{
    config_no_in_section_t no;                      /** line no of this comment in this section */
    char* comment;                                  /** comment */
    config_string_size_t comment_size;             /** comment size */
};

#endif // _CONFIG_COMMENT_H