echo off
rem %1 - значение первого аргумента командной строки bat-файла (какой он есть)
rem %~1 - значение первого аргумента командной строки bat-файла с удалением обрамляющих кавычек (если они были)

rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"

rem проверяем отсутствие аргументов
%PROGRAM%  >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\invalid_number_agrs.out
if ERRORLEVEL 1 goto err

rem проверяем более 1 аргумента
%PROGRAM% 1 2 >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\invalid_number_agrs.out
if ERRORLEVEL 1 goto err

rem проверяем ошибку преобразования 'q' в число
%PROGRAM% q >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\convert_error1.out
if ERRORLEVEL 1 goto err

rem проверяем ошибку преобразования '15q' в число
%PROGRAM% 15q >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\convert_error2.out
if ERRORLEVEL 1 goto err

rem проверяем ошибку преобразования '214748364899999999999' в число
%PROGRAM% 214748364899999999999 >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\convert_error3.out
if ERRORLEVEL 1 goto err

rem проверяем нарушение диапазона при успешном преобразовании '-5' в число
%PROGRAM% -5 >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\out_of_bounds1.out
if ERRORLEVEL 1 goto err

rem проверяем нарушение диапазона при успешном преобразовании '256' в число
%PROGRAM% 256 >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\out_of_bounds2.out
if ERRORLEVEL 1 goto err

rem проверяем правильную работу для 0
%PROGRAM% 0 >%TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\work1.out
if ERRORLEVEL 1 goto err

rem проверяем правильную работу для 255
%PROGRAM% 255 >%TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\work2.out
if ERRORLEVEL 1 goto err

rem проверяем правильную работу для 9
%PROGRAM% 9 >%TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\work3.out
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1