#include "iniparser.h"
#include "_config_common.h"
#include "_config_file.h"
#include <string.h>

ConfigFile* readIniFile(const char* filename)
{
    ConfigFile* file = createConfigFileFromFileName(filename, strlen(filename)+1);
    return readConfigFile(file);
}