/* altohw.c
 * L. Stewart
 */

#include "altohw.h"

mainloop()
{
  task = selecttask();
  dooperation();
  mi = readmicroinstruction();
}

/* signals */
uint16_t bus;
uint16_t skip;   /* might be a microinstruction field */
uint16_t carry;
uint16_t t_from_alu;
uint16_t alu_out;
uint16_t constant_rom_out;
uint16_t r_reg_out;
uint16_t s_reg_out;
uint16_t instruction_address;
int memcycle = 0;

/* registers */
uint16_t mem[4][65536];
uint32_t ucode[4][1024];
uint16_t r_reg[32];
uint16_t s_reg[256];
uint16_t constant_reg[256];
uint16_t cur_task;
uint16_t next_task;
uint16_t mpc[16];
uint16_t mpc_bank[16];
uint32_t instruction;
uint16_t mi_rsel;
uint16_t mi_aluf;
uint16_t mi_bs;
uint16_t mi_f1;
uint16_t mi_f2;
uint16_t mi_t;
uint16_t mi_l;
uint16_t mi_next;

uint16_t t_reg;
uint16_t l_reg;
uint16_t m_reg;
uint16_t bank_reg;  /* bank for the running reference */
uint16_t mar_reg;
uint16_t md_reg; /* load data */
uint16_t ir_reg;






do_one_cycle()
{
  instruction = ucode[mpc_bank[cur_task]][instruction_address];
  mi_rsel = GETFIELD(instruction, MI_RSEL);
  mi_aluf = GETFIELD(instruction, MI_ALUF);
  mi_bs = GETFIELD(instruction, MI_BS);
  mi_f1 = GETFIELD(instruction, MI_F1);
  mi_f2 = GETFIELD(instruction, MI_F2);
  mi_t = GETFIELD(instruction, MI_T);
  mi_l = GETFIELD(instruction, MI_L);
  mi_next = GETFIELD(instruction, MI_NEXT);

  /* check that F1 != 7 and F2 != 7 */
  switch(mi_bs) {
  case MI_BS_READR: {
    bus = r_reg[mi_rsel];
    break;
  }
  case MI_BS_LOADR: {
    bus = 0;
    break;
  }
  case MI_BS_NONE: {
    break;
  }
  case MI_BS_TASK_1: {
    break;
  }
  case MI_BS_TASK_2: {
    
    break;
  }
  case MI_BS_GETMD: {
    bus = get_md(); /* a function to handle side effects */
    break;
  }
  case MI_BS_MOUSE: {
    bus = 0xfff0 | (mouse_reg & 0xf);
    break;
  }
  case MI_BS_DISP: {
    bus = 
    break;
  }
  }
  t_from_alu = 0;
  switch(mi_aluf) {
  case MI_ALUF_BUS: {
    alu_out = bus;
    t_from_alu = 1;
    break;
  }
 case MI_ALUF_T: {
   alu_out = t_reg;
   break;
 }
 case MI_ALUF_BUS_OR_T: {
   alu_out = bus | t_reg;
   t_from_alu = 1;
   break;
 }
 case MI_ALUF_BUS_AND_T: {
   alu_out = bus & t_reg;
   break;
 }
 case MI_ALUF_BUS_XOR_T: {
   alu_out = bus ^ t_reg;
   break;
 }
 case MI_ALUF_BUS_ADD_1: {
   alu_out = bus + 1;
   t_from_alu = 1;
   break;
 }
 case MI_ALUF_BUS_SUB_1: {
   alu_out = bus - 1;
   t_from_alu = 1;
   break;
 }
 case MI_ALUF_BUS_ADD_T: {
   alu_out = bus + t_reg;
   break;
 }
 case MI_ALUF_BUS_SUB_T: {
   alu_out = bus - t_reg;
   break;
 }
 case MI_ALUF_BUS_SUB_T_SUB_1: {
   alu_out = bus - t_reg - 1;
   break;
 }
 case MI_ALUF_BUS_ADD_T_ADD_1: {
   alu_out = bus + t_reg + 1;
   t_from_alu = 1;
   break;
 }
 case MI_ALUF_BUS_ADD_SKIP: {
   alu_out = bus + skip;
   t_from_alu = 1;
   break;
 }
 case MI_ALUF_BUS_DOT_T: {
   alu_out = bus & t_reg;
   t_from_alu = 1;
   break;
 }
 case MI_ALUF_BUS_AND_NOT_T: {
   alu_out = bus & (~t_reg);
   break;
 }
 case MI_ALUF_BUS_UNDEF_1: {
   assert(0);
   break;
 }
 case MI_ALUF_BUS_UNDEF_2: {
   assert(0);
   break;
 }
  }
  if (mi_loadt) {
    if (t_from_alu) {
      t_reg = alu_out;
    } else {
      t_reg = bus;
    }
  }

  lmmar_cycle();
  wite_rs_cycle();
}

/* Utilities and initialization */
int load_microcode(chat *filename) 
{
  int fd;
  fd = open(filename, O_RDONLY);
  if (fd < 0) return (-1);
  /* XXX */
  close(fd);
  return(0);
}

/* main hardware units */
/*
r_read
r_write
s_read
s_write
+
alu(a, b, op);
*/

/* Memory follows Alto II timing
 * See section 2.3 of the hardware manual
 */
/* memcycle == 0 means the memory is idle
 * memcycle == 1 is the cycle when MAR<- happens
 * memcycle == 2 cannot be MD<- or <-MD
 * the memory will stall if MD<- or <-MD cannot be accomodated
 * necessarily, the stall must be figured out before any state changes occur to L, T, etc.
 *
 * stores:  the first MD<- can occur in cycle 3 or 4
 *    a second MD<- can occur in cycle 4
 * loads: the first <-MD can occur in cycle 5
 *   an optional <- MD can occur in cycle 6 (and fetches MAR XOR 1
 */

/* decide whether this microcycle needs to be suspended or is an error 
 * return 1 if we need to suspend
 */

int mi_memtiming()
{
  if (memcycle == 1) {
    storexor = 0;
    loadxor = 0;
    memcycle = 2;
    return(0);
  }
  /* REQUIRED not to touch the memory registers during cycle 1 */
  if (memcycle == 2) { 
    if ((mi_bs == MI_BS_GETMD) || (mi_f1 == MI_F1_MARGETS) || (mi_f2 == MI_F2_MDGETS)) {
      assert(0);
    }
    memcycle = 3;
    return(0);
  }
  if (memcycle == 3) {
    if (mi_f1 == MI_F1_MARGETS) {
      assert(0);
    }
    if ((mi_bs == MI_BS_GETMD) && (mi_f2 == MI_F2_MDGETS)) {
      assert(0);
    }
    if (mi_bs == MI_BS_GETMD) {
      memcycle = 4;
      return(1);
    }
    /* MDGETS starts first word of a store */
    if (mi_f2 == MI_F2_MDGETS) {
      mem[bank_reg][mar_reg ^ storexor] = bus_reg;
      storexor=1;
    }
    memcycle = 4;
    return(0);
  }
  if (memcycle == 4) {
    if (mi_f1 == MI_F1_MARGETS) {
      assert(0);
    }
    if ((mi_bs == MI_BS_GETMD) && (mi_f2 == MI_F2_MDGETS)) {
      assert(0);
    }
    /* first load */
    if (mi_bs == MI_BS_GETMD) {
      memcycle = 5;
      return(1);
    }
    if (mi_f2 == MI_F2_MDGETS) {
      /* if this is the second store, storexor will already be set */
      mem[bank_reg][mar_reg ^ storexor] = bus_reg;
      storexor=1;
    }
    memcycle = 5;
    return(0);
  }
  if (memcycle == 5) {
    if (mi_f1 == MI_F1_MARGETS) {
      memcycle = 0;
      return(1);
    }
    if (mi_f2 == MI_F2_MDGETS) {
      assert(0);
    }
    if (mi_bs == MI_BS_GETMD) {
      md_reg = mem[bank_reg][mar_reg];
      readxor = 1;
    }
    memcycle = 6;
    return(0);
  }
  if (memcycle == 6) {
    if (mi_f1 == MI_F1_MARGETS) {
      memcycle = 0;
      return(1);
    }
    if (mi_bs == MI_BS_GETMD) {
      md_reg = mem[bank_reg][mar_reg];
      readxor = 1;
    }
  }
}

