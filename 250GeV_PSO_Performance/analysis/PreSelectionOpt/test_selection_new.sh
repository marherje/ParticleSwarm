#!/bin/bash
mkdir output
for pol in eL_pR eR_pL
do
    for cat in all catA
    do
        for quality in Good Medium Bad 
	do
	    for k in 35 
	    do
		for cuts in {0..7}
		do
		    #cuts=5
		    echo "sel:" $pol $cat $quality $cuts
		    root -l test_selection_new.cc\(\"$pol\",$cuts,$k,\"$cat\",\"$quality\"\) > log_sel_bkg_${k}_${pol}_${cat}_bdt_${quality}_genkt_restorer_cuts${cuts}
		    mv log_sel* output/.
		    mv selection_cuts* output/.
		done
	    done
	done
    done
done
