#目标对象:依赖对象
#	编译命令
#
BIN=out 

# *代表任意字符
SRC=$(wildcard *.c) # a.c b.c c.c test.c
OBJ=$(patsubst %.c, %.o, $(SRC)) #算a.o b.o c.o test.o(汇编完成后的文件)
CFLAGS=-g

.PHONY:$(BIN) 
$(BIN):$(OBJ) #依赖文件为 a.o b.o c.o test.o
	gcc $^ -o $@
	
%.o:%.c
	gcc $(CFLAGS) -c $< -o $@ #$< 就相当于是a.c

clean:
	rm $(BIN) $(OBJ)
#a.o = %.o --> % = a --> %.c = a.c

#相当于
#a.o:a.c
#	gcc a.c -o a.o
#b.o:b.c
#	gcc b.c -o b.o

#$(BIN):$(SRC)
#	gcc $^ -o $@
#$(BIN):test.c a.c b.c c.c
#	gcc $^ -o $@
#clean:
#	rm $(BIN)

#.PHONY:test
#test:test.c a.c b.c c.c
#	gcc $^ -o $@

#clean:
#	rm test


#test:linux.o
#	gcc linux.o -o test 

#linux.o:test.c
#	gcc -c test.c -o linux.o

#test:test.o
#	gcc test.o -o test

#test.o:test.c
#	gcc -c test.c -o test.o

#coretest:coretest.c
#	gcc coretest.c -o coretest
