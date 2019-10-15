#!/bin/bash

expdir=/home/Guillaume.Vernieres/scratch1/rundir/test005
listofcycles=`ls $expdir`
echo $listofcycles
for cycle in $listofcycles; do
    echo $expdir/$cycle
    ./oceanview.py -i ${expdir}/${cycle}/Data/*.out_0*.nc    
done


