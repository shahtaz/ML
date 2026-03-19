@echo off

echo compiling
g++ assessment.cpp -o assessment.exe


ls

echo running the prog.
assessment.exe


del assessment.exe
echo delete done
ls
