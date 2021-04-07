#include "config_section.h"

/**
 * @brief create config section structure from title and options, comments.
 * @param[in] title A title of this section.
 * @param[in] title_size title array size.
 * @param[in] comment A comment of this section.
 * @param[in] comment_size comment array size.
 * @param[in] comments The lines with comment in this section.
 * @param[in] comments_count comments array size.
 * @param[in] options The options in this section.
 * @param[in] options_count options array size.
 * @return A ConfigSection structure made from arguments.
 * @details
 * create ConfigSection structure from arguments.
 * if could not create structure, return NULL.
*/
ConfigSection* createConfigSection(const char* title, config_string_size_t title_size,
                                    const char* comment, config_string_size_t comment_size,
                                    ConfigComment** comments, config_array_count_t comments_count,
                                    ConfigOption** options, config_array_count_t options_count)
{
    if(title == NULL) return NULL;
    ConfigSection* section = (ConfigSection*)mallocConfig(sizeof(ConfigSection));

    section->title = initializeString(title, title_size);
    section->title_size = title_size;

    section->comment = initializeString(comment, comment_size);
    section->comment_size = comment_size;

    section->comments = comments;
    section->comments_count = comments_count;

    section->options = options;
    section->options_count = options_count;
    
    return section;
}

/**
 * @brief create config section structure from a line.
 * @param[in] line A line of a section.
 * @param[in] line_size the line size.
 * @return A ConfigSection structure made from a line.
 * @details
 * create ConfigSection structure from a line.
 * the comments array and the options array in the structure which created by this function are empty.
 * So if it has comments or options, need to add these.
*/
ConfigSection* createConfigSectionFromLine(char* line, config_string_size_t line_size)
{

}

ConfigSection* appEndFromLine(char* line, config_string_size_t line_size)
{

}

ConfigSection* appEndComment()
{

}

ConfigSection* appEndOption()
{

}