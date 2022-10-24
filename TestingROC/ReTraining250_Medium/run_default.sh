#!/bin/bash
# file name: kt_xNAMEfile.sh

path="/lhome/ific/m/marherje/QQbarAnalysis500/scripts/ReTraining250"
source ${path}/init_ilcsoft.sh
cp -r ${path}/lib $PWD/.
cp -r ${path}/data $PWD/.
cp -r ${path}/lcfiweights $PWD/.
#cp ${path}/GearOutput.xml $PWD/.
cp ${path}/test_xPROD_xFLAVOUR_xNAMEfile_Kisr_xISRCUT.xml .

export MARLIN_DLL="$MARLIN_DLL:$PWD/lib/libISRQQ500.so"
echo $PWD
Marlin ${PWD}/test_xPROD_xFLAVOUR_xNAMEfile_Kisr_xISRCUT.xml
