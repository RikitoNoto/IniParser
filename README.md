# **What's Ini Paser ?**
Ini Paser is an API for oparate an ini file.

## **Features of Ini Paser**
This library is made by C language, so very fast.

## **Install**
### **How to Install**

Execute make command.
```
make -f <this directory>/MakeFile
```

## **How to Use**

### **Example: Read**

The read function return "ConfigFile" structure.\
It has the array of the "ConfigSection" structure.\
you can read the options and comments from that structure.

* example.c
```C
#include <stdio.h>
#include "inipaser.h"

int main(int argc, char* argv[])
{
    ConfigFile* ini_file = readIniFile(<filename>);//read ini file.
    ConfigSection** sections = ini_file->sections;//the sections in the ini file.
    for(int i = 0; i < ini_file->sections_count; i++)
    {
        section = sections[i];//the section.
        printf("<%s>\n", section->title);//display the section title.
        for(int j = 0; j < section->options_count; j++)
        {
            printf("\t%s: %s\n", section->options[j]->title, section->options[j]->value);//display the option title and the option value.
        }
    }
}
```
When this code run display all sections titles and its options titles, values.