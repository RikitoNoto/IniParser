#include "config_file.h"

#define INI_FILE_READ_BUFFER_SIZE 10


/**
 * @brief create the ConfigFile structure from the arguments.
 * @param[in] file_name the file name of the ini file.
 * @param[in] file_name_size the size of the file name.
 * @param[in] version the last time of changed this file.
 * @param[in] file_size the size of this file.
 * @param[in] sections the sections this file has.
 * @param[in] sections_size the size of the sections.
 * @param[in] comments the comments this file has.
 * @param[in] comments_size the size of the comments.
 * @return the ConfigFile structure from the arguments.
 * @details
 * create the ConfigFile structure from the arguments.
*/
ConfigFile* createConfigFile(const char* file_name, config_string_size_t file_name_size,
                            ConfigFileVersion* version, off_t file_size,
                            ConfigSection** sections, config_array_count_t sections_size,
                            ConfigComment** comments, config_array_count_t comments_size)
{
    ConfigFile* file = (ConfigFile*)mallocConfig(sizeof(ConfigFile));
    file->file_name = initializeString(file_name, file_name_size);
    file->file_name_size = file_name_size;
    file->version = version;
    file->file_size = file_size;
    file->sections = sections;
    file->sections_size = sections_size;
    file->comments = comments;
    file->comments_size = comments_size;

    return file;
}

void freeConfigFile(ConfigFile* file)
{
}

/**
 * @brief read a line from the ini file stream.
 * @param[in] file the file stream to read.
 * @param[out] line_size the size of the line.
 * @return A line read from the ini file stream.
 * @details
 * read a line from the ini file stream and return the line as a string.
 * this function reads for each 'INI_FILE_READ_BUFFER_SIZE'.
 * the value of the line_size is the size of the line size and null char.
 * when a line is "1234", the line_size return 5.
*/
static char* readALine(FILE* file, config_string_size_t* line_size)
{
    char* line = NULL;
    char** bufs = mallocConfig(sizeof(char*));
    config_array_count_t bufs_size = 0;

    for(int i = 0;; i++)
    {
        char* buf = mallocConfig(INI_FILE_READ_BUFFER_SIZE);
        memset(buf, '\0', INI_FILE_READ_BUFFER_SIZE);


        if(fgets(buf, INI_FILE_READ_BUFFER_SIZE, file) == NULL) return NULL;//if read eof, return NULL.
        bufs_size++;
        bufs = (char**)reallocConfig(bufs, sizeof(char*) * bufs_size);
        bufs[bufs_size-1] = buf;

        char last_char_of_buf = buf[INI_FILE_READ_BUFFER_SIZE - 2];
        if(last_char_of_buf == '\r' || last_char_of_buf == '\n' || last_char_of_buf == '\0') break;
        
    }
    line = concatBufs(bufs, bufs_size, line_size);
    freeBufs(bufs, bufs_size);
    return line;
}

/**
 * @brief concat the read buffers from a line.
 * @param[in] bufs the read buffers.
 * @param[in] bufs_size the size of the bufs.
 * @param[out] line_size the size of the line.
 * @return A line made by concat the bufs.
 * @details
 * the readALine function continue reading the size of INI_FILE_READ_BUFFER_SIZE until read '\n' character.
 * the read strings put into bufs in order.
 * this function make a string from the bufs.
*/
static char* concatBufs(char** bufs, config_array_count_t bufs_size, config_string_size_t* line_size)
{
    char* line = (char*)mallocConfig(sizeof(char) * INI_FILE_READ_BUFFER_SIZE * bufs_size);
    *line_size = 0;

    for(int i = 0; i < bufs_size; i++)
    {
        for(int j = 0; j < INI_FILE_READ_BUFFER_SIZE; j++)
        {
            if(bufs[i][j] == '\n'|| bufs[i][j] == '\r'|| bufs[i][j] == '\0') break;
            line[(*line_size)++] = bufs[i][j];
        }
    }
    line[(*line_size)++] = '\0';
    return reallocConfig(line, sizeof(char) * (*line_size));
}

/**
 * @brief free the bufs that used in the readALine function.
 * @param[in] bufs the read buffers.
 * @param[in] bufs_size the size of the bufs.
 * @return
 * @details
 * free the bufs that used in the readALine function.
*/
static void freeBufs(char** bufs, config_array_count_t bufs_size)
{
    for(int i = 0; i < bufs_size; i++)
    {
        free(bufs[i]);
    }
    free(bufs);
}

/**
 * @brief give the status to a ConfigFile structure.
 * @param[in] file A ConfigFile structure to give the status.
 * @return the ConfigFile structure.
 * @details
 * give the status of the last change time and the file size to a ConfigFile structure.
*/
static ConfigFile* getFileStat(ConfigFile* file)
{
    struct stat buf;

    if(stat(file->file_name, &buf) < 0) raiseConfigError(file->file_name, "could not get status.");
    
    file->file_size = buf.st_size;
    file->version = buf.st_ctime; //timespecCpy(&(buf.st_ctime));
    
    return file;
}

// static ConfigFileVersion* timespecCpy(ConfigFileVersion* time)
// {
//     ConfigFileVersion* time_spec_cpy = (ConfigFileVersion*)mallocConfig(sizeof(ConfigFileVersion));
//     time_spec_cpy->tv_sec = time->tv_sec;
//     time_spec_cpy->tv_nsec = time->tv_nsec;
//     return time_spec_cpy;
// }

enum ConfigLineType getLineType(char* line, config_string_size_t line_size)
{

}

/**
 * @brief compare the files version from their last change time and size.
 * @param[in] file the ConfigFile structures to compare.
 * @return if the same version, true otherwise false.
 * @details
 * compare the files version from their last change time and size.
*/
config_bool configFileVersionCmp(ConfigFile* file1, ConfigFile* file2)
{
    if(file1->file_size != file2->file_size) return CONFIG_FALSE;
    // TODO: if kernel version is upper 2.5.48, the st_ctime field in a stat structure change a st_ctim field.
    // else if(file1->version->tv_sec != file2->version->tv_sec) return CONFIG_FALSE;
    // else if(file1->version->tv_nsec != file2->version->tv_nsec) return CONFIG_FALSE;
    else if(file1->version != file2->version) return CONFIG_FALSE;
    return CONFIG_TRUE;
}

/**
 * @brief check the file version is the latest version.
 * @param[in] file the ConfigFile structures to check.
 * @return if the latest version, true otherwise false.
 * @details
 * the ConfigFile structure has the infomation of the version.
 * it is the time of the last changed file and the size of the file.
 * the ConfigFile structure record the version when make itself.
 * this function check its version is the latest version.
*/
config_bool is_latest_version(ConfigFile* file)
{
    ConfigFile* latest_file = createConfigFile(file->file_name, file->file_name_size, NULL, 0, NULL, 0, NULL, 0);
    getFileStat(latest_file);
    config_bool result = configFileVersionCmp(file, latest_file);
    freeConfigFile(latest_file);
    return result;
}

#if CONFIG_FILE_TEST
char* _readALine(FILE* file, config_string_size_t* line_size)
{
    return readALine(file, line_size);
}

char* _concatBufs(char** bufs, config_array_count_t bufs_size, config_string_size_t* line_size)
{
    return concatBufs(bufs, bufs_size, line_size);
}

ConfigFile* _getFileStat(ConfigFile* file)
{
    return getFileStat(file);
}

// TODO: if kernel version is upper 2.5.48, the st_ctime field in a stat structure change a st_ctim field.
// ConfigFileVersion* _timespecCpy(ConfigFileVersion* time)
// {
//     return timespecCpy(time);
// }

#endif