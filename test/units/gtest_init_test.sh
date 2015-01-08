export GTEST_HOME=../gtest
export LD_LIBRARY_PATH=$GTEST_HOME/lib:$LD_LIBRARY_PATH
g++ -I $GTEST_HOME/include -L $GTEST_HOME/lib -lgtest -lgtest_main -lpthread gtest_init_test.cpp
./a.out
rm a.out