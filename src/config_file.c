#include "config_file.h"

ConfigFile* createConfigFile(const char* file_name)
{

}

static char* readALine(FILE* file, config_string_size_t* line_size)
{
    
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