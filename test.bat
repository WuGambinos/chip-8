cd build
cmake --build .
cd Debug
move mainWin.exe ../../
cd ../../
timeout 1
mainWin roms/Fishie.ch8