# Project-Bare-Metal

How to install openocd:
```
git clone https://github.com/ntfreak/openocd.git
./bootstrap
./configure --enable-cmsis-dap --enable-jlink --enable-stlink --enable-ti-icdi
make
sudo make install
```

Embedded Penguin Studio Goals:

 - Make a project generator for supported boards
 - Make utilities for the following:
    - Dynamically add and remove modules
    - Dedicated 2d pinout viewer
    - Make dedicated configuration file similar to visual studio .cproj file (but with less junk)
 - Target directory structure:
    ```
        .
        ├── eps                     # Embedded Penguin Studio container, core of the project
        │   ├── bin                 # holds binaries files built by the project
        │   ├── build               # holds .o files built by the project
        │   ├── cfg                 # holds config files for the EPS side of the project
        │   ├── hal                 # holds mcu specific hardware abstraction files                                                                                            
        │   │   ├── inc                                                                                                         
        │   │   │   ├── component   # headers for mcu specific components, aka component register definitions
        │   │   │   ├── instance    # headers for mcu specific instances of hardware
        │   │   │   └── pio         # pin definition headers for specific mcus in that family
        │   │   └── src   
        │   ├── linker              # ld files
        |   └── 'Makefile'          # makefile
        |
        ├── cfg                     # Hold config files for application side of project
        ├── inc                     # hold header file application
        ├── src                     # hold source files for application
        └── third_party             # third party libraries container (examples: lwip, paho-mqtt, cryptoauthlib, freertos)
    ```