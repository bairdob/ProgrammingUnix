Practice1

1. Написать модуль ядра
2. Написать символьный драйвер
3. Добавить получение имени задачи, которая вызвало open

Practice2

1. Реализовать функции read
2. Реализовать функции write
3. Реализовать IOCTL для сброса



### requirements Ubuntu 22.04

```
$ sudo apt install make gcc
```

### log Pracice1 task2
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

### log Practice1 task3
```bash
...
$ cat /dev/chardev 
Я уже сообщил тебе 0 раз Hello world!
$ cat /dev/chardev 
Я уже сообщил тебе 1 раз Hello world!
$ sudo dmesg 
...
[11278.922153] Был присвоен major-номер 236.
[11278.922160] To talk to the driver, create a dev file with
[11278.922160] 'mknod /dev/chardev c 236 0'.
[11278.922162] Try various minor numbers. Try to cat and echo to
[11278.922162] the device file.
[11278.922163] Remove the device file and module when done.
[11413.758657] The process name is cat
[11415.046363] The process name is cat
```