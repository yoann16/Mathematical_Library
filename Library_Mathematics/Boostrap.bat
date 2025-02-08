@echo off
echo Nettoyage du dossier build existant...
if exist build rmdir /s /q build

echo Creation du nouveau dossier build...
mkdir build
cd build

echo Generation du projet Visual Studio 2022...
cmake .. -G "Visual Studio 17 2022"

echo Terminé !
pause