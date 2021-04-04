#include "config_option.h"

int main(int argc, char* argv[])
{
    printf("====Title Test====\n");
    searchOptionTitleFromLineTest();

    printf("====Value Test====\n");
    searchOptionValueFromLineTest();

    printf("====Create Option Test====\n");
    createConfigOptionFromLineTest();
}

static void searchOptionTitleFromLineTest()
{
    char* lines[] = {"test=abc", " test=abc", " test = abc", "\"test test\"=abc", NULL};
    char* corrects[] = {"test", "test", "test", "test test"};
    config_string_size_t sizes[sizeof(lines)/sizeof(lines[0])];
    for(int i = 0; i < sizeof(corrects)/sizeof(corrects[0]); i++)
    {
        int size = 0;
        while(CONFIG_TEST_TRUE)
        {
            size++;
            if(lines[i][size] == '\0') break;
        }
        sizes[i] = size;
    }

    int i=0;
    while(CONFIG_TEST_TRUE)
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

static config_test_bool _searchOptionTitleFromLineTest(char* correct, char* line)
{
    char** value_start_point = mallocConfig(sizeof(char*));
    config_string_size_t title_size=0;
    int line_size = 0;
    int correct_title_size = 0;

    while(CONFIG_TEST_TRUE)
    {
        line_size++;
        if(line[line_size] == '\0') break;
    }
    line_size++;
    while(CONFIG_TEST_TRUE)
    {
        correct_title_size++;
        if(correct[correct_title_size] == '\0') break;
    }
    correct_title_size++;//+1 :null char
    char* title = _searchOptionTitleFromLine(line, line_size, &title_size, value_start_point);
    //if strings is same, strcmp return 0.
    return (config_test_bool)(!strcmp(title, correct) && title_size==correct_title_size);
}

static void searchOptionValueFromLineTest()
{
    char* lines[] = {"abc;comment", " abc  ;comment", "  abc  ", "\"  test  \" ; comment", NULL};
    char* corrects[] = {"abc", "abc", "abc", "  test  "};
    config_string_size_t sizes[sizeof(lines)/sizeof(lines[0])];
    for(int i = 0; i < sizeof(corrects)/sizeof(corrects[0]); i++)
    {
        int size = 0;
        while(CONFIG_TEST_TRUE)
        {
            size++;
            if(lines[i][size] == '\0') break;
        }
        sizes[i] = size;
    }

    int i=0;
    while(CONFIG_TEST_TRUE)
    {
        if(lines[i] == NULL) break;
        printf(COLOR_CYAN);
        printf("test%d\n"COLOR_RESET, i);
        printf(COLOR_CYAN);
        char* dest = (char*)mallocConfig(sizeof(char)*sizes[i]);
        int result = _searchOptionValueFromLineTest(corrects[i], strncpy(dest, lines[i], sizes[i]));
        printf(COLOR_RESET);

        printf(COLOR_CYAN"\t<%s == %s>\n", lines[i],corrects[i]);

        printf(result?COLOR_GREEN:COLOR_RED);
        printf("\tresult: %s\n"COLOR_RESET, result?"OK":"NG");
        i++;
    }
}

static config_test_bool _searchOptionValueFromLineTest(char* correct, char* line)
{
    char* comment_start_point = NULL;
    config_string_size_t value_size=0;
    int line_size = 0;
    int correct_value_size = 0;

    while(CONFIG_TEST_TRUE)
    {
        line_size++;
        if(line[line_size] == '\0') break;
    }
    line_size++;
    while(CONFIG_TEST_TRUE)
    {
        correct_value_size++;
        if(correct[correct_value_size] == '\0') break;
    }
    correct_value_size++;//+1 :null char
    char* value = _searchOptionValueFromLine(line, line_size, &value_size, &comment_start_point);
    printf("\tvalue:\"%s\"\n", value);
    printf("\tvalue_size:%d\n", value_size);
    //if strings is same, strcmp return 0.
    return (config_test_bool)(!strcmp(value, correct) && value_size==correct_value_size);
}

static void createConfigOptionFromLineTest()
{
    ConfigOption* corrects[4] = {
        createConfigOption(0, "title", sizeof("title"), "value", sizeof("value"), "comment", sizeof("comment")),
        createConfigOption(0, " title ", sizeof(" title "), " value ", sizeof(" value "), " comment ", sizeof(" comment ")),
        createConfigOption(0, "title", sizeof("title"), "value", sizeof("value"), NULL, 0),
        NULL
    };

    char* lines[4] = {
        "title=value;comment",
        "\" title \"  =  \" value \"   ; comment ",
        "  title  =  value  ",
        NULL
    };

    int i = 0;

    while(CONFIG_TEST_TRUE)
    {

        if(lines[i] == NULL) break;
        printf(COLOR_CYAN);
        printf("test%d\n"COLOR_RESET, i);
        printf(COLOR_CYAN);

        printf(COLOR_RESET);

        config_bool result = _createConfigOptionFromLineTest(lines[i], corrects[i]);
        printf(result?COLOR_GREEN:COLOR_RED);
        printf("\tresult: %s\n"COLOR_RESET, result?"OK":"NG");
        i++;
    }
}

static config_test_bool _createConfigOptionFromLineTest(char* line, ConfigOption* correct)
{
    ConfigOption* op = createConfigOptionFromLine(0, line, getStringSizeForTest(line));
    printConfigOption(op, "\t"COLOR_CYAN, COLOR_RESET);
    return configOptionCmp(op, correct, CONFIG_TEST_TRUE);
}

static config_string_size_t getStringSizeForTest(char* str)
{
    config_string_size_t size = 0;
    while(CONFIG_TEST_TRUE)
    {
        if(str[size] == '\0')
        {
            size++;
            break;
        }
        size++;
    }
    return size;
}

static void printConfigOption(ConfigOption* op, char* prefix, char* suffix)
{
    printf("%stitle: %s%s\n", prefix, op->title, suffix);
    printf("%svalue: %s%s\n", prefix, op->value, suffix);
    printf("%scomment: %s%s\n", prefix, op->comment, suffix);
}