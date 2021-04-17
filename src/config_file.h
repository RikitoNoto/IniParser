#ifndef _CONFIG_FILE_H
#define _CONFIG_FILE_H

#include "config_common.h"
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>

#define CONFIG_FILE_TEST 1

struct _ConfigFile
{
    char* file_name;                                /** file name of this ini file */
    ConfigFileVersion* version;                       /** file version that is written by a structure FileVersion */
    off_t file_size;                                /** file size that is got by a system call of stat */
    ConfigSection** sections;                       /** section array in this ini file */
    config_array_count_t sections_size;
};
/**
 * @struct ConfigFile
 * @brief A ini file structure.
 * @details
 * this struct express a ini file.
 * this structure has multiple ConfigSection structures and one FileVersion structure.
 * sections stored in line order.
*/

enum ConfigLineType
{
    CONFIG_COMMENT,
    CONFIG_OPTION,
    CONFIG_SECTION_TITLE,
    CONFIG_EOF
};

static char* readALine(FILE* file, config_string_size_t* line_size);
static char* concatBufs(char** bufs, config_array_count_t bufs_size, config_string_size_t* line_size);
static ConfigFile* getFileStat(ConfigFile* file);
static ConfigFileVersion* timespecCpy(ConfigFileVersion* time);

#if CONFIG_FILE_TEST

char* _readALine(FILE* file, config_string_size_t* line_size);
char* _concatBufs(char** bufs, config_array_count_t bufs_size, config_string_size_t* line_size);
ConfigFile* _getFileStat(ConfigFile* file);
ConfigFileVersion* _timespecCpy(ConfigFileVersion* time);

#endif

#endif // _CONFIG_FILE_H