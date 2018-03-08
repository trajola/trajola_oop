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

rem проверяем 1 аргумент, открываем несуществующий файл
echo test 2
%PROGRAM% Tests\not-exist.in Tests\fill.out >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\invalid_arg1.out
if ERRORLEVEL 1 goto err

rem проверяем 2 аргумент, открываем для записи открытый для чтения файл
echo test 3
%PROGRAM% Tests\fill1.in Tests\fill1.in >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\invalid_arg2_same.out
if ERRORLEVEL 1 goto err

rem проверяем 2 аргумент, открываем для записи файл в несуществующей папке
echo test 4
%PROGRAM% Tests\fill1.in Not-exist\fill1.out >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\invalid_arg2_not.out
if ERRORLEVEL 1 goto err

rem проверяем посторонний символ в файле
echo test 5
%PROGRAM% Tests\fill_bad_symbol.in Tests\fill.out >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\invalid_symbol.out
if ERRORLEVEL 1 goto err

rem проверяем правильную работу, контур с дыркой	
echo test 6
%PROGRAM% Tests\fill1.in %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe Tests\fill1.out %TEMP%\output.txt
if ERRORLEVEL 1 goto err

rem проверяем правильную работу, контур, нет стартовых точек 	
echo test 7
%PROGRAM% Tests\fill2.in %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe Tests\fill2.out %TEMP%\output.txt
if ERRORLEVEL 1 goto err

rem проверяем правильную работу, тот же контур с точкой внутри
echo test 8
%PROGRAM% Tests\fill3.in %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe Tests\fill3.out %TEMP%\output.txt
if ERRORLEVEL 1 goto err

rem проверяем правильную работу, тот же контур с точкой снаружи	
echo test 9
%PROGRAM% Tests\fill4.in %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe Tests\fill4.out %TEMP%\output.txt
if ERRORLEVEL 1 goto err

rem проверяем правильную работу, пустой файл без стартовых точек	
echo test 10
%PROGRAM% Tests\fill5.in %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe Tests\fill5.out %TEMP%\output.txt
if ERRORLEVEL 1 goto err

rem проверяем правильную работу, пустой файл с 1 стартовой точкой	
echo test 10
%PROGRAM% Tests\fill6.in %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe Tests\fill6.out %TEMP%\output.txt
if ERRORLEVEL 1 goto err

rem проверяем правильную работу, 2 контура с точками, один без	
echo test 11
%PROGRAM% Tests\fill7.in %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe Tests\fill7.out %TEMP%\output.txt
if ERRORLEVEL 1 goto err


echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1