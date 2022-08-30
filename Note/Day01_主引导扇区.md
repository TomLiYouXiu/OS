# 实现编译自动化

上一章完成截图

![](https://pic.imgdb.cn/item/630d97c316f2c2beb1cc4fcb.jpg)

makefile文件编写

~~~makefile
//汇编
boot.bin: boot.asm
	nasm -f bin boot.asm -o boot.bin
//镜像写入
master.img: boot.bin
	yes | bximage -q -hd=16 -func=create -sectsize=512 -imgmode=flat master.img
	dd if=boot.bin of=master.img bs=512 count=1 conv=notruncma
//自动删除
//每次自动执行
.PHONY: clean
clean: 
	rm -rf *.bin
	rm -rf *.img
//bochs的命令
.PHONY: bohcs
bohcs: master.img
	bohcs -q
~~~

# BIOS

**Basic Input Output System**

在加电自检，检测硬件功能是否完整，然后将主引导扇区读0x7c00位置，并跳转到这里执行

在bochs上打上断点

~~~
break 0x7c00
~~~

![](https://pic.imgdb.cn/item/630dd69516f2c2beb1fdf54c.jpg)

此时可以看到BIOS的一些信息，还可以看到自己之前写的汇编代码

~~~asm
int 0x10 
;BIOS 系统调用 显示器相关的功能
~~~

# 实模式

8086模式：16位

与实模式相对的是保护系统

此操作系统是保护模式

流程如下

- Real Mode
- Protected Mode

~~~asm
;内存中0xb8000为文本显示器的内存区域
mov ax,0xb800
mov ds,ax
mov byte [0],'L'
~~~

## 实模式的寻址方式

*有效地址=段地址16+偏移地址*

EA=0xb800*16+0=0xb8000

EA(Effective Address)

实模式的寄存器都是16位的，但是实模式的内存一般为1M也就是是20根地址线，还差4根地址线，剩下的由段地址提供，段地址<<4

保护模式下寄存器变成了32位，可以访问4G内存，所以保护模式下不需要这个方式

# 主引导扇区的结构

一个扇区有512个字节，其中前面的代码占了446字节，硬盘分区表总共有64个字节

* 代码：446B

* 硬盘分区表：64B=4*16B（硬盘最多被分为4个区）
* 魔数：0xaa55 或者 0x55 0xaa 必须为这个

要是没有硬盘分区表可能无法启动

# 主引导扇区的功能

读取内核加载器，并执行

# 参考文献

- IBM PS 2 and PC BIOS Interface Technical Reference