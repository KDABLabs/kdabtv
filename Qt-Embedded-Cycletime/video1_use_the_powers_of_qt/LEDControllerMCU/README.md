# Code for controlling a NeoPixelRing with a simple Serial Protocol*

# Install 
1. install `platformio` 
2. `pio run -t upload --upload-port=/dev/ttyXXX`


# Basic protocol 

The chips expects data at`9600` baud.
Byteorder is 
``` 
 \0xb4 <red> <green> <blue>
```
