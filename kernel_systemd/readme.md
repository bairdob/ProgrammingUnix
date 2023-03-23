### Task4

- Разработать тестовый сервис, которые ничего не делает просто работает в бесконечном цикле который можно устанавливать/запускать

- Добавить функцию read символьного драйвера обработку блокирования

- Добавить с символьный драйвер возможность генерировать данные с заданной частотой (1 раз в заданное число секунд)

- Добавить в сервис возможность читать данные из символьного драйвера и писать в файл

### log

```bash
$ gcc read_chardev.c
```


```bash
$ touch chardev.log
```

```bash
$ sudo cp read-chardev-write-to-file.service /etc/systemd/system/read-chardev-write-to-file.service
$ sudo systemctl daemon-reload
$ sudo systemctl start read-chardev-write-to-file.service
$ tail -f chardev.log 
```