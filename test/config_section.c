#include "config_section.h"

int main(int argc, char* argv[])
{
    printf("====section title test =====\n");
    searchSectionTitleTest();
    printf("====create section from line test====\n");
    createConfigSectionFromLineTest();
    printf("====app end option from line test =====\n");
    appEndOptionFromLineTest();
}

static void searchSectionTitleTest()
{
    char* lines[] = {"[test]", " [test] ", " [ test ] ", "[ test test ]", NULL};
    char* corrects[] = {"test", "test", "test", "test"};
    config_string_size_t sizes[sizeof(lines)/sizeof(lines[0])];
    for(int i = 0; i < sizeof(corrects)/sizeof(corrects[0]); i++)
    {
        sizes[i] = getStringSizeForTest(lines[i]);
    }

    for(int i=0;;i++)
    {
        if(lines[i] == NULL) break;
        char* dest = (char*)mallocConfig(sizeof(char)*sizes[i]);
        int result = _searchSectionTitleTest(corrects[i], strncpy(dest, lines[i], sizes[i]), sizes[i]);
        printf(COLOR_CYAN);
        printf("test%d\n"COLOR_RESET, i);

        printf(COLOR_CYAN"\t<%s == %s>\n", lines[i],corrects[i]);

        printf(result?COLOR_GREEN:COLOR_RED);
        printf("\tresult: %s\n"COLOR_RESET, result?"OK":"NG");
    }
}

config_bool _searchSectionTitleTest(char* correct, char* line, config_string_size_t line_size)
{
    config_string_size_t title_size = 0;
    char* title = NULL;
    char* _title = searchSectionTitle(line, line_size, &title_size);
    title = mallocConfig(sizeof(char) * title_size);
    strncpy(title, _title, title_size);
    title[title_size - 1] = '\0';
    return !strcmp(correct, title);
}

static void createConfigSectionFromLineTest()
{
    
    char* lines[] = {"[test]", " [test] ", " [ test ] ", "[ test test ]", NULL};
    ConfigSection* corrects[] = {
        createConfigSection("test", getStringSizeForTest("test"), NULL, 0, NULL, 0, NULL, 0),
        createConfigSection("test", getStringSizeForTest("test"), NULL, 0, NULL, 0, NULL, 0),
        createConfigSection("test", getStringSizeForTest("test"), NULL, 0, NULL, 0, NULL, 0),
        createConfigSection("test", getStringSizeForTest("test"), NULL, 0, NULL, 0, NULL, 0)};
    config_string_size_t sizes[sizeof(lines)/sizeof(lines[0])];
    for(int i = 0; i < sizeof(corrects)/sizeof(corrects[0]); i++)
    {
        sizes[i] = getStringSizeForTest(lines[i]);
    }

    for(int i=0;;i++)
    {
        if(lines[i] == NULL) break;
        char* dest = (char*)mallocConfig(sizeof(char)*sizes[i]);
        int result = _createConfigSectionFromLineTest(strncpy(dest, lines[i], sizes[i]), sizes[i], corrects[i]);
        printf(COLOR_CYAN);
        printf("test%d\n"COLOR_RESET, i);

        printf(COLOR_CYAN"\t<%s == %s>\n", lines[i],corrects[i]->title);

        printf(result?COLOR_GREEN:COLOR_RED);
        printf("\tresult: %s\n"COLOR_RESET, result?"OK":"NG");
    }
}

static config_bool _createConfigSectionFromLineTest(char* line, config_string_size_t line_size, ConfigSection* correct)
{
    ConfigSection* section = createConfigSectionFromLine(line, line_size);
    return configSectionCmp(section, correct);
}

static void appEndOptionFromLineTest()
{
    char* lines[] = {"test=value", " test = value ", "\"test\"= \"value\"", NULL};

    ConfigOption* options[] = {createConfigOption(0, "test", getStringSizeForTest("test"), "value", getStringSizeForTest("value"), NULL, 0)};
    ConfigSection* correct = createConfigSection("test", getStringSizeForTest("test"), NULL, 0, options, 1, NULL, 0);
    config_string_size_t sizes[sizeof(lines)/sizeof(lines[0])];
    for(int i = 0; i < sizeof(lines)/sizeof(lines[0])-1; i++)
    {
        sizes[i] = getStringSizeForTest(lines[i]);
    }

    for(int i=0;;i++)
    {
        if(lines[i] == NULL) break;
        int result = _appEndOptionFromLineTest(createConfigSectionFromLine("[test]", getStringSizeForTest("[test]")), lines[i], sizes[i], correct);
        printf(COLOR_CYAN);
        printf("test%d\n"COLOR_RESET, i);

        printf(COLOR_CYAN"\t<%s == %s>\n", lines[i],correct->title);

        printf(result?COLOR_GREEN:COLOR_RED);
        printf("\tresult: %s\n"COLOR_RESET, result?"OK":"NG");
    }

}

static config_bool _appEndOptionFromLineTest(ConfigSection* section, char* line, config_string_size_t line_size, ConfigSection* correct)
{
    appEndOptionFromLine(section, line, line_size);
    return configSectionCmpDeep(section, correct);
}