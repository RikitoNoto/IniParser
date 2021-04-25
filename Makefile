GCC_COMPILE = gcc -Wall -c -o $@

all: libiniparser.a

libiniparser.a: bin/main.o bin/file.o bin/section.o bin/option.o bin/comment.o bin/common.o
	ar rcs $@ $^

clean:
	rm bin/*

bin/main.o: src/config_main.c
	$(GCC_COMPILE) $^

bin/common.o: src/config_common.c
	$(GCC_COMPILE) $^

bin/file.o: src/config_file.c
	$(GCC_COMPILE) $^

bin/section.o: src/config_section.c
	$(GCC_COMPILE) $^

bin/option.o: src/config_option.c
	$(GCC_COMPILE) $^

bin/comment.o: src/config_comment.c
	$(GCC_COMPILE) $^