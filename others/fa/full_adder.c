#include <stdio.h>


#define and &
#define xor ^
#define or  |

#define FSTD(iter_count) (byte index = 0; index < iter_count; index++)

#define SUM(bita, bitb, carry_in)       ((bita xor bitb) xor carry_in)
#define CARRY_OUT(bita, bitb, carry_in) ((bita and bitb) or ((bita xor bitb) and carry_in))


typedef char byte;


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
