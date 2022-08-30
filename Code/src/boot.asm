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

;内存中0xb800为文本显示器的内存区域
mov ax,0xb800
mov ds,ax
mov byte [0],'L'

;阻塞
jmp $

;填充0
times 510-($-$$) db 0

;主引导扇区的最后两个字节必须是0x55和0xaa
;dw 0xaa55 cpu 是小端存储
db 0x55,0xaa