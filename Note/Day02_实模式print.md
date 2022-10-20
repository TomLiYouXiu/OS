# 实模式print

实模式使用的也是int 0x10

参数

**ah：0x0e**

**al：字符**

**int 0x10：打印字符**

# asm代码

~~~asm
xchg bx,bx;交换 bochs魔数断点

mov si,booting
call print

;阻塞
jmp $

;定义打印函数
print:
    mov ah,0x0e
.next:
    mov al,[si]
    cmp al,0
    jz .done
    int 0x10
    inc si
    jmp .next
.done
    ret


;定义字符串
;10 \n 13 \r 
booting:
    db "LiYouXiu Create LOX", 10, 13 ,0
~~~



# 修改bochs魔数

magic_break: enabled=1

等于1时将在执行xchg bx,bx语句时进行中断

![](https://pic.imgdb.cn/item/630f0d3e16f2c2beb19d1798.jpg)

![](https://pic.imgdb.cn/item/630f0d8b16f2c2beb19d467c.jpg)

