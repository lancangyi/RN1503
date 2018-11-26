DEL *.Bak /S
DEL /Q KeilMisc\Lst\*.*
DEL /Q KeilMisc\Map\*.*
DEL /Q KeilMisc\Obj\*.*
for /r . %%a in (.) do @if exist "%%a\.svn" rd /s /q "%%a\.svn"

DEL *.uvgui.* /S
DEL *.uvopt /S