/* @(#) fdreg.h 1.1@(#) Solbourne id 9/22/93 00:06:21 */
/*
 * Copyright 1988 Solbourne Computer, Inc.
 * All rights reserved.
 */

#define FD_DEBUG 0
#ifdef S4000
#define PAD(x) u_char fd_pad/**/x[15]
/*
 * Register set for 82077 in PS/2 mode
 */
struct fdreg {
    u_char fd_sra;		/* Status Register A (ro) */
    PAD(0);
    u_char fd_srb;		/* Status Register B (ro) */
    PAD(1);
    u_char fd_dor;		/* Digital Output Register (rw) */
    PAD(2);
    u_char fd_reserved0;	/* Reserved register */
    PAD(3);
    u_char fd_msr;		/* Main Status Register (read)
				 * Data Rate Select Register (write)
				 */
    PAD(4);
    u_char fd_fifo;		/* Data FIFO (rw) */
    PAD(5);
    u_char fd_reserved1;	/* Reserved register */
    PAD(6);
    u_char fd_dir;		/* Digital Input Register (read)
				 * Configuration Control Register (write)
				 */
    PAD(7);
};

#define fd_dsr fd_msr
#define fd_ccr fd_dir

#define LOW_DENSITY	0x40	/* When this bit is set in Status Register A
				 * a low density floppy is inserted.
				 */
#define FD_CLRRST	0x04	/* clear reset condition */
#define FD_DMAGATE	0x08	/* This should have any effect. The manual
				 * states the if IDENT pin is tied to VSS
				 * DMAGATE has no effect upon INT and DRQ.
				 */
#define MOT_EN		0x10	/* Enable motor */
#define FD_EJECT	0x40	/* The IDT has MOT EN2 tied to pin1 on the
				 * floppy cable which causes the drive to
				 * ejecj
				 */
#define TC_SET		0x80	/* MOT EN3 is tied back into the chip to
				 * pin 25 which is TC(terminal count).
				 * TC is an active low signal in the PS/2 mode
				 * and should be driven high normally. The
				 * invert pin inverts the bits in the DOR
				 * so by setting MOT EN3 we will actually
				 * be driving TC low.
				 */
#define TC_CLR		0x00	/* clear terminal count */
#define INT_PEND	0x80	/* SRA has a interrupt pending bit.  The
				 * documentation indicates that after
				 * programming the data rate the driver should
				 * wait until an interrupt is pending before
				 * issuing SENSE_INTR which makes some sense.
				 * The driver used to have a 400us delay
				 * instead of checking for interrupt.
				 */
#define DSK_CHG		0x80	/* Monitor the pin of the same name and
				 * reflects the opposite value seen on the
				 * disk cable, regardless of the value of
				 * XINVERT.  This should only be tested
				 * after a command has been sent otherwise
				 * its value is bogus.
				 */
#else
/*
 * Parameters for PC AT floppy disk driver using 82072 floppy controller.
 */
struct fdreg {
	u_char	fd_pad_0[0x81];
	u_char	fd_xx_eject;
	u_char	fd_pad_1[0x1F];
	u_char	fd_cr;			/* 82072 Controller register */
#define		fd_msr		fd_cr	/* MSR: Main Status bits (read) */
#define 	fd_dsr		fd_cr	/* DSR: Datarate Sel bits (write) */
	u_char	fd_pad_2[0x01];
	u_char	fd_fifo;		/* 82072 FIFO register */
	u_char	fd_pad_3[0x1D];
	u_char	fd_xx_vec;
	u_char	fd_pad_4[0x0F];
	u_char	fd_xx_am;
	u_char	fd_pad_5[0x0F];
	u_char	fd_xx_csr;
#define		  FD_XX_CSR_TC		0x80	/* requires board rework. */
#define		  FD_XX_CSR_FCIE	0x01
#define		  FD_XX_CSR_SMRST	0x04
	u_char	fd_pad_6[0x0F];
	u_char	fd_xx_cacr;
	u_char	fd_pad_7[0x0F];
};
#endif /* S4000

#define MSR_FDBSY_MSK	0x0F    /* which drives are seeking */
#define MSR_FDBSY_0	0x01
#define MSR_FDBSY_1	0x02
#define MSR_FDBSY_2	0x04
#define MSR_FDBSY_3	0x08
#define MSR_FCBUSY	0x10	/* ctlr busy bit */
#define MSR_NODMA	0x20    /* ctlr in data phase non-DMA mode */
#define MSR_IODIR	0x40	/* I/O direction, 1 = read, 0 = write */
#define MSR_IODIR_R	0x40	/*   read fifo/disk */
#define MSR_IODIR_W	0x00	/*   write fifo/disk */
#define MSR_IORDY	0x80	/* data register ready to xfer bit */
#define MSR_BITS	\
"\20\10IORDY\7IODIR_R\6NDMA\5CBUSY\4DBSY_3\3DBSY_2\2DBSY_1\1DBSY_0"

#define DSR_SWRESET 	0x80	/* Software reset */
#define DSR_PWRDOWN	0x40	/* Power down */
#define DSR_ENAPLL	0x20	/* Enable PLL */
#define DSR_PRECOMP	0x1C	/* Pre-compensation */
#define DSR_DRATESEL	0x03	/* Data rate select */
#define   MFM_R1M	3	/* MFM    1 Mbps */
#define   MFM_R500K	0	/* MFM  500 Kbps */
#define   MFM_R300K	1	/* MFM  300 Kbps */
#define   MFM_R250K	2	/* MFM  250 Kbps */
#define   FM_R250K	0	/* FM   250 Kbps */
#define   FM_R150K	1	/* FM   150 Kbps */
#define   FM_R125K	2	/* FM   125 Kbps */


/* Floppy controller commands */
union	fdc_cmd {
    u_char	cmd;			/* quick access to command code */
#define		  CMD_MT	0x80	/*     cmd modifier, multi-track */
#define		  CMD_DEN_MFM	0x40	/*     cmd modifier, MFM mode */
#define		  CMD_DEN_FM	0x00	/*     cmd modifier, FM mode */
#define		  CMD_SK	0x20	/*     cmd modifier, skip flag */
#define		  CMD_MSK	0x1F	/*     mask for command */
#define		  CMD_BITS	"\20\10MULTI-TRK\7MFM\6SKIP"
    struct cmd_dt {			/* data transfer commands */
	u_char	dt_cmd;			/*   command code */
#define		  CMD_READTRACK	0x02	/*     read entire track */
#define		  CMD_WR	0x05	/*     write data */
#define		  CMD_RD	0x06	/*     read data */
#define		  CMD_WRITEDEL	0x09	/*     write deleted data */
#define		  CMD_READDEL	0x0C	/*     read deleted data */
#define		  CMD_VERIFY	0x16	/*     verify (077 only) */
	u_char	dt_h_ds;		/*   head, drive */
	u_char	dt_c;			/*   cylinder [0-255] */
	u_char	dt_h;			/*   head [0-1] */
	u_char	dt_r;			/*   sector */
	u_char	dt_n;			/*   sector size code */
#define		  N_128		00
#define		  N_256		01
#define		  N_512		02
	u_char	dt_eot;			/*   end of track sector number */
	u_char	dt_gpl;			/*   gap 3 size */
	u_char	dt_dtl;			/*   special sector size */
#define		  DTL_DC	0xFF	/*     DONT CARE, n != 0 */
    }   cmd_dt;
    struct cmd_fmt {
	u_char	fmt_cmd;		/* format command */
#define		  CMD_FORMAT	0x0D	/*   format track */
	u_char	fmt_h_ds;		/*   head, drive */
	u_char	fmt_n;			/*   sector size code */
	u_char	fmt_sc;			/*   number of sectors/track */
	u_char	fmt_gpl;		/*   gap 3 size */
	u_char	fmt_d;			/*   special sector size */
    }   cmd_fmt;
    struct cmd_rcal {			/* recalibrate drive (goto trk 0) */
	u_char	rcal_cmd;
#define		  CMD_RECAL	0x07
	u_char	rcal_h_ds;
    }   cmd_rcal;
    struct cmd_seek {			/* seek to track */
	u_char	seek_cmd;
#define		  CMD_SEEK	0x0F
	u_char	seek_h_ds;
	u_char	seek_c;
    }   cmd_seek;
    struct cmd_sis {			/* sense interrupt status */
	u_char	sis_cmd;
#define		  CMD_SENSE_INT	0x08
    }   cmd_sis;
    struct cmd_sds {			/* sense drive status */
	u_char	sds_cmd;
#define		  CMD_SENSE_DRV	0x04
	u_char	sds_h_ds;
    }   cmd_sds;
    struct cmd_rid {			/* read id */
	u_char	rid_cmd;
#define		  CMD_READID	0x0A
	u_char	rid_h_ds;
    }   cmd_rid;
    struct cmd_conf {			/* configure */
	u_char	conf_cmd;
#define		  CMD_CONFIG	0x13
	u_char	conf_mot;
	u_char	conf_p;
#define		  CONF_P_EIS	0x40	/*   Enable Implied Seek */
#define		  CONF_P_DFIFO	0x20	/*   Disable FIFO */
#define		  CONF_P_DPOLL	0x10	/*   Disable poll of drives */
#define		  CONF_P_FTH	0x0F	/*   FIFO threshold mask */
	u_char	conf_pretrk;
    }   cmd_conf;
    struct cmd_spec {			/* specify */
	u_char	spec_cmd;
#define		  CMD_SPECIFY	0x03
	u_char	spec_srt_hut;
	u_char	spec_hlt_nd;
    }   cmd_spec;
    u_char	cmd_bytes[9];		/* byte access to commands */
};


/* Floppy controller command results */
union	fdc_rsl {
    struct rsl_sds {			/* result of sense drive status cmd */
	u_char	rsl_sds_st3;		/*   Status Register 3 bits */
#define		  ST3_FAULT	0x80	/*     Fault from selected disk */
#define		  ST3_WPROT	0x40	/*     status of WP pin */
#define		  ST3_RDY	0x20	/*     status of RDY pin */
#define		  ST3_TRK0	0x10	/*     status of TRK0 pin */
#define		  ST3_TS	0x08	/*     Two Sided of TRK0 pin */
#define		  ST3_HEAD	0x04	/*     status of HDSEL pin */
#define		  ST3_DS_MSK	0x03	/*     status of DS pin */
#define		  ST3_BITS	\
"\20\10FAULT\7WRITE_PROTECTED\6READY\5TRACK_0\4TS\3HEAD1\2DS1\1DS0"
    }   rsl_sds;
    struct rsl_dump {			/* result of dumpreg command */
	u_char	dump_pcn0;
	u_char	dump_pcn1;
	u_char	dump_pcn2;
	u_char	dump_pcn3;
	u_char	dump_spec0;
	u_char	dump_spec1;
	u_char	dump_eot;
	u_char	dump_undef;
	u_char	dump_conf0;
	u_char	dump_conf1;
    }   rsl_dump;
    struct rsl_sis {			/* result of sense intr status cmd */
	u_char	sis_st0;		/*   see below... */
	u_char	sis_c;			/*   cylinder */
    }   rsl_sis;
    u_char	rsl_ver;		/* result of version command */
    struct rsl {			/* result of all other commands */
	u_char	rsl_st0;		/*   Status Register 0 bits */
#define		  ST0_ICODE_MSK	0xC0	/*     interrupt code mask */
#define		  ST0_ICODE_OK	0x00	/*     normal termination */
#define		  ST0_ICODE_ERR	0x40	/*     abnormal termination */
#define		  ST0_ICODE_INV	0x80	/*     invalid command termination */
#define		  ST0_ICODE_NR	0xC0	/*     RDY signal chang during cmd */
#define		  ST0_SEEKEND	0x20	/*     (implied) seek completed */
#define		  ST0_EQCHK	0x10	/*     cant find TRK0 */
#define		  ST0_NOTRDY	0x08	/*     RDY pin became 0 during cmd */
#define		  ST0_HEAD	0x04	/*     current head */
#define		  ST0_DS_MSK	0x03	/*     current drive */
#define		  ST0_BITS	\
"\20\10INVALID\7ABNORMAL\6SEEK_DONE\5EQCHK\4NOT_READY\3HEAD1\2DS1\1DS0"
	u_char	rsl_st1;		/*   Status Register 1 bits */
#define		  ST1_EOCYL	0x80	/*     end of cylinder */
#define		  ST1_CRCERR	0x20	/*     crc error in id or data field */
#define		  ST1_OVRRUN	0x10	/*     data overrun/underrun */
#define		  ST1_NODATA	0x04	/*     cant find requested data */
#define		  ST1_WP	0x02	/*     WP pin became 1 during a write */
#define		  ST1_MADR	0x01	/*     missing address mark */
#define		  ST1_BITS	\
"\20\10END_OF_CYL\6CRC_ERROR\5OVER/UNDER_RUN\3SECTOR_NOT_FOUND\2NOT_WRITABLE\1MISSING_ADDRESS_MARK"
	u_char	rsl_st2;		/*   Status Register 2 bits */
#define		  ST2_CM	0x40	/*     Control Mark */
#define		  ST2_CRCERRD	0x20	/*     CRC error in data field */
#define		  ST2_WC	0x10	/*     drive on wrong cylinder */
#define		  ST2_SH	0x08	/*     scan hit */
#define		  ST2_SN	0x04	/*     scan not satisfied */
#define		  ST2_BC	0x02	/*     bad cylinder */
#define		  ST2_MD	0x01	/*     missing data address mark */
#define		  ST2_BITS	\
"\20\7CONTROL_MARK\6DATA_ERROR\5WRONG_CYL\4SH\3SN\2BAD_CYL\1MISSING_DATA"
	u_char	rsl_c;			/*   cylinder */
	u_char	rsl_h;			/*   head */
	u_char	rsl_r;			/*   sector */
	u_char	rsl_n;			/*   sector size code */
    }   rsl;
    u_char	rsl_bytes[7];		/* byte access to results */
};


/* command information table indexed by command code */
struct fdcmd_tlb {
	char	*cmd_name;
	char	cmd_cmd_bytes;	/* number of bytes to xfer in command phase */
	char	cmd_rsl_bytes;	/* number of bytes to xfer in result phase */
	short	cmd_flags;	/* flags about command */
#define		  CMD_FLAGS_DATA	0x0001	/* command has data phase */
#define		  CMD_FLAGS_DIR		0x0002	/* direction of data */
#define		  CMD_FLAGS_DIR_IN	0x0000	/* data comes in */
#define		  CMD_FLAGS_DIR_OUT	0x0002	/* data goes out */
#define		  CMD_FLAGS_DATADIR	(CMD_FLAGS_DATA|CMD_FLAGS_DIR)
#define		  CMD_FLAGS_DATAIN	(CMD_FLAGS_DATA|CMD_FLAGS_DIR_IN)
#define		  CMD_FLAGS_DATAOUT	(CMD_FLAGS_DATA|CMD_FLAGS_DIR_OUT)
#define		  CMD_FLAGS_RSLT	0x0004	/* command has result phase */
#define		  CMD_FLAGS_INT		0x0008	/* command interrupts */
#define		  CMD_FLAGS_MEDIA	0x0010	/* command accesses media */
#define		  CMD_FLAGS_HAS_MT	0x0020	/* command has MT modifier */
#define		  CMD_FLAGS_HAS_DEN	0x0040	/* command has density mod */
#define		  CMD_FLAGS_HAS_SK	0x0080	/* command has MT modifier */
#define		  CMD_FLAGS_BITS	\
"\20\10SK\7DEN\6MT\5MEDIA\4INTR\3RSL\2OUT\1DATA"
};

#define	FDCMD_TLB	{ 						\
    {""}, 								\
    {""}, 								\
    {"READ TRK",							\
	sizeof(struct cmd_dt), sizeof(struct rsl),			\
	CMD_FLAGS_DATAIN|CMD_FLAGS_RSLT|CMD_FLAGS_INT|CMD_FLAGS_MEDIA|	\
	CMD_FLAGS_HAS_DEN},						\
    {"SPECIFY",								\
	sizeof(struct cmd_spec), 0,					\
	},				 				\
    {"SENSE DRIVE",							\
	sizeof(struct cmd_sds), sizeof(struct rsl_sds),			\
	CMD_FLAGS_RSLT|CMD_FLAGS_MEDIA},				\
    {"WRITE",								\
	sizeof(struct cmd_dt), sizeof(struct rsl),			\
	CMD_FLAGS_DATAOUT|CMD_FLAGS_RSLT|CMD_FLAGS_INT|CMD_FLAGS_MEDIA|	\
	CMD_FLAGS_HAS_MT|CMD_FLAGS_HAS_DEN},				\
    {"READ",								\
	sizeof(struct cmd_dt), sizeof(struct rsl),			\
	CMD_FLAGS_DATAIN|CMD_FLAGS_RSLT|CMD_FLAGS_INT|CMD_FLAGS_MEDIA|	\
	CMD_FLAGS_HAS_MT|CMD_FLAGS_HAS_DEN|CMD_FLAGS_HAS_SK},		\
    {"RECALIBRATE",							\
	sizeof(struct cmd_rcal), 0,					\
	CMD_FLAGS_INT|CMD_FLAGS_MEDIA},					\
    {"SENSE INT",							\
	sizeof(struct cmd_sis), sizeof(struct rsl_sis),			\
	CMD_FLAGS_RSLT},						\
    {"WRITE DEL",							\
	sizeof(struct cmd_dt), sizeof(struct rsl),			\
	CMD_FLAGS_DATAOUT|CMD_FLAGS_RSLT|CMD_FLAGS_INT|CMD_FLAGS_MEDIA|	\
	CMD_FLAGS_HAS_MT|CMD_FLAGS_HAS_DEN},				\
    {"READ ID",								\
	sizeof(struct cmd_rid), sizeof(struct rsl),			\
	CMD_FLAGS_RSLT|CMD_FLAGS_INT|CMD_FLAGS_MEDIA|			\
	CMD_FLAGS_HAS_DEN},						\
    {""},								\
    {"READ DEL",							\
	sizeof(struct cmd_dt), sizeof(struct rsl),			\
	CMD_FLAGS_DATAIN|CMD_FLAGS_RSLT|CMD_FLAGS_INT|CMD_FLAGS_MEDIA|	\
	CMD_FLAGS_HAS_MT|CMD_FLAGS_HAS_DEN|CMD_FLAGS_HAS_SK},		\
    {"FMT TRK",	/* DONT GENERATE TC!!! */				\
	sizeof(struct cmd_fmt), sizeof(struct rsl),			\
	CMD_FLAGS_DATAOUT|CMD_FLAGS_RSLT|CMD_FLAGS_INT|CMD_FLAGS_MEDIA|	\
	CMD_FLAGS_HAS_DEN},						\
    {"DUMPREG",								\
	1, 10,								\
	},								\
    {"SEEK",								\
	sizeof(struct cmd_seek), 0,					\
	CMD_FLAGS_INT|CMD_FLAGS_MEDIA},					\
    {"VERSION"},							\
    {"SCANEQ"},								\
    {"PERP"},	 							\
    {"CONFIG",								\
	sizeof(struct cmd_conf), 0,					\
	},								\
    {""},								\
    {""},								\
    {"VERIFY"},								\
    {""},								\
    {""},								\
    {"SCANLE"},								\
    {""},								\
    {""},								\
    {""},								\
    {"SCANHI"},								\
    {""},								\
    {""}								}
