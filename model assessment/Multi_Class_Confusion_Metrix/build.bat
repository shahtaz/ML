@echo off

echo building

g++ multi_class_c_mat.cpp -o sol.exe


echo running
echo --------------------------------------------+
sol.exe
echo --------------------------------------------+
del sol.exe
echo deleted
