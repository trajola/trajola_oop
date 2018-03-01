echo off
rem %1 - �������� ������� ��������� ��������� ������ bat-����� (����� �� ����)
rem %~1 - �������� ������� ��������� ��������� ������ bat-����� � ��������� ����������� ������� (���� ��� ����)

rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"

rem ��������� ��������� ����������
%PROGRAM%  >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\invalid_number_args.out
if ERRORLEVEL 1 goto err

rem ��������� 2 ���������
%PROGRAM% Tests\matrix.in Tests\matrix.out >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\invalid_number_args.out
if ERRORLEVEL 1 goto err

rem ��������� ���������� �������� �����
%PROGRAM% non_exist.in >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\file_not_exist.out
if ERRORLEVEL 1 goto err

rem ��������� ����������� ������� � ������
%PROGRAM% Tests\matrix_non_number.in >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\error_reading.out
if ERRORLEVEL 1 goto err

rem ��������� �������� ������ 3x2
%PROGRAM% Tests\matrix_3x2.in >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\error_reading.out
if ERRORLEVEL 1 goto err

rem ��������� �������� ������ 2x3
%PROGRAM% Tests\matrix_2x3.in >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\error_reading.out
if ERRORLEVEL 1 goto err

rem ��������� �������� - ������ ����
%PROGRAM% Tests\matrix_empty.in >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\error_reading.out
if ERRORLEVEL 1 goto err

rem ��������� ���������� ������ 	
%PROGRAM% Tests\matrix.in >%TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\matrix.out
if ERRORLEVEL 1 goto err

rem ��������� ���������� ������ ��� ������� ������������ 	
%PROGRAM% Tests\matrix_det0.in >%TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\matrix_det0.out
if ERRORLEVEL 1 goto err


echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1