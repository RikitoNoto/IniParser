#ifndef _CONFIG_FILE_H
#define _CONFIG_FILE_H

#include "config_common.h"
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>


struct FileVersion
{
    time_t sec;                                     /** time stamp of this file */
    long nsec;                                      /** time stamp of this file(nano sec) */
};
/**
 * @struct FileVersion
 * @brief this struct record file version by file change time.
 * @details
 * this struct is for A ConfigFile structure.
 * When make a ConfigFile this struct is made.
 * Then recorded the last changed time of file by the stat system call.
*/


struct ConfigFile
{
    char* file_name;                                /** file name of this ini file */
    struct FileVersion* version;                    /** file version that is written by a structure FileVersion */
    off_t content_size;                             /** file size that is got by a system call of stat */
    struct ConfigSection** sections;                /** section array in this ini file */
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