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
ConfigSection* createConfigSectionFromLine(const char* line, config_string_size_t line_size)
{
    char* title;
    config_string_size_t title_size = 0;
    char* comment = NULL;
    config_string_size_t comment_size = 0;
    ConfigOption** options = (ConfigOption**)mallocConfig(sizeof(ConfigOption*));
    ConfigComment** comments = (ConfigComment**)mallocConfig(sizeof(ConfigComment*));


    title = searchSectionTitle(line, line_size, &title_size);

    config_string_size_t remain_size = title_size+title-line;
    char* _comment = searchConfigCommentFromLine(title+title_size, remain_size);

    if(_comment)
    {
        comment = searchCommentFromLine(_comment, remain_size, &comment_size);
    }

    return createConfigSection(title, title_size, comment, comment_size, options, 0, comments, 0);
}

config_array_count_t getSectionChildrenCount(ConfigSection* section)
{
    return section->comments_count + section->options_count;
}

/**
 * @brief search title from a line.
 * @param[in] line A line of a section.
 * @param[in] line_size the line size.
 * @param[out] title_size the return title size.
 * @return A title of this section.
 * @details
 * search the section title from a title line.
 * this function return the position of title from a received line,
 * but it do not allocate memory for the searched title.
*/
char* searchSectionTitle(const char* line, config_string_size_t line_size, config_string_size_t* title_size)
{
    int delete_size = 0;
    char* title = deleteIndent(line, line_size, &delete_size) + 1;//the return value of deleteIndent is '[', so a next character is used as the title.
    line_size -= delete_size;

    *title_size = searchStringFromLine(title, line_size, "]", 1);
    return title;
}

/**
 * @brief change the comments array size of the config section structure.
 * @param[in] section A section structure for change the comments array size.
 * @param[in] add_count the add count.
 * @return A section structure.
 * @details
 * re allocate the comments array of config section structure.
*/
ConfigSection* addConfigSectionCommentCount(ConfigSection* section, config_array_count_t add_count)
{
    section->comments_count += add_count;
    section->comments = (ConfigComment**)reallocConfig(section->comments, sizeof(ConfigComment*) * section->comments_count);
    return section;
}

/**
 * @brief change the options array size of the config section structure.
 * @param[in] section A section structure for change the options array size.
 * @param[in] add_count the add count.
 * @return A section structure.
 * @details
 * re allocate the options array of config section structure.
*/
ConfigSection* addConfigSectionOptionCount(ConfigSection* section, config_array_count_t add_count)
{
    section->options_count += add_count;
    section->options = (ConfigOption**)reallocConfig(section->options, sizeof(ConfigOption*) * section->options_count);
    return section;
}

/**
 * @brief add the comment structure in the section structure.
 * @param[in] section A section structure for add the comment.
 * @param[in] comment the add comment.
 * @param[in] comment_size the add comment size.
 * @return A section structure.
 * @details
 * add the comment structure to the end in the section structure.
*/
ConfigSection* appEndComment(ConfigSection* section, char* comment, config_string_size_t comment_size)
{
    addConfigSectionCommentCount(section, 1)->comments[section->comments_count - 1] = createConfigComment(getSectionChildrenCount(section)-1, comment, comment_size);
    return section;
}

/**
 * @brief add the comment structure in the section structure from a line.
 * @param[in] section A section structure for add the comment.
 * @param[in] line a line where the comment is written.
 * @param[in] line_size the line size.
 * @return A section structure.
 * @details
 * add the comment structure to the end in the section structure from a line.
*/
ConfigSection* appEndCommentFromLine(ConfigSection* section, char* line, config_string_size_t line_size)
{
    addConfigSectionCommentCount(section, 1)->comments[section->comments_count - 1] = createConfigCommentFromLine(getSectionChildrenCount(section), line, line_size);
    return section;
}

/**
 * @brief add the option structure in the section structure.
 * @param[in] section A section structure for add the option.
 * @param[in] option the add option.
 * @param[in] option_size the add option size.
 * @return A section structure.
 * @details
 * add the option structure to the end in the section structure.
*/
ConfigSection* appEndOption(ConfigSection* section, char* op, config_string_size_t option_size)
{
    addConfigSectionOptionCount(section, 1)->comments[section->options_count - 1] = createConfigComment(getSectionChildrenCount(section)-1, op, option_size);
    return section;
}

/**
 * @brief add the option structure in the section structure from a line.
 * @param[in] section A section structure for add the option.
 * @param[in] line a line where the option is written.
 * @param[in] line_size the line size.
 * @return A section structure.
 * @details
 * add the option structure to the end in the section structure from a line.
*/
ConfigSection* appEndOptionFromLine(ConfigSection* section, char* line, config_string_size_t line_size)
{
    addConfigSectionOptionCount(section, 1)->options[section->options_count - 1] = createConfigOptionFromLine(getSectionChildrenCount(section), line, line_size);
    return section;
}