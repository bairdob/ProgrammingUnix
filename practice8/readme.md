### task 8

- Найти сетевую карту на компьютере и определить ее vendor di, device id

- Разработать символьный драйвер для PCI устройства, который возвращает через IOCTL MAC адрес сетевой карты

### requirements ubuntu 22.04

```bash
$ sudo apt install net-tools
```

### log

```bash
$ lspci | egrep -i --color 'network|ethernet'
04:00.0 Ethernet controller: Realtek Semiconductor Co., Ltd. RTL8111/8168/8411 PCI Express Gigabit Ethernet Controller (rev 03)
$ lspci -n | grep 04:00                      
04:00.0 0200: 10ec:8168 (rev 03)
```

```bash
$ ifconfig | grep enp 
enp4s0: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
$ lspci -v 
...
04:00.0 Ethernet controller: Realtek Semiconductor Co., Ltd. RTL8111/8168/8411 PCI Express Gigabit Ethernet Controller (rev 03)
	Subsystem: Gigabyte Technology Co., Ltd Onboard Ethernet
	Flags: bus master, fast devsel, latency 0, IRQ 17
	I/O ports at ce00 [size=256]
	Memory at fbeff000 (64-bit, prefetchable) [size=4K]
	Memory at fbef8000 (64-bit, prefetchable) [size=16K]
	Expansion ROM at fbc00000 [virtual] [disabled] [size=128K]
	Capabilities: <access denied>
	Kernel driver in use: r8169
	Kernel modules: r8169
...
```

```bash
$ sudo ifconfig enp4s0 down
$ sudo rmmod r8169  
```

```bash
$ make
$ gcc read_ioctl.c
$ sudo insmod pci_skel.ko
$ sudo mknod /dev/chardev c 234 0
$ sudo dmesg
[  899.499560] *** inside init  *** 
[  899.499565] To talk to the driver, create a dev file with
[  899.499566] 'mknod /dev/chardev c 234 0'.
[  899.499569] Try various minor numbers. Try to cat and echo to
[  899.499570] the device file.
[  899.499600] *** inside probe  *** 
[  899.499641] MAC address: 74:09:41:38:d0:75
$ ./a.out                 
ioctl: Inappropriate ioctl for device
$ sudo dmesg
...
[ 1023.286256] *** inside ioctl*** 
[ 1023.286258] IOCTL MAC address: 74:09:41:38:d0:75
[ 1023.286261] IOCTL cmd: 1




