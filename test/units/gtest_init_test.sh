export GTEST_HOME=../gtest
export YAARAA_HOME=/home/pi/yaaraa
export LD_LIBRARY_PATH=$GTEST_HOME/lib:$LD_LIBRARY_PATH
g++ -std=c++0x -I $GTEST_HOME/include -L $GTEST_HOME/lib -lgtest -lgtest_main -lpthread gtest_init_test.cpp
#g++ -I $YARAA_HOME/src $GTEST_HOME/include -L $GTEST_HOME/lib -lgtest -lgtest_main -lpthread gtest_init_test.cpp
./a.out
rm a.out