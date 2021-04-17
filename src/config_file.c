#include "config_file.h"

#define INI_FILE_READ_BUFFER_SIZE 1024


ConfigFile* createConfigFile(const char* file_name)
{

}

static char* readALine(FILE* file, config_string_size_t* line_size)
{
    char** bufs = mallocConfig(sizeof(char*));
    config_array_count_t bufs_size = 0;

    for(int i = 0;; i++)
    {
        char buf[INI_FILE_READ_BUFFER_SIZE];
        memset(buf, '\0', sizeof(buf));

        bufs_size++;
        bufs = (char**)reallocConfig(bufs, bufs_size);

        if(fgets(buf, sizeof(buf), file) == NULL) return NULL;//if read eof, return NULL.
        bufs[bufs_size-1] = buf;

        char last_char_of_buf = buf[INI_FILE_READ_BUFFER_SIZE - 2];
        if(last_char_of_buf == '\r' || last_char_of_buf == '\n' || last_char_of_buf == '\0') break;
        
    }
    return concatBufs(bufs, bufs_size, line_size);
}

static char* concatBufs(char** bufs, config_array_count_t bufs_size, config_string_size_t* line_size)
{
    char* line = (char*)mallocConfig(sizeof(char) * INI_FILE_READ_BUFFER_SIZE * bufs_size);
    *line_size = 0;

    for(int i = 0; i < bufs_size; i++)
    {
        for(int j = 0; j < INI_FILE_READ_BUFFER_SIZE; j++)
        {
            if(bufs[i][j] == '\0') break;
            line[(*line_size)++] = bufs[i][j];
        }
    }
    line[(*line)++] = '\0';
    return reallocConfig(line, line_size);
}

static ConfigFile* getFileStat(ConfigFile* file)
{
    struct stat buf;

    if(stat(file->file_name, &buf) < 0) raiseConfigError(file->file_name, "could not get status.");
    
    file->file_size = buf.st_size;
    file->version = timespecCpy(&(buf.st_ctime));
    
    return file;
}

static ConfigFileVersion* timespecCpy(ConfigFileVersion* time)
{
    ConfigFileVersion* time_spec_cpy = (ConfigFileVersion*)mallocConfig(sizeof(ConfigFileVersion));
    time_spec_cpy->tv_sec = time->tv_sec;
    time_spec_cpy->tv_nsec = time->tv_nsec;
    return time_spec_cpy;
}

enum ConfigLineType getLineType(char* line, config_string_size_t line_size)
{

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

ConfigFileVersion* _timespecCpy(ConfigFileVersion* time)
{
    return time_spec_cpy(time);
}
#endif