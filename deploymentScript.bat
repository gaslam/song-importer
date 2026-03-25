@ECHO OFF

REM set the folder variables for the application itself

SET "BASE_FOLDER=%~dp0build\Desktop_Qt_6_10_1_MinGW_64_bit-Release\SongImporterExe\"
SET "TARGET_FILE=appSongImporterExe.exe"
SET "TARGET_LOCATION=%BASE_FOLDER%%TARGET_FILE%"
SET "TARGET_FOLDER=%~dp0deploy\"
SET "QML_DIR=%~dp0SongImporterExe"

REM set the folder variables for the class library

SET "IMPORTER_LIB_LOCATION=%~dp0build\Desktop_Qt_6_10_1_MinGW_64_bit-Release\SongImporterLib\"
SET "IMPORTER_LIB_DLL=libSongImporterLib.dll"
SET "IMPORTER_LIB_TARGET_LOCATION=%IMPORTER_LIB_LOCATION%%IMPORTER_LIB_DLL%"

REM set the folder variables for the taglib library

SET "IMPORTER_TAGLIB_LOCATION=%~dp0ThirdParty\taglib\bin\"
SET "IMPORTER_TAGLIB_DLL=libtag.dll"
SET "IMPORTER_TAGLIB_TARGET_LOCATION=%IMPORTER_TAGLIB_LOCATION%%IMPORTER_TAGLIB_DLL%"

REM Check if the dll and the .exe files exist before copying

IF NOT EXIST "%TARGET_LOCATION%" (
    ECHO The file: %TARGET_LOCATION% does not exist. Build the project in Release to start.
    PAUSE
    EXIT /B 1
)

IF NOT EXIST "%IMPORTER_LIB_TARGET_LOCATION%" (
    ECHO The file: %IMPORTER_LIB_TARGET_LOCATION% does not exist. Build the project in Release to start.
    PAUSE
    EXIT /B 1
)

IF NOT EXIST "%IMPORTER_TAGLIB_TARGET_LOCATION%" (
    ECHO The file: %IMPORTER_TAGLIB_TARGET_LOCATION% does not exist. Compile taglib and make sure the dll exists.
    PAUSE
    EXIT /B 1
)

REM Check if the destination of the executable exists. Otherwise, make it.

IF NOT EXIST "%TARGET_FOLDER%" (
    ECHO Folder does not exist. Creating it...
    MKDIR "%TARGET_FOLDER%"
)

REM Copy executable to the destination

ECHO Copying %TARGET_LOCATION% to %TARGET_FOLDER%

COPY %TARGET_LOCATION% %TARGET_FOLDER%


REM Deploy application with winqtdeploy and specify the qml directories

ECHO deploying application

windeployqt --no-translations --no-opengl-sw --no-system-d3d-compiler "%TARGET_FOLDER%%TARGET_FILE%" --qmldir "%QML_DIR%"

REM Copy DLL of the library to the new location

ECHO copying %IMPORTER_LIB_TARGET_LOCATION% to %TARGET_FOLDER%

COPY %IMPORTER_LIB_TARGET_LOCATION% %TARGET_FOLDER%

ECHO copying %IMPORTER_TAGLIB_TARGET_LOCATION% to %TARGET_FOLDER%

COPY %IMPORTER_TAGLIB_TARGET_LOCATION% %TARGET_FOLDER%

PAUSE