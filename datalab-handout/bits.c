/*
 * CS:APP Data Lab
 *
 * <Please put your name and userid here>
 * //   Hou Binyang
 * //   21302010042
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.
 
You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */

#endif
/* Copyright (C) 1991-2018 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 10.0.0.  Version 10.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2017, fifth edition, plus
   the following additions from Amendment 1 to the fifth edition:
   - 56 emoji characters
   - 285 hentaigana
   - 3 additional Zanabazar Square characters */
/* We do not support C11 <threads.h>.  */
// 1
/*
 * bitXor - x^y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y)
{
  return (~(x & y)) & (~((~x) & (~y)));
}
/*
 * tmin - return minimum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void)
{
  int result = 1;
  result = result << 31;
  return result;
}
// 2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x)
{
  int result;
  int check_first_bit = 1;
  check_first_bit = check_first_bit << 31;
  result = ((x + 1) ^ (~x)) | (x & check_first_bit);
  result = !result;
  return result;
}
/*
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x)
{
  int temp = 170;
  temp = temp | (temp << 8) | (temp << 16) | (temp << 24);
  return !((temp & x) ^ temp);
}
/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x)
{
  return (~x + 1);
}
// 3
/*
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x)
{
  int min = 48;
  int max = 57;
  int result;
  result = (~((~(x + (~min + 1))) & (~(max + (~x + 1))))) | (x);
  result = (result >> 31) + 1;
  return result;
}
/*
 * conditional - same as x ? y : z
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z)
{
  int turn = !(!x);
  turn = ~turn + 1;
  return ((turn & (y ^ z)) ^ z);
}
/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y)
{
  int result;
  result = ((~(y + (~x + 1))) & (~(x ^ y))) | ((~y) & (x));
  result = !((result >> 31) + 1);
  return result;
}
// 4
/*
 * logicalNeg - implement the ! operator, using all of
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int logicalNeg(int x)
{
  int result = (~x + 1) ^ x;
  result = result | x;
  result = ((result >> 31) + 1);
  return result;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x)
{
  int first_bit = x >> 31;
  int temp = 7;
  int result = 1;
  int abs = (first_bit & ((~x) ^ x)) ^ x;
  abs = (abs) | (abs >> 1);
  abs = (abs) | (abs >> 2);
  abs = (abs) | (abs >> 4);
  abs = (abs) | (abs >> 8);
  abs = (abs) | (abs >> 16);
  result = result + ((((abs & temp) + 5) >> 2) & abs);
  abs = abs >> 3;
  result = result + ((((abs & temp) + 5) >> 2) & abs);
  abs = abs >> 3;
  result = result + ((((abs & temp) + 5) >> 2) & abs);
  abs = abs >> 3;
  result = result + ((((abs & temp) + 5) >> 2) & abs);
  abs = abs >> 3;
  result = result + ((((abs & temp) + 5) >> 2) & abs);
  abs = abs >> 3;
  result = result + ((((abs & temp) + 5) >> 2) & abs);
  abs = abs >> 3;
  result = result + ((((abs & temp) + 5) >> 2) & abs);
  abs = abs >> 3;
  result = result + ((((abs & temp) + 5) >> 2) & abs);
  abs = abs >> 3;
  result = result + ((((abs & temp) + 5) >> 2) & abs);
  abs = abs >> 3;
  result = result + ((((abs & temp) + 5) >> 2) & abs);
  abs = abs >> 3;
  result = result + ((((abs & temp) + 5) >> 2) & abs);
  return result;
}
// float
/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf)
{
  unsigned ninth_bit = 1 << 23;
  unsigned tenth_bit = ninth_bit >> 1;
  unsigned _1_to_9_bits = 4286578688;
  unsigned test_uf_exp = uf >> 23;
  unsigned test_bit = 255;
  unsigned test_bit_2 = 254;
  unsigned frac_mult_2 = (_1_to_9_bits & uf) | ((~_1_to_9_bits) & (uf << 1));
  if ((test_uf_exp & test_bit) ^ test_bit)
  {
    if (test_uf_exp & test_bit) // nor
    {
      if ((test_uf_exp & test_bit_2) ^ test_bit_2) // exp_not_full
      {
        return uf + ninth_bit;
      }
      else // exp_full
      {
        return uf + ninth_bit;
      }
    }
    else // unnor
    {
      if (tenth_bit & uf) // overflow
      {
        return frac_mult_2 | ninth_bit;
      }
      else // not_overflow
      {
        return frac_mult_2;
      }
    }
  }
  else // NaN
  {
    return uf;
  }
}
/*
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf)
{
  unsigned _9_bit = 8388608;
  unsigned _9_to_32_bits = 16777215;
  unsigned exp = uf >> 23;
  unsigned last_8_bits = 255;
  unsigned _M_ = (_9_bit | uf) & _9_to_32_bits;
  unsigned _s_ = 2147483648;
  unsigned _E_;
  unsigned result;
  exp = (exp & last_8_bits);
  _s_ = (_s_ & uf) >> 31;

  if (exp ^ last_8_bits)
  {
    if (exp) // nor
    {
      if (exp > 157)
      {
        return -2147483648;
      }
      else if (exp < 127)
      {
        return 0;
      }
      else
      {
        _E_ = exp - 127;
        if (_E_ >= 23)
        {
          result = _M_ << (_E_ - 23);
        }
        else
        {
          result = _M_ >> (23 - _E_);
        }
        if (_s_)
        {
          return (~result + 1);
        }
        else
        {
          return result;
        }
      }
    }
    else // unnor
    {
      return 0;
    }
  }
  else // NaN
  {
    return -2147483648;
  }
}
/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatPower2(int x)
{
  int _s_ = -2147483648;
  _s_ = _s_ & x;
  int all_bit = -1;
  int abs = (all_bit & ((~x + 1) ^ x)) ^ x;
  int _E_ = 0;
  int i = abs;
  while (i)
  {
    i = i >> 1;
    _E_ = _E_ + 1;
  }
  int exp = _E_ + 127;
  exp = exp >> 23;
  // int _10_to_32_bits = 8388607;
  int cut_bit = -2147483648;
  cut_bit = cut_bit >> (32 - _E_); // to the _E_ fisrt bit
  int frac = (~cut_bit) & x;
  if (_E_ <= 24)
  {
    frac = (frac << (24 - _E_));
  }
  else
  {
    frac = (frac >> (_E_ - 24));
  }
  int result = _s_ | exp | frac;
  return result;
}
/*
unsigned floatPower2(int x)
{
  int _s_ = -2147483648;
  _s_ = _s_ & x;
  int all_bit = -1;
  int abs = (all_bit & ((~x + 1) ^ x)) ^ x;
  int _E_ = 0;
  int i = abs;
  while (i)
  {
    i = i >> 1;
    _E_ = _E_ + 1;
  }
  int exp = _E_ + 127;
  exp = exp >> 23;
  // int _10_to_32_bits = 8388607;
  int cut_bit = -2147483648;
  cut_bit = cut_bit >> (32 - _E_); // to the _E_ fisrt bit
  int frac = (~cut_bit) & x;
  if (_E_ <= 24)
  {
    frac = (frac << (24 - _E_));
  }
  else
  {
    frac = (frac >> (_E_ - 24));
  }
  int result = _s_ | exp | frac;
  return result;
}
*/
