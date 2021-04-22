#ifndef _INIPASER_H
#define _INIPASER_H

#include "config_common.h"
#include "config_file.h"
#include "config_section.h"
#include "config_option.h"
#include "config_comment.h"

ConfigFile* readIniFile(char* filename);
#endif // _INIPASER_H