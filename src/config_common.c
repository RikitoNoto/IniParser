#include "config_common.h"

/**
* @brief delete indents and spaces from first in a line.
* @param[in] line a line for delete indents and spaces.
* @param[out] delete_size count of deleted characters.
* @param[in] size size of a line.
* @return start point of a line that deleted indents and spaces.
* @details
* delete indents and spaces from first in a line until other characters.
*/
char* deleteIndent(char* line, config_string_size_t size, config_string_size_t* delete_size)
{
    for(*delete_size = 0; *delete_size < size; (*delete_size)++)
    {
        if(line[*delete_size] != ' '&& line[*delete_size] != '\t') break;
    }

    if(*delete_size == size-1) return NULL;
    return &(line[*delete_size]);
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
*/
char* initializeString(const char* srcstr, config_string_size_t size)
{
    char* str = (char*)mallocConfig(sizeof(char)*size);
    memset(str, '\0', size);
    strncpy(str, srcstr, size);

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

    perror(cause);
    vfprintf(stderr, fmt, ap);

    va_end(ap);
    exit(1);
}