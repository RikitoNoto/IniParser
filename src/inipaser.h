#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
//MEMO change unistdio.h -> stdio.h


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

struct ConfigFile
{
    char* file_name;                                /** file name of this ini file */
    FileVersion version;                            /** file version that is written by a structure FileVersion */
    off_t content_size;                             /** file size that is got by a system call of stat */
    ConfigSection* sections;                        /** section array in this ini file */
};

struct ConfigSection
{
    char* title;                                    /** section title that is surrounded '[]' */
    config_title_size_t title_size;                 /** title size */
    char* comment;                                  /** comment to title(character after ']') */
    config_comment_size_t comment_size;             /** comment size */
    ConfigComment* comments;                        /** comment array in this section */
    config_comments_count_t comments_count;         /** comment array size */
    ConfigOption* options;                          /** option array in this section */
    config_options_count_t options_count;           /** option array size */
};

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

struct ConfigComment
{
    config_no_in_section_t no;                      /** line no of this comment in this section */
    char* comment;                                  /** comment */
    config_comment_size_t comment_size;             /** comment size */
};