# 正常编译过程

假设有一个.c文件

~~~shell
gcc  .c文件 -o 生成文件名
~~~

但是有多个或者n+1个文件时就需要反复编译，此时就需要makefile

新建Makefile，注意不需要添加后缀名 M不区分大小写

# 格式

~~~
target： dependencies
	command
target 目标文件 需要编译成什么文件
dependencies 文件依赖，生成目标文件需要什么依赖文件
command 前面加的是tab 编译代码
~~~

**例**

~~~makefile
test: test.c
        gcc test.c -o test

~~~

