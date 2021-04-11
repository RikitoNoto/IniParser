#ifndef _CONFIG_SECTION_H
#define _CONFIG_SECTION_H

#include "config_common.h"
#include "config_option.h"
#include "config_comment.h"

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
#endif // _CONFIG_SECTION_H