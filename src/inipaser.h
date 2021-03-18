#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>


struct FileVersion;
struct ConfigFile;
struct ConfigSection;
struct ConfigOption;
struct ConfigComment;
typedef unsigned int config_comment_size_t;
typedef unsigned int config_option_size_t;
typedef unsigned int config_title_size_t;
typedef unsigned int config_value_size_t;
typedef unsigned int config_sections_count_t;
typedef unsigned int config_comments_count_t;
typedef unsigned int config_options_count_t;
typedef unsigned int config_no_in_section_t;


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
    struct FileVersion* version;                            /** file version that is written by a structure FileVersion */
    off_t content_size;                             /** file size that is got by a system call of stat */
    struct ConfigSection** sections;                        /** section array in this ini file */
};
/**
 * @struct ConfigFile
 * @brief A ini file structure.
 * @details
 * this struct express a ini file.
 * this structure has multiple ConfigSection structures and one FileVersion structure.
 * sections stored in line order.
*/

struct ConfigSection
{
    char* title;                                    /** section title that is surrounded '[]' */
    config_title_size_t title_size;                 /** title size */
    char* comment;                                  /** comment to title(character after ']') */
    config_comment_size_t comment_size;             /** comment size */
    struct ConfigComment** comments;                        /** comment array in this section */
    config_comments_count_t comments_count;         /** comment array size */
    struct ConfigOption** options;                          /** option array in this section */
    config_options_count_t options_count;           /** option array size */
};
/**
 * @struct ConfigSection
 * @brief A section structure in a ini file.
 * @details
 * This structure express a section.
 * This structure has multiple ConfigOption structures and ConfigComment structures.
 * A order of comments and options is expressed by a "no" member that each structure has.
*/

struct ConfigOption
{
    config_no_in_section_t no;                      /** line no of this option in this section */
    char* title;                                    /** option title */
    config_title_size_t title_size;                 /** title size */
    char* value;                                    /** option value */
    config_value_size_t value_size;                 /** value size */
    char* comment;                                  /** option comment */
    config_comment_size_t comment_size;             /** comment size */
};
/**
 * @struct ConfigOption
 * @brief A option structure in a section.
 * @details
 * This structure express a option in a section.
*/

struct ConfigComment
{
    config_no_in_section_t no;                      /** line no of this comment in this section */
    char* comment;                                  /** comment */
    config_comment_size_t comment_size;             /** comment size */
};
/**
 * @struct ConfigComment
 * @brief A comment structure in a line of a section.
 * @details
 * This structure express a line comment.
*/