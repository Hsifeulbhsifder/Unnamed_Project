@echo off

echo Generating Visual Studio 2015 32-bit solution

mkdir VS-2015x86
cd VS-2015x86

cmake -G "Visual Studio 14 Win32" ../
echo.
echo.
echo Solution generated in /VS-2015x86
cd VS-2015x86
for /r %%x in (*.sln) do (
echo Opening %%x
"%%x"
)
delay 2000
exit