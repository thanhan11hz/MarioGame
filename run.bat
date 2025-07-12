cmake -G "MinGW Makefiles" -S . -B build 
cmake --build build
cd build
main.exe
