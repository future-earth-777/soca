#!/bin/sh

#source anaconda2/Python/bin/activate nco

JCSDA_SING="/home/gvernier/Sandboxes/soca/JCSDA-singularity-master-latest.simg"
SOCA_BUILD="/home/gvernier/Sandboxes/soca/soca-ioda-ufo-split/build"
SOCA_BIN="${SOCA_BUILD}/bin"
SOCA_INPUT="${SOCA_BUILD}/soca/test/testinput"
SOCA_TEST="${SOCA_BUILD}/soca/test"
SOCA_MODEL_RSC="/home/gvernier/Sandboxes/soca/soca-ioda-ufo-split/soca/test/Data/360x210x63"
SOCA_MODEL_FORCING="/home/gvernier/Sandboxes/soca/soca-ioda-ufo-split/soca/test/Data/360x210x63"

cd ${SOCA_TEST}

# Run 3DVAR
#----------
singularity exec ${JCSDA_SING} ${SOCA_BIN}/soca_3dvar.x ${SOCA_INPUT}/3dvar_test.yml

# Put analysis in restart file
#-----------------------------

# Make copy of bkg and ana
cp ${SOCA_TEST}/INPUT/MOM.res.nc ${SOCA_TEST}/MOM-ana.res.nc
cp ${SOCA_TEST}/Data/3dvar.an.2018-04-15T00\:00\:00Z.nc ${SOCA_TEST}/3DVAR.an.tmp.nc

# Rename variable in ana file
ncrename -v temp,Temp 3DVAR.an.tmp.nc

# Dump Temp analysis into bkg restart file
ncks -A -v Temp 3dvar.an.test.nc MOM-ana.res.nc

# Setup model
#------------

SCRATCH=${SOCA_TEST}/scratch
rm -rf ${SCRATCH}
mkdir  ${SCRATCH}

# Copy resource files in scratch
cp ${SOCA_MODEL_RSC}/* ${SCRATCH} 
mkdir ${SCRATCH}/INPUT
mkdir ${SCRATCH}/RESTART
cp ${SOCA_MODEL_RSC}/INPUT/ocean_hgrid.nc ${SCRATCH}/INPUT/
cp ${SOCA_MODEL_RSC}/INPUT/topog.nc ${SCRATCH}/INPUT/
cp MOM-ana.res.nc ${SCRATCH}/INPUT/
cp ./INPUT/ice_model.res.nc ${SCRATCH}/INPUT/
ln -s /home/gvernier/Sandboxes/MOM6-examples/ice_ocean_SIS2/SIS2/scratch/minscratch/INPUT/* ${SCRATCH}/INPUT/
cp /home/gvernier/Sandboxes/MOM6-examples/ice_ocean_SIS2/SIS2/scratch/minscratch/MOM6 ${SCRATCH}


#cp /home/gvernier/Sandboxes/MOM6-examples/ice_ocean_SIS2/SIS2/scratch
#singularity exec ${JCSDA_SING} mpirun 

# Start MOM6-SIS2
#----------------
cd ${SCRATCH}
singularity exec ${JCSDA_SING} mpirun -np 4 MOM6 