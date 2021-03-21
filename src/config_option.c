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
ConfigOption* createConfigOption(char* title, config_string_size_t title_size, char* value, config_string_size_t value_size, char* comment, config_string_size_t comment_size)
{
    if(title == NULL || value == NULL) return NULL;

    ConfigOption* op = (ConfigOption*)mallocConfig(sizeof(ConfigOption));
    if(op == NULL) return NULL;

    op->title = initializeString(title, title_size);
    op->value = initializeString(value, value_size);
    op->comment = initializeString(comment, comment_size);

    return op;
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
    
    line = deleteIndent(line, &delete_size, line_size);
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
    for(int i=0; i < line_size; i++)
    {
        if(!is_title_searched)
        {
            if((is_double_quotation && (line[i]=='\"' && line[i]!='\\')) || (!is_double_quotation && line[i]==' '))
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