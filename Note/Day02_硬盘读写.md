# 硬盘简介

**扇区**：硬盘读写的最小单位，最小一个，最多256个

**机械臂的寻道时间是硬盘性能的主要瓶颈**

一般情况下有一个磁道有63个扇区，主要是由于BIOS最大支持这么多，磁道从外侧技术，所以一般情况下c盘的读写速度最快

# IDE / ATA PIO Mode

* **PIO**:Input Output 端口的输入输出模式

端口类似外部设备的内部寄存器

* **IDE**：Integerated Drive Electronics 集成电子驱动器

* **ATA**：Advanced Technology Attachment / American National Standards Institute ANSI 美国国家标准学会

- SATA / PATA

# 硬盘读写

- CHS 模式 / Cylinder / Head / Sector
- LBA 模式 / Logical Block Address

LBA28，总共能访问 128G 的磁盘空间； 28位

查看bochsrc配置文件

~~~
ata0: enabled=true, ioaddr1=0x1f0, ioaddr2=0x3f0, irq=14
ata0-master: type=disk, path="master.img", mode=flat
ata0-slave: type=none
ata1: enabled=true, ioaddr1=0x170, ioaddr2=0x370, irq=15
ata1-master: type=none
ata1-slave: type=none

//看到：一个通道可以挂两个硬盘
~~~



**硬盘控制端口**

| Primary 通道 | Secondary 通道 | in 操作      | out 操作     |
| ------------ | -------------- | ------------ | ------------ |
| 0x1F0        | 0x170          | Data         | Data         |
| 0x1F1        | 0x171          | Error        | Features     |
| 0x1F2        | 0x172          | Sector count | Sector count |
| 0x1F3        | 0x173          | LBA low      | LBA low      |
| 0x1F4        | 0x174          | LBA mid      | LBA mid      |
| 0x1F5        | 0x175          | LBA high     | LBA high     |
| 0x1F6        | 0x176          | Device       | Device       |
| 0x1F7        | 0x177          | Status       | Command      |

- 0x1F0：16bit 端口，用于读写数据
- 0x1F1：检测前一个指令的错误
- 0x1F2：读写扇区的数量
- 0x1F3：起始扇区的 0 ~ 7 位
- 0x1F4：起始扇区的 8 ~ 15 位
- 0x1F5：起始扇区的 16 ~ 23 位
- 0x1F6:
  - 0 ~ 3：起始扇区的 24 ~ 27 位
  - 4: 0 主盘, 1 从片
  - 6: 0 CHS, 1 LBA
  - 5 ~ 7：固定为1
- 0x1F7: out
  - 0xEC: 识别硬盘
  - 0x20: 读硬盘
  - 0x30: 写硬盘
- 0x1F7: in / 8bit
  - 0 ERR
  - 3 DRQ 数据准备完毕
  - 7 BSY 硬盘繁忙

# 汇编代码

## 读

~~~asm
mov edi,0x1000;读取的目标内存
mov ecx,0;起始扇区 ecx:cx寄存器的扩展有32位
mov bl,1;扇区数量
call read_disk
;定义硬盘读写函数
read_disk:
    ;设置读写扇区的数量
    mov dx,0x1f2
    mov al,bl
    out dx,al
   
    inc dx ;0x1f3
    mov al,cl;起始扇区的前八位
    out dx,al

    inc dx ;0x1f4
    shr ecx,8
    mov al,cl;起始扇区的中八位
    out dx,al

    inc dx ;0x1f5
    shr ecx,8
    mov al,cl;起始扇区的高八位
    out dx,al

    inc dx;0x1f6 
    shr ecx,8
    and cl,0b1111;将高四位置零
    mov al,0b1110_0000;端口字 主盘LBA模式
    or al,cl
    out dx,al

    ;读硬盘
    inc dx;0x1f7
    mov al,0x20
    out dx,al

    xor ecx,ecx;清空
    mov cl,bl;得到读写扇区的数量

    .read:
        push cx ;保存cx
        call .waits;等待数据准备完毕
        call .reads;读取一个扇区
        pop cx ;恢复cx
        loop .read

    ret 

    .waits:
        mov dx,0x1f7
        .check:
            in al,dx
            jmp $+2;nop 直接跳转到下一行
            jmp $+2;一点点延迟
            jmp $+2
            and al,0b1000_1000
            cmp al,0b0000_1000
            jnz .check
        ret 

    .reads:
        mov dx,0x1f0
        mov cx,256;一个扇区256个字
        .readw:
            jmp $+2;nop 直接跳转到下一行
            jmp $+2;一点点延迟
            jmp $+2
            mov [edi],ax
            add edi,2
            loop .readw
        ret
~~~

## 写

~~~asm
wirte_disk:

    ; 设置读写扇区的数量
    mov dx, 0x1f2
    mov al, bl
    out dx, al

    inc dx; 0x1f3
    mov al, cl; 起始扇区的前八位
    out dx, al

    inc dx; 0x1f4
    shr ecx, 8
    mov al, cl; 起始扇区的中八位
    out dx, al

    inc dx; 0x1f5
    shr ecx, 8
    mov al, cl; 起始扇区的高八位
    out dx, al

    inc dx; 0x1f6
    shr ecx, 8
    and cl, 0b1111; 将高四位置为 0

    mov al, 0b1110_0000;
    or al, cl
    out dx, al; 主盘 - LBA 模式

    inc dx; 0x1f7
    mov al, 0x30; 写硬盘
    out dx, al

    xor ecx, ecx; 将 ecx 清空
    mov cl, bl; 得到读写扇区的数量

    .write:
        push cx; 保存 cx
        call .writes; 写一个扇区
        call .waits; 等待硬盘繁忙结束
        pop cx; 恢复 cx
        loop .write

    ret

    .waits:
        mov dx, 0x1f7
        .check:
            in al, dx
            jmp $+2; nop 直接跳转到下一行
            jmp $+2; 一点点延迟
            jmp $+2
            and al, 0b1000_1000
            cmp al, 0b0000_0000
            jnz .check
        ret

    .writes:
        mov dx, 0x1f0
        mov cx, 256; 一个扇区 256 字
        .writew:
            mov ax,[edi]
            out dx, ax
            jmp $+2; 一点点延迟
            jmp $+2
            jmp $+2
            mov [edi], ax
            add edi, 2
            loop .writew
        ret
~~~



# 读硬盘

**查看0x1000地址**

![](https://pic.imgdb.cn/item/631066a816f2c2beb14bbe53.jpg)

此时地址全部为0

下一步

![](https://pic.imgdb.cn/item/6310685016f2c2beb14d6a3e.jpg)

可以看到引导已被写入扇区

# 写硬盘

![](https://pic.imgdb.cn/item/6310700716f2c2beb152da9a.jpg)

# 参考文献

- https://www.youtube.com/watch?v=oEORcCQ62nQ
- https://wiki.osdev.org/ATA_PIO_Mode
- https://bochs.sourceforge.io/techspec/PORTS.LST
- https://www.techtarget.com/searchstorage/definition/IDE

~~~asm
;代码开始的位置
[org 0x7c00]
;设置屏幕模式为文本模式，清除屏幕
mov ax,3
int 0x10

;初始化段寄存器
mov ax,0
mov ds,ax
mov es,ax
mov ss,ax
mov sp,0x7c00

mov si,booting
call print

xchg bx,bx;交换 bochs魔数断点

mov edi,0x1000;读取的目标内存
mov ecx,0;起始扇区 ecx:cx寄存器的扩展有32位
mov bl,1;扇区数量

call read_disk

;阻塞
jmp $

;定义硬盘读写函数
read_disk:
    ;设置读写扇区的数量
    mov dx,0x1f2
    mov al,bl
    out dx,al
   
    inc dx ;0x1f3
    mov al,cl;起始扇区的前八位
    out dx,al

    inc dx ;0x1f4
    shr ecx,8
    mov al,cl;起始扇区的中八位
    out dx,al

    inc dx ;0x1f5
    shr ecx,8
    mov al,cl;起始扇区的高八位
    out dx,al

    inc dx;0x1f6 
    shr ecx,8
    and cl,0b1111;将高四位置零
    mov al,0b1110_0000;端口字 主盘LBA模式
    or al,cl
    out dx,al

    ;读硬盘
    inc dx;0x1f7
    mov al,0x20
    out dx,al

    xor ecx,ecx;清空
    mov cl,bl;得到读写扇区的数量

    .read:
        push cx ;保存cx
        call .waits;等待数据准备完毕
        call .reads;读取一个扇区
        pop cx ;恢复cx
        loop .read

    ret 

    .waits:
        mov dx,0x1f7
        .check:
            in al,dx
            jmp $+2;nop 直接跳转到下一行
            jmp $+2;一点点延迟
            jmp $+2
            and al,0b1000_1000
            cmp al,0b0000_1000
            jnz .check
        ret 

    .reads:
        mov dx,0x1f0
        mov cx,256;一个扇区256个字
        .readw:
            jmp $+2;nop 直接跳转到下一行
            jmp $+2;一点点延迟
            jmp $+2
            mov [edi],ax
            add edi,2
            loop .readw
        ret
    
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
.done:
    ret


;定义字符串
;10 \n 13 \r 
booting:
    db "LiYouXiu Create LOX", 10, 13 ,0

;填充0
times 510-($-$$) db 0

;主引导扇区的最后两个字节必须是0x55和0xaa
;dw 0xaa55 cpu 是小端存储
db 0x55,0xaa
~~~

