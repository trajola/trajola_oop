echo off
rem %1 - значение первого аргумента командной строки bat-файла (какой он есть)
rem %~1 - значение первого аргумента командной строки bat-файла с удалением обрамляющих кавычек (если они были)

rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"

rem проверяем отутствие аргументов
echo test 1
%PROGRAM%  >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\invalid_number_args.out
if ERRORLEVEL 1 goto err

rem проверяем 1 аргумент 
echo test 2
%PROGRAM% encrypt Tests\text1.in Tests\text1.out 35 >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\invalid_arg1.out
if ERRORLEVEL 1 goto err

rem проверяем 2 аргумент, открываем несуществующий файл
echo test 3
%PROGRAM% crypt Tests\not-exist.in Tests\text1.out 35 >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\invalid_arg2.out
if ERRORLEVEL 1 goto err

rem проверяем 3 аргумент, открываем для записи открытый для чтения файл
echo test 4
%PROGRAM% crypt Tests\text1.in Tests\text1.in 35 >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\invalid_arg3.out
if ERRORLEVEL 1 goto err

rem проверяем 4 аргумент, вне диапазона
echo test 5
%PROGRAM% crypt Tests\text1.in Tests\text1.out 355 >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\invalid_arg4.out
if ERRORLEVEL 1 goto err

rem проверяем 4 аргумент, не число
echo test 6
%PROGRAM% crypt Tests\text1.in Tests\text1.out 35a >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\invalid_arg4.out
if ERRORLEVEL 1 goto err

rem проверяем правильную работу	
echo test 7
%PROGRAM% crypt Tests\text1.in Tests\text1.out 35
if ERRORLEVEL 1 goto err
%PROGRAM% decrypt Tests\text1.out Tests\text1.test 35
if ERRORLEVEL 1 goto err
fc.exe Tests\text1.in Tests\text1.test
if ERRORLEVEL 1 goto err

rem проверяем правильную работу	с пустым файлом
echo test 8
%PROGRAM% crypt Tests\text-empty.in Tests\text-empty.out 35
if ERRORLEVEL 1 goto err
%PROGRAM% decrypt Tests\text-empty.out Tests\text-empty.test 35
if ERRORLEVEL 1 goto err
fc.exe Tests\text-empty.in Tests\text-empty.test
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1