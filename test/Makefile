config_common_test: ../bin/config_common.o ../bin/config_common_test.o
	gcc -Wall -g -o ../bin/configCommonTest.o ../bin/config_common_test.o ../bin/config_common.o

../bin/config_common.o: ../src/config_common.c
	gcc -Wall -g -c -o ../bin/config_common.o ../src/config_common.c

../bin/config_common_test.o: config_common.c
	gcc -Wall -g -c -o ../bin/config_common_test.o config_common.c

config_option_test: ../src/config_option.c config_option.c ../bin/config_common.o
	gcc -Wall -g -o ../bin/config_option_test.o config_option.c ../bin/config_common.o