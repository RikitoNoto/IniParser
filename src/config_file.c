#include "_config_file.h"

#define INI_FILE_READ_BUFFER_SIZE 1024
const char* DEFAULT_SECTION_NAME = "DEFAULT";


/**
 * @brief create the ConfigFile structure from the arguments.
 * @param[in] file_name the file name of the ini file.
 * @param[in] file_name_size the size of the file name.
 * @param[in] version the last time of changed this file.
 * @param[in] file_size the size of this file.
 * @param[in] sections the sections this file has.
 * @param[in] sections_size the size of the sections.
 * @return the ConfigFile structure created from the arguments.
 * @details
 * create the ConfigFile structure from the arguments.
*/
ConfigFile* createConfigFile(const char* file_name, config_string_size_t file_name_size,
                            ConfigFileVersion* version, off_t file_size,
                            ConfigSection** sections, config_array_count_t sections_size)
{
    ConfigFile* file = (ConfigFile*)mallocConfig(sizeof(ConfigFile));
    file->file_name = initializeString(file_name, file_name_size);
    file->file_name_size = file_name_size;
    file->version = version;
    file->file_size = file_size;
    file->sections = sections;
    file->sections_size = sections_size;

    return file;
}

/**
 * @brief create the ConfigFile structure from a file name.
 * @param[in] file_name the file name of the ini file.
 * @param[in] file_name_size the size of the file name.
 * @return the ConfigFile structure created from a file name.
 * @details
 * create the ConfigFile structure from a file name.
 * the created ConfigFile structure has no sections.
*/
ConfigFile* createConfigFileFromFileName(const char* file_name, config_string_size_t file_name_size)
{
    ConfigFile* file = createConfigFile(file_name, file_name_size, NULL, 0, NULL, 0);
    return getFileStat(file);
}

/**
 * @brief read config file from the structure.
 * @param[in] file the config file structure for read and update the sections.
 * @return the received ConfigFile structure.
 * @details
 * read config file from the name of ConfigFile structure.
 * this function write over the received structure's sections.
*/
ConfigFile* readConfigFile(ConfigFile* file)
{
    if(file->sections != NULL) freeConfigSection(file->sections);
    file->sections = (ConfigSection**)mallocConfig(sizeof(ConfigSection**));
    file->sections_size = 0;
    ConfigSection* current_section = createConfigSection(DEFAULT_SECTION_NAME, sizeof(DEFAULT_SECTION_NAME)+1, NULL, 0, NULL, 0, NULL, 0);

    file->sections[file->sections_size++] = current_section;
    FILE* fd = fopen(file->file_name, "r");
    config_bool is_eof = CONFIG_FALSE;

    for(;!is_eof;)
    {
        config_string_size_t  line_size = 0;
        char* line = readALine(fd, &line_size);
        switch(getLineType(line, line_size))
        {
            case CONFIG_SECTION_TITLE:
                current_section = appEndConfigSectionFromLine(file, line, line_size);
                break;

            case CONFIG_OPTION:
                appEndOptionFromLine(current_section, line, line_size);
                break;

            case CONFIG_COMMENT:
                appEndCommentFromLine(current_section, line, line_size);
                break;
            
            case CONFIG_EOF:
                is_eof = CONFIG_TRUE;
                break;

            case CONFIG_UNKNOWN:
                raiseConfigError(__func__, "unknown error.");
                break;
        }
    }

    return file;
}

/**
 * @brief app end a ConfigSection structure from a line.
 * @param[in] file the config file structure.
 * @param[in] line the line for add the config section.
 * @param[in] line_size the size of the line.
 * @return the created ConfigSection structure.
 * @details
 * create the ConfigSection structure from the line and add to the sections of the ConfigFile structure.
*/
ConfigSection* appEndConfigSectionFromLine(ConfigFile* file, char* line, config_string_size_t line_size)
{
    ConfigSection* section = createConfigSectionFromLine(line, line_size);
    appEndConfigSection(file)->sections[file->sections_size-1] = section;
    return section;
}

/**
 * @brief add a section space to the ConfigFile structure.
 * @param[in] file the config file structure.
 * @return the received ConfigFile structure.
 * @details
 * re allocate memory of the sections of the ConfigFile structure.
 * change the size of the sections to plus one.
*/
ConfigFile* appEndConfigSection(ConfigFile* file)
{
    file->sections_size++;
    reallocConfig(file->sections, file->sections_size);
    return file;
}

/**
 * @brief free config file structure.
 * @param[in] file the config file structure.
 * @return void.
 * @details
 * free the memory of the ConfigFile structure.
*/
void freeConfigFile(ConfigFile* file)
{
    for(int i = 0; i < file->sections_size; i++)
    {
        freeConfigSection(file->sections[i]);
    }
    free(file->file_name);
    //free(file->version);
    free(file);
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

/**
 * @brief get the type of the line.
 * @param[in] line the line to get the type.
 * @param[in] line_size the size of the line.
 * @return the type of the line.
 * @details
 * get the type of the line.
 * the types are kind of the line(e.g. section title, option, comment)
*/
enum ConfigLineType getLineType(char* line, config_string_size_t line_size)
{
    if(line == NULL) return CONFIG_EOF;
    config_string_size_t delete_size = 0;
    return judgeLineTypeFromChar(deleteIndent(line, line_size, &delete_size)[0]);
}

/**
 * @brief judge the line type from the first char of it.
 * @param[in] first_char a first character of the line.
 * @return the type of the line.
 * @details
 * judge the type of the line from the first char of it.
*/
enum ConfigLineType judgeLineTypeFromChar(char first_char)
{
    switch(first_char)
    {
        case '\r':
        case '\n':
        case ';':
            return CONFIG_COMMENT;

        case '[':
            return CONFIG_SECTION_TITLE;
            
        case ' ':
        case '\t':
            return CONFIG_UNKNOWN;

        default:
            return CONFIG_OPTION;

    }
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
    ConfigFile* latest_file = createConfigFile(file->file_name, file->file_name_size, NULL, 0, NULL, 0);
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