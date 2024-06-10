# GAME OF LIFE

Made using raylib. Still Work in progress.

## TO GET STARTED

- Compile raylib for your device. Make sure you are using mingw 64 bit if you are on windows, make sure that you use the same compiler when compiling this game as well.

- For Windows
  - Install raylib from github or installer
  - Go to src folder inside raylib
  - If you have downloaded 64 bit version of mingw compiler you can continue.
  - If you have not downloaded compiler, raylib installer comes with pre installed compiler in 
    webkit64 or something similar folder, make sure to update your path variables to the bin of that folder

  - Open terminal
  
    ```javascript
    mingw32-make PLATFORM=PLATFORM_DESKTOP
    ```

- Copy the generated libraylib.a file into the ```/lib``` folder.
- Run in the game folder
  
  ```lua
  mingw32-make
  ```
