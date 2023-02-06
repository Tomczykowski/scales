#include <exception>
#include <gtest/gtest.h>
#include "Scale.h"
#include <sstream>

static void AreEqual (double expected, double actual, double delta){
    ASSERT_TRUE(abs(expected - actual) < delta);
}

TEST(ScalesUnitTest, getters) {
    Scale s(10.0, "g");
    ASSERT_EQ(s.getWeight(), 10.0);
    ASSERT_EQ(s.getUnit(), "g");
}

TEST(ScalesUnitTest, setters) {
    Scale s(10.0, "dag");
    s.setUnit("g");
    s.setWeight(1.0);
    ASSERT_EQ(s.getWeight(), 1.0);
    ASSERT_EQ(s.getUnit(), "g");
}

TEST(ScalesUnitTest, operatorPlusDouble) {
    Scale s(10.0, "g");
    s = s+10.0;
    AreEqual(s.getWeight(), 20.0, 0.0001);
}

TEST(ScalesUnitTest, changeUnit) {
    Scale s(1.0, "kg");
    s.changeUnit("g");
    AreEqual(s.getWeight(), 1000.0, 0.0001);
}

TEST(ScalesUnitTest, changeUnit2) {
    Scale s(1.0, "kg");
    s.changeUnit("lb");
    AreEqual(s.getWeight(), 2.20462, 0.0001);
}

TEST(ScalesUnitTest, changeUnit3) {
    Scale s(1.0, "g");
    s.changeUnit("oz");
    AreEqual(s.getWeight(), 0.0352739, 0.0001);
}

TEST(ScalesUnitTest, changeUnit4) {
    Scale s(1.0, "dag");
    s.changeUnit("cwt");
    AreEqual(s.getWeight(), 0.0001968, 0.0001);
}

TEST(ScalesUnitTest, changeUnit5) {
    Scale s(1.0, "oz");
    s.changeUnit("mg");
    AreEqual(s.getWeight(), 28349.5, 0.0001);
}

TEST(ScalesUnitTest, changeUnit6) {
    Scale s(1.0, "oz");
    s.changeUnit("oz");
    AreEqual(s.getWeight(), 1.0, 0.0001);
}

TEST(ScalesUnitTest, getWeightIn1) {
    Scale s(1.0, "kg");
    double a = s.getWeightIn("oz");
    AreEqual(a, 35.2739, 0.0001);
}

TEST(ScalesUnitTest, getWeightIn2) {
    Scale s(1.0, "dag");
    double a = s.getWeightIn("cwt");
    AreEqual(a, 0.0001968, 0.0001);
}

TEST(ScalesUnitTest, getWeightIn3) {
    Scale s(1.0, "lb");
    double a = s.getWeightIn("oz");
    AreEqual(a, 16.0, 0.0001);
}

TEST(ScalesUnitTest, addWeight1) {
    Scale s(1.0, "lb");
    s.addWeight(10.0);
    AreEqual(s.getWeight(), 11.0, 0.0001);
    ASSERT_EQ(s.getUnit(), "lb");
}

TEST(ScalesUnitTest, addWeight2) {
    Scale s(1.0, "cwt");
    s.addWeight(1.0);
    AreEqual(s.getWeight(), 2.0, 0.0001);
    ASSERT_EQ(s.getUnit(), "cwt");
}

TEST(ScalesUnitTest, heavier1) {
    Scale s1(1.0, "cwt");
    Scale s2(1.0, "g");
    auto heavier = s1.heavier(s2);
    ASSERT_EQ(heavier.getUnit(), "cwt");
    AreEqual(heavier.getWeight(), 1.0, 0.0001);
}

TEST(ScalesUnitTest, heavier2) {
    Scale s1(1.1, "dag");
    Scale s2(0.01, "kg");
    auto heavier = s1.heavier(s2);
    ASSERT_EQ(heavier.getUnit(), "dag");
    AreEqual(heavier.getWeight(), 1.1, 0.0001);
}

TEST(ScalesUnitTest, lighter1) {
    Scale s1(1.1, "dag");
    Scale s2(0.01, "kg");
    auto heavier = s1.lighter(s2);
    ASSERT_EQ(heavier.getUnit(), "kg");
    AreEqual(heavier.getWeight(), 0.01, 0.0001);
}

TEST(ScalesUnitTest, lighter2) {
    Scale s1(1.1, "cwt");
    Scale s2(10, "g");
    auto heavier = s1.lighter(s2);
    ASSERT_EQ(heavier.getUnit(), "g");
    AreEqual(heavier.getWeight(), 10, 0.0001);
}

TEST(ScalesUnitTest, operatorPlus1) {
    Scale s1(1.1, "cwt");
    Scale s2(10000, "g");
    Scale sum = s1 + s2;
    ASSERT_EQ(sum.getUnit(), "cwt");
    AreEqual(sum.getWeight(), 1.296841, 0.0001);
}

TEST(ScalesUnitTest, operatorPlus2) {
    Scale s1(1.1, "dag");
    Scale s2(10, "g");
    Scale sum = s1 + s2;
    ASSERT_EQ(sum.getUnit(), "dag");
    AreEqual(sum.getWeight(), 2.1, 0.0001);
}

TEST(ScalesUnitTest, operatorMinus1) {
    Scale s1(1.1, "dag");
    Scale s2(10, "g");
    Scale sum = s1 - s2;
    ASSERT_EQ(sum.getUnit(), "dag");
    AreEqual(sum.getWeight(), 0.1, 0.0001);
}

TEST(ScalesUnitTest, operatorMinus2) {
    Scale s1(1.1, "dag");
    Scale s2(1.1, "dag");
    Scale sum = s1 - s2;
    ASSERT_EQ(sum.getUnit(), "dag");
    AreEqual(sum.getWeight(), 0, 0.0001);
}

TEST(ScalesUnitTest, operatorPlusDouble1) {
    Scale s1(1.1, "dag");
    Scale sum = s1 + 10;
    ASSERT_EQ(sum.getUnit(), "dag");
    AreEqual(sum.getWeight(), 11.1, 0.0001);
}

TEST(ScalesUnitTest, operatorMinusDouble1) {
    Scale s1(1.1, "dag");
    Scale sum = s1 - 0;
    ASSERT_EQ(sum.getUnit(), "dag");
    AreEqual(sum.getWeight(), 1.1, 0.0001);
}

TEST(ScalesUnitTest, operatorMinusDouble2) {
    Scale s1(1.1, "dag");
    Scale sum = s1 - 2;
    ASSERT_EQ(sum.getUnit(), "dag");
    AreEqual(sum.getWeight(), 0, 0.0001);
}

TEST(ScalesUnitTest, operatorPlusEq) {
    Scale s1(1.1, "dag");
    Scale s2(100, "g");
    s1+=s2;
    ASSERT_EQ(s1.getUnit(), "dag");
    AreEqual(s1.getWeight(), 11.1, 0.0001);
}

TEST(ScalesUnitTest, operatorMinusEq1) {
    Scale s1(10.1, "dag");
    Scale s2(100, "g");
    s1-=s2;
    ASSERT_EQ(s1.getUnit(), "dag");
    AreEqual(s1.getWeight(), 0.1, 0.0001);
}

TEST(ScalesUnitTest, operatorMinusEq2) {
    Scale s1(1.1, "dag");
    Scale s2(100, "g");
    s1-=s2;
    ASSERT_EQ(s1.getUnit(), "dag");
    AreEqual(s1.getWeight(), 0, 0.0001);
}

TEST(ScalesUnitTest, operatorPlusEqDouble) {
    Scale s1(1.1, "cwt");
    s1+=5;
    ASSERT_EQ(s1.getUnit(), "cwt");
    AreEqual(s1.getWeight(), 6.1, 0.0001);
}

TEST(ScalesUnitTest, operatorMinusEqDouble1) {
    Scale s1(10.4, "dag");
    s1-=0.5;
    ASSERT_EQ(s1.getUnit(), "dag");
    AreEqual(s1.getWeight(), 9.9, 0.0001);
}

TEST(ScalesUnitTest, operatorMinusEqDouble2) {
    Scale s1(1.1, "dag");
    s1-=1.12;
    ASSERT_EQ(s1.getUnit(), "dag");
    AreEqual(s1.getWeight(), 0, 0.0001);
}

TEST(ScalesUnitTest, operatorEq) {
    Scale s1(1.1, "dag");
    Scale s2(1.1, "dag");
    ASSERT_TRUE(s1 == s2);
}

TEST(ScalesUnitTest, operatorEqDouble) {
    Scale s1(1.1, "dag");
    ASSERT_TRUE(s1 == 1.1);
}

TEST(ScalesUnitTest, operatorEqString) {
    Scale s1(1.1, "dag");
    ASSERT_TRUE(s1 == "dag");
}

TEST(ScalesUnitTest, operatorGrater) {
    Scale s1(1.1, "kg");
    Scale s2(1.1, "dag");
    ASSERT_TRUE(s1 > s2);
}

TEST(ScalesUnitTest, operatorSmaller) {
    Scale s1(1.1, "g");
    Scale s2(1.1, "cwt");
    ASSERT_TRUE(s1 < s2);
}

TEST(ScalesUnitTest, operatorGraterDouble) {
    Scale s1(1.1, "kg");
    ASSERT_TRUE(s1 > 0.1);
}

TEST(ScalesUnitTest, operatorSmallerDouble) {
    Scale s1(1.1, "g");
    ASSERT_TRUE(s1 < 2);
}

TEST(ScalesUnitTest, operatorOstream)
{
    stringstream test;
    test.str("");
    Scale s(10.0, "dag");
    test << s;
    ASSERT_EQ(test.str(), "10[dag]");
}

TEST(ScalesUnitTest, operatorIstream)
{
    stringstream test;
    test.str("10.0 dag");
    Scale s;
    test >> s;
    ASSERT_EQ(s.getWeight(), 10.0);
    ASSERT_EQ(s.getUnit(), "dag");
}

TEST(ScalesUnitTest, divisionBy0)
{
    Scale s(10.0, "dag");
    ASSERT_THROW(s/0, std::logic_error);
}

TEST(ScalesUnitTest, InvalidUnit)
{
    ASSERT_THROW(Scale s(10.0, "kilometers"), std::logic_error);
}
