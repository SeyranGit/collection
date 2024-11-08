#include <stdio.h>


#define and &
#define xor ^
#define or  |

#define FSTD(upto) (byte index = 0; index < upto; index++)

#define __XOR(bita, bitb)               (bita xor bitb)
#define SUM(bita, bitb, carry_in)       (__XOR(bita, bitb) xor carry_in)
#define CARRY_OUT(bita, bitb, carry_in) ((bita and bitb) or (__XOR(bita, bitb) and carry_in))


typedef char byte;
typedef unsigned char ubyte;


static byte fa(byte num1, byte num2, byte carry_in) {
  byte result = 0;
  for FSTD(8) {
    byte bita = ((num1 >> index) & (byte)1);
    byte bitb = ((num2 >> index) & (byte)1);

    result = ((result) or ((byte)(SUM(bita, bitb, carry_in) << index)));
    carry_in = CARRY_OUT(bita, bitb, carry_in);
  }
  return result;
}


int main(void) {
  printf(
    "\n%d\n", 
    fa(
      (byte)-24, 
      (byte)51, 
      (byte)0
    )
  );
  return 0;
}
