@echo off

echo compiling file
g++ main.cpp -o main.exe
pause


echo running the file
main.exe
pause

del main.exe
echo [ del ]
