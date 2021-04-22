#ifndef __CONFIG_FILE_H
#define __CONFIG_FILE_H

#include "config_file.h"
#include "_config_common.h"
#include "_config_section.h"
#include "_config_option.h"
#include "_config_comment.h"
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>

#define CONFIG_FILE_TEST 1



static char* readALine(FILE* file, config_string_size_t* line_size);
static char* concatBufs(char** bufs, config_array_count_t bufs_size, config_string_size_t* line_size);
static void freeBufs(char** bufs, config_array_count_t bufs_size);
static ConfigFile* getFileStat(ConfigFile* file);
static ConfigFileVersion* timespecCpy(ConfigFileVersion* time);
config_bool is_latest_version(ConfigFile* file);
config_bool configFileVersionCmp(ConfigFile* file1, ConfigFile* file2);
ConfigFile* createConfigFile(const char* file_name, config_string_size_t file_name_size,
                            ConfigFileVersion* version, off_t file_size,
                            ConfigSection** sections, config_array_count_t sections_size);
ConfigFile* createConfigFileFromFileName(const char* file_name, config_string_size_t file_name_size);
ConfigFile* readConfigFile(ConfigFile* file);
ConfigSection* appEndConfigSectionFromLine(ConfigFile* file, char* line, config_string_size_t line_size);
ConfigFile* appEndConfigSection(ConfigFile* file);
enum ConfigLineType getLineType(char* line, config_string_size_t line_size);
enum ConfigLineType judgeLineTypeFromChar(char first_char);

#if CONFIG_FILE_TEST

char* _readALine(FILE* file, config_string_size_t* line_size);
char* _concatBufs(char** bufs, config_array_count_t bufs_size, config_string_size_t* line_size);
ConfigFile* _getFileStat(ConfigFile* file);
ConfigFileVersion* _timespecCpy(ConfigFileVersion* time);

#endif

#endif // __CONFIG_FILE_H