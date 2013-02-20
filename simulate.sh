if [ -e ./*.o ]
	then make clean
fi
make
./banker
make clean > /dev/null
