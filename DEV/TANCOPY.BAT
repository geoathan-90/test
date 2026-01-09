@echo off
cls
echo ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
echo ³                   ‘ç¤«˜¥ž œ¤«¦¢ãª                    ³
echo ÃÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ´
echo ³ ¢ã¨žª ˜¤« š¨˜­ã ³ tancopy [drive: [e ã ¦,« ›ã§¦«œ]] ³
echo ³ Run time copy    ³ tancopy [drive: [e ã ¦,« ›ã§¦«œ]] ³
echo ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ

if '%1'=='' goto exit
echo €¤ âš¨˜¯œª ©à©«á «ž¤ œ¤«¦¢ã, §á«˜ (Enter), ˜¢¢¦ éª §á«˜ (Ctrl-C) 
pause > null
if '%2'=='e' goto exe
del *.bak
del *.~*
xcopy *.ver %1\tan/s/v
copy *.prj %1\tan
copy *.bat %1\tan
if '%2'=='' goto jump
:exe
copy *.exe %1\tan
if '%2'=='e' goto exit
:jump
cd prm
del *.bak
del *.~*
xcopy *.* %1\tan\prm/s/v
cd ..\src
del *.bak
del *.~*
xcopy *.* %1\tan\src/s/v
cd ..
:exit
echo on