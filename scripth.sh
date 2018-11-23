g++ -std=c++11 main.cpp

#small:
./a.out 0.1 0.1 407 10490 239 0.001 0.0001 1 input_small.txt output_small.txt
gnuplot plotme_small.gp

#medium:
./a.out 0.1 1.0 407 10490 239 0.001 0.0001 1 input_medium.txt output_medium.txt
gnuplot plotme_medium.gp

#large:
./a.out 1.0 1.0 407 10490 239 0.001 0.0001 1 input_large.txt output_large.txt
gnuplot plotme_large.gp
