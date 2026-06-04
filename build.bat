@echo off
chcp 65001 >nul
:: 1. 加载VS2022编译环境
call "C:\Program Files\Microsoft Visual Studio\2022\Professional\Common7\Tools\VsDevCmd.bat"

:: 2. 处理build目录
if exist build (
    rmdir /s /q build
)
mkdir build

:: 3. 进入build，cmake生成ninja
cd build
cmake -G Ninja ..

:: 判断cmake是否成功
if %errorlevel% neq 0 (
    echo CMake配置失败，终止编译
    pause
    exit /b %errorlevel%
)

:: 4. ninja编译
ninja

:: 编译结束暂停看日志
pause