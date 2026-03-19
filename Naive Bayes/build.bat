@echo off

echo building

g++ naive_bayes.cpp -o naive_bayes.exe


echo running
naive_bayes.exe


del naive_bayes.exe
echo del
