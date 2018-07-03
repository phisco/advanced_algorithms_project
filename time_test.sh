if [ $# !=  1 ]
      then
              echo "help: time_test.sh root_dir"
              exit 1
fi
for g in `ls $1 | sort -n`
do 
    echo "$g";
    ./cmake-build-debug/test_stdin < $1/$g;
done

