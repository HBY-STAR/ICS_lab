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

//代码托管在GitHub上，可访问：https://github.com/HBY-STAR/ICS_lab/tree/master/datalab-handout

int bitXor(int x, int y)
{
  /*
  思路：
  要用~和&运算符实现^运算，可以先通过x&y运算找出
  x与y同时为1的位；然后再通过~x&~y运算找出x与y的
  同时为0的位；而^运算只是相同位赋0而不同位赋1，
  故最后只需要让上面两个运算找到的位都为0，而其他
  位都为1，即让两个运算都取~之后再取&。
  */
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
  /*
  思路：
  补码int型的最小值即让最高位取1而其他位取0，故很
  容易可以想到让0x00000001左移31位得到结果。
  */
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
  /*
  思路：
  本题的关键在于观察Tmax与其他值有什么不同，我个人的发现是
  Tmax^(Tmax+1)==0xffffffff。然而具有该特点的还有-1，故之
  后还需要想办法排除 -1 的干扰。而对于0xffffffff，将其与自
  身取异或可以得到0。故下面先构造一个all_bits==0xffffffff，
  然后通过all_bits ^ (x ^ (x_add_1))来检查x是否为Tmax或-1。
  之后的 ...|(!x_add_1))则排除了-1的干扰。最后的取反运算则
  将整个式子的值映射到0和1。注：后面还有很多在最后进行取反运
  算的案例，皆为上述作用，不再赘述。
  */
  int all_bits = 1;
  int x_add_1 = x + 1;
  all_bits = ~all_bits + 1;
  return !((all_bits ^ (x ^ (x_add_1))) | (!x_add_1));
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
  /*
  思路：
  对于本题首先应该构造出0xAAAAAAAA，然而只能用255以内的常量，
  考虑到要使操作最少，故取常量为170并执行以下的移位操作，之后
  只需要检查x对应于temp为1的位是否也为1，即(temp & x) ^ temp
  操作。
  */
  int temp = 170;
  temp = temp | (temp << 8);
  temp = temp | (temp << 16);
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
  /*
  思路：
  通过对于int型补码的观察即可得到取负操作即为取反加一。
  */
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
  /*
  思路：
  本题的关键在于实现比较操作，想到可以将比较操作转化为一个减法
  和检查一个数是否为非负的操作。x-min即x + (~min + 1)，同理
  max-x即max + (~x + 1)。若x满足条件则：
  式子~((~(x + (~min + 1))) & (~(max + (~x + 1))))最高位为0。
  该式子如此复杂是因为考虑到了x为正时溢出的情况，保证x为正且溢出时
  式子最高位为1。而右面的式子...| (x)则排除了负数的干扰。而最后的
  移位加一以及取反操作只是对于302行result的最高位的检查。
  */
  int min = 48;
  int max = 57;
  int result;
  result = (~((~(x + (~min + 1))) & (~(max + (~x + 1))))) | (x); //仅仅将最高位作为检查条件
  result = (result >> 31) + 1;                                   //检查最高位
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
  /*
  思路：
  先通过两次取反运算和一次取负运算将x转化为：
  1.当x!=0时有turn==0x00000000
  2.当x==0时有turn==0xffffffff
  而这里的turn意为转换，
  1.当turn==0x00000000时，有0^z==z;
  2.当turn==0xffffffff时，有(y^z)^z==y;
  从而实现了式子的值在两个数之间转换的效果。
  */
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
  /*
  思路：
  要比较两个数的大小并不容易，但是检查一个数是否为非负却
  非常容易，只需要检查最高位即可。故可以将x<=y转化为
  y-x>=0。而y-x即y + (~x+1)。然而此时又存在了溢出的
  问题，故需要排除一些情况。注意到当x与y不同号时才有可
  能出现溢出，故用(~(y+(~x+1))) & (~(x^y))来保证当x与y
  同号即不出现溢出的情况下上面式子能给出正确的结果。之后
  再补充上x与y不同号时的情况，注意到当y为正且x为负时式子
  的值应该为1，故有后面的...| ((~y) & (x))。这样一来整个
  式子就可以给出正确的结果了。而最后的移位加一以及取反操作
  只是对于349行result的最高位的检查。
  */
  int result;
  result = ((~(y + (~x + 1))) & (~(x ^ y))) | ((~y) & (x)); //仅仅用最高位作为检查条件
  result = !((result >> 31) + 1);                           //检查最高位
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
  /*
  思路：
  逻辑非即当x==0时返回0，当x!=0时返回1。
  此时关键在于观察0x00000000的特征。而
  0最显著的特征便是其取负后为其本身。但
  由于补码的特殊性，0x80000000也具有同
  样的特征，故需要再对x首位为1的情形进行
  排除。即操作result = result | x;
  */
  int result = (~x + 1) ^ x;
  result = result | x;           //排除0x80000000的情形
  result = ((result >> 31) + 1); //检查最高位
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
  /*
  思路：
  通过下面获取abs的操作将上述问题转化为求abs最高位的位置坐标
  由于只能进行位运算，故要找到最高位很困难。在这里我通过填充
  最高位之后的所有位都为1再进行计数整个数的1的数量来获取最高
  位的位置。然而这样做的话就要对32位都进行检查，如何节省操作
  又成了难题。首先注意到填充通过指数递增的形式是最省操作的，
  然后想到每次检查1位的话要32次，而每次检查2位只用16次，每次
  检查3位只用11次。经过不断优化最终找到了每次检查3位的操作，
  将总的操作优化到了80。
  注：第一次找到了100多个操作的方法，是用每次检查1位。然后又
  开始找每次检查2位的编码方法，虽然找到了编码方法，但最终要用
  94个操作，还是不行。又开始探索每次检查3位的编码方法，找了很
  久终于找到了，如下代码所示，这一次把操作直接减小到了80。然而
  之后去找更高位的时候发现也很困难，最后也是考虑到不能一直耗在
  这题上，就没再进行探索。
  */
  int first_bit = x >> 31;                //提取x的最高位，此时应注意是算术右移。
  int temp = 7;                           // 0x00000007
  int result = 1;                         //可以看做一个计数器
  int abs = (first_bit & ((~x) ^ x)) ^ x; //为负则取反，为正则不变。

  //进行位填充，将最高位之后的位全部填充上0，此处用指数递增的方式减少操作。
  abs = (abs) | (abs >> 1);
  abs = (abs) | (abs >> 2);
  abs = (abs) | (abs >> 4);
  abs = (abs) | (abs >> 8);
  abs = (abs) | (abs >> 16);

  //每次检查3位中1的数量。
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
  /*
  思路：
  首先排除掉NaN的uf，之后对于规格化的uf，要使其乘以2，只需要调整
  阶码位，让阶码位加一即可。然后对于非规格化的uf，要使其乘以2需要
  注意到非规格数会溢出到规格化数的情况。若小数位左移1位不会溢出，
  那么直接让其他位不变，调整小数位即可。若溢出到规格化数，在进行小
  数位左移1位且其他位不变的操作之后还需要设置阶码值为1。
  */
  unsigned ninth_bit = 1 << 23;                                               // 0x00800000
  unsigned tenth_bit = ninth_bit >> 1;                                        // 0x00400000
  unsigned _1_to_9_bits = 4286578688;                                         // 0xff800000
  unsigned test_uf_exp = uf >> 23;                                            //找exp的8位并置于最右侧
  unsigned test_bit = 255;                                                    // 0x000000ff
  unsigned test_bit_2 = 254;                                                  // 0x000000fe
  unsigned frac_mult_2 = (_1_to_9_bits & uf) | ((~_1_to_9_bits) & (uf << 1)); //让小数位左移1位并保持其他位值不变
  if ((test_uf_exp & test_bit) ^ test_bit)
  {
    if (test_uf_exp & test_bit) // 规格化
    {
      return uf + ninth_bit; //阶码位加1
    }
    else // 非规格化
    {
      if (tenth_bit & uf) // 小数位左移1位会溢出
      {
        return frac_mult_2 | ninth_bit; //让阶码位为1
      }
      else // 小数位左移1位不会溢出
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
  /*
  思路：
  由于浮点数不同位有不同的解释方式，此外还存在规格化、非规格化、
  以及NaN的区别，故需要分类进行解码。首先排除NaN，然后由于非规
  格化数绝对值都小于1，也很好排除。最后在规格化中，先排除掉阶码
  位过大过小的情况，留下可以表示的情况，再根据浮点数的表示规则
  进行操作即可。
  */
  unsigned _9_bit = 8388608;                    // 0x00800000
  unsigned _9_to_32_bits = 16777215;            // 0x00ffffff
  unsigned exp = uf >> 23;                      //取exp位并置于最右侧
  unsigned last_8_bits = 255;                   // 0x000000ff
  unsigned _M_ = (_9_bit | uf) & _9_to_32_bits; //小数位的值
  unsigned _s_ = 2147483648;                    //符号位的值
  unsigned _E_;                                 // exp位的值
  unsigned result;
  exp = (exp & last_8_bits); //取exp位并置于最右侧并使其他位为0
  _s_ = (_s_ & uf) >> 31;    //取符号位，注意是算术右移

  if (exp ^ last_8_bits)
  {
    if (exp) // 规格化
    {
      if (exp > 157) //阶码位过大，超过int可以表示的范围
      {
        return -2147483648;
      }
      else if (exp < 127) //阶码位小于0，结果的绝对值必然小于1，故直接置0
      {
        return 0;
      }
      else //阶码位合适，在int型可以表示的范围内
      {
        _E_ = exp - 127;
        if (_E_ >= 23) //需要将小数位左移的情况
        {
          result = _M_ << (_E_ - 23);
        }
        else //需要将小数位右移的情况
        {
          result = _M_ >> (23 - _E_);
        }
        if (_s_) //符号位不为0，结果取负
        {
          return (~result + 1);
        }
        else //符号位为0，结果不变
        {
          return result;
        }
      }
    }
    else // 非规格化
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
  /*
  此代码一遍过！
  思路：由于浮点数表示的范围比较容易确定，故可以先排除较大的和较小的数，
  直接通过比较即可。对于非规格化的数，由于返回的是2的x次方，故最后的位
  级表示只有最后的23位里面含有一个1，且从左到右依次为2^(-128),2^(-129)...
  故构造了一个_9_bit来进行移位得到最后的值；对于规格化的数，由于小数位和
  符号位均为0，故只需要让x+127就得到了浮点exp表示的位。之后再左移23位即
  为浮点数表示的2^x的值。
  */
  int _E_ = x;
  int INF = 2139095040; //定义正无穷
  int _9_bit = 8388608; // 0x00800000
  if (_E_ > 128)        //过大
  {
    return INF;
  }
  else if (_E_ < -150) //过小
  {
    return 0;
  }
  else if ((_E_ >= -150) && (_E_ < -127)) //在非规格化表示范围内
  {
    return (_9_bit >> (-127 - _E_));
  }
  else //在规格化表示范围内
  {
    return ((_E_ + 127) << 23);
  }
}
/*
unsigned floatPower2(int x)
{
  //注：一开始看错题目了以为要实现2*x。
  //    下面的代码实现了和上面一个题目相反的
  //    操作，即int转换成float。代码没有测试
  //    过，但大致思路应该是对的。在实现完之后
  //    才发现看错题目了......
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