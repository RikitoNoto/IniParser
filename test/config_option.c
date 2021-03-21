#include "config_option.h"

int main(int argc, char* argv[])
{
    //TODO delete
    //for temp test
    char* line = malloc(sizeof("test=abc")/sizeof(char*));
    config_string_size_t value_size;
    char* comment_start_point;
    line = strncpy(line, "test=abc;a", 9);
    printf("%s", searchOptionValueFromLine(line+5, 5, &value_size, &comment_start_point));
    //===============

    searchOptionTitleFromLineTest();
}

static void searchOptionTitleFromLineTest()
{
    char* lines[] = {"test=abc", " test=abc", " test = abc", "\"test test\"=abc", NULL};
    char* corrects[] = {"test", "test", "test", "test test"};
    config_string_size_t sizes[sizeof(lines)/sizeof(lines[0])];
    for(int i = 0; i < sizeof(corrects)/sizeof(corrects[0]); i++)
    {
        int size = 0;
        while(TEST_TRUE)
        {
            size++;
            if(lines[i][size] == '\0') break;
        }
        sizes[i] = size;
    }

    int i=0;
    while(TEST_TRUE)
    {
        if(lines[i] == NULL) break;
        char* dest = (char*)mallocConfig(sizeof(char)*sizes[i]);
        int result = _searchOptionTitleFromLineTest(corrects[i], strncpy(dest, lines[i], sizes[i]));
        printf(COLOR_CYAN);
        printf("test%d\n"COLOR_RESET, i);

        printf(COLOR_CYAN"\t<%s == %s>\n", lines[i],corrects[i]);

        printf(result?COLOR_GREEN:COLOR_RED);
        printf("\tresult: %s\n"COLOR_RESET, result?"OK":"NG");
        i++;
    }
}

static int _searchOptionTitleFromLineTest(char* correct, char* line)
{
    char** value_start_point = mallocConfig(sizeof(char*));
    config_string_size_t title_size=0;
    int line_size = 0;
    int correct_title_size = 0;

    while(TEST_TRUE)
    {
        line_size++;
        if(line[line_size] == '\0') break;
    }
    line_size++;
    while(TEST_TRUE)
    {
        correct_title_size++;
        if(correct[correct_title_size] == '\0') break;
    }
    correct_title_size++;//+1 :null char
    char* title = searchOptionTitleFromLine(line, line_size, &title_size, value_start_point);
    //if strings is same, strcmp return 0.
    return (!strcmp(title, correct) && title_size==correct_title_size);
}


static int _searchOptionValueFromLineTest(char* correct, char* line)
{
    char** value_start_point = mallocConfig(sizeof(char*));
    config_string_size_t title_size=0;
    int line_size = 0;
    int correct_title_size = 0;

    while(TEST_TRUE)
    {
        line_size++;
        if(line[line_size] == '\0') break;
    }
    line_size++;
    while(TEST_TRUE)
    {
        correct_title_size++;
        if(correct[correct_title_size] == '\0') break;
    }
    correct_title_size++;//+1 :null char
    char* title = searchOptionTitleFromLine(line, line_size, &title_size, value_start_point);
    //if strings is same, strcmp return 0.
    return (!strcmp(title, correct) && title_size==correct_title_size);
}