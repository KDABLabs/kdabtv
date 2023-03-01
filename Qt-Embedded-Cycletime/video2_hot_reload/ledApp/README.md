# LED App
## Build Instructions
 1. `cmake .`  
 or for crosscompile 
 2. `cmake -DCMAKE_TOOLCHAIN_FILE=<path_to_your_buildroot_toolchain_file>/Toolchain.cmake`
 3. `make -j` 
 
## Attention!

 * In order for the application to work, initially copy the `qml` folder next to your binary executable on desktop or on target!
