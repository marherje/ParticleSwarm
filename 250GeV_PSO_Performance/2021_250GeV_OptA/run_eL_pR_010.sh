#!/bin/bash
# file name: kt_010.sh

path="/lhome/ific/m/marherje/ParticleSwarmOptimization/250GeV_PSO_Performance/2021_250GeV_OptA"
source ${path}/init_ilcsoft.sh
cp -r ${path}/data $PWD/.
cp -r ${path}/lib $PWD/.
cp -r ${path}/lcfiweights $PWD/.
cp ${path}/GearOutput.xml $PWD/.
cp ${path}/test_eL_pR_010.xml .

export MARLIN_DLL="$MARLIN_DLL:$PWD/lib/libQQbarProcessor.so"
echo $PWD
Marlin ${PWD}/test_eL_pR_010.xml
