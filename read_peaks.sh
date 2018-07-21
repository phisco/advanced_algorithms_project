#!/bin/zsh 
for f in `ls $1`
do
    echo $f >> res.txt
    cat $1/$f | grep -I -B 4 -A 4 peak | tee >(awk '/mem_heap_B=/{print $1}' >>res.txt) >(awk '/mem_heap_extra_B=/{print $1}' >> res.txt) >(awk '/mem_stacks_B=/{print $1}' >> res.txt)
done
python read_peaks.py

