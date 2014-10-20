/* altohw.h
 * L. Stewart
 */

/* Field access macros */
#define GETFIELD(field, value) \
  ((value >> field ## _START) & ((1 << field ## _WIDTH) - 1))

/* Microinstruction fields */
/* Little endian format */

#define MI_NEXT_START 0
#define MI_NEXT_WIDTH 10
#define MI_LOADL_START 10
#define MI_LOADL_WIDTH 1
#define MI_LOADT_START 11
#define MI_LOADT_WIDTH 1
#define MI_F2_START 12
#define MI_F2_WIDTH 4
#define MI_F1_START 16
#define MI_F1_WIDTH 4
#define MI_BS_START 20
#define MI_BS_WIDTH 3
#define MI_ALUF_START 23
#define MI_ALUF_WIDTH 4
#define MI_RSEL_START 27
#define MI_RSEL_WIDTH 5

/* ALUF values */
#define MI_ALUF_BUS 0
#define MI_ALUF_T 1
#define MI_ALUF_BUS_OR_T 2
#define MI_ALUF_BUS_AND_T 3
#define MI_ALUF_BUS_XOR_T 4
#define MI_ALUF_BUS_ADD_1 5
#define MI_ALUF_BUS_SUB_1 6
#define MI_ALUF_BUS_ADD_T 7
#define MI_ALUF_BUS_SUB_T 8
#define MI_ALUF_BUS_SUB_T_SUB_1 9
#define MI_ALUF_BUS_ADD_T_ADD_1 10
#define MI_ALUF_BUS_ADD_SKIP 11
#define MI_ALUF_BUS_DOT_T 12
#define MI_ALUF_BUS_AND_NOT_T 13
#define MI_ALUF_BUS_UNDEF_1 14
#define MI_ALUF_BUS_UNDEF_2 15

/* T is loaded from the ALU output rather than BUS in the following cases */
#define tmux(aluf) ((aluf==0) || (aluf==2) || (aluf==5) || (aluf==6) || (aluf=10) || (aluf==11) || (aluf==12))


/* Bus source values */
/* Bus ANDs multiple sources
 * Decode not done if F1=7 or F2=7
 * LOADR forces bus to 0
 */
#define MI_BS_READR 0
#define MI_BS_LOADR 1
#define MI_BS_NONE 2
#define MI_BS_TASK_1 3
#define MI_BS_TASK_2 4
#define MI_BS_GETMD 5
#define MI_BS_MOUSE 6
#define MI_BS_DISP 7

/* F1 values */
#define MI_F1_NONE 0
#define MI_F1_MARGETS 1
#define MI_F1_TASK 2
#define MI_F1_BLOCK 3
#define MI_F1_LLSH1 4
#define MI_F1_LRSH1 5
#define MI_F1_LLCY8 6
#define MI_F1_CONSTANT 7

/* F2 values */
#define MI_F2_NONE 0
#define MI_F2_BUS0 1
#define MI_F2_SHLT 2
#define MI_F2_SHEQ 3
#define MI_F2_BUS 4
#define MI_F2_ALUCY 5
#define MI_F2_MDGETS 6
#define MI_F2_CONSTANT 7

/* Task 0 Specific F1 values */
#define MI_F1_EM_SWMODE 8
#define MI_F1_EM_WRTRAM 9
#define MI_F1_EM_RDRAM 10
#define MI_F1_EM_LOADRMR 11
#define MI_F1_EM_12 12
#define MI_F1_EM_LOADESRB 13
#define MI_F1_EM_RSNF 14
#define MI_F1_EM_STARTF 15

/* Task 0 specific F2 values */
#define MI_F2_EM_BUSODD 8
#define MI_F2_EM_MAGIC 9
#define MI_F2_EM_LOADDNS 10
#define MI_F2_EM_ACDEST 11
#define MI_F2_EM_LoadIR 12
#define MI_F2_EM_IDISP 13
#define MI_F2_EM_ACSOURCE 14
#define MI_F2_EM_15

/* Task 4,14 (KSEC,KWD) Specific F1 values */

#define MI_F1_K_STROBE 9
#define MI_F1_K_LOADKSTAT 10
#define MI_F1_K_INCRECNO 11
#define MI_F1_K_CLRSTAT 12
#define MI_F1_K_LOADKCOMM 13
#define MI_F1_K_LOADKADR 14
#define MI_F1_K_LOADKDATA 15

/* Task 4,14 (KSEC, KWD) specific F2 values */
#define MI_F2_K_INIT 8
#define MI_F2_K_RWC 9
#define MI_F2_K_RECNO 10
#define MI_F2_K_XFRDAT 11
#define MI_F2_K_SWRNRDY 12
#define MI_F2_K_NFER 13
#define MI_F2_K_STROBON 14

/* Task 7 (Ether) Specific F1 values */
#define MI_F1_ETHER_ELFCT 11
#define MI_F1_ETHER_EPFCT 12
#define MI_F1_ETHER_EWFCT 13

/* Task 7 (Ether) Specific F2 values */
#define MI_F2_ETHER_EODFCT 8
#define MI_F2_ETHER_EOSFCT 9
#define MI_F2_ETHER_ERBFCT 10
#define MI_F2_ETHER_EEFCT 11
#define MI_F2_ETHER_EBFCT 12
#define MI_F2_ETHER_ECBFCT 13
#define MI_F2_ETHER_EISFCT 14

/* Task 9 DWT Specific F2 values */
#define MI_F2_DWT_LOADDDR 8

/* Task 10 CURT Specific F2 values */
#define MI_F2_CURT_LOADXPREG 8
#define MI_F2_CURT_LOADCSR 9

/* Task 11 DHT Specific F2 values */
#define MI_F2_DHT_EVENFIELD 8
#define MI_F2_DHT_SETMODE 9

/* Task 12 DVT Specific F2 values */
#define MI_F2_DVT_EVENFIELD 8

/* Bank register */
#define BR_EXTENDED_START 0
#define BR_EXTENDED_LENGTH 2
#define BR_NORMAL_START 2
#define BR_EXTENDED_LENGTH 2


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

