# ESP32 (Wall-mounted room temperature sensor) for underfloor heating system v2.0

Software (C/C++) for Wall-mounted room temperature sensors. 

#### Description SW parts
- In [local_thermostat.ino](local_thermostat/local_thermostat.ino) is main loop for all parts and settings pins SPI bus.
- In [buttons.ino](local_thermostat/buttons.ino) is all for buttons.
- In [connection_ethernet.ino](local_thermostat/connection_ethernet.ino) is all for Ethernet connection.
- In [connection_wifi.ino](local_thermostat/connection_wifi.ino) is all for WiFi connection.
- In [ds18b20.ino](local_thermostat/ds18b20.ino) is all for temperature sensor DS18B20.
- In [mqtt.ino](local_thermostat/mqtt.ino) is all for MQTT (transive and receive message)

More information at https://github.com/RomLab/system-for-underfloor-heating-v2.0
