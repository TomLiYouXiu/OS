boot.bin: boot.asm
	nasm -f bin boot.asm -o boot.bin

master.img: boot.bin
	# 创建一个 16M 的硬盘镜像
	yes | bximage -q -hd=16 -func=create -sectsize=512 -imgmode=flat master.img
	# 将 boot.bin 写入主引导扇区
	dd if=boot.bin of=master.img bs=512 count=1 conv=notrunc

#u盘启动
.PHONY: usb
usb: boot.bin /dev/sdb
	sudo dd if=/dev/sdb of=tmp.bin bs=512 count=1 conv=notrunc
	cp tmp.bin usb.bin
	sudo rm tmp.bin
	dd if=boot.bin of=usb.bin bs=446 count=1 conv=notrunc
	sudo dd if=usb.bin of=/dev/sdb bs=512 count=1 conv=notrunc
	sudo rm usb.bin

.PHONY: clean
clean:
	rm -rf *.bin
	rm -rf *.img

.PHONY: bochs
bochs: master.img
	bochs -q