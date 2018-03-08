echo off
rem %1 - �������� ������� ��������� ��������� ������ bat-����� (����� �� ����)
rem %~1 - �������� ������� ��������� ��������� ������ bat-����� � ��������� ����������� ������� (���� ��� ����)

rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"

rem ��������� ��������� ����������
echo test 1
%PROGRAM%  >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\invalid_number_args.out
if ERRORLEVEL 1 goto err

rem ��������� 1 �������� 
echo test 2
%PROGRAM% encrypt Tests\text1.in Tests\text1.out 35 >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\invalid_arg1.out
if ERRORLEVEL 1 goto err

rem ��������� 2 ��������, ��������� �������������� ����
echo test 3
%PROGRAM% crypt Tests\not-exist.in Tests\text1.out 35 >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\invalid_arg2.out
if ERRORLEVEL 1 goto err

rem ��������� 3 ��������, ��������� ��� ������ �������� ��� ������ ����
echo test 4
%PROGRAM% crypt Tests\text1.in Tests\text1.in 35 >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\invalid_arg3.out
if ERRORLEVEL 1 goto err

rem ��������� 4 ��������, ��� ���������
echo test 5
%PROGRAM% crypt Tests\text1.in Tests\text1.out 355 >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\invalid_arg4.out
if ERRORLEVEL 1 goto err

rem ��������� 4 ��������, �� �����
echo test 6
%PROGRAM% crypt Tests\text1.in Tests\text1.out 35a >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\invalid_arg4.out
if ERRORLEVEL 1 goto err

rem ��������� ���������� ������	
echo test 7
%PROGRAM% crypt Tests\text1.in Tests\text1.out 35
if ERRORLEVEL 1 goto err
%PROGRAM% decrypt Tests\text1.out Tests\text1.test 35
if ERRORLEVEL 1 goto err
fc.exe Tests\text1.in Tests\text1.test
if ERRORLEVEL 1 goto err

rem ��������� ���������� ������	� ������ ������
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