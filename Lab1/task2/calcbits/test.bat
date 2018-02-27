echo off
rem %1 - �������� ������� ��������� ��������� ������ bat-����� (����� �� ����)
rem %~1 - �������� ������� ��������� ��������� ������ bat-����� � ��������� ����������� ������� (���� ��� ����)

rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"

rem ��������� ���������� ����������
%PROGRAM%  >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\invalid_number_agrs.out
if ERRORLEVEL 1 goto err

rem ��������� ����� 1 ���������
%PROGRAM% 1 2 >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\invalid_number_agrs.out
if ERRORLEVEL 1 goto err

rem ��������� ������ �������������� 'q' � �����
%PROGRAM% q >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\convert_error1.out
if ERRORLEVEL 1 goto err

rem ��������� ������ �������������� '15q' � �����
%PROGRAM% 15q >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\convert_error2.out
if ERRORLEVEL 1 goto err

rem ��������� ������ �������������� '214748364899999999999' � �����
%PROGRAM% 214748364899999999999 >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\convert_error3.out
if ERRORLEVEL 1 goto err

rem ��������� ��������� ��������� ��� �������� �������������� '-5' � �����
%PROGRAM% -5 >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\out_of_bounds1.out
if ERRORLEVEL 1 goto err

rem ��������� ��������� ��������� ��� �������� �������������� '256' � �����
%PROGRAM% 256 >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\out_of_bounds2.out
if ERRORLEVEL 1 goto err

rem ��������� ���������� ������ ��� 0
%PROGRAM% 0 >%TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\work1.out
if ERRORLEVEL 1 goto err

rem ��������� ���������� ������ ��� 255
%PROGRAM% 255 >%TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\work2.out
if ERRORLEVEL 1 goto err

rem ��������� ���������� ������ ��� 9
%PROGRAM% 9 >%TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\work3.out
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1