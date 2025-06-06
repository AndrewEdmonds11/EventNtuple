#!/bin/bash

usage() {

   cat << EOF

   System to parallilize RooUtil macros on the Elastic Analysi Facility

   parallelize.sh [-h] macro n_jobs


   Arguments:
   -h, --help: print help
   macro: macro.C file that you want to parallelize
   n_jobs: number of jobs (max: 5)
EOF
}

if [[ "$1" == "-h" || "$1" == "--help" ]]; then
    usage
    return 0
fi

HOSTNAME=`hostname`
if [[ ${HOSTNAME} == *"mu2egpvm"* ]]; then
    echo "Error: This script should not be run on the mu2egpvms. Run it on the EAF"
    return 1
fi

MACRO_FILE=$1
MACRO_FUNCTION=`echo ${MACRO_FILE##*/} | cut -d '.' -f 1` # special arguments to get macro.C from something that might contain a path, then remove the .C
#echo $MACRO_FUNCTION

DATASET_FILELIST=$2
echo ${DATASET_FILELIST}

MAX_JOBS=20
N_JOBS=$3
if [[ ${N_JOBS} -gt ${MAX_JOBS} ]]; then
   N_JOBS=${MAX_JOBS}
fi
echo ${N_JOBS}

rm sublist*.txt
split --numeric-suffixes=1 --additional-suffix=.txt -n l/${N_JOBS} ${DATASET_FILELIST} sublist # start at 01
#ls sublist*.txt
#wc -l sublist*.txt

# Need to get the ROOT_INCLUDE_PATH in order to compile the macro
OLDIFS="$IFS"
IFS=':' tokens=( $ROOT_INCLUDE_PATH )
INC_PATHS=""
for INC_PATH in "${tokens[@]}"; do
    INC_PATHS=${INC_PATHS}" -I"$INC_PATH
done
IFS="$OLDIFS" # restore IFS

# Add the macro to a new file and also a main function so we can run this as a program
cat ${MACRO_FILE} > macro.cxx
echo "

int main(int argc, char* argv[]) {
   std::cout << argv[0] << \", \" << argv[1] << \", \" << argv[2] << std::endl;
   $MACRO_FUNCTION(argv[1], argv[2]);
   return 0;
}

" >> macro.cxx

# Compile the program
g++ macro.cxx $(root-config --cflags --libs) ${INC_PATHS} -o macro

# Run the program in parallel with different outputs
for i in $(seq -f "%02g" 1 ${N_JOBS}); do
    ./macro sublist${i}.txt output_N${i}.root >& output_N${i}.log &
done

# Want to wait for programs to finish
wait
# Combine the outputs
hadd -f output_full.root output_N*.root

# Clean up
rm output_N*.root
