GCC_LINK = gcc -Wall -g -o
GCC_COMPILE = gcc -Wall -g -c -o $@
DIR_BIN = ../bin/
DIR_SRC = ../src/


config_common_test: $(DIR_BIN)config_common_test.o $(DIR_BIN)config_common.o
	$(GCC_LINK) $(DIR_BIN)configCommonTest.o $^

config_option_test: config_option_test.o $(DIR_BIN)config_common.o $(DIR_BIN)config_option.o $(DIR_BIN)config_comment.o $(DIR_BIN)config_test.o
	$(GCC_LINK) $(DIR_BIN)configOptionTest.o $^

config_comment_test: config_comment_test.o $(DIR_BIN)config_comment.o $(DIR_BIN)config_common.o $(DIR_BIN)config_test.o
	$(GCC_LINK) $(DIR_BIN)configCommentTest.o $^

$(DIR_BIN)config_common.o: $(DIR_SRC)config_common.c $(DIR_SRC)config_common.h
	$(GCC_COMPILE) $(DIR_SRC)config_common.c

$(DIR_BIN)config_common_test.o: config_common.h config_common.c
	$(GCC_COMPILE) config_common.c

$(DIR_BIN)config_test.o: config_test.h config_test.c
	$(GCC_COMPILE) config_test.c

config_option_test.o: config_option.h config_option.c
	$(GCC_COMPILE) config_option.c

$(DIR_BIN)config_option.o: $(DIR_SRC)config_option.c $(DIR_SRC)config_option.h
	$(GCC_COMPILE) $(DIR_SRC)config_option.c

config_comment_test.o: config_comment.h config_comment.c
	$(GCC_COMPILE) config_comment.c

$(DIR_BIN)config_comment.o: $(DIR_SRC)config_comment.c $(DIR_SRC)config_comment.h
	$(GCC_COMPILE) $(DIR_SRC)config_comment.c