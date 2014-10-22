/* altohw.h
 * L. Stewart
 * See LICENSE file
 */


/* Field access macros */
#define GETFIELD(value, field)				\
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
