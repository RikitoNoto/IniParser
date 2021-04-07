#include "config_comment.h"

/**
 * @brief create config comment structure from comment and no.
 * @param[in] no no of this comment in a section.
 * @param[in] _comment comment text.
 * @param[in] _comment_size comment text size.
 * @return A ConfigComment structure made from arguments.
 * @details
 * create ConfigComment structure from arguments.
 * if could not create structure, return NULL.
*/
ConfigComment* createConfigComment(config_no_in_section_t no, char* _comment, config_string_size_t _comment_size)
{
    if(_comment == NULL) return NULL;

    ConfigComment* comment = (ConfigComment*)mallocConfig(sizeof(ConfigComment));

    comment->no = no;
    comment->comment = initializeString(_comment, _comment_size);
    comment->comment_size = _comment_size;
    return comment;
}

/**
 * @brief create config comment structure from a line.
 * @param[in] no no of this comment in a section.
 * @param[in] line A line of a option in a ini file.
 * @param[in] line_size the line size.
 * @return A ConfigComment structure made from a line.
 * @details
 * create ConfigComment structure from a line.
*/
ConfigComment* createConfigCommentFromLine(config_no_in_section_t no, char* _line, config_string_size_t line_size)
{
    char* comment;
    config_string_size_t comment_size = 0;
    char* line = mallocConfig(sizeof(char)*line_size);
    strncpy(line, _line, line_size);

    comment = searchCommentFromLine(line, line_size, &comment_size);
    return createConfigComment(no, comment, comment_size);
}

/**
 * @brief serch a comment from a line.
 * @param[in] line a line in a ini file for serch.
 * @param[in] line_size the size of the line.
 * @param[out] comment_size the size of returned comment.
 * @return a start point of comment in a line.
 * @details
 * search comment in a line.
 * if start to ';' in a line, assume a comment after ';'.
*/
char* searchCommentFromLine(char* line, config_string_size_t line_size, config_string_size_t* comment_size)
{
    char* comment;
    
    //if start ';' in a line, shift the start line.
    config_string_size_t delete_size = 0;
    char* _line = deleteIndent(line, line_size, &delete_size);
    if(*_line == ';') line = _line + 1;

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
 * @brief compare ConfigComment structures.
 * @param[in] config_comment structure for compare.
 * @return bool.
 * @details
 * compare two ConfigComment structures and return the result as boolean.
*/
config_bool configCommentCmp(const ConfigComment* config_comment1, const ConfigComment* config_comment2)
{
    // if(!(config_comment1->no == config_comment2->no)) return CONFIG_FALSE;
    if(strcmp(config_comment1->comment, config_comment2->comment)) return CONFIG_FALSE;

    return CONFIG_TRUE;
}

/**
 * @brief free memory of ConfigComment structure.
 * @param[in] comment ConfigComment structure.
 * @details
 * free memory of ConfigComment structure and its members.
*/
void freeConfigComment(ConfigComment* comment)
{
    free(comment->comment);
    free(comment);
}