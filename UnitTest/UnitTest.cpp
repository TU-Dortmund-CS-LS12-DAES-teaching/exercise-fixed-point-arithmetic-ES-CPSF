#include <bitset>
#include <iostream>

#include <gtest/gtest.h>

#include "../FixedPoint/FixedPoint.cpp"

TEST(Positive, Print1) {
  std::ostringstream Stream;
  Fixp<int8_t, 2> A(7);

  Stream << A;
  std::string Str = Stream.str();
  const char *ChrA = Str.c_str();
  EXPECT_TRUE(strcmp(ChrA, "1.750") == 0);
  std::cout << "A: " << A << "\n";
}

TEST(Positive, Print2) {
  std::ostringstream Stream;
  Fixp<int16_t, 4> A(14);

  Stream << A;
  std::string Str = Stream.str();
  const char *ChrA = Str.c_str();
  EXPECT_TRUE(strcmp(ChrA, "0.87500") == 0);
  std::cout << "A: " << A << "\n";
}

TEST(Positive, Print3) {
  std::ostringstream Stream;
  Fixp<int16_t, 3> A(0b00000001);

  Stream << A;
  std::string Str = Stream.str();
  const char *ChrA = Str.c_str();
  EXPECT_TRUE(strcmp(ChrA, "0.12500") == 0);
  std::cout << "A: " << A << "\n";
}

TEST(Negative, Print1) {
  std::ostringstream Stream;
  Fixp<int8_t, 3> A(0b11111111);

  Stream << A;
  std::string Str = Stream.str();
  const char *ChrA = Str.c_str();
  EXPECT_TRUE(strcmp(ChrA, "-0.125") == 0);
  std::cout << "A: " << A << "\n";
}

TEST(Negative, Print2) {
  std::ostringstream Stream;
  Fixp<int8_t, 2> A(0b11111100);

  Stream << A;
  std::string Str = Stream.str();
  const char *ChrA = Str.c_str();
  EXPECT_TRUE(strcmp(ChrA, "-1.0") == 0);
  std::cout << "A: " << A << "\n";
}


TEST(Positive, Print4) {
  std::ostringstream Stream;
  Fixp<int8_t, 4> A(0b00000010);

  Stream << A;
  std::string Str = Stream.str();
  const char *ChrA = Str.c_str();
  std::cout << "A: " << A << "\n";
  EXPECT_TRUE(strcmp(ChrA, "0.125") == 0);
}

TEST(Positive, IntVal) {
  Fixp<int8_t, 2> A(7);
  std::cout << "\nA: " << A << "\n";
  int8_t AInt = A.getIntVal();
  EXPECT_TRUE(AInt == 1);
}

TEST(Negative, IntVal) {
  Fixp<int8_t, 2> A(0b11111111);
  std::cout << "A: " << A << "\n";
  int8_t AInt = A.getIntVal();
  std::cout << "AInt: " << +AInt << "\n";
  EXPECT_TRUE(AInt == 0);
}

TEST(Positive, FracVal) {
  Fixp<int16_t, 2> A(0b111);
  std::cout << "A: " << A << "\n";
  int16_t AFrac = A.getFracVal();
  std::cout << "AFrac: " << AFrac << "\n";
  EXPECT_TRUE(AFrac == 3);
}

TEST(Negative, FracVal) {
  Fixp<int16_t, 2> A(0b111);
  std::cout << "A: " << A << "\n";
  int16_t AFrac = A.getFracVal();
  std::cout << "AFrac: " << AFrac << "\n";
  EXPECT_TRUE(AFrac == 3);
}

TEST(Positive, Equal) {
  Fixp<int8_t, 2> A(2);
  Fixp<int8_t, 2> B(2);
  Fixp<int8_t, 2> C(3);
  Fixp<int8_t, 2> D(3);
  EXPECT_TRUE(A == B);
  EXPECT_FALSE(A == C);
  EXPECT_FALSE(A == D);
  EXPECT_TRUE(D == C);
}

TEST(Negative, Equal) {
  Fixp<int8_t, 2> A(-2);
  Fixp<int8_t, 2> B(-2);
  Fixp<int8_t, 2> C(-3);
  Fixp<int8_t, 2> D(-3);
  EXPECT_TRUE(A == B);
  EXPECT_FALSE(A == C);
  EXPECT_FALSE(A == D);
  EXPECT_TRUE(D == C);
}

TEST(Positive, UnEqual) {
  Fixp<int8_t, 2> A(2);
  Fixp<int8_t, 2> B(2);
  Fixp<int8_t, 2> C(3);
  Fixp<int8_t, 2> D(3);
  EXPECT_TRUE(A != C);
  EXPECT_FALSE(A != B);
  EXPECT_TRUE(A != D);
  EXPECT_FALSE(D != C);
}

TEST(Negative, UnEqual) {
  Fixp<int8_t, 2> A(-2);
  Fixp<int8_t, 2> B(-2);
  Fixp<int8_t, 2> C(-3);
  Fixp<int8_t, 2> D(-3);
  EXPECT_TRUE(A != C);
  EXPECT_FALSE(A != B);
  EXPECT_TRUE(A != D);
  EXPECT_FALSE(D != C);
}

TEST(Positive, Addition) {
  Fixp<int8_t, 2> A(2);
  Fixp<int8_t, 2> B(2);
  Fixp<int8_t, 2> C(3);
  Fixp<int8_t, 2> D(4);
  Fixp<int8_t, 2> E(5);
  Fixp<int8_t, 2> ApB = A + B;
  Fixp<int8_t, 2> ApC = A + C;
  EXPECT_TRUE(ApB == D);
  EXPECT_TRUE(ApC == E);
}

TEST(Negative, Addition) {
  Fixp<int8_t, 2> A(0b11111111);
  Fixp<int8_t, 2> B(0b11111110);
  Fixp<int8_t, 2> C(0b00000001);
  Fixp<int8_t, 2> D(0b11111101);
  Fixp<int8_t, 2> E(0);
  Fixp<int8_t, 2> ApB = A + B;
  Fixp<int8_t, 2> ApC = A + C;
  EXPECT_TRUE(ApB == D);
  std::cout << "ApB: " << ApB << ", D: " << D << "\n";
  EXPECT_TRUE(ApC == E);
  std::cout << "Apc: " << ApC << "\n";
}

TEST(Positive, Substraction) {
  Fixp<int8_t, 2> A(10);
  Fixp<int8_t, 2> B(2);
  Fixp<int8_t, 2> C(5);
  Fixp<int8_t, 2> D(8);
  Fixp<int8_t, 2> E(5);
  Fixp<int8_t, 2> AmB = A - B;
  Fixp<int8_t, 2> AmC = A - C;
  Fixp<int8_t, 2> AmD = A - D;
  EXPECT_TRUE(AmB == D);
  EXPECT_TRUE(AmC == E);
  EXPECT_TRUE(AmD == B);
}

TEST(Negative, Substraction) {
  Fixp<int8_t, 2> A(0b11111100); // -1.0
  Fixp<int8_t, 2> B(0b11111101); // -0.75
  Fixp<int8_t, 2> C(0b11111100); // -1.0
  Fixp<int8_t, 2> D(0b11111111); // -0.25
  Fixp<int8_t, 2> E(0);
  Fixp<int8_t, 2> AmB = A - B; // -1 - -0.75 = -0.25
  Fixp<int8_t, 2> AmC = A - C; // -1 - -1 = 0
  Fixp<int8_t, 2> AmD = A - D; // -1 - -0.25 =  -0.75
  EXPECT_TRUE(AmB == D);
  EXPECT_TRUE(AmC == E);
  EXPECT_TRUE(AmD == B);
}

TEST(Positive, Multiplication) {
  Fixp<int16_t, 2> A(0b111);
  Fixp<int16_t, 2> B(0b10);
  Fixp<int16_t, 4> C(0b1110);
  Fixp<int16_t, 4> AmB = A * B;
  std::cout << "\nAmB: " << AmB << ", A: " << A << ", B: " << B << " ,C: " << C
            << "\n";
  EXPECT_TRUE(AmB == C);
}

TEST(Negative, Multiplication) {
  Fixp<int8_t, 2> A(0b11111111); // -0.25
  Fixp<int8_t, 2> B(0b11111110); // -0.5
  Fixp<int8_t, 4> C(0b00000010); // 0.75
  Fixp<int8_t, 4> AmB = A * B;
  std::bitset<8> X(AmB.Value);
  std::cout << "AmB: " << X << "\n";
  std::cout << "AmB: " << AmB << ", A: " << A << ", B: " << B << " ,C: " << C
            << "\n";
  EXPECT_TRUE(AmB == C);
}

TEST(Positive, Division) {
  Fixp<int16_t, 2> A(0b111);
  Fixp<int16_t, 2> B(0b10);
  Fixp<int16_t, 4> C(20);
  Fixp<int16_t, 0> D(0b11);
  Fixp<int16_t, 2> E(5);
  Fixp<int16_t, 2> F(0b100);
  Fixp<int16_t, 0> AdB = A / B;
  std::cout << "\nA: " << A << "/ B " << B << "= " << AdB << " , check: " << D
            << "\n";
  Fixp<int16_t, 2> CdE = C / E;

  std::cout << "\nC: " << C << "/ E " << E << "= " << CdE << " , check: " << F
            << "\n";
  EXPECT_TRUE(AdB == D);
  EXPECT_TRUE(CdE == F);
}
