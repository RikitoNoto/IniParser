#ifndef _CONFIG_COMMON_H
#define _CONFIG_COMMON_H
typedef struct _ConfigFile ConfigFile;
typedef struct _ConfigSection ConfigSection;
typedef struct _ConfigOption ConfigOption;
typedef struct _ConfigComment ConfigComment;
typedef unsigned int config_string_size_t;
typedef unsigned int config_array_count_t;
typedef unsigned int config_no_in_section_t;
typedef struct timespec ConfigFileVersion;

#endif // _CONFIG_COMMON_H