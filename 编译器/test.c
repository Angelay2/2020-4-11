/*
编译器(gcc/g++)
	gcc -> C语言的编译器
	g++ -> C++语言的编译器
	编译的4个步骤:
	1. 预处理: 宏替换, 头文件展开, 去注释
	  gcc/g++ -E[源码文件名称] -o[待生成文件名称].i
	2. 编译: 语法语义的检测 生成汇编代码
	  gcc/g++ -S[源码文件名称] -o[待生成文件名称].s
	3. 汇编: 将汇编代码转换为机器代码
	  gcc/g++ -c[源码文件名称] -o[待生成文件名称].o
	4. 链接: 将生成的不同机器代码,链接在一起产生可执行程序
	  gcc/g++ [源码文件名称] -o[可执行程序名称]
动态链接: 在可执行程序中,记录可执行程序依赖C运行时库或者C++运行时库当中的函数位置, 将该函数的位置记录在符号表中, 在可执行程序运行的时候,再去动态地执行代码(printf在C语言运行时库): 可知信息港程序文件的大小 比较小
静态链接: 在编译可执行程序时, 需要执行一个命令参数-static, 将依赖的C或者C++运行时库当中的函数, 直接编译到可执行程序当中去. 可执行程序的大小比较大 整个编译过程耗时比较长.
	file: 查看文件属性的命令
	ldd命令: 查看可执行程序以来哪些库文件
调试器: gdb
 前提: 需要在编译可执行程序的时候增加 -g 选项, 从而可执行程序当中就有了调试信息
 1. 起手式(如何进行调试)
	gdb[可执行程序的名称]
 2.常用的命令( 先打断点, 再r, 跑起来 再n逐语句执行
  l: 查看源码
  r: 使可执行的程序跑起来
  b[num]: 在main函数所在的源码文件中打断点
  info b(i b): 查看断点信息
   enable[断点的序号]: 使断点生效
   disable[断点的序号]: 使断点不生效
   b[filename]:[num]: 在某一个文件当中的某一行进行打断点
   delete[断点的序号]: 删除断点
  n: 逐过程执行 --> win的F10 
  s: 逐语句执行 --> win的F11
  c: 继续执行 --> win的F5
  bt: 查看调用堆栈
  f[堆栈序号]: 切换到不同的堆栈中查看具体的信息
  p[变量名称]: 打印某一个变量的内容
  i locals: 查看当前作用域当中的临时变量
  q: 退出调试
3. 如何调试可执行程序
	gdb[可执行程序]
4. 如何调试一个已经跑起来的程序
	ps aux|grep[可执行程序的名称]: 拿到进程id
	gdb attach [进程id]  可以将调试加到已经跑起来的进程当中去
	gdb -p[进程id]
5.如何调试已经崩溃的程序, 调试coredump文件
	unlimit -a: 去查看core file size(这个大小决定系统在程序产生崩溃时 是否会产生一个coredump文件)
	0: 即使崩溃也不会产生coredump文件
	unlimited: 程序崩溃, 理论上也会产生coredump文件, 除非磁盘空间不够, 才不会产生coredump文件
	程序崩溃(产生coredump文件)的现象:
	 段错误:内存访问越界/解引用空指针
	 double free: 程序当中释放两次从堆上申请的空间(free野指针)

如何调试一个coredump文件
 gdb[可执行程序名称][coredump文件]
  a): 需要确定当前代码崩溃在哪一行,使用bt命令查看程序崩溃的时候, 代码运行的堆栈长什么样子
  b): 根据崩溃提示的代码行, 进行源码分析,发现错误
  c)和b)是或者的关系: 跳转大具体的崩溃的堆栈, f[堆栈序号] -> 进行打印(p)崩溃的时候, 变量的值

make/makefile
	make: 解释器, 本质上是一个程序
	Makefile/makefile: 本质上是一个文件, 被make解释器解释的一个编译可执行程序的规则文件,
	1. Makefile的编写规则
	 1.1 注释 (#xxxx)
	 1.2 目标对象:依赖对象
		编译命令
		目标对象: 需要生成的可执行程序的名称
		依赖对象: 生成可执行程序的源码文件
		编译命令: 如何使用依赖对象生成目标对象
	2. Makefile解释器的解释规则
	 2.1: 对比目标对象和依赖对象的最后一次修改时间, 如果说当目标对象比依赖对象最后一次修改时间距离现在比较近, 意味着目标对象比较新, 则make在解释Makefile当中的解释规则的时候,对比完成后, 就不会执行编译命令
	 2.2: 永远只为了生成第一个目标对象而服务
	 2.3: 在生产目标对象的时候, 发现依赖对象在当前目录下不存在. 则在Makefile中查找生成依赖对象的方法
	   查找到: 先执行生产依赖对象, 再反过头来生成目标对象
	   没有查找到: 
			第一种: make会默认补全一个依赖对象的补全方法, 但是这个依赖对象的生成方法在补全的时候,依赖对象的名称起到至关重要的作用;如果依赖对象的名称和源码文件的名称不一样, 则补全的时候就会有问题,则生成不了依赖对象
			第二种: 如果依赖对象的名称和源码文件名称一致, make解释器会补全依赖对象的生成方法
		总结: 在编写Makefile的时候 ,一定要注意依赖对象的生成方法, 不要遗漏
3. 预定义变量
	$^: 所有依赖的对象
	$@: 目标对象
	$<: 第一个依赖对象
4. 清理
	clean:
5. 伪目标
	使当前定义的目标对象一旦生成,而make解释器不再对比目标对象和依赖对象的最后一次修改时间
6. 自定义变量
	BIN:定义可执行程序
	OBJ: 定义汇编完成之后的.o文件
	SRC: 源码文件

*/