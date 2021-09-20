/* @(#) wdreg.h 1.1@(#) Solbourne id 9/22/93 00:09:22 */
/*
 * Copyright 1988 Solbourne Computer, Inc.
 * All rights reserved.
 */

/*
 * The WD33C93A is attached to the system board in an indirrect register
 * fashion.  The chip occupies only two bytes of address space.  To get at 
 * a particular internal register of the 93A you must first program an address 
 * register inside the 93A which makes the desired internal regiter available
 * through the other port.  There is no C "structure" representation of 
 * the register file.
 */

#ifdef	S4000
#define	WD_PADSIZE	3
#else
#define	WD_PADSIZE	0xF
#endif

struct wd_reg {
	u_char	wd_ia;		/* write - indirect address */
#define		wd_asr	wd_ia	/* read  - auxilary status register */
	u_char	wd_pad0[WD_PADSIZE];
	u_char	wd_rval;	/* register indexed by indirect address */
	u_char	wd_pad1[0x10-1];
	u_char	wd_pseudo_flush;/* force asic to flush data */
};

#define	WD_OID		0x00		/* Own ID register */
#define	    WD_OID_FSMSK	0xC0	/*    Frequency Select MaSK */
#define	    WD_OID_FSSHFT	6	/*    Frequency Select Shift */
#define	    WD_OID_FS_8_10	0x00	/*    8-10 MHz operation */
#define	    WD_OID_FS_12_15	0x40	/*    12-15 MHz operation */
#define	    WD_OID_FS_16	0x80	/*    16 MHz operation */
#define	    WD_OID_FS_16_20	0x80	/*    16-20 MHz operation */
#define	    WD_OID_EIH		0x20	/*    Enable Immediate Halt (Bpart) */
					/*      set w reset, ucode rev CDB1 */
#define	    WD_OID_EHP		0x10	/*    Enable Host Parity */
#define	    WD_OID_EAF		0x08	/*  A Enable Advanced Features */
#define	    WD_OID_IDMSK	0x07	/*    ID MaSK */
#define WD_AF_CDBSZ	WD_OID
#define	    WD_CDBSZ_MSK	0x07	/*  A Command Descriptor Size MaSK */
#define	WD_CR		0x01		/* Control Register */
#define	    WD_CR_DMMSK		0xE0	/*    DMA select MaSK */
#define	    WD_CR_DM_DMA	0x80	/*    dma- DMA mode */
#define	    WD_CR_DM_BUR	0x20	/*    dma- BURst mode */
#define	    WD_CR_DM_PIO	0x00	/*    dma- Polled IO mode */
#define	    WD_CR_HHP		0x10	/*    Halt on Host Parity errors */
#define	    WD_CR_EDI		0x08	/*    Ending Disconnect Interrupt */
#define	    WD_CR_IDI		0x04	/*    Intermediate Discon Interrupt */
#define	    WD_CR_HA		0x02	/*    Halt on Attention */
#define	    WD_CR_HSP		0x01	/*    Halt on Scsi Parity error */
#define	WD_TPR		0x02		/* Timeout Period Register */
#define	WD_CDB		0x03		/* Command Descriptor Block */
#define	WD_UCODEREV	WD_CDB		/* (Bpart) */
/*			 ::		/* */
#define	WD_TLUN		0x0F		/* Target Logical UNit */
#define	    WD_TLUN_TLV		0x80	/*    Target Lun Valid */
#define	    WD_TLUN_DOK		0x40	/*    Disconnects OK */
#define	    WD_TLUN_TRN		0x20	/*    Target Routine (Bpart) */
#define	    WD_TLUN_TLUN_MSK	0x07	/*    Target MASK */
#define	WD_SSTATUS	WD_TLUN		/* SCSI Status */
#define	WD_IDENTIFY	WD_TLUN		/* Identify message (Advanced) */
#define	WD_CP		0x10		/* Command Phase Register */
#define	    WD_CP_S_NOSEL	0x00	/*    Not device selected */ 
#define	    WD_CP_S_SEL		0x10	/*    Target selected */ 
#define	    WD_CP_S_IDENT	0x20	/*    Identify sent */ 
#define	    WD_CP_S_CMD		0x30	/*    Start of CDB transfer */ 
#define	    WD_CP_S_MDS		0x41	/*    Save Data Pointer Recieved */
#define	    WD_CP_S_DMR		0x42	/*    Disconnect Message revieved */
#define	    WD_CP_S_DISCON	0x43	/*    Target Disconnected */
#define	    WD_CP_S_RSEL	0x44	/*    Target Reselected */
#define	    WD_CP_S_IDOK	0x45	/*    Correct Identify recieved */
#define	    WD_CP_S_TCR		0x46	/*    Transfer counter exausted */
#define	    WD_CP_S_RSTATUS	0x47	/*    Start recieve status */
#define	    WD_CP_S_RSTATUS_E	0xFF	/*    Start recieve status errata */
#define	    WD_CP_S_SBR		0x50	/*    Status Byte recieved */
#define	    WD_CP_S_CCR		0x60	/*    Command complete recieved */
#define	    WD_CP_R_SEL		0x10	/*    after target selection */ 
#define	    WD_CP_R_IDENT	0x20	/*    after identify message out */
#define	    WD_CP_R_CMD		0x30	/*    at start of command phase */
#define	    WD_CP_R_A_CMD_SDP	0x41	/*    after command phase or SDP */
#define	    WD_CP_R_DMI_ACK	0x42	/*    at disconnect message in */
#define	    WD_CP_R_RSEL	0x44	/*    after reselection */
#define	    WD_CP_R_MORE_DATA	0x45	/*    to transfer more data */
#define	    WD_CP_R_AFTER_DATA	0x46	/*    after data phase */
#define	    WD_CP_R_STATUS	0x50	/*    to complete status phase */
#define	    WD_CP_R_CMD_CMP	0x60	/*    to complete command complete */
#define	WD_STR		0x11		/* Synchronous Transfer Register */
#define	    WD_STR_FAST_SCSI	0x80	/*    Fast SCSI select (Bpart) */
#define	    WD_STR_TP_MSK	0x70	/*    Transfer period mask */
#define	    WD_STR_OFF_MSK	0x0F	/*    Offset mask */ 
#define	WD_TCR		0x12		/* Transfer Counter Register */
#define	WD_TCR_H	0x12		/* Transfer Counter Register High */
#define	WD_TCR_M	0x13		/* Transfer Counter Register High */
#define	WD_TCR_L	0x14		/* Transfer Counter Register High */
#define	WD_DID		0x15		/* Destination ID register */
#define	    WD_DID_SCC		0x80	/*    Select command chain */
#define	    WD_DID_DPD		0x40	/*    Data Phase Direction (1 => in) */
#define	    WD_DID_DF		0x20	/*    Disable Feature (Bpart) */
#define	    WD_DID_TAGM_MSK	0x18	/*    Tag Message (Bpart) */
#define	    WD_DID_TAGM_NONE	0x00	/*      No Message (Bpart) */
#define	    WD_DID_TAGM_SIMPLEQ	0x08	/*      Simple Queue Tag 0x20(Bpart) */
#define	    WD_DID_TAGM_HEADQ	0x10	/*      Head of Queue Tag 0x21(Bpart) */
#define	    WD_DID_TAGM_ORDERQ	0x18	/*      Ordered Queue Tag 0x22(Bpart) */
#define	    WD_DID_MSK		0x07	/*    Destination ID mask */
#define	WD_SID		0x16		/* Source ID register */
#define	    WD_SID_ER		0x80	/*    Enable Reselection */
#define	    WD_SID_ES		0x40	/*    Enable Selection */
#define	    WD_SID_DSP		0x20	/*    Disable Selection Parity */
#define	    WD_SID_ID_V		0x08	/*    Source ID Valid */
#define	    WD_SID_ID_MSK	0x07	/*    Source ID MaSK */
#define	WD_IST		0x17		/* interrupt scsi STatus */
#define	    WD_IST_TYPE_MSK	0xF0	/*    STatus TYPE MaSK */
#define	    WD_IST_MCI_BIT	0x08	/*    IST in MCI form */
#define	    WD_IST_MCI_MSK	0x07	/*    Message Command In MaSK */
#define	    WD_IST_MCI_PHASE(x)	((x) & WD_IST_MCI_MSK)
#define	    WD_IST_RST		0x00	/*	WD33C93A in reset state */
#define	    WD_IST_RST_OK	(WD_IST_RST|0x0)   /* Reset command */
#define	    WD_IST_RST_ADV	(WD_IST_RST|0x1)   /* Reset command */
#define	    WD_IST_OK		0x10	/*	Successful completion */
#define	    WD_IST_OK_RSEL	(WD_IST_OK|0x0)   /* Reselect command ok */
#define	    WD_IST_OK_SEL	(WD_IST_OK|0x1)   /* Select command ok */
#define	    WD_IST_OK_SR_NAT	(WD_IST_OK|0x3)   /* SEND/RECV ok, no ATN */
#define	    WD_IST_OK_SR_AT	(WD_IST_OK|0x4)   /* SEND/RECV ok, ATN */
#define	    WD_IST_OK_XLAT	(WD_IST_OK|0x5)   /* Translate address ok */
#define	    WD_IST_OK_SAT	(WD_IST_OK|0x6)   /* SAT command ok */
#define	    WD_IST_OK_X_MCI	(WD_IST_OK|0x8)   /* Transfer command ok */
#define	    WD_IST_PA		0x20	/*	Paused/Aborted */
#define	    WD_IST_PA_X_ACK	(WD_IST_PA|0x0)   /* Transter paused with ACK */
#define	    WD_IST_PA_SAT_SDP	(WD_IST_PA|0x1)   /* SAT Save Data Pointers */
#define	    WD_IST_PA_SEL_ABORT	(WD_IST_PA|0x2)   /* SELect cmd aborted */
#define	    WD_IST_PA_SR_NAT	(WD_IST_PA|0x3)   /* SEND/RECV aborted no ATN */
#define	    WD_IST_PA_SR_AT	(WD_IST_PA|0x4)   /* SEND/RECV aborted w ATN */
#define	    WD_IST_PA_RSP_SEL	(WD_IST_PA|0x5)   /* aborted during SEL res */
#define	    WD_IST_PA_SAT_RSEL	(WD_IST_PA|0x6)   /* SAT unxpected reselect */
#define	    WD_IST_PA_X_MCI	(WD_IST_PA|0x8)   /* Transfer cmd pause/abort */
#define	    WD_IST_TE		0x40	/*	Terminated */
#define	    WD_IST_TE_INVALID	(WD_IST_TE|0x0)   /* Invalid Command */
#define	    WD_IST_TE_UDISC	(WD_IST_TE|0x1)   /* Unexpected Disconnect */
#define	    WD_IST_TE_TIMEOUT	(WD_IST_TE|0x2)   /* TIMEOUT during select */
#define	    WD_IST_TE_PE_NAT	(WD_IST_TE|0x3)   /* Parity Err no ATN */
#define	    WD_IST_TE_PE_AT	(WD_IST_TE|0x4)   /* Parity Err with ATN */
#define	    WD_IST_TE_XLAT	(WD_IST_TE|0x5)   /* bad tranalate addr */
#define	    WD_IST_TE_TAR_RSEL	(WD_IST_TE|0x6)   /* wrong target reselected */
#define	    WD_IST_TE_PE_STATUS	(WD_IST_TE|0x7)   /* bad status byte parity */
#define	    WD_IST_TE_MCI	(WD_IST_PA|0x8)   /* unexpected phase */
#define	    WD_IST_SR		0x80	/*	Requires Service */
#define	    WD_IST_SR_RSEL	(WD_IST_SR|0x0)   /* Reselected */
#define	    WD_IST_SR_RSEL_ID	(WD_IST_SR|0x1)   /* Reselected w identify  */
#define	    WD_IST_SR_SEL_NAT	(WD_IST_SR|0x2)   /* Selected no ATN */
#define	    WD_IST_SR_SEL_AT	(WD_IST_SR|0x3)   /* Selected w ATN */
#define	    WD_IST_SR_AT	(WD_IST_SR|0x4)   /* ATN Asserted */
#define	    WD_IST_SR_DISC	(WD_IST_SR|0x5)   /* Disconnect Occured */
#define	    WD_IST_SR_UN_CDB	(WD_IST_SR|0x7)   /* Unknown CDB recieved */
#define	    WD_IST_SR_REQ_MCI	(WD_IST_SR|0x8)   /* Request Asserted */
#define	WD_CMD		0x18		/* CoMmanD register */
#define	    WD_CMD_1BYTE	0x80	/*    modifier, Single Byte Transfer */
#define	    WD_CMD_RESET	0x00	/*    Reset */
#define	    WD_CMD_ABORT	0x01	/*    Abort */
#define	    WD_CMD_AATN		0x02	/*    Assert ATN */
#define	    WD_CMD_NACK		0x03	/*    Negate ACK */
#define	    WD_CMD_DISC		0x04	/*    Disconnect */
#define	    WD_CMD_RSEL		0x05	/*    Reselect */
#define	    WD_CMD_SEL_AT	0x06	/*    Select with ATN */
#define	    WD_CMD_SEL_NAT	0x07	/*    Select w/o ATN */
#define	    WD_CMD_SAT_AT	0x08	/*    Select with ATN and Transfer */
#define	    WD_CMD_SAT_NAT	0x09	/*    Select w/o ATN and Transfer */
#define	    WD_CMD_RSEL_R	0x0A	/*    Reselect and recieve data */
#define	    WD_CMD_RSEL_S	0x0B	/*    Reselect and send data */
#define	    WD_CMD_WSEL_R	0x0C	/*    Wait for select and recieve */
#define	    WD_CMD_SSCC		0x0D	/*    Send Status and Cmd Complete */
#define	    WD_CMD_SDISC_MSG	0x0E	/*    Send Disconnect message */
#define	    WD_CMD_SIDI		0x0F	/*    Set IDI */
#define	    WD_CMD_R_CMD	0x10	/*    Recieve Command */
#define	    WD_CMD_R_DAT	0x11	/*    Recieve Data */
#define	    WD_CMD_R_MO		0x12	/*    Recieve Message Out */
#define	    WD_CMD_R_IO		0x13	/*    Recieve unspecified info out */
#define	    WD_CMD_S_ST		0x14	/*    Send Status */
#define	    WD_CMD_S_DAT	0x15	/*    Send Data */
#define	    WD_CMD_S_MI		0x16	/*    Send Message In */
#define	    WD_CMD_S_II		0x17	/*    Send unspecified Info In */
#define	    WD_CMD_XLAT		0x18	/*    Translate address */
#define	    WD_CMD_X		0x20	/*    Transfer Info */
#define	    WD_CMD_X_PAD	0x21	/*    Transfer Pad */
#define	WD_DATA		0x19		/* DATA register */
#define	WD_QTAG		0x1A		/* Queue TAG register (Bpart) */
#define	WD_ASR		0x1F		/* Auxiliary Status Register */
#define	    WD_ASR_INT		0x80	/*    INTerrupt pending */
#define	    WD_ASR_LCI		0x40	/*    Last Command Ignored */
#define	    WD_ASR_BSY		0x20	/*    BuSY */
#define	    WD_ASR_CIP		0x10	/*    Command In Progress */
#define	    WD_ASR_MBZ_MASK_A	0x0C	/*    Bits that are zero when valid */
#define	    WD_ASR_MBZ_MASK_B	0x08	/*    Bits that are zero when valid */
#define	    WD_ASR_FFE		0x04	/*    FIFO Full/Empty (Bpart) */
#define	    WD_ASR_PE		0x02	/*    Parity Error */
#define	    WD_ASR_DBR		0x01	/*    Data Buffer Ready */
#define	    WD_ASR_BITS		"\20\10INT\7LCI\6BSY\5CIP\2PE\1DBR"

#if defined(S4000) && defined(KERNEL) && defined(KAPBUG_S461)
# define _WD_SET(wd, reg, val) (((wd)->wd_ia = (reg)), ((wd)->wd_rval = (val)))
# define _WD_GET(wd, reg) ((si_s = splhigh()), ((wd)->wd_ia = (reg)), (si_rval = (wd)->wd_rval), (splx(si_s)), (si_rval))
#else
# define _WD_SET(wd, reg, val)	(((wd)->wd_ia = (reg)),			\
				((wd)->wd_rval = (val)),		\
				flush_writebuffers_to(&(wd)->wd_rval))
# define _WD_GET(wd, reg) (((wd)->wd_ia = (reg)), ((wd)->wd_rval))
#endif

#define	WD_REG_ASCII	{	"OID ",	"CR  ",	"TPR ",	"C0  ",		\
				"C1  ",	"C2  ",	"C3  ",	"C4  ",		\
				"C5  ",	"C6  ",	"C7  ",	"C8  ",		\
				"C9  ",	"C10 ",	"C11 ",	"TLUN",		\
				"CP  ",	"STR ",	"TCRH",	"TCRM",		\
				"TCRL",	"DID ",	"SID ",	"IST ",		\
				"CMD ",	"DATA",	"QTAG", "?1B?",		\
				"?1C?",	"?1D?",	"?1E",	"ASR "}

#ifdef	WD_REG_DEBUG
#define	WD_SET(wd, reg, val)	(printf("SET %s = %x\n", 		\
				    wd_reg_ascii[(reg)], 		\
				    val & 0xFF),			\
				    _WD_SET(wd, reg, val))
#define	WD_GET(wd, reg)		(printf("GET %s = %x\n",		\
				    wd_reg_ascii[(reg)], 		\
				    _WD_GET(wd, reg) & 0xFF),		\
				    _WD_GET(wd, reg))
#else	WD_REG_DEBUG
#define	WD_SET(wd, reg, val)	_WD_SET(wd, reg, val)
#define	WD_GET(wd, reg)		_WD_GET(wd, reg)
#endif	WD_REG_DEBUG
