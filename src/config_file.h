#ifndef _CONFIG_FILE_H
#define _CONFIG_FILE_H

#include "config_common.h"
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>

struct _ConfigFile
{
    char* file_name;                                /** file name of this ini file */
    timespec* version;                              /** file version that is written by a structure FileVersion */
    off_t content_size;                             /** file size that is got by a system call of stat */
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


#endif // _CONFIG_FILE_H