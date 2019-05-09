REM 
REM Tested with node-v8.15.1-x86 ( Node must be preinstalled )
REM

@echo Installing Node Modules ..
npm i node-red
npm i node-red-node-serialport
npm i node-red-dashboard

@echo Installing Flows ..
@copy flows*.json %HOMEDRIVE%%HOMEPATH%\.node-red\
@echo Done ..
@echo Now launch start.bat