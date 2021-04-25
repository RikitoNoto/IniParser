#ifndef _TEST_CONFIG_FILE_H
#define _TEST_CONFIG_FILE_H

#include "config_test.h"
#include "../src/_config_file.h"

static void readALineTest(char* filename);
static config_bool _readALineTest(FILE* file, char* correct);
static void getFileStatTest(char* filename);
static void readConfigFileTest(char* filename);
static void printConfigFile(ConfigFile* file);

#endif // _TEST_CONFIG_FILE_H