#!/bin/sh
#args = filename stepsize framenumber

for i in $(seq 1 $3); do i=$(($i * $2)); ./drip $1 "$i"; done

#Example:
# ./filter.sh ./image.png 5 100 #for drip-stepsize of 5 and 100 frames
