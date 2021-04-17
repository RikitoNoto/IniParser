#include "config_file.h"

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        printf("Usage: %s <filename>", argv[0]);
        exit(1);
    }
    readALineTest(argv[1]);
}

static void readALineTest(char* filename)
{
    FILE* file = fopen(filename, "r");
    char* corrects[4] = {"test", "0123456789ABCDEF", "\\0\\0\\0\\0\\0\\0\\0\\0\\0\\0\\0\\0\\0\\0", NULL};
    int i = 0;
    for(;;)
    {
        if(corrects[i] == NULL) break;
        printf(COLOR_CYAN);
        printf("test%d\n"COLOR_RESET, i);
        printf(COLOR_CYAN);

        printf(COLOR_RESET);

        config_bool result = _readALineTest(file, corrects[i]);
        printf(result?COLOR_GREEN:COLOR_RED);
        printf("\tresult: %s\n"COLOR_RESET, result?"OK":"NG");
        i++;
    }

}

static config_bool _readALineTest(FILE* file, char* correct)
{
    config_string_size_t line_size = 0;
    char* line = _readALine(file, &line_size);
    if(getStringSizeForTest(correct) != line_size) return CONFIG_FALSE;
    return !strcmp(line, correct);
}