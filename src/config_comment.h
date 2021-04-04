#ifndef _CONFIG_COMMENT_H
#define _CONFIG_COMMENT_H

#include "config_common.h"


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

ConfigComment* createConfigComment(config_no_in_section_t no, char* _comment, config_string_size_t _comment_size);
ConfigComment* createConfigCommentFromLine(config_no_in_section_t no, char* _line, config_string_size_t line_size);
char* searchCommentFromLine(char* line, config_string_size_t line_size, config_string_size_t* comment_size);
config_bool configCommentCmp(const ConfigComment* config_comment1, const ConfigComment* config_comment2);

#endif // _CONFIG_COMMENT_H