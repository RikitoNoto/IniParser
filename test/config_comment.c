#include "config_comment.h"

int main(int argc, char* argv[])
{
    createConfigCommentFromLineTest();
}

static void createConfigCommentFromLineTest()
{
    
    ConfigOption* corrects[4] = {
        createConfigComment(0, "comment", sizeof("comment")),
        createConfigComment(0, " comment", sizeof(" comment")),
        createConfigComment(0, "comment;comment", sizeof("comment;comment")),
        NULL
    };

    char* lines[4] = {
        "comment",
        "; comment",
        "comment;comment",
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

        config_bool result = _createConfigCommentFromLineTest(lines[i], corrects[i]);
        printf(result?COLOR_GREEN:COLOR_RED);
        printf("\tresult: %s\n"COLOR_RESET, result?"OK":"NG");
        i++;
    }
}

static config_bool _createConfigCommentFromLineTest(char* line, ConfigComment* correct)
{
    ConfigComment* comment = createConfigCommentFromLine(0, line, getStringSizeForTest(line));
    return configCommentCmp(comment, correct);
}