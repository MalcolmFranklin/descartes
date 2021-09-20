/* @(#) sodio.h 1.1@(#) Solbourne id 9/22/93 00:08:15 */
/* structures and defines for so ioctls */
struct sod_par {
	long	sp_base;		/* base sector in file system blocks */
	long	sp_size;		/* size in file system blocks */
	};

struct sod_err {
	long	sod_err_type;
	long	sod_err_sense_key;
	long	sod_err_error_code;
};

#define	SODIOSETBASE	_IOW(o,0,struct sod_par)   /* set the base block #  */
#define	SODIOGETBASE	_IOR(o,1,struct sod_par)   /* get the base block #  */
#define	SODIOBLKSIZE	_IOR(o,2,int)	/* get the block size               */
#define	SODIOODSIZE	_IOR(o,3,int)	/* get the max block #              */
#define	SODIOLOAD	_IOW(o,4,int)	/* load the disk                    */
#define SODIOSBLKSIZE	_IOW(o,5,int)	/* set the block size               */
#define SODIOCDSIZE	_IOR(o,6,int)	/* get cd max block #               */
#define SODIOERROR	_IOR(o,7,struct sod_err) /* get drive type,         */
						   /* sense key, error code */
#define SODIOBLNKCHK	_IOW(o,8,int)	/* test for blank sector	    */
