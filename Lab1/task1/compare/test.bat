echo off
rem %1 - �������� ������� ��������� ��������� ������ bat-����� (����� �� ����)
rem %~1 - �������� ������� ��������� ��������� ������ bat-����� � ��������� ����������� ������� (���� ��� ����)

rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"

rem 1. ��������� �������������� ������ ����
%PROGRAM% not-exist.txt empty.txt
if NOT ERRORLEVEL 2 goto err

rem 2. ��������� �������������� ������ ����
%PROGRAM% empty.txt not-exist.txt 
if NOT ERRORLEVEL 2 goto err

rem 3. ��������� ���������� ������
%PROGRAM% empty.txt empty-copy.txt >%TEMP%\empty-equal.txt
if ERRORLEVEL 1  goto err
fc.exe %TEMP%\empty-equal.txt is-equal.txt
if ERRORLEVEL 1 goto err

rem 4. ��������� ������ � ��������
%PROGRAM% empty.txt one-line.txt >%TEMP%\empty-not-empty.txt
if ERRORLEVEL 2  goto err
fc.exe %TEMP%\empty-not-empty.txt not-equal-1.txt
if ERRORLEVEL 1 goto err

rem 5. ��������� �������� � ������
%PROGRAM% multiline.txt empty.txt >%TEMP%\not-empty-empty.txt
if ERRORLEVEL 2  goto err
fc.exe %TEMP%\not-empty-empty.txt not-equal-1.txt
if ERRORLEVEL 1 goto err

rem 6. ��������� ������������ ����������
%PROGRAM% one-line.txt one-line-copy.txt >%TEMP%\one-line-equal.txt
if ERRORLEVEL 1  goto err
fc.exe %TEMP%\one-line-equal.txt is-equal.txt
if ERRORLEVEL 1 goto err

rem 7. ��������� ������������ ������������ ��������
%PROGRAM% one-line.txt one-line-diff.txt >%TEMP%\one-line-diff.txt
if ERRORLEVEL 2 goto err
fc.exe %TEMP%\one-line-diff.txt not-equal-1.txt
if ERRORLEVEL 1 goto err

rem 8. ��������� ������������ �������������
%PROGRAM% one-line.txt one-line-diff-2emptyline.txt >%TEMP%\one-line-two-line-diff.txt
if ERRORLEVEL 2  goto err
fc.exe %TEMP%\one-line-two-line-diff.txt not-equal-2.txt
if ERRORLEVEL 1 goto err

rem 9. ��������� ������������� ������������ 
%PROGRAM% one-line-diff-2emptyline.txt one-line.txt >%TEMP%\two-line-one-line-diff.txt
if ERRORLEVEL 2  goto err
fc.exe %TEMP%\two-line-one-line-diff.txt not-equal-2.txt
if ERRORLEVEL 1 goto err

rem 10. ��������� ������������� ���������� 
%PROGRAM% multiline.txt multiline-copy.txt >%TEMP%\multi-line-equal.txt
if ERRORLEVEL 1  goto err
fc.exe %TEMP%\multi-line-equal.txt is-equal.txt
if ERRORLEVEL 1 goto err

rem 11. ��������� ������������� ��������� 
%PROGRAM% multiline.txt multiline-diff-2line.txt >%TEMP%\multi-line-diff2.txt
if ERRORLEVEL 2  goto err
fc.exe %TEMP%\multi-line-diff2.txt not-equal-2.txt
if ERRORLEVEL 1 goto err

rem 12. ��������� ������������� ��������� 
%PROGRAM% multiline-diff-3line.txt multiline.txt >%TEMP%\multi-line-diff3.txt
if ERRORLEVEL 2  goto err
fc.exe %TEMP%\multi-line-diff3.txt not-equal-3.txt
if ERRORLEVEL 1 goto err




echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1