echo off
rem %1 - значение первого аргумента командной строки bat-файла (какой он есть)
rem %~1 - значение первого аргумента командной строки bat-файла с удалением обрамляющих кавычек (если они были)

rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"

rem проверяем отсутствие аргументов
%PROGRAM%  >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\invalid_number_args.out
if ERRORLEVEL 1 goto err

rem проверяем 1 аргумент
%PROGRAM% 1 >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\invalid_number_args.out
if ERRORLEVEL 1 goto err

rem проверяем 2 аргумента
%PROGRAM% 1 2 >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\invalid_number_args.out
if ERRORLEVEL 1 goto err

rem проверяем 4 аргумента
%PROGRAM% 1 2 L R >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\invalid_number_args.out
if ERRORLEVEL 1 goto err

rem проверяем ошибку преобразования 1 аргумента
%PROGRAM% q 1 R >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\invalid_1_arg.out
if ERRORLEVEL 1 goto err

rem проверяем ошибку преобразования 1 аргумента
%PROGRAM% 256 1 R >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\invalid_1_arg.out
if ERRORLEVEL 1 goto err

rem проверяем ошибку преобразования 1 аргумента
%PROGRAM% 25q 1 R >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\invalid_1_arg.out
if ERRORLEVEL 1 goto err


rem проверяем ошибку преобразования 2 аргумента
%PROGRAM% 1 q R >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\invalid_2_arg.out
if ERRORLEVEL 1 goto err

rem проверяем ошибку преобразования 2 аргумента
%PROGRAM% 1 8 R >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\invalid_2_arg.out
if ERRORLEVEL 1 goto err

rem проверяем ошибку преобразования 2 аргумента
%PROGRAM% 1 1q R >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\invalid_2_arg.out
if ERRORLEVEL 1 goto err


rem проверяем ошибку 3 аргумента
%PROGRAM% 1 1 Q >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\invalid_3_arg1.out
if ERRORLEVEL 1 goto err

rem проверяем ошибку 3 аргумента
%PROGRAM% 1 1 LQ >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\invalid_3_arg2.out
if ERRORLEVEL 1 goto err

rem проверяем правильную работу для 254 5 L	
%PROGRAM% 254 5 L >%TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\work1.out
if ERRORLEVEL 1 goto err

rem проверяем правильную работу для 254 4 R	
%PROGRAM% 254 4 R >%TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\work2.out
if ERRORLEVEL 1 goto err

rem проверяем правильную работу для 255 7 L	
%PROGRAM% 255 7 L >%TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\work3.out
if ERRORLEVEL 1 goto err

rem проверяем правильную работу для 0 7 R	
%PROGRAM% 0 7 R >%TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\work4.out
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1