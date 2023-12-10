#include <cassert>
#include <cstdint>
#include <iostream>
#include <istream>
#include <tgmath.h>

#include "../include/TypeChecker.h"

// https://inst.eecs.berkeley.edu/~cs61c/sp06/handout/fixedpt.html
/**
 * @brief Implementation of a fixed floating point data type.
 *
 * @tparam T used Type for representation. Must be of: int[8,16,32,64]_t type.
 * @tparam FracBits Number of bits used to represent the part smaller 0.
 */
template <class T, T FracBits> class Fixp {
public:
  T Value = 0;

  Fixp(T In) { 
    //get a number in and check if its either of size 8,16,32 or 64 if not theres an error
    //if input number is correct and of a correct size, Value = the input value
    int8_t TypeSanityCheck = false;
    TypeSanityCheck += std::is_same<T, int8_t>::value;
    TypeSanityCheck += std::is_same<T, int16_t>::value;
    TypeSanityCheck += std::is_same<T, int32_t>::value;
    TypeSanityCheck += std::is_same<T, int64_t>::value;
    assert(TypeSanityCheck == 1);
    assert(sizeof(T) * 8 > FracBits);
    Value = In;
  }

  /**
   * @brief Get the Portion of the fixed point before the ".", bianry encoded.
   *        This Value is also the ceiling function (integer rounding) of the
   *        fixed point.
   *         kriege die integer-Zahl vor dem komma, in binary
            falls Value >= 0, dann shifte die zahl um die Anzahl an Stellen nach dem komma nach rechts
            also 01010.000 => 00001010
            falls Value negativ: multipliziere mit -1 und verschiebe dann um Fracbits um Integer wert zu bekommen
    * @return T
   */
  inline T getIntVal() {
    return (Value >= 0) ? (Value >> FracBits) : (Value * -1) >> FracBits;
  }

  /**
   * @brief Get the Portion of the fixed point behind the ".", binary encoded.
   *        die Zahl hinter dem komma bekommen
            01010.000 => (00001.010)<<3 = 01010.000^01010.00
   * @return T
   */
  T getFracVal() {
    return ((Value >> FracBits) << FracBits) ^ Value;
  }

  /**
   * @brief Summation of two Fixed Points.
   *        In case two fixed points with different FracBits are added,
   *        The resulting fixed point will use the higher FracBits.
   *
   * @tparam TIn
   * @tparam FracBitsIn
   * @param In
   * @return Fixp
   */
  template <class TIn, TIn FracBitsIn>
  Fixp operator+(Fixp<TIn, FracBitsIn> In) {

    //assert(sizeof(T) == sizeof(TIn));

    return Fixp<T,(T)(std::max(FracBitsIn, FracBits))>((T)Value + In.Value);

  
  }
  /*
    template <class TIn, TIn FracBitsIn>
  Fixp<T, (T)((FracBits - FracBitsIn))> operator/(Fixp<TIn, FracBitsIn> In) {
      assert(sizeof(T) == sizeof(TIn));
      return Fixp<T, (T)((FracBits - FracBitsIn))>((T)Value / In.Value);
    }
  */
  /**
   * @brief Substraction of two fixed points.
   *        In case two fixed points with different accuracy are substracted,
   *        The resulting fixed point will use the higher accuracy/FracBits.
   *
   * @tparam TIn
   * @tparam FracBitsIn
   * @param In
   * @return Fixp
   */
  template <class TIn, TIn FracBitsIn>
  Fixp operator-(Fixp<TIn, FracBitsIn> In) {
    /*if(Value<0){
    return Fixp<T,(T)(std::max(FracBitsIn, FracBits))>((T)Value + (In.Value*-1));
    }
  */
    return Fixp<T,(T)(std::max(FracBitsIn, FracBits))>((T)Value - In.Value);
  }

  /**
   * @brief Multiplication of two fixed points.
   *        The resulting fixed point will use the sum of both FracBits.
   *
   * @tparam TIn
   * @tparam FracBitsIn
   * @param In
   * @return Fixp<T, FracBits + FracBitsIn>
   */
  template <class TIn, TIn FracBitsIn>
  Fixp<T, FracBits + FracBitsIn> operator*(Fixp<TIn, FracBitsIn> In) {
    assert(sizeof(T) == sizeof(TIn));
    return Fixp<T, (T)((FracBits + FracBitsIn))>((T)Value * In.Value);
  }

  /**
   * @brief Division of two fixed points.
  *         The resulting fixed point will use the substraction of both FracBits.
   *        Das Ergebnis der Division nutzt die Subtraktion aus den FracBiots
   * @tparam TIn
   * @tparam FracBitsIn
   * @param In
   * @return Fixp<T, (T)((FracBits - FracBitsIn))>
   */
  template <class TIn, TIn FracBitsIn>
  Fixp<T, (T)((FracBits - FracBitsIn))> operator/(Fixp<TIn, FracBitsIn> In) {
    assert(sizeof(T) == sizeof(TIn));
    return Fixp<T, (T)((FracBits - FracBitsIn))>((T)Value / In.Value);
  }

  /**
   * @brief Checking for Value equality.
  *         Can only be used on fixed points of same dataType and accuracy.
   *
   * @param In
   * @return true
   * @return false
   */
  bool const operator==(Fixp In) {
    assert(checkTypes(*this, In));
    return this->Value == In.Value;
  }

  /**
   * @brief Checking for Value inequality.
  *         Can only be used on fixed points of same dataType and accuracy.
   *
   * @param In
   * @return true
   * @return false
   */
  bool const operator!=(Fixp In) {
    assert(checkTypes(*this, In));
    return this->Value != In.Value;
  }

  /**
   * @brief Printfunction for fixed points.
  *         Some digits after the "." may be cut off during printing.
   *
   * @param Os
   * @param In
   * @return std::ostream&
   */
  friend std::ostream &operator<<(std::ostream &Os, const Fixp In) {
    long Pow10 = log10(pow(2, (sizeof(T) * 8))) + 1;
    long IntValue =
        (In.Value >= 0) ? In.Value >> FracBits : (In.Value >> FracBits) + 1;
    long TempValue = In.Value;
    unsigned long FracDec =
        (In.Value >= 0) ? 0 : (pow(2, -((FracBits))) * pow(10, Pow10));
    for (int I = 1; I <= FracBits; I++) {
      bool FracBit = (In.Value >= 0) ? TempValue % 2 : !(TempValue % 2);
      TempValue = TempValue >> 1;
      if (FracBit)
        FracDec += (pow(2, -((FracBits + 1) - I)) * pow(10, Pow10));
    }
    if (In.Value < 0 && IntValue >= 0)
      Os << "-";
    if (FracDec == pow(10, Pow10)) {
      Os << +IntValue + 1 << "."
         << "0";
    } else {
      Os << +IntValue << "." << +FracDec;
    }
    return Os;
  }
};
