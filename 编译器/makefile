#目标对象:依赖对象
#	编译命令
#	可以在前面定义一个变量, 然后用$去解析这个变量
# $^: 所有依赖对象
# $@: 目标对象
# $<: 第一个依赖对象
BIN=out 

# *代表任意字符
# 把所有.c文件以空格格式放入SRC中
SRC=$(wildcard *.c) # a.c b.c c.c test.c
# 把所有.c文件变为.o文件以空格形式放入OBJ中
OBJ=$(patsubst %.c, %.o, $(SRC)) #算a.o b.o c.o test.o(汇编完成后的文件)
CFLAGS=-g #-g: debug编译选项 编译后就可以进行调试了

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
