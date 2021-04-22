#ifndef __CONFIG_COMMON_H
#define __CONFIG_COMMON_H
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include "config_common.h"

#define CONFIG_TRUE (char)1
#define CONFIG_FALSE (char)0
typedef unsigned char config_bool;


// typedef struct _ConfigStringInfo
// {
//     char* content;
//     config_string_size_t length;
// } ConfigStringInfo;

// ConfigStringInfo* createStringInfo(const char* content, config_string_size_t length);
// ConfigStringInfo* searchStringFromStringInfo(const ConfigStringInfo* line, ConfigStringInfo* end_chars);
config_string_size_t searchStringFromLine(const char* line, config_string_size_t line_size, char* end_chars, config_array_count_t end_chars_count);
char* deleteIndent(const char* line, config_string_size_t size, config_string_size_t* delete_size);
// ConfigStringInfo* deleteIndentFromStringInfo(const ConfigStringInfo* line);
void* mallocConfig(size_t size);
void* reallocConfig(void *ptr, size_t size);
char* initializeString(const char* srcstr, config_string_size_t size);
void raiseConfigError(char* cause, char* fmt, ...);

#endif // __CONFIG_COMMON_H