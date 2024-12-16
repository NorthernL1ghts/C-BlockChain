@echo off
setlocal

REM Ensure OpenSSL is installed and added to the PATH
REM Adjust the OpenSSL paths if necessary

echo.
echo ==========================
echo Building blockchain project...
echo ==========================
echo.

REM Create directories if they do not exist
if not exist ..\bin mkdir ..\bin
if not exist ..\bin-int mkdir ..\bin-int

REM Change directory to src
cd ..

REM Compile the project
echo Compiling source files...
gcc -o bin-int\main.o src\main.c -lssl -lcrypto -c

if %errorlevel% neq 0 (
    echo.
    echo Compilation failed!
    exit /b %errorlevel%
)

echo Linking object files...
gcc -o bin\blockchain.exe bin-int\main.o -lssl -lcrypto

if %errorlevel% neq 0 (
    echo.
    echo Linking failed!
    exit /b %errorlevel%
)

echo.
echo ==========================
echo Build successful!
echo ==========================
echo Running blockchain...
echo.

bin\blockchain.exe

endlocal
pause
