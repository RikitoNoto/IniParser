#include "config_common.h"

int main(int argc, char* argv[])
{


    char* delete_indent_corrects[] = {"3", "4", "5", "0", NULL};
    char* delete_indent_lines[] = {"   3__", "    4_", "     5", "0_____"};
    config_string_size_t sizes[] = {6, 6, 6, 6};
    deleteIndentTest(delete_indent_corrects, delete_indent_lines, sizes);
}

static void deleteIndentTest(char** corrects, char** lines, config_string_size_t* sizes)
{
    int i=0;
    while(TEST_TRUE)
    {
        if(corrects[i] == NULL) break;
        int result = _deleteIndentTest(corrects[i], lines[i], sizes[i]);
        printf(COLOR_CYAN);
        printf("test%d\n"COLOR_RESET, i);

        printf(result?COLOR_GREEN:COLOR_RED);
        printf("\tresult: %s\n"COLOR_RESET, result?"OK":"NG");
        i++;
    }
}

static int _deleteIndentTest(char* correct, char* line, config_string_size_t size)
{
    config_string_size_t correct_delete_size = atoi(correct);
    config_string_size_t delete_size = 0;
    deleteIndent(line, &delete_size, size);
    if(delete_size == correct_delete_size) return 1;
    return 0;
}