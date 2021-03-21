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
                (line[i]=='\"' && line[i]!='\\')) || (!is_double_quotation && line[i]==' '))
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
 * @param[in] value_start_point the start point of value in the line.
 * @param[out] value_size the size of value returned.
 * @return a start point of value in a line.
 * @details
 * search option value start point.
 * if value_start_point is not NULL, serach from value_start_point.
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

    for(*value_size = 0; *value_size < line_size; (*value_size)++)
    {
        //if did not discover option value end point
        //and discover end point that is space or tab or double quotation.
        if( !is_value_searched &&
            ((is_double_quotation && line[*value_size]=="\"" && line[*value_size]!="\\")
            ||
            (!is_double_quotation && (line[*value_size] ==' '|| line[*value_size] == '\t'))))
        {
            if(is_double_quotation) is_double_quotation = CONFIG_FALSE;
            line[*value_size] = '\0';
            (*value_size)++;
            is_value_searched = CONFIG_TRUE;
        }
        //if discover ';', return a comment start point.
        else if(!is_double_quotation && (line[*value_size] ==';'))
        {
            //if did not discover option value end point.
            if(!is_value_searched)
            {
                line[*value_size] = '\0';
                (*value_size)++;
            }
            *comment_start_point = line[*value_size];
            break;
        }
        //if discover a new line character or null character.
        else if(!is_double_quotation && (line[*value_size] == '\n' || line[*value_size] == '\r' || line[*value_size] == '\0'))
        {
            line[*value_size] = '\0';
            (*value_size)++;
            *comment_start_point = NULL;
            break;
        }

        if(*value_size == line_size-1) raiseConfigError(NULL, "invalid context option.\n%s\n", line);
    }
    return value;
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