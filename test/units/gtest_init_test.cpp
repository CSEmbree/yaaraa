#include <gtest/gtest.h>
#include "../../src/utils.h"
//#include "utils.h"

TEST(MathTest, TwoPlusTwoEqualsFour) {
  EXPECT_EQ(2 + 2, 4);
}


TEST(utils, number_to_string) {
  EXPECT_EQ("10", utils::number_to_string(10) );
} 


TEST(utils, string_to_number) {
  EXPECT_EQ(10, utils::string_to_number<int>("10") );
} 


TEST(utils, is_pos_int) {

  EXPECT_EQ(true, utils::is_pos_int("0") );
  EXPECT_EQ(true, utils::is_pos_int("10") );

  EXPECT_EQ(false, utils::is_pos_int("-1") );
} 

TEST(utils, pathify) {

  string path = "", res = "";


  path = ""; //empty
  res = "";  //same as empty
  EXPECT_EQ(res, utils::pathify(path) );


  path = "/some/path/"; //end with slash
  res = "/some/path/";  //valid, change nothing
  EXPECT_EQ(res, utils::pathify(path) );


  path = "/some/path";  //end with no slash
  res = "/some/path/";  //add slash ending if not provided
  EXPECT_EQ(res, utils::pathify(path) );


  path = "/some/path//"; //end with two slashes
  res = "/some/path//";  //two slashes is valid directory path
  EXPECT_EQ(res, utils::pathify(path) );

}


TEST(utils, trim) {

  string word = "", pat = "", res = "";

  word = " hello ";
  res = "hello";
  EXPECT_EQ(res, utils::trim(word, pat) );

  word = " hello  world   ";
  res = "hello  world";
  EXPECT_EQ(res, utils::trim(word, pat) );

}


TEST(utils, get_base) {

  string word = "", res = "";

  word = "";
  res = "";
  EXPECT_EQ(res, utils::get_base(word) );


  word = "some/directory/path1/";
  res = "path1";
  EXPECT_EQ(res, utils::get_base(word) );


  word = "some/directory/path2";
  res = "path2";
  EXPECT_EQ(res, utils::get_base(word) );

  //TODO - FIX ME
  word = "some/path3//";
  res = "path3";
  EXPECT_EQ(res, utils::get_base(word) );

  word = "path4/";
  res = "path4";
  EXPECT_EQ(res, utils::get_base(word) );


  word = "/path5";
  res = "path5";
  EXPECT_EQ(res, utils::get_base(word) );

  word = "path";
  res = "path";
  EXPECT_EQ(res, utils::get_base(word) );

}



int main(int argc, char **argv) {
  ::testing::InitGoogleTest( &argc, argv );
  return RUN_ALL_TESTS();
}
