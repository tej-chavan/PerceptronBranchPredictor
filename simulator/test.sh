export $HOME_DIR=$pwd
./Run.pl -db ./bench.db -dir results/gcc1 -benchmark gcc -sim $HOME_DIR/ss3/sim-outorder -args "-max:inst 1000000"
