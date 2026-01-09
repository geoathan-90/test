@echo off
cls
echo ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
echo ³     ‘ç¤«˜¥ž œ¤«¦¢ãª  (Version 1.02)       ³
echo ÃÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ´
echo ³ ¢ã¨žª ˜¤« š¨˜­ã   ³ tancopy [drive:]     ³
echo ³ €¨®œ ˜ src & dev   ³ tancopy [drive: [d]] ³
echo ³ Mæ¤¦ src ˜¨®œå˜    ³ tancopy [drive: [s]] ³
echo ³ „¡«œ¢¦ç£œ¤˜ ˜¨®œ ˜ ³ tancopy [drive: [e]] ³
echo ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ

if '%1'==''  goto exit
cd \tan\src
del *.bak
del *.~*
cd \tan\prm
del *.bak
del *.~*
cd \tan
del *.bak
del *.~*
if '%2'==''  goto all
if '%2'=='d' goto srcdev
if '%2'=='s' goto srcprm
if '%2'=='e' goto exe
rem ************************************ ALL ******
:all
echo ‡˜ «˜ ˜¤« š¨á¯à æ¢˜;
echo €¤ ¤˜ , §á«˜ (Enter), ˜¢¢¦ éª §á«˜ (Ctrl-C)
pause > null
xcopy *.* %1\tan/s/v
goto exit
rem ************************************ SRCDEV ******
:srcdev
echo ‡˜ ˜¤« š¨á¯à «˜ ˜¨®œå˜ ˜¤˜§«ç¥œàª ;
echo €¤ ¤˜ , §á«˜ (Enter), ˜¢¢¦ éª §á«˜ (Ctrl-C)
pause > null
copy *.* %1\tan
xcopy src\*.* %1\tan\src/s/v
xcopy prm\*.* %1\tan\prm/s/v
goto exit
rem ************************************ SRCPRM ******
:src
echo ‡˜ ˜¤« š¨á¯à «˜ sources ˜¨®œå˜;
echo €¤ ¤˜ , §á«˜ (Enter), ˜¢¢¦ éª §á«˜ (Ctrl-C)
pause > null
xcopy src\*.* %1\tan\src/s/v
xcopy apo\*.* %1\tan\apo/s/v
xcopy prm\*.* %1\tan\prm/s/v
goto exit
rem ************************************ EXE ******
:exe
echo ‡˜ ˜¤« š¨á¯à «˜ œ¡«œ¢¦ç£œ¤˜ ˜¨®œå˜;
echo €¤ ¤˜ , §á«˜ (Enter), ˜¢¢¦ éª §á«˜ (Ctrl-C)
pause > null
copy *.exe %1\tan
xcopy dat\*.* %1\tan\dat/s/v
xcopy prm\*.* %1\tan\prm/s/v
rem ************************************ EXE ******
:exit
cd \tan
echo on
