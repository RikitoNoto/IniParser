config_common_test: ../bin/config_common.o ../bin/config_common_test.o
	gcc -Wall -g -o ../bin/configCommonTest.o ../bin/config_common_test.o ../bin/config_common.o

../bin/config_common.o: ../src/config_common.c
	gcc -Wall -g -c -o ../bin/config_common.o ../src/config_common.c

../bin/config_common_test.o: config_common.c
	gcc -Wall -g -c -o ../bin/config_common_test.o config_common.c