#!/bin/bash

dbus-monitor --system "sender=org.freedesktop.NetworkManager, path=/org/freedesktop/NetworkManager, member=StateChanged" | sed -u -n 's/   uint32 20/\/usr\/bin\/python3 \/home\/bair\/kernel_practice\/dbus\/network_stop.py/p; s/   uint32 70/python3 \/home\/bair\/kernel_practice\/dbus\/network_start.py/p' | sh
