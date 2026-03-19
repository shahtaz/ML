@echo off

echo building
g++ Confusion_Matrix.cpp -o con_mat.exe

echo build done*

con_mat.exe

del con_mat.exe

