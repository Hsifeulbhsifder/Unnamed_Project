@echo off

echo Generating Visual Studio 2013 32-bit solution

mkdir VS-2013x86
cd VS-2013x86

cmake -G "Visual Studio 12 Win32" ../
echo.
echo.
echo Solution generated in /VS-2013x86
cd VS-2013x86
for /r %%x in (*.sln) do (
echo Opening %%x
"%%x"
)
TIMEOUT 10
exit