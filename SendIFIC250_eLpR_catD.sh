#!/bin/bash

ORIGIN="/lhome/ific/m/marherje/ParticleSwarmOptimization"
source $ORIGIN/init_ilcsoft_v02-02-02.sh
#cp -r ${path}/init_ilcsoft_v02-02-01.sh $PWD/.
#cp -r ${path}/JP_FlavourTag/ $PWD/.
#cp -r ${path}/PSO/ $PWD/.
#cp -r ${path}/runPSO.py $PWD/.
#cp -r ${path}/runPSO_exe.sh $PWD/.
#cp ${path}/FlavourTag500IFIC.txt $PWD/.
#source init_ilcsoft_v02-02-01.sh
#echo $PWD

cd $ORIGIN
. /cvmfs/sft.cern.ch/lcg/releases/gcc/8.2.0-3fa06/x86_64-centos7/setup.sh

export PATH=/cvmfs/sft.cern.ch/lcg/releases/LCG_96/Python/2.7.16/x86_64-centos7-gcc8-opt/bi\
n:${PATH}
export LD_LIBRARY_PATH=/cvmfs/sft.cern.ch/lcg/releases/LCG_96/Python/2.7.16/x86_64-centos7-\
gcc8-opt/lib:${LD_LIBRARY_PATH}

export CXX=g++
export CC=gcc
source /cvmfs/ilc.desy.de/sw/x86_64_gcc82_centos7/v02-02-03/root/6.18.04/bin/thisroot.sh
# Loading newer ROOT:
#/cvmfs/sft.cern.ch/lcg/app/releases/ROOT/6.24.02/x86_64-centos7-gcc48-opt/bin/thisroot.sh

for pol in eLpR #eRpL
do
    for cat in catD #catB catC catD
    do
	python runPSO.py -c FlavourTag250IFIC_configs/FlavourTag250IFIC_${pol}_${cat}.txt -o FlavourTag250IFIC_${pol}_${cat} > LogFlavourTag250IFIC_${pol}_${cat}
    done
done
	

#nohup ./sendtoyific.sh >& run_production.out  &
