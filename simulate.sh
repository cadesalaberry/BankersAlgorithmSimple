if [ -e ./*.o ]
	then make clean
fi
make > /dev/null
./banker
make clean > /dev/null
