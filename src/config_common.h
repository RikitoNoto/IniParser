#ifndef _CONFIG_COMMON_H
#define _CONFIG_COMMON_H
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

typedef unsigned char config_bool;
#define CONFIG_TRUE (char)1
#define CONFIG_FALSE (char)0

typedef struct _ConfigFile ConfigFile;
typedef struct _ConfigSection ConfigSection;
typedef struct _ConfigOption ConfigOption;
typedef struct _ConfigComment ConfigComment;
typedef unsigned int config_string_size_t;
typedef unsigned int config_array_count_t;
typedef unsigned int config_no_in_section_t;

typedef struct _ConfigStringInfo
{
    char* content;
    config_string_size_t length;
} ConfigStringInfo;

ConfigStringInfo* createStringInfo(const char* content, config_string_size_t length);
ConfigStringInfo* searchStringFromLine(const ConfigStringInfo* line, const ConfigStringInfo* end_chars);
char* deleteIndent(char* line, config_string_size_t size, config_string_size_t* delete_size);
ConfigStringInfo* deleteIndentFromStringInfo(const ConfigStringInfo* line);
void* mallocConfig(size_t size);
void* reallocConfig(void *ptr, size_t size);
char* initializeString(const char* srcstr, config_string_size_t size);
void raiseConfigError(char* cause, char* fmt, ...);

#endif // _CONFIG_COMMON_H