/* @(#) ipi_2.h 1.1@(#) Solbourne id 9/22/93 00:06:30 */
/*
 * Definitions for IPI Level-2: Intelignet Peripherial Interface Level 2
 */

/* command codes */
#define	IPI_CMD_LD_SLAVE		0x01	/* load slave function */
#define	    LD_SLAVE_DISABLE_APORT	    0x10/* alternate port disable */
#define	    LD_SLAVE_ENABLE_APORT	    0x11/* alternate port enable */
#define	    LD_SLAVE_DISABLE_PORT	    0x12/* port disable */
#define	    LD_SLAVE_PRIORITYRES	    0x13/* priority reserve */
#define	    LD_SLAVE_RESERVE		    0x14/* reserve */
#define	    LD_SLAVE_RELEASE		    0x15/* release */
#define	    LD_SLAVE_NOTIFYALTP		    0x16/* notify alt port fmt done */
#define	    LD_SLAVE_DISABLE_SCCA	    0x18/* disable success cmd atn */
#define	    LD_SLAVE_ENABLE_SCCA	    0x19/* enable success cmd atn */
#define	    LD_SLAVE_DISABLE_RPSA	    0x1A/* disable RPS atn */
#define	    LD_SLAVE_ENABLE_RPSA	    0x1B/* enable RPS atn */
#define	    LD_SLAVE_DISABLE_SPEND	    0x1C/* disable status pend atn */
#define	    LD_SLAVE_ENABLE_SPEND	    0x1D/* disable status pend atn */
#define	    LD_SLAVE_DISABLE_NLB	    0x1E/* disable nolonger busy atn */
#define	    LD_SLAVE_ENABLE_NLB		    0x1F/* disable nolonger busy atn */
#define	    LD_SLAVE_NOOP		    0x20/* no operation */
#define	    LD_SLAVE_SPINUP		    0x22/* spin up */
#define	    LD_SLAVE_SPINDOWN		    0x23/* spin down */
#define	    LD_SLAVE_LOADHEADS		    0x24/* load heads */
#define	    LD_SLAVE_UNLOADHEADS	    0x25/* unload heads */
#define	    LD_SLAVE_LOCKCARRIAGE	    0x26/* lock carriage */
#define	    LD_SLAVE_UNLKCARRIAGE	    0x27/* unlock carriage */
#define	    LD_SLAVE_RECALIBRATE	    0x28/* recalibrate */
#define	    LD_SLAVE_EXECDIAG		    0x29/* execute internal diags */
#define	    LD_SLAVE_PSECTORMARK	    0x2B/* perform sector marking */
#define	    LD_SLAVE_DISABLE_ECC	    0x2c/* disable slave ecc */
#define	    LD_SLAVE_ENABLE_ECC		    0x2D/* enable slave ecc */
#define	    LD_SLAVE_RESET_OFFSET	    0x41/* enable slave ecc */
#define	    LD_SLAVE_OFFSET1_POS	    0x42/* set positive offset */
#define	    LD_SLAVE_OFFSET1_NEG	    0x43/* set negative offset */
#define	    LD_SLAVE_OFFSET2_POS	    0x44/* set positive offset */
#define	    LD_SLAVE_OFFSET2_NEG	    0x45/* set negative offset */
#define	    LD_SLAVE_OFFSET3_POS	    0x46/* set positive offset */
#define	    LD_SLAVE_OFFSET3_NEG	    0x47/* set negative offset */
#define	    LD_SLAVE_OFFSET4_POS	    0x48/* set positive offset */
#define	    LD_SLAVE_OFFSET4_NEG	    0x49/* set negative offset */
#define	    LD_SLAVE_SLATECODE		    0x4A/* set late code */
#define	    LD_SLACE_SLAVEFUNC0		    0x80/* slave specific func: 0 */
#define	    LD_SLACE_SLAVEFUNC1		    0x80/* slave specific func: 1 */
#define	IPI_CMD_LD_FORMAT		0x02	/* load format specification */
#define	IPI_CMD_LD_SLAVESPEC		0x03	/* load slave-specific info */
#define	IPI_CMD_LD_CYL_ADR		0x04	/* load cylinder address */
#define	IPI_CMD_LD_HEAD_ADR		0x05	/* load head address */
#define	IPI_CMD_LD_RPS			0x06	/* load RPS address */
#define	IPI_CMD_RD_CONFIG		0x41	/* read configuration */
#define	IPI_CMD_RD_FORMAT		0x42	/* read format specification */
#define	IPI_CMD_RD_SLAVESPEC		0x43	/* read slave specific info */
#define	IPI_CMD_RD_STATUS		0x44	/* read status */
#define	IPI_CMD_RD_CORVEC		0x45	/* read correction vectors */
#define	IPI_CMD_RD_SEC_ADR		0x46	/* read current sector addr */
#define	IPI_CMD_RD_POS			0x47	/* read current position */
#define	IPI_CMD_RD_STATUSEX		0x48	/* read status, extended */

/* data direction definitions for command codes */
#define	IPI_CMD_DIRECT_MASK		0x40
#define	IPI_CMD_DIRECTION_IN		0x40	/* read */
#define	IPI_CMD_DIRECTION_OUT		0x00	/* write(load) */

/* ipi configuration packet */
struct	ipi_conf {
    u_short	conf_len;		/* number of bytes remaining */
    u_char	conf_dev_class;		/* class of device */
#define		  DEV_CLASS_DISK	1
    u_char	conf_typ_flags;		/* type flags */
#define		  TYP_FLAGS_NONREM	0x80	/* non-removable disk */
#define		  TYP_FLAGS_REM		0x40	/* removable disk */
#define		  TYP_FLAGS_HDFIXED	0x10	/* fixed head disk (drum) */
#define		  TYP_FLAGS_HDMOVE	0x08	/* moving head disk */
#define		  TYP_FLAGS_BITS	\
"\20\10NON-REMOVABLE\7REMOVABLE\5FIXHEAD\4MOVABLEHEAD"
    u_char	conf_cap_flags;		/* capability flags */
#define		  CAP_FLAGS_VARBLK	0x40	/* variable block mode */
#define		  CAP_FLAGS_FIXBLK_FS	0x20	/* fixed block fixed sector */
#define		  CAP_FLAGS_FIXBLK_VS	0x10	/* fixed block variable sec */
#define		  CAP_FLAGS_SOFTSEC	0x08	/* soft sector */
#define		  CAP_FLAGS_HARDSEC	0x04	/* hard sector */
#define		  CAP_FLAGS_FDC		0x02	/* field data controls */
#define		  CAP_FLAGS_SDC		0x01	/* sector data controls */
#define		  CAP_FLAGS_BITS	\
"\20\7VARBLK\6FIXBLK_FS\5FIXBLK_VS\4SOFTECC\3HARDSEC\2FDC\1SDC"
    u_char	conf_fet_flags;		/* feature flags */
#define		  FET_FLAGS_RPS		0x80	/* Rotational Position Sense */
#define		  FET_FLAGS_DUALPORT	0x40	/* Dual Port */
#define		  FET_FLAGS_SLAVEECC	0x20	/* Drive ECC */
#define		  FET_FLAGS_OEDA	0x08	/* odd/even dual actuator */
#define		  FET_FLAGS_OEDD	0x04	/* odd/even dual device */
#define		  FET_FLAGS_RFS		0x02	/* restores format spec */
#define		  FET_FLAGS_FIXEDFMT	0x01	/* fixed format spec */
#define		  FET_FLAGS_BITS	\
"\20\10RPS\7DUALPORT\6SLAVEECC\4OEDA\3OEDD\2RFS\1FIXEDFMT"
    u_short	conf_datcyl_h,		/* number or data cylinders */
		conf_datcyl_l;		
    u_short	conf_defcyl_h,		/* last defect cylinders */
		conf_defcyl_l;		
    u_short	conf_nhead;		/* number of heads */
    u_short	conf_nfspt;		/* number of fixed sectors per track */
    u_short	conf_nbpt_h,		/* number of bytes per track*/
		conf_nbpt_l;		
    u_short	conf_seek_cyl_h,	/* one cylinder seek time */
		conf_seek_cyl_l;
    u_short	conf_seek_ave_h,	/* average seek time */
		conf_seek_ave_l;
    u_short	conf_seek_max_h,	/* max seek time */
		conf_seek_max_l;
    u_short	conf_rot_h,		/* rotational speed */
		conf_rot_l;
    u_short	conf_head_sw_h,		/* head switch time */
		conf_head_sw_l;
    u_short	conf_wtor_h,		/* write to read recovery time */
		conf_wtor_l;
    u_char	conf_mfg[4];		/* manufacturer ascii */
    u_char	conf_model[8];		/* model */
    u_char	conf_rev[4];		/* revision */
    u_char	conf_id[8];
    u_char	conf_switches[2];	/* drive switches */
#define		CONF_VU_PAD	0x40
    u_char	conf_vu[CONF_VU_PAD];	/* ... vendor unique */
};

struct	ipi_fmtfix {
    u_short	fmtfix_len;		/* number of bytes remaining */
    u_char	fmtfix_type;		/* type of format specification */
#define		  FMTFIX_TYPE	1	/*    fixed block */
    u_char	fmtfix_flags;		/* capability flags */
#define		  FMTFIX_FLAGS_INIT	0x80	/* initialized */
#define		  FMTFIX_FLAGS_MFGDFLT	0x40	/* manufacturer's default */
#define		  FMTFIX_FLAGS_SECM_2	0x20	/* sector mode 2 */
#define		  FMTFIX_FLAGS_SECM_1	0x10	/* sector mode 1 */
#define		  FMTFIX_FLAGS_SOFT	0x08	/* soft sectored */
#define		  FMTFIX_FLAGS_HARD	0x04	/* hard sectored */
#define		  FMTFIX_FLAGS_FDC	0x02	/* use field data controls */
#define		  FMTFIX_FLAGS_SDC	0x01	/* use sector data controls */
#define		  FMTFIX_FLAGS_BITS	\
"\20\10INIT\7MFGDFLT\6SECM_2\5SECM_1\4SOFT\3HARD\2FDC\1SDC"
    u_short	fmtfix_nspt;		/* number of sectors per track */
    u_short	fmtfix_pnbps_h;		/* physical number bytes per sector */
    u_short	fmtfix_pnbps_l;		/* physical number bytes per sector */
    u_short	fmtfix_nbskip;		/* number of begining header bytes to skip */
    u_short	fmtfix_nfps;		/* number of fields per sector */
    u_short	fmtfix_fld1_len_h;	/* size of header field */
    u_short	fmtfix_fld1_len_l;	/* size of header field */
    u_short	fmtfix_fld1_tad;	/* header turn around delay */
    u_short	fmtfix_fld2_len_h;	/* size of data field */
    u_short	fmtfix_fld2_len_l;	/* size of data field */
    u_short	fmtfix_fld2_tad;	/* data turn around delay */
    u_short	fmtfix_fld3_len_h;	/* size of ecc field */
    u_short	fmtfix_fld3_len_l;	/* size of ecc field */
    u_short	fmtfix_fld3_tad;	/* ecc turn around delay */
};

struct ipi_stat {
    u_char	stat_esb;		/* exception status byte */
#define		  ESB_STAT		0x80	/* Status Response */
#define		  ESB_UNEX		0x40	/* unsolicited exception */
#define		  ESB_BCEX		0x20	/* bus control exception */
#define		  ESB_READ_F		0x10	/* read fault */
#define		  ESB_WRITE_F		0x08	/* write fault */
#define		  ESB_SEEK_F		0x04	/* seek fault */
#define		  ESB_SPIN_F		0x02	/* spindle fault */
#define		  ESB_EX_F		0x01	/* execution fault */
#define		  ESB_BITS		\
"\20\10STAT\7UNEX\6BCEX\5READ_F\4WRITE_F\3SEEK_F\2SPIN_F\1EX_F"
    u_char	stat_unex;		/* unsolicited exception status byte */
#define		  UNEX_RESET		0x80	/* reset complete */
#define		  UNEX_APPS		0x40	/* alt port priority select */
#define		  UNEX_APFC		0x20	/* alt port format changed */
#define		  UNEX_APFD		0x10	/* alt port format done */
#define		  UNEX_NRDY		0x04	/* not ready */
#define		  UNEX_RDY		0x02	/* ready */
#define		  UNEX_CMEDIA		0x01	/* media change */
#define		  UNEX_BITS		\
"\20\10RESET\7APPS\6APFC\5APFD\3NRDY\2RDY\1CMEDIA"
    u_char	stat_bcex;		/* bus control exception status byte */
#define		  BCEX_IBC		0x80	/* invalid bus control */
#define		  BCEX_IP		0x40	/* invalid parameter */
#define		  BCEX_UBC		0x20	/* unsupported bus control */
#define		  BCEX_BCC		0x10	/* bus control context */
#define		  BCEX_DBCL		0x08	/* data bus control late */
#define		  BCEX_BITS		\
"\20\10IBC\7IP\6UBC\5BCC\4DBCL"
    u_char	stat_slex_0;		/* slave status byte */
#define		  SLEX_0_SPEED		0x80	/* speed fault */
#define		  SLEX_0_OFFCYL		0x40	/* off cylinder fault */
#define		  SLEX_0_HSEL		0x20	/* head select fault */
#define		  SLEX_0_VOLT		0x04	/* voltage fault */
#define		  SLEX_0_LTEMP		0x02	/* logic temperature fault */
#define		  SLEX_0_ATEMP		0x01	/* actuator temp fault */
#define		  SLEX_0_BITS		\
"\20\10SPEED\7OFFCYL\6HSEL\3VOLT\2LTEMP\1ATEMP"
    u_char	stat_slex_1;		/* slave status byte */
#define		  SLEX_1_WPROT		0x80	/* write protect fault */
#define		  SLEX_1_WCUR		0x40	/* write current fault */
#define		  SLEX_1_WTRAN		0x20	/* write transition fault */
#define		  SLEX_1_HEADO		0x10	/* head offset fault */
#define		  SLEX_1_DS		0x08	/* data strobe fault */
#define		  SLEX_1_BITS		\
"\20\10WPROT\7WCUR\6WTRAN\5HEAD0\4DS"
    u_char	stat_slex_2;		/* slave status byte (vendor unique) */
    u_char	stat_slex_3;		/* slave status byte (vendor unique) */
    u_char	stat_slex_4;		/* slave status byte (vendor unique) */
};

#ifdef	TODO
struct ipi_estat {
};
#endif	TODO

struct	ipi_defect {		/* ipi defect */
    u_short	defect_cyl_h,
		defect_cyl_l;
    u_short	defect_head;
    u_short	defect_off_h,
		defect_off_l;
    u_short	defect_len;
};

struct	ipi_defl {		/* ipi defect list */
    u_short	defl_len;		/* number of bytes remaining */
    u_char	defl_flags;		/* defect list flags */
#define		  DEFL_FLAGS_LAST	0x80	/* last data field of map */
#define		  DEFL_FLAGS_NXTCYL	0x40	/* defect map continues */
#define		  DEFL_FLAGS_SECTOR	0x20	/* sector list used */
#define		  DEFL_FLAGS_FOPT	0x10	/* field options used */
#define		  DEFL_FLAGS_OUTSEQ	0x04	/* defects out of sequence */
#define		  DEFL_FLAGS_BITS	\
"\20\10LAST\7MORE\6SECTOR\5FOPT\4SEQ"
    u_char	defl_copy;		/* copy number */
#define		  DEFL_COPY_MAX		3
#define		  DEFL_COPY_IGNORE	0xFF
    u_short	defl_sets_per_map;	/* number of sets in map */
    u_short	defl_set;		/* number of this set */
    u_short	defl_fss_cyl_h,		/* cylinder address of format spec */
		defl_fss_cyl_l;
    u_short	defl_fss_head;		/* head address of format spec */
    struct	ipi_defect defl_defects; /* ... defects */
    /*...*/
/*  u_short	defl_crc;		/* CRC-16 (x16 + x15 + x2 + 1) */
};

/* pick up (set) 4 byte "_h _l" field in (from) an int */
#define	IPI_HL(x)		((x/**/_h<<16)|(x/**/_l))
#define	IPI_HL_SET(x, v)	(x/**/_h=(v)>>16, x/**/_l=(v))
