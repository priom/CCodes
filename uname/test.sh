#!/bin/bash

gcc -Wall $1 -o testUname



diff --brief <(./testUname) UnameOutput.log >/dev/null
comp_value=$?  #Look at diff exit status

if [ $comp_value -eq 1 ]
then
    echo "WARNING: Output is different!"
else
    echo "SUCCESS: Output is the same!"
fi
