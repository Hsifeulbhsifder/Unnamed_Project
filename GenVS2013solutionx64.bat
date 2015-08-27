@echo off

echo Generating Visual Studio 2013 64-bit solution

mkdir VS-2013x64
cd VS-2013x64

cmake -G "Visual Studio 12 Win64" ../
echo.
echo.
echo Solution generated in /VS-2013x64
cd VS-2013x64
for /r %%x in (*.sln) do (
echo Opening %%x
"%%x"
)
TIMEOUT 10
exit