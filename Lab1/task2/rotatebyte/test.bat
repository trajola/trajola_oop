echo off
rem %1 - �������� ������� ��������� ��������� ������ bat-����� (����� �� ����)
rem %~1 - �������� ������� ��������� ��������� ������ bat-����� � ��������� ����������� ������� (���� ��� ����)

rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"

rem ��������� ���������� ����������
%PROGRAM%  >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\invalid_number_args.out
if ERRORLEVEL 1 goto err

rem ��������� 1 ��������
%PROGRAM% 1 >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\invalid_number_args.out
if ERRORLEVEL 1 goto err

rem ��������� 2 ���������
%PROGRAM% 1 2 >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\invalid_number_args.out
if ERRORLEVEL 1 goto err

rem ��������� 4 ���������
%PROGRAM% 1 2 L R >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\invalid_number_args.out
if ERRORLEVEL 1 goto err

rem ��������� ������ �������������� 1 ���������
%PROGRAM% q 1 R >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\invalid_1_arg.out
if ERRORLEVEL 1 goto err

rem ��������� ������ �������������� 1 ���������
%PROGRAM% 256 1 R >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\invalid_1_arg.out
if ERRORLEVEL 1 goto err

rem ��������� ������ �������������� 1 ���������
%PROGRAM% 25q 1 R >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\invalid_1_arg.out
if ERRORLEVEL 1 goto err


rem ��������� ������ �������������� 2 ���������
%PROGRAM% 1 q R >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\invalid_2_arg.out
if ERRORLEVEL 1 goto err

rem ��������� ������ �������������� 2 ���������
%PROGRAM% 1 8 R >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\invalid_2_arg.out
if ERRORLEVEL 1 goto err

rem ��������� ������ �������������� 2 ���������
%PROGRAM% 1 1q R >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\invalid_2_arg.out
if ERRORLEVEL 1 goto err


rem ��������� ������ 3 ���������
%PROGRAM% 1 1 Q >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\invalid_3_arg1.out
if ERRORLEVEL 1 goto err

rem ��������� ������ 3 ���������
%PROGRAM% 1 1 LQ >%TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\invalid_3_arg2.out
if ERRORLEVEL 1 goto err

rem ��������� ���������� ������ ��� 254 5 L	
%PROGRAM% 254 5 L >%TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\work1.out
if ERRORLEVEL 1 goto err

rem ��������� ���������� ������ ��� 254 4 R	
%PROGRAM% 254 4 R >%TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\work2.out
if ERRORLEVEL 1 goto err

rem ��������� ���������� ������ ��� 255 7 L	
%PROGRAM% 255 7 L >%TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\work3.out
if ERRORLEVEL 1 goto err

rem ��������� ���������� ������ ��� 0 7 R	
%PROGRAM% 0 7 R >%TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt Tests\work4.out
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1