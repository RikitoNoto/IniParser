#ifndef _CONFIG_FILE_H
#define _CONFIG_FILE_H

#include "config_common.h"
#include <time.h>
#include <sys/types.h>

#define CONFIG_FILE_TEST 1


struct _ConfigFile
{
    char* file_name;                                /** file name of this ini file */
    config_string_size_t file_name_size;            /** the size of this ini file name */
    // ConfigFileVersion* version;                     /** file version that is written by a structure FileVersion */
    time_t version;
    off_t file_size;                                /** file size that is got by a system call of stat */
    ConfigSection** sections;                       /** the section array in this ini file */
    config_array_count_t sections_size;             /** the size of the sections array */
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
    CONFIG_UNKNOWN,
    CONFIG_EOF
};


void freeConfigFile(ConfigFile* file);
#endif // _CONFIG_FILE_H