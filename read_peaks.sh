for f in `ls $1`
do
    echo $f >> res.txt
    cat $f | grep -I -B 4 -A 4 peak | tee >(awk '/mem_heap_B=/{print $1}' | grep -o "[0-9]\+" >>res.txt) | tee >(awk '/mem_heap_extra_B=/{print $1}' | grep -o "[0-9]\+" >> res.txt) | awk '/mem_stacks_B=/{print $1}' | grep -o "[0-9]\+" >> res.txt
done
python read_peaks.py

