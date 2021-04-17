GCC_LINK = gcc -Wall -g -o
GCC_COMPILE = gcc -Wall -g -c -o $@
DIR_BIN = ../bin/
DIR_SRC = ../src/
TEST_COMMONS = $(DIR_BIN)config_common.o $(DIR_BIN)config_test.o
OP_AND_COMMENT = $(DIR_BIN)config_option.o $(DIR_BIN)config_comment.o


config_common_test: $(DIR_BIN)config_common_test.o $(DIR_BIN)config_common.o
	$(GCC_LINK) $(DIR_BIN)configCommonTest.o $^

config_option_test: $(DIR_BIN)config_option_test.o $(TEST_COMMONS) $(OP_AND_COMMENT)
	$(GCC_LINK) $(DIR_BIN)configOptionTest.o $^

config_comment_test: $(DIR_BIN)config_comment_test.o $(DIR_BIN)config_comment.o $(TEST_COMMONS)
	$(GCC_LINK) $(DIR_BIN)configCommentTest.o $^

config_section_test: $(DIR_BIN)config_section_test.o $(DIR_BIN)config_section.o $(TEST_COMMONS) $(OP_AND_COMMENT)
	$(GCC_LINK) $(DIR_BIN)configSectionTest.o $^

config_file_test: $(DIR_BIN)config_file_test.o $(DIR_BIN)config_file.o $(TEST_COMMONS) $(OP_AND_COMMENT)
	$(GCC_LINK) $(DIR_BIN)configFileTest.o $^

$(DIR_BIN)config_test.o: config_test.h config_test.c
	$(GCC_COMPILE) config_test.c

$(DIR_BIN)config_common_test.o: config_common.h config_common.c
	$(GCC_COMPILE) config_common.c

$(DIR_BIN)config_file_test.o: config_file.h config_file.c
	$(GCC_COMPILE) config_file.c

$(DIR_BIN)config_section_test.o: config_section.c config_section.h
	$(GCC_COMPILE) config_section.c

$(DIR_BIN)config_option_test.o: config_option.h config_option.c
	$(GCC_COMPILE) config_option.c

$(DIR_BIN)config_comment_test.o: config_comment.h config_comment.c
	$(GCC_COMPILE) config_comment.c


$(DIR_BIN)config_common.o: $(DIR_SRC)config_common.c $(DIR_SRC)config_common.h
	$(GCC_COMPILE) $(DIR_SRC)config_common.c

$(DIR_BIN)config_file.o: $(DIR_SRC)config_file.c $(DIR_SRC)config_file.h
	$(GCC_COMPILE) $(DIR_SRC)config_file.c

$(DIR_BIN)config_section.o: $(DIR_SRC)config_section.c $(DIR_SRC)config_section.h
	$(GCC_COMPILE) $(DIR_SRC)config_section.c

$(DIR_BIN)config_option.o: $(DIR_SRC)config_option.c $(DIR_SRC)config_option.h
	$(GCC_COMPILE) $(DIR_SRC)config_option.c

$(DIR_BIN)config_comment.o: $(DIR_SRC)config_comment.c $(DIR_SRC)config_comment.h
	$(GCC_COMPILE) $(DIR_SRC)config_comment.c
