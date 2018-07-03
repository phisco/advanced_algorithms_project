if [ $# !=  2 ]
      then
              echo "help: time_test.sh root_dir dest_file"
              exit 1
fi
for g in `ls $1 | sort -n`
do 
    echo "\n-$g--------------------------------" >> $2;
    ./cmake-build-debug/test_stdin < $1/$g >> $2;
done

