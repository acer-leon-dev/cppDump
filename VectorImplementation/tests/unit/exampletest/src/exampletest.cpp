// 
// Most of the following code was produced using generative artificial intelligence.
// 

#include <gtest/gtest.h>
#include <vectorimpl/vector.hpp>
#include <algorithm>
#include <utility>

// Test fixture for dev::vector
class VectorTest : public ::testing::Test {
protected:
    dev::vector<int> vec;
};

// Test Rule of 5
TEST_F(VectorTest, RuleOfFive) {
    dev::vector<int> other = {1, 2, 3};
    dev::vector<int> copy(other);
    EXPECT_EQ(copy.size(), 3);
    EXPECT_EQ(copy[1], 2);
    
    dev::vector<int> moved(std::move(copy));
    EXPECT_EQ(moved.size(), 3);
    EXPECT_EQ(moved[1], 2);
    
    dev::vector<int> assigned = moved;
    EXPECT_EQ(assigned.size(), 3);
}

// Test fill constructor
TEST_F(VectorTest, FillConstructor) {
    dev::vector<int> filled(10, 99);
    EXPECT_EQ(filled.size(), 10);
    EXPECT_EQ(filled[0], 99);
    EXPECT_EQ(filled[9], 99);
}

// Test initializer list constructor
TEST_F(VectorTest, InitializerListConstructor) {
    dev::vector<int> initListVec = {10, 20, 30, 40};
    EXPECT_EQ(initListVec.size(), 4);
    EXPECT_EQ(initListVec[0], 10);
    EXPECT_EQ(initListVec[3], 40);
}

// Test initializer list assignment
TEST_F(VectorTest, InitializerListAssignment) {
    vec = {1, 2, 3};
    vec = {100, 200, 300, 400};
    EXPECT_EQ(vec.size(), 4);
    EXPECT_EQ(vec[0], 100);
    EXPECT_EQ(vec[3], 400);
}

// Test at method
TEST_F(VectorTest, AtMethod) {
    vec = {10, 20, 30};
    EXPECT_EQ(vec.at(0), 10);
    EXPECT_EQ(vec.at(2), 30);
    EXPECT_THROW(vec.at(5), std::out_of_range);
}

// Test operator[]
TEST_F(VectorTest, BracketOperator) {
    vec = {5, 10, 15};
    EXPECT_EQ(vec[0], 5);
    EXPECT_EQ(vec[2], 15);
    vec[1] = 99;
    EXPECT_EQ(vec[1], 99);
}

// Test front and back
TEST_F(VectorTest, FrontAndBack) {
    vec = {100, 200, 300};
    EXPECT_EQ(vec.front(), 100);
    EXPECT_EQ(vec.back(), 300);
    vec.back() = 999;
    EXPECT_EQ(vec.back(), 999);
}

// Test data method
TEST_F(VectorTest, DataMethod) {
    vec = {7, 14, 21};
    int* ptr = vec.data();
    EXPECT_EQ(ptr[0], 7);
    EXPECT_EQ(ptr[1], 14);
}

// Test empty method
TEST_F(VectorTest, EmptyMethod) {
    EXPECT_TRUE(vec.empty());
    vec.push_back(1);
    EXPECT_FALSE(vec.empty());
}

// Test size method
TEST_F(VectorTest, SizeMethod) {
    vec = {1, 2, 3};
    EXPECT_EQ(vec.size(), 3);
}

// Test reserve and capacity
TEST_F(VectorTest, ReserveAndCapacity) {
    vec.reserve(50);
    EXPECT_GE(vec.capacity(), 50);
    vec.push_back(1);
    EXPECT_GE(vec.capacity(), 50);
}

// Test clear
TEST_F(VectorTest, Clear) {
    vec = {1, 2, 3, 4};
    vec.clear();
    EXPECT_TRUE(vec.empty());
    EXPECT_EQ(vec.size(), 0);
}

// Test insert
TEST_F(VectorTest, Insert) {
    vec = {1, 2, 4};
    vec.insert(vec.begin() + 2, 3);
    EXPECT_EQ(vec[2], 3);
    EXPECT_EQ(vec.size(), 4);
}

// Test erase
TEST_F(VectorTest, Erase) {
    vec = {10, 20, 30, 40};
    vec.erase(vec.begin() + 1);
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[1], 30);
}

// Test push_back
TEST_F(VectorTest, PushBack) {
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
}

// Test pop_back
TEST_F(VectorTest, PopBack) {
    vec.push_back(10);
    vec.push_back(20);
    vec.pop_back();
    EXPECT_EQ(vec.size(), 1);
    EXPECT_EQ(vec.back(), 10);
}

// Additional pop_back tests
TEST_F(VectorTest, MultiplePopBack) {
    vec = {1, 2, 3, 4, 5};
    vec.pop_back();
    vec.pop_back();
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec.back(), 3);
}
