@echo off

:: This batch file requires a developer command prompt as shown shell.bat 
:: Compiling is substantially faster if you open your editor using the developer cmd instead of calling vcvarsall.bat

:: %~dp0 Cool way of getting the d = drive and p = path name of the current batch file.
set BuildDir=%~dp0..\build
 
if not exist %BuildDir% mkdir %BuildDir%
 
pushd %BuildDir%

:: delete pdb file and get rid of output errors
:: del *.pdb > NUL 2> NUL
 
set CommonCompilerFlags=/O2 /nologo -fp:fast -GR- /MP /Zi /FC /EHsc /I"..\deps\include" /W1 /MD
set CommonCompilerFlags= /std:c++latest %CommonCompilerFlags% 

set CommonLinkerFlags=user32.lib gdi32.lib winmm.lib opengl32.lib kernel32.lib shell32.lib glu32.lib
set GLFWLibPath=/LIBPATH:..\deps\lib\GLFW\lib-vc2017 glfw3.lib
set GLEWLibPath=/LIBPATH:..\deps\lib\GLEW glew32s.lib glew32.lib

:: Code and libraries directory path
set CodePath=..\code\*.cpp

:: Compile and Link
cl %CommonCompilerFlags% %CodePath% %ImGuiPath% %tfdPath% /link %CommonLinkerFlags% %GLEWLibPath% %GLFWLibpath% /out:"main.exe"
 
:: Copy dependencies if needed (dll, config)



echo .........
echo Build Finished!
popd

:: Compiler Options Explained
:: /O2 = Creates fast code.
:: /nologo = does not display copyright banner during compilation
:: /fp = floating point calculation options
:: /Zi = enable debugging information
:: /FC = use full path in diagnostics
:: /I = look for other include directories
:: /W# = Warnings
:: /MD = Which runtime library to use (Static/Dynamic)
:: /GR = enable run-time type information
::
::