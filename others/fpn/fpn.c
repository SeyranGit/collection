
extern int printf(char const* const format, ...);  // or do include <stdio.h>


#define EXTRACT_BITS(value, shift, mask) (((value) >> (shift)) & (mask))
#define max(a, b)                        ((a) > (b) ? (a) : (b))
#define min(a, b)                        ((a) < (b) ? (a) : (b))
#define max_attr(a, b, attr)             (a.attr > b.attr ? a : b)
#define max_attr_ptr(a, b, attr)         (a->attr > b->attr ? a : b)
#define min_attr_ptr(a, b, attr)         (a->attr < b->attr ? a : b)


typedef unsigned char u8;
typedef unsigned int  u32;


#define IEEE_754_SIGN32         ((u32)0x00000001)  // 00000000 00000000 00000000 00000001
#define IEEE_754_EXPONENT32     ((u32)0x000000FF)  // 00000000 00000000 00000000 11111111
#define IEEE_754_MANTISSA32     ((u32)0x007FFFFF)  // 00000000 01111111 11111111 11111111
#define IEEE_754_ON_HIDDEN_BIT  ((u32)0x00800000)  // 00000000 10000000 00000000 00000000


typedef struct {
  u8 sign;
  u8 exponent;
  u32 mantissa;
} IEEEFloat;


static void analyze(IEEEFloat *ieee_float, float num) {
  register u32 *pnum = (u32*)(&num);
  ieee_float->sign = (u8)EXTRACT_BITS((*pnum), 31, IEEE_754_SIGN32);
  ieee_float->exponent = (u8)EXTRACT_BITS((*pnum), 23, IEEE_754_EXPONENT32);
  ieee_float->mantissa = (u32)EXTRACT_BITS((*pnum), 0, IEEE_754_MANTISSA32);
  if (ieee_float->exponent != 0) {
    ieee_float->mantissa |= IEEE_754_ON_HIDDEN_BIT;
    ieee_float->exponent -= 127;
  }
}


static float compose(const IEEEFloat *ieee_float) {
  u32 result = (
    ((u32)(ieee_float->sign) << 31) |
    ((u32)(ieee_float->exponent + 127) << 23) | 
    ((u32)(ieee_float->mantissa & IEEE_754_MANTISSA32))
  );
  return *((float*)(&result));
}


static u32 perform_operation(IEEEFloat *n1, IEEEFloat *n2, u8 exp, char op) {
  register u32 max_mantissa = n1->mantissa;
  register u32 min_mantissa = n2->mantissa;
  if (n1->exponent != n2->exponent) {
    max_mantissa = max_attr_ptr(n1, n2, exponent)->mantissa;
    min_mantissa = (
      min_attr_ptr(n1, n2, exponent)->mantissa >> (
        exp - min(n1->exponent, n2->exponent)
      )
    );
  }  
  return (op == '+') ? (max_mantissa + min_mantissa) : (max_mantissa - min_mantissa);
}


static void normalize(IEEEFloat *ieee_float) {
  while ((ieee_float->mantissa < 0x00800000) && (ieee_float->exponent > 0)) {
    ieee_float->mantissa <<= 1;
    ieee_float->exponent--;
  }
  while (ieee_float->mantissa >= 0x01000000) {
    ieee_float->mantissa >>= 1;
    ieee_float->exponent++;
  }
}


static float ieee_add(float num1, float num2) {
  IEEEFloat ieee_fnum1;
  IEEEFloat ieee_fnum2;
  IEEEFloat result;
  analyze(&ieee_fnum1, num1);
  analyze(&ieee_fnum2, num2);
  result.exponent = max(ieee_fnum1.exponent, ieee_fnum2.exponent);
  if (ieee_fnum1.sign == ieee_fnum2.sign) {
    result.sign = ieee_fnum1.sign;
    result.mantissa = (
      perform_operation(
        &ieee_fnum1, 
        &ieee_fnum2, 
        result.exponent, '+'
      )
    );
  } else {
    result.sign = max_attr(ieee_fnum1, ieee_fnum2, mantissa).sign;
    result.mantissa = (
      perform_operation(
        &ieee_fnum1, 
        &ieee_fnum2, 
        result.exponent, '-'
      )
    );
  }
  normalize(&result);
  return compose(&result);
}


static float ieee_sub(float num1, float num2) {
  return (-1) * ieee_add(-num1, num2);
}


int main(void) {
  float result_add;
  float result_sub;
  result_add = ieee_add(732.732423f, -5.075f);
  result_sub = ieee_sub(-732.732423f, 5.075f);
  printf("%f\n", (double)result_add);
  printf("%f\n", (double)result_sub);
  return 0;
}
