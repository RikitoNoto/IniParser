#include "config_common.h"

int main(int argc, char* argv[])
{
    printf("====delete indent test====\n");
    deleteIndentTest();

    printf("====search string test====\n");
    searchStringFromLineTest();
}

static void deleteIndentTest()
{
    char* corrects[] = {"3", "4", "5", "0", NULL};
    char* lines[] = {"   3__", "    4_", "     5", "0_____"};
    config_string_size_t sizes[] = {6, 6, 6, 6};
    int i=0;
    for(;;)
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
    deleteIndent(line, size, &delete_size);
    if(delete_size == correct_delete_size) return 1;
    return 0;
}

static void searchStringFromLineTest()
{
    ConfigStringInfo* lines[5] = {createStringInfo("test] ", 7), createStringInfo("test test\n", 11), createStringInfo("test; test", 11), createStringInfo("test\0test", 10), NULL};
    ConfigStringInfo* end_chars[5] = {createStringInfo("]", 2), createStringInfo("\r\n\0", 4),
                                    createStringInfo("];", 3), createStringInfo("\0", 2), NULL};
    ConfigStringInfo* corrects[5] = {createStringInfo("test", 5), createStringInfo("test test", 10),
                                    createStringInfo("test", 5), createStringInfo("test", 5), NULL};
    
    int i=0;
    for(;;)
    {
        if(lines[i] == NULL) break;
        config_bool result = _searchStringFromLineTest(lines[i], end_chars[i], corrects[i]);
        printf(COLOR_CYAN);
        printf("test%d\n"COLOR_RESET, i);

        printf(COLOR_CYAN"\t<%s == %s>\n", lines[i]->content, corrects[i]->content);

        printf(result?COLOR_GREEN:COLOR_RED);
        printf("\tresult: %s\n"COLOR_RESET, result?"OK":"NG");
        i++;
    }

}

static config_bool _searchStringFromLineTest(const ConfigStringInfo* line, ConfigStringInfo* end_chars, ConfigStringInfo* correct)
{
    ConfigStringInfo* temp = searchStringFromLine(line, end_chars);
    ConfigStringInfo* info = createStringInfo(temp->content, temp->length);
    printf("%s\\%d\n", info->content, info->length);
    return configStringInfoCmp(info, correct);
}

static config_bool configStringInfoCmp(const ConfigStringInfo* info1, const ConfigStringInfo* info2)
{
    if(strcmp(info1->content, info2->content)) return CONFIG_FALSE;
    if(info1->length!=info2->length) return CONFIG_FALSE;
    return CONFIG_TRUE;
}