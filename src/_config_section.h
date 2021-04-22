#ifndef __CONFIG_SECTION_H
#define __CONFIG_SECTION_H

#include "config_section.h"
#include "_config_common.h"
#include "_config_option.h"
#include "_config_comment.h"


ConfigSection* createConfigSection(const char* title, config_string_size_t title_size, const char* comment, config_string_size_t comment_size, ConfigOption** options, config_array_count_t options_count, ConfigComment** comments, config_array_count_t comments_count);
ConfigSection* createConfigSectionFromLine(const char* line, config_string_size_t line_size);
config_array_count_t getSectionChildrenCount(ConfigSection* section);
char* searchSectionTitle(const char* line, config_string_size_t line_size, config_string_size_t* title_size);
ConfigSection* addConfigSectionCommentCount(ConfigSection* section, config_array_count_t add_count);
ConfigSection* addConfigSectionOptionCount(ConfigSection* section, config_array_count_t add_count);
ConfigSection* appEndComment(ConfigSection* section, char* comment, config_string_size_t comment_size);
ConfigSection* appEndCommentFromLine(ConfigSection* section, char* line, config_string_size_t line_size);
ConfigSection* appEndOption(ConfigSection* section, char* op, config_string_size_t option_size);
ConfigSection* appEndOptionFromLine(ConfigSection* section, char* line, config_string_size_t line_size);
config_bool configSectionCmp(ConfigSection* section1, ConfigSection* section2);
config_bool configSectionCmpDeep(ConfigSection* section1, ConfigSection* section2);
void freeConfigSection(ConfigSection* section);
#endif // __CONFIG_SECTION_H