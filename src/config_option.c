#define CONFIG_OPTION_STATIC 1
#include "config_option.h"


/**
 * @brief create config option structure from title and value.
 * @param[in] title A title of this option.
 * @param[in] title_size title array size.
 * @param[in] value A value of this option.
 * @param[in] value_size value array size.
 * @param[in] comment A comment of this option.
 * @param[in] comment_size comment array size
 * @return A ConfigOption structure made from arguments.
 * @details
 * create ConfigOption structure from arguments.
 * if could not create structure, return NULL.
*/
ConfigOption* createConfigOption(config_no_in_section_t no, char* title, config_string_size_t title_size, char* value, config_string_size_t value_size, char* comment, config_string_size_t comment_size)
{
    if(title == NULL || value == NULL) return NULL;

    ConfigOption* op = (ConfigOption*)mallocConfig(sizeof(ConfigOption));
    if(op == NULL) return NULL;

    op->no = no;
    op->title = initializeString(title, title_size);
    op->value = initializeString(value, value_size);
    op->comment = initializeString(comment, comment_size);

    return op;
}

/**
 * @brief create config option structure from a line.
 * @param[in] line A line of a option in a ini file.
 * @param[in] line_size the line size.
 * @return A ConfigOption structure made from a line.
 * @details
 * create ConfigOption structure from a line.
*/
ConfigOption* createConfigOptionFromLine(config_no_in_section_t no, char* _line, config_string_size_t line_size)
{
    char* title;
    char* value;
    char* comment;

    config_string_size_t title_size=0;
    config_string_size_t value_size = 0;
    config_string_size_t comment_size = 0;

    char* value_start_point = NULL;
    char* comment_start_point = NULL;

    char* line = mallocConfig(sizeof(char)*line_size);
    strncpy(line, _line, line_size);

    title = searchOptionTitleFromLine(line, line_size, &title_size, &value_start_point);
    line_size -= value_start_point - line;

    value = searchOptionValueFromLine(value_start_point, line_size, &value_size, &comment_start_point);
    if(comment_start_point != NULL)
    {
        line_size -= comment_start_point - value_start_point;
        comment = searchOptionCommentFromLine(comment_start_point, line_size, &comment_size);
    }

    return createConfigOption(no, title, title_size, value, value_size, comment, comment_size);
}

/**
 * @brief compare ConfigOption structures.
 * @param[in] config_option structure for compare.
 * @param[in] comment_check if true, compare also the comment of ConfigOption structures.
 * @return bool.
 * @details
 * compare two ConfigOption structures and return the result as boolean.
*/
config_bool configOptionCmp(const ConfigOption* config_option1, const ConfigOption* config_option2, config_bool comment_check)
{
    if(!(config_option1->no == config_option2->no)) return CONFIG_FALSE;
    if(strcmp(config_option1->title, config_option2->title)) return CONFIG_FALSE;
    if(strcmp(config_option1->value, config_option2->value)) return CONFIG_FALSE;

    if(comment_check)
    {
        if(strcmp(config_option1->comment, config_option2->comment)) return CONFIG_FALSE;
    }

    return CONFIG_TRUE;
}

/**
 * @brief serch option title and value start point from a line.
 * @param[in] line a line in a ini file for serch.
 * @param[in] line_size the size of the line.
 * @param[out] title_size the size of title returned.
 * @param[out] value_start_point a start point of value.
 * @return a start point of title in a line.
 * @details
 * search option title start point and value start point.
 * if there is no a equal, raise error and exit program.
*/
static char* searchOptionTitleFromLine(char* line, config_string_size_t line_size, config_string_size_t* title_size, char** value_start_point)
{
    config_bool is_double_quotation = CONFIG_FALSE;
    config_bool is_title_searched = CONFIG_FALSE;
    config_string_size_t delete_size;
    char* title;

    *value_start_point = NULL;
    
    line = deleteIndent(line, line_size, &delete_size);
    line_size -= delete_size;

    if(*line == '\"')
    {
        is_double_quotation = CONFIG_TRUE;
        line++;
        line_size--;
    }

    title = line;

    // serach equal and title end.
    // if there is a double quotation, the title end is a double quotation.
    // else title end is a space or a equal.
    // a next character of a equal is a value start point.
    for(config_string_size_t i=0; i < line_size; i++)
    {
        if(!is_title_searched)
        {
            if((is_double_quotation
                &&
                (line[i]=='\"' && line[i-1]!='\\')) || (!is_double_quotation && line[i]==' '))
            {
                if(is_double_quotation) is_double_quotation = CONFIG_FALSE;

                line[i] = '\0';
                *title_size = i+1;
                is_title_searched = CONFIG_TRUE;
            }
        }

        // when current character is a equal, exit loop.
        if((!is_double_quotation && line[i]=='=') && i<=line_size-1)
        {
            if(!is_title_searched)
            {
                line[i] = '\0';
                *title_size = i+1;
            }
            *value_start_point = line + i + 1;
            break;
        }
        if(i==line_size-1) raiseConfigError(NULL, "invalid context option.\n%s\n", line);
    }
    return title;
}

/**
 * @brief serch option value from a line.
 * @param[in] line a line in a ini file for serch.
 * @param[in] line_size the size of the line.
 * @param[out] value_size the size of value returned.
 * @param[out] comment_start_point a start point of comment.
 * @return a start point of value in a line.
 * @details
 * search option value start point.
*/
static char* searchOptionValueFromLine(char* line, config_string_size_t line_size, config_string_size_t* value_size, char** comment_start_point)
{
    config_bool is_double_quotation = CONFIG_FALSE;
    config_bool is_value_searched = CONFIG_FALSE;
    config_string_size_t delete_size;
    char* value;

    line = deleteIndent(line, line_size, &delete_size);
    line_size -= delete_size;
    value = line;
    if(line[0] == '\"')//there is double quote.
    {
        line++;
        line_size--;
        value = line;
        is_double_quotation = CONFIG_TRUE;
    }

    for(int i = 0; i < line_size; i++)
    {
        //if did not discover option value end point
        //and discover end point that is space or tab or double quotation.
        if( !is_value_searched &&
            ((is_double_quotation && line[i]=='\"' && line[i-1]!='\\')
            ||
            (!is_double_quotation && (line[i] ==' '|| line[i] == '\t'))))
        {
            if(is_double_quotation) is_double_quotation = CONFIG_FALSE;
            line[i] = '\0';
            *value_size = i + 1;
            is_value_searched = CONFIG_TRUE;
        }
        //if discover ';', return a comment start point.
        else if(!is_double_quotation && (line[i] ==';'))
        {
            //if did not discover option value end point.
            if(!is_value_searched)
            {
                line[i] = '\0';
                *value_size = i + 1;
            }
            *comment_start_point = line+i+1;
            break;
        }
        //if discover a new line character or null character.
        else if(!is_double_quotation && (line[i] == '\n' || line[i] == '\r' || line[i] == '\0'))
        {
            if(!is_value_searched)
            {
                line[i] = '\0';
                *value_size = i + 1;
            }
            *comment_start_point = NULL;
            break;
        }

        if(i == line_size-1) raiseConfigError(NULL, "invalid context option.\n%s\n", line);
    }
    return value;
}

/**
 * @brief serch option comment from a line.
 * @param[in] line a line in a ini file for serch.
 * @param[in] line_size the size of the line.
 * @param[out] comment_size the size of comment returned.
 * @return a start point of comment in a line.
 * @details
 * search option comment start point.
*/
static char* searchOptionCommentFromLine(char* line, config_string_size_t line_size, config_string_size_t* comment_size)
{
    char* comment;

    comment = line;

    for(int i = 0; i < line_size; i++)
    {
        if(line[i] == '\n' || line[i] == '\r' || line[i] == '\0')
        {
            line[i] = '\0';
            *comment_size = i + 1;
            break;
        }
    }

    return comment;
}

/**
 * @brief free memory of ConfigOption structure.
 * @param[in] op ConfigOption structure.
 * @details
 * free memory of ConfigOption structure and its members.
*/
void freeConfigOption(ConfigOption* op)
{
    free(op->title);
    free(op->value);
    free(op->comment);
    free(op);
}

#ifdef CONFIG_OPTION_TEST
char* _searchOptionTitleFromLine(char* line, config_string_size_t line_size, config_string_size_t* title_size, char** value_start_point)
{
    return searchOptionTitleFromLine(line, line_size, title_size, value_start_point);
}

char* _searchOptionValueFromLine(char* line, config_string_size_t line_size, config_string_size_t* value_size, char** comment_start_point)
{
    return searchOptionValueFromLine(line, line_size, value_size, comment_start_point);
}

#endif