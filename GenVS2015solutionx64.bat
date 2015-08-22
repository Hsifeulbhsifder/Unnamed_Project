@echo off

echo Generating Visual Studio 2015 64-bit solution

mkdir VS-2015x64
cd VS-2015x64

cmake -G "Visual Studio 14 Win64" ../
echo.
echo.
echo Solution generated in /VS-2015x64
pause
exit