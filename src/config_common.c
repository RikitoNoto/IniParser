#include "config_common.h"

/**
 * @brief search string based on the given characters from a line.
 * @param[in] line a line info.
 * @param[in] end_chars end characters. this structure's content is received as char array, but not string.
 * @return the string infomation searched.
 * @details
 * search string based on the given characters from a line.
 * if could not find the given characters, return Null.
*/
config_string_size_t searchStringFromLine(const char* line, config_string_size_t line_size, char* end_chars, config_array_count_t end_chars_count)
{
    config_bool find_char = CONFIG_FALSE;
    for(int i = 0; i < line_size; i++)
    {
        for(int j=0; j < end_chars_count; j++)
        {
            if(line[i] == end_chars[j])
            {
                find_char = CONFIG_TRUE;
                break;
            }
        }

        if(find_char)
        {
            return i + 1;
            break;
        }
        if(i == line_size-1) return 0;
    }
    return 0;
}

/**
* @brief delete indents and spaces from first in a line.
* @param[in] line a line for delete indents and spaces.
* @param[out] delete_size count of deleted characters.
* @param[in] size size of a line.
* @return start point of a line that deleted indents and spaces.
* @details
* delete indents and spaces from first in a line until other characters.
*/
char* deleteIndent(const char* line, config_string_size_t size, config_string_size_t* delete_size)
{
    for(*delete_size = 0; *delete_size < size; (*delete_size)++)
    {
        if(line[*delete_size] != ' '&& line[*delete_size] != '\t') break;
    }

    if(*delete_size == size-1) return NULL;
    return line + *delete_size;
}

/**
 * @brief allocate memory.
 * @param[in] size memory size to allocate in bytes.
 * @return a pointer of memory allocated.
 * @details
 * allocate memory in size of argument.
 * if allocation failed then raise error and exit program.
*/
void* mallocConfig(size_t size)
{
    void* ptr = malloc(size);
    if(ptr == NULL) raiseConfigError(NULL, "Memory allocation failed.");
    return ptr;
}

/**
 * @brief allocate memory again.
 * @param[in] ptr a memory pointer for reallocate.
 * @param[in] size memory size to allocate in bytes.
 * @return a pointer of memory allocated.
 * @details
 * reallocate memory in size of argument.
 * if allocation failed then raise error and exit program.
*/
void* reallocConfig(void* ptr, size_t size)
{
    void* reptr = realloc(ptr, size);
    if(reptr == NULL) raiseConfigError(NULL, "Memory allocation failed.");
    return reptr;
}

/**
 * @brief initialize memory for string.
 * @param[in] srcstr source string.
 * @param[in] size source string size.
 * @details
 * initialize memory for string.
 * first allocate memory for string.
 * next set \0 to memory.
 * after copy srcstr to memory allocated.
 * this function add null character to the end of string.
*/
char* initializeString(const char* srcstr, config_string_size_t size)
{
    if(size <= 0) return NULL;
    char* str = (char*)mallocConfig(sizeof(char)*size);
    strncpy(str, srcstr, size);
    str[size-1] = '\0';

    return str;
}

/**
 * @brief raise error and exit program.
 * @param[in] cause A cause of the error.
 * @param[in] fmt A string describing the error.
 * @details
 * Raise error and exit program.
 * Then display the error message from errno and a message of argument to the stderr.
*/
void raiseConfigError(char* cause, char* fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    if(errno) perror(cause);
    vfprintf(stderr, fmt, ap);

    va_end(ap);
    exit(1);
}