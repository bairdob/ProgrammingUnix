### task 7

Часть 1:

1. Разработать API для работы с логами dbgwrite, dbginit, dbgclose - запись пишет в SHM

2. Реализовать разделяемую библиотеку

Часть 2:

1. Реализовать демона для передачи данных

2. Реализовать демона для приема по TCP

3. Реализовать deb или rpm пакет для установки


### log

```bash
$ gcc -c -Wall -Werror -fpic dbg.c
$ gcc -shared -o libdbg.so dbg.o 
$ gcc main.c -L /home/bair/kernel_practice/shm_library
 -ldbg -o test 
$ ./test
```

```bash
$ export LD_LIBRARY_PATH=/home/bair/kernel_practice/shm_library/:$LD_LIBRARY_PATH
```