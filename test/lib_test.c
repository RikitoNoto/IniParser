// #include "config_test.h"
// #include "../src/_config_file.h"
#include "../src/iniparser.h"
#include <stdio.h>

static void printConfigFile(ConfigFile* file)
{
    for(int i = 0; i < file->sections_size; i++)
    {
        ConfigSection* section = file->sections[i];
        printf("<%s>\n", section->title);

        for(int j = 0; j < section->options_count; j++)
        {
            printf("\t%s: %s\n", section->options[j]->title, section->options[j]->value);
        }
    }
}

int main(int argc, char* argv[])
{
    ConfigFile* file = readIniFile(argv[1]);
    printf("called: %s", file->file_name);
    printConfigFile(file);
}