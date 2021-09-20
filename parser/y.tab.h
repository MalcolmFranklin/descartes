typedef union{
        int ival;
        NODE symbol;
} YYSTYPE;
#define	NEW_LINE	258
#define	NEW_PAGE	259
#define	RETURN	260
#define	R_PAR	261
#define	L_PAR	262
#define	INDENT	263
#define	RANGE	264
#define	LITERALS	265
#define	REFER	266
#define	MATCH	267
#define	CAP_C	268
#define	P_PLUS	269
#define	P_MINUS	270
#define	P_TIMES	271
#define	P_DIVIDED_BY	272
#define	P_RAISED_TO	273
#define	P_EQUAL	274
#define	P_NOT_EQUAL	275
#define	P_GREATER_THAN	276
#define	P_LESS_THAN	277
#define	P_GREATER_THAN_OR_EQUAL	278
#define	P_LESS_THAN_OR_EQUAL	279
#define	P_OR	280
#define	P_AND	281
#define	P_NOT	282
#define	P_PARALLEL	283
#define	P_CONCUR	284
#define	P_EQUAL_TO	285
#define	P_TIMER	286
#define	P_SEND_TO	287
#define	P_RECEIVE_FROM	288
#define	P_DELAY	289
#define	P_ASEND_TO	290
#define	P_ARECEIVE_FROM	291
#define	P_GTIME	292


extern YYSTYPE yylval;
