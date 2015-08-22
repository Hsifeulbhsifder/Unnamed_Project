@echo off

echo -------
echo -------

set Wildcard=*.h *.cpp *.inl *.c *.cxx *.cc *.hpp

echo STATICS FOUND:
findstr -s -n -i -l "static" %Wildcard%

echo -------
echo -------

@echo GLOBALS FOUND:
findstr -s -n -i -l "lscope" %Wildcard%
findstr -s -n -i -l "glob" %Wildcard%

echo -------
echo -------
pause
