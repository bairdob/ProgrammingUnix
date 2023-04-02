### Task 6

Необходимо разработать сервис для подсчета времени, которое человек проводит в интернет. Должны отслеживать события подключения и отключения от интернет.

Сервис должен быть оформлен в виде сервиса systemd, который можно было бы запускать и останавливать при помощи sysctl service start/stop

Для определения наличия связи с internet используем событие от DBus


### log

for some reason systemd service not working so bellow code showing fucntionality
```bash
$ ./dbus_listener.sh &
```


```bash
$ sudo cp dbus_network_listener.service /etc/systemd/system/dbus_network_listener.service
$ sudo systemctl daemon-reload
$ sudo systemctl start dbus_network_listener.service
$ tail -f network.log 
```