@echo off

echo -------
echo -------

set Wildcard=*.h *.cpp *.inl *.c *.hpp *.cxx *.cc

echo TODOS FOUND:
findstr -s -n -i -l "TODO" %Wildcard%

echo -------
echo -------
pause