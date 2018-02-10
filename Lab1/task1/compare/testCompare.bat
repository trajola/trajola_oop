echo off
rem %1 - значение первого аргумента командной строки bat-файла (какой он есть)
rem %~1 - значение первого аргумента командной строки bat-файла с удалением обрамляющих кавычек (если они были)

rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"

rem 1. проверяем несуществующий первый файл
%PROGRAM% not-exist.txt empty.txt
if NOT ERRORLEVEL 2 goto err

rem 2. проверяем несуществующий второй файл
%PROGRAM% empty.txt not-exist.txt 
if NOT ERRORLEVEL 2 goto err

rem 3. проверяем одинаковый пустой
%PROGRAM% empty.txt empty-copy.txt >%TEMP%\empty-equal.txt
if ERRORLEVEL 1  goto err
fc.exe %TEMP%\empty-equal.txt is-equal.txt
if ERRORLEVEL 1 goto err

rem 4. проверяем пустой с непустым
%PROGRAM% empty.txt one-line.txt >%TEMP%\empty-not-empty.txt
if ERRORLEVEL 2  goto err
fc.exe %TEMP%\empty-not-empty.txt not-equal-1.txt
if ERRORLEVEL 1 goto err

rem 5. проверяем непустой с пустым
%PROGRAM% multiline.txt empty.txt >%TEMP%\not-empty-empty.txt
if ERRORLEVEL 2  goto err
fc.exe %TEMP%\not-empty-empty.txt not-equal-1.txt
if ERRORLEVEL 1 goto err

rem 6. проверяем однострочный одинаковый
%PROGRAM% one-line.txt one-line-copy.txt >%TEMP%\one-line-equal.txt
if ERRORLEVEL 1  goto err
fc.exe %TEMP%\one-line-equal.txt is-equal.txt
if ERRORLEVEL 1 goto err

rem 7. проверяем однострочный однострочный отличный
%PROGRAM% one-line.txt one-line-diff.txt >%TEMP%\one-line-diff.txt
if ERRORLEVEL 2 goto err
fc.exe %TEMP%\one-line-diff.txt not-equal-1.txt
if ERRORLEVEL 1 goto err

rem 8. проверяем однострочный многострочный
%PROGRAM% one-line.txt one-line-diff-2emptyline.txt >%TEMP%\one-line-two-line-diff.txt
if ERRORLEVEL 2  goto err
fc.exe %TEMP%\one-line-two-line-diff.txt not-equal-2.txt
if ERRORLEVEL 1 goto err

rem 9. проверяем многострочный однострочный 
%PROGRAM% one-line-diff-2emptyline.txt one-line.txt >%TEMP%\two-line-one-line-diff.txt
if ERRORLEVEL 2  goto err
fc.exe %TEMP%\two-line-one-line-diff.txt not-equal-2.txt
if ERRORLEVEL 1 goto err

rem 10. проверяем многострочный одинаковый 
%PROGRAM% multiline.txt multiline-copy.txt >%TEMP%\multi-line-equal.txt
if ERRORLEVEL 1  goto err
fc.exe %TEMP%\multi-line-equal.txt is-equal.txt
if ERRORLEVEL 1 goto err

rem 11. проверяем многострочный различный 
%PROGRAM% multiline.txt multiline-diff-2line.txt >%TEMP%\multi-line-diff2.txt
if ERRORLEVEL 2  goto err
fc.exe %TEMP%\multi-line-diff2.txt not-equal-2.txt
if ERRORLEVEL 1 goto err

rem 12. проверяем многострочный различный 
%PROGRAM% multiline-diff-3line.txt multiline.txt >%TEMP%\multi-line-diff3.txt
if ERRORLEVEL 2  goto err
fc.exe %TEMP%\multi-line-diff3.txt not-equal-3.txt
if ERRORLEVEL 1 goto err




echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1