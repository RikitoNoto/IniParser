#include "config_option.h"

ConfigOption* createConfigOption(char* title, config_string_size_t title_size, char* value, config_string_size_t value_size, char* comment, config_string_size_t comment_size)
{
    if(title == NULL || value == NULL) return NULL;

    ConfigOption* op = (ConfigOption*) malloc(sizeof(ConfigOption));
    if(op == NULL) return NULL;

    //string malloc
    strncpy(op->title, title, title_size);
    strncpy(op->value, value, value_size);

    if(comment != NULL)
    {
        strncpy(op->comment, comment, comment_size);
    }
    return op;
}

int freeConfigOption(ConfigOption* op)
{
    free();
}