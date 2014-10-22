/* dumpucode.c
 * L. Stewart
 * See LICENSE
 */

#include "altohw.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

uint32_t instruction;

uint16_t mi_rsel;
uint16_t mi_aluf;
uint16_t mi_bs;
uint16_t mi_f1;
uint16_t mi_f2;
uint16_t mi_t;
uint16_t mi_l;
uint16_t mi_next;

void disassemble()
{
}


int main(int argc, char *argv[])
{
  int res;
  int i;
  uint32_t ucode[1024];
  res = read(0, ucode, 1024 * sizeof(uint32_t));
  if (res < 0)
    return(1);

  printf(" adr: rs  alu bs f1 f2 t l next\n");

  for (i = 0; i < 1024; i += 1) {
    instruction = ucode[i];
    mi_rsel = GETFIELD(instruction, MI_RSEL);
    mi_aluf = GETFIELD(instruction, MI_ALUF);
    mi_bs = GETFIELD(instruction, MI_BS);
    mi_f1 = GETFIELD(instruction, MI_F1);
    mi_f2 = GETFIELD(instruction, MI_F2);
    mi_t = GETFIELD(instruction, MI_LOADT);
    mi_l = GETFIELD(instruction, MI_LOADL);
    mi_next = GETFIELD(instruction, MI_NEXT);

    printf("%04o:  %02o  %02o  %01o %02o %02o %01o %01o %04o",
	   i, mi_rsel, mi_aluf, mi_bs, mi_f1, mi_f2, mi_t, mi_l, mi_next);
    disassemble();
    

  }

  return(0);
}
