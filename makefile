#目标对象:依赖对象
#	编译命令
#
#
test:test.o
	gcc test.o -o test

test.o:test.c
	gcc -c test.c -o test.o

#coretest:coretest.c
#	gcc coretest.c -o coretest
