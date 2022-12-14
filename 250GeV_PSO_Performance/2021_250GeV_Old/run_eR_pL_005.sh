#!/bin/bash
# file name: kt_005.sh

path="/lhome/ific/m/marherje/ParticleSwarmOptimization/250GeV_PSO_Performance/2021_250GeV_Old"
source ${path}/init_ilcsoft.sh
cp -r ${path}/data $PWD/.
cp -r ${path}/lib $PWD/.
cp -r ${path}/lcfiweights $PWD/.
cp ${path}/GearOutput.xml $PWD/.
cp ${path}/test_eR_pL_005.xml .

export MARLIN_DLL="$MARLIN_DLL:$PWD/lib/libQQbarProcessor.so"
echo $PWD
Marlin ${PWD}/test_eR_pL_005.xml
