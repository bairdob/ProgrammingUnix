1. Написать модуль ядра
2. Написать символьный драйвер
3. Добавить получение имени задачи, которая вызвало open


### requirements Ubuntu 22.04

```
$ sudo apt install make gcc
```

### log task2
```bash
$ make
$ sudo insmod chardev.ko
$ sudo dmesg
[ 7214.262791] Был присвоен major-номер 236.
[ 7214.262882] To talk to the driver, create a dev file with
[ 7214.262884] 'mknod /dev/chardev c 236 0'.
[ 7214.262889] Try various minor numbers. Try to cat and echo to
[ 7214.262890] the device file.
[ 7214.262890] Remove the device file and module when done.
$ sudo mknod /dev/chardev c 236 0
$ ls /dev | grep chardev
chardev
$ cat /dev/chardev 
Я уже сообщил тебе 0 раз Hello world!
$ cat /dev/chardev 
Я уже сообщил тебе 1 раз Hello world!
```

### log task3
```bash
...
$ cat /dev/chardev 
Я уже сообщил тебе 0 раз Hello world!
$ cat /dev/chardev 
Я уже сообщил тебе 1 раз Hello world!
$ sudo dmesg 
[ 7214.262791] Был присвоен major-номер 236.
[ 7214.262882] To talk to the driver, create a dev file with
[ 7214.262884] 'mknod /dev/chardev c 236 0'.
[ 7214.262889] Try various minor numbers. Try to cat and echo to
[ 7214.262890] the device file.
[ 7214.262890] Remove the device file and module when done.
[ 7357.922365] usb 4-6: new SuperSpeed USB device number 12 using xhci_hcd
[ 7357.941921] usb 4-6: LPM exit latency is zeroed, disabling LPM.
[ 7357.942754] usb 4-6: New USB device found, idVendor=203a, idProduct=fff9, bcdDevice= 1.00
[ 7357.942822] usb 4-6: New USB device strings: Mfr=1, Product=2, SerialNumber=3
[ 7357.942825] usb 4-6: Product: Камера (iPhone)
[ 7357.942828] usb 4-6: Manufacturer: Parallels
[ 7357.942829] usb 4-6: SerialNumber: 42364631-0000-0000-0000-000000000001
[ 7357.950485] usb 4-6: Found UVC 1.00 device Камера (iPhone) (203a:fff9)
[11278.922153] Был присвоен major-номер 236.
[11278.922160] To talk to the driver, create a dev file with
[11278.922160] 'mknod /dev/chardev c 236 0'.
[11278.922162] Try various minor numbers. Try to cat and echo to
[11278.922162] the device file.
[11278.922163] Remove the device file and module when done.
[11413.758657] The process name is cat
[11415.046363] The process name is cat
```