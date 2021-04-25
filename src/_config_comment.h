#ifndef __CONFIG_COMMENT_H
#define __CONFIG_COMMENT_H

#include "_config_common.h"
#include "config_comment.h"

#define CONFIG_COMMENT_CHARACTERS ";"


ConfigComment* createConfigComment(config_no_in_section_t no, char* _comment, config_string_size_t _comment_size);
ConfigComment* createConfigCommentFromLine(config_no_in_section_t no, char* _line, config_string_size_t line_size);
char* searchCommentFromLine(char* line, config_string_size_t line_size, config_string_size_t* comment_size);
char* searchConfigCommentFromLine(char* line, config_string_size_t line_size);
config_bool configCommentCmp(const ConfigComment* config_comment1, const ConfigComment* config_comment2);
void freeConfigComment(ConfigComment* comment);

#endif // __CONFIG_COMMENT_H