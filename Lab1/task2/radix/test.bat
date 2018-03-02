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
%PROGRAM% 2 >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\invalid_number_args.out
if ERRORLEVEL 1 goto err

rem ��������� 2 ���������
echo test 3
%PROGRAM% 2 2 >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\invalid_number_args.out
if ERRORLEVEL 1 goto err

rem ��������� 4 ���������
echo test 4
%PROGRAM% 1 2 2 2 >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\invalid_number_args.out
if ERRORLEVEL 1 goto err

rem ��������� ����������� ������� � �����
echo test 5
%PROGRAM% 2 2 k-k-k >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\error_src_value.out
if ERRORLEVEL 1 goto err

rem ��������� ����� �� ������� ���������
echo test 6
%PROGRAM% 2 2 -12 >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\error_src_value.out
if ERRORLEVEL 1 goto err

rem ��������� ����� �� ������� ���������
echo test 7
%PROGRAM% 16 2 FFG >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\error_src_value.out
if ERRORLEVEL 1 goto err

rem ��������� ������������ � ���� �� 2^31
echo test 8
%PROGRAM% 2 10 10000000000000000000000000000000 >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\error_src_value.out
if ERRORLEVEL 1 goto err

rem ��������� ������������ � ����� �� -(2^31+1)
echo test 9
%PROGRAM% 2 10 -10000000000000000000000000000001 >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\error_src_value.out
if ERRORLEVEL 1 goto err

rem ��������� ���������� ������ ��� 10 2 2147483647	
echo test 10
%PROGRAM% 10 2 2147483647 >%TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\work1.out
if ERRORLEVEL 1 goto err

rem ��������� ���������� ������ ��� 36 10 -ZIK0ZK (-2^31)	
echo test 11
%PROGRAM% 36 10 -ZIK0ZK >%TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\work2.out
if ERRORLEVEL 1 goto err

rem ��������� ���������� ������ ��� 10 36 0	
echo test 12
%PROGRAM% 10 36 0 >%TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\work3.out
if ERRORLEVEL 1 goto err

rem ��������� ���������� ������ ��� 10 36 -0	
echo test 13
%PROGRAM% 10 36 -0 >%TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\work4.out
if ERRORLEVEL 1 goto err

rem ��������� ���������� ������ ��� 2 10 -10000001
echo test 14
%PROGRAM% 2 10 -10000001 >%TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\work5.out
if ERRORLEVEL 1 goto err


echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1