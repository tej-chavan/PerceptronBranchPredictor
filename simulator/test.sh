export HOME_DIR=$PWD
./Run.pl -db ./bench.db -dir results/gcc1 -benchmark gcc -sim $HOME_DIR/ss3/sim-outorder -args "-bpred perceptron -max:inst 1000000"
