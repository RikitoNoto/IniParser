#include "config_file.h"

#define INI_FILE_READ_BUFFER_SIZE 10


ConfigFile* createConfigFile(const char* file_name)
{

}

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

static void freeBufs(char** bufs, config_array_count_t bufs_size)
{
    for(int i = 0; i < bufs_size; i++)
    {
        free(bufs[i]);
    }
    free(bufs);
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
    return timespecCpy(time);
}
#endif