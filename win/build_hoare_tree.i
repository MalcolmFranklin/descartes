
#line 37 "/usr/tmp/MWFAAa10474"
#pragma assembly_label(text,"clcc_1_0.")
#pragma onwarn(303)
#line 12 "build_hoare_tree.c"
 
#line 125
static char    *rcsid = "@(#) $Id: build_hoare_tree.c,v 1.26 1994/08/04 17:53:19 franklin Exp franklin $";
#line 7 "/tmp_mnt/home/tools1/CenterLine/clcc/sparc-sunos4/inc/stdlib.h"
 
#line 7 "/tmp_mnt/home/tools1/CenterLine/clcc/sparc-sunos4/inc/sizet.h"
 
#line 27
 typedef int size_t;  
#line 26 "/tmp_mnt/home/tools1/CenterLine/clcc/sparc-sunos4/inc/stdlib.h"
typedef _wchar_t wchar_t;




typedef struct { int quot; int rem; } div_t;
typedef struct { long quot; long rem; } ldiv_t;
#line 70
 
extern  double          atof(const char *__nptr);

extern  long double     _atold(const char *__nptr);

extern  int             atoi(const char *__nptr);
extern  long            atol(const char *__nptr);
extern  double          strtod(const char *__nptr, char **__endptr);
extern  long            strtol(const char *__nptr, char **__endptr, int __base);
extern  unsigned long   strtoul(const char *__nptr, char **__endptr, int __base);
#line 96
 



extern  int             rand(void);
extern  void            srand(unsigned int __seed);

 
extern  void *          calloc(size_t __nelem, size_t __size);
extern  void            free(void *__ptr);
extern  void *          malloc(size_t __size);
extern  void *          realloc(void *__ptr, size_t __size);

 
extern  void            abort(void);
extern  int             atexit(void (*func)(void));
extern  void            exit(int __status);
extern  char *          getenv(const char *__name);
extern  int             system(const char *__string);

 
extern char * _itoa(int, char *, int);
extern char * _ltoa(long ,char *, int);
extern char * _ultoa(unsigned long ,char *, int);
extern char * _ecvt(double, int, int *, int *);
extern char * _fcvt(double, int, int *, int *);
extern char * _gcvt(double, int, char *);

extern char * itoa(int, char *, int);
extern char * ltoa(long ,char *, int);
extern char * ultoa(unsigned long ,char *, int);
extern char * ecvt(double, int, int *, int *);
extern char * fcvt(double, int, int *, int *);
extern char * gcvt(double, int, char *);
#line 153
 
extern  void *          bsearch(const void *__key, const void *__base,
                                size_t __nmemb, size_t __size,
                                int (*__compar)(const void *, const void *));
extern  void            qsort(void *__base, size_t __nmemb, size_t __size,
                                int (*__compar)(const void *, const void *));

 


extern  int             abs(int __j);
extern  long            labs(long int __j);
#line 174
extern  div_t           div(int __numer, int __denom);
extern  ldiv_t          ldiv(long int __numer, long int __denom);

 
extern  int  mblen(const char *__s, size_t __n);

extern  int             mbtowc(wchar_t *__pwc, const char *__s, size_t __n);
extern  int             wctomb(char *__s, wchar_t __wchar);

 
extern  size_t          mbstowcs(wchar_t *__pwcs, const char *__s, size_t __n);
extern  size_t          wcstombs(char *__s, const wchar_t *__pwcs, size_t __n);
#line 20 "cchk_missing_stdlib.h"
 
#line 37
static char    *cchk_missing_stdlib_h_rcsid = "$Id: cchk_missing_stdlib.h,v 1.2 1994/08/04 18:18:27 franklin Exp $";
#line 7 "/tmp_mnt/home/tools1/CenterLine/clcc/sparc-sunos4/inc/stdio.h"
 
#line 29
 
#line 42
typedef long fpos_t;

 



 
#line 60
 
extern int _fopen_max;




 
#line 83
 
#line 91
 

 

    typedef int _iob_cnt_t;
    typedef char _iob_ptr_t;
    typedef int _bufsiz_t;
    typedef short _iob_flag_t;
    typedef char _iob_file_t;

    typedef struct {
 _iob_cnt_t _cnt;
 _iob_ptr_t *_ptr;
 _iob_ptr_t *_base;
 _bufsiz_t _bufsiz;
 _iob_flag_t _flag;
 _iob_file_t _file;
 char _unused[1];     
 } FILE;
#line 305
 
enum {
    _IOFBF =  0x0000,   
    _IOREAD =  0x0001,   
    _IOWRT =  0x0002,   
    _IONBF =  0x0004,   
    _IOMYBUF =  0x0008,   
    _IOEOF =  0x0010,   
    _IOERR =  0x0020,   
 




 _IOSTRG =      0x0040,          
 _IOLBF = 0x0080,   
 _IORW =  0x0100   
 
    };

 
#line 333
 
#line 346
 
typedef enum {
    _FIOAPPEND =    0x0001,          
 


 


    _FIOALLOCATED =     0x0008          
    } _iob_fioflag_t;

 
typedef struct {
    _iob_cnt_t _iob_cnt;         
    int _bufsiz;          
    unsigned char *_base;  
    unsigned char *_ptr;  
    } _iob_unget_t;
#line 370
 
#line 378
     
    extern char *_iob_tmpnam[];   
    extern _iob_fioflag_t _iob_fioflag[];  
    extern _iob_unget_t _iob_unget[];  
 


 
 
    extern FILE _iob [];
#line 409
extern int remove(const char *__pathname);
extern int rename(const char *__old, const char *__new);
extern FILE *tmpfile(void);
extern char *tmpnam(char *__s);
extern int fclose(FILE *__stream);
extern int fflush(FILE *__stream);
extern FILE *fopen(const char *__pathname, const char *__type);

    extern FILE *fdopen(int __fd, const char *__type);

extern FILE *freopen(const char *__pathname, const char *__type, FILE *__stream);
extern void setbuf(FILE *__stream, char *__buf);
extern int setvbuf(FILE *__stream, char *__buf, int __type, size_t __size);
extern size_t fread
  (void *__ptr, size_t __size, size_t __nelem, FILE *__stream);
extern size_t fwrite
  (const void *__ptr, size_t __size, size_t __nelem, FILE *__stream);
extern int fgetc(FILE *__stream);


extern int getc(FILE *__stream);



extern int getchar(void);


extern char *gets(char *__s);
extern char *fgets(char *__s, int __N, FILE *__stream);
extern int fputs(const char *__s, FILE *__stream);
extern int fputc(int __c, FILE *__stream);
#line 466
    extern char *tempnam(char *dir,char *prefix);



extern int putc(int __c, FILE *__stream);


extern int putchar(int __c);

extern int puts(const char *__s);
extern int ungetc(int __c, FILE *__stream);
extern int fseek(FILE *__stream, long __offset, int __ptrname);
extern long ftell(FILE *__stream);
extern void rewind(FILE *__stream);
extern int fsetpos(FILE *__stream, const fpos_t *__pos);
extern int fgetpos(FILE *__stream, fpos_t *__pos);


extern void clearerr(FILE *__stream);
 



extern int feof(FILE *__stream);



extern int ferror(FILE *__stream);


extern void perror(const char *__s);
#line 8 "/tmp_mnt/home/tools1/CenterLine/clcc/sparc-sunos4/inc/stdarg.h"
 
#line 32
 
typedef char __vararg_char;




 



        
#line 173
     typedef void *va_list;
#line 499 "/tmp_mnt/home/tools1/CenterLine/clcc/sparc-sunos4/inc/stdio.h"
extern int vprintf(const char *__format, va_list __arg);
extern int vfprintf(FILE *__stream, const char *__format, va_list __arg);
extern int vsprintf(char *__s, const char *__format, va_list __arg);
extern int printf(const char *__format, ...);
extern int fprintf(FILE *__stream, const char *__format, ...);
extern int sprintf(char *__s, const char *__format, ...);
extern int fscanf(FILE *__stream, const char *__format, ...);
extern int scanf(const char *__format, ...);
extern int sscanf(const char *__s, const char *__format, ...);
#line 520
 
#line 8 "/tmp_mnt/home/tools1/CenterLine/clcc/sparc-sunos4/inc/string.h"
 
#line 25
 
extern  void *      memcpy(void *__s1, const void *__s2, size_t __n);
extern  void *      memmove(void *__s1, const void *__s2, size_t __n);
extern  char *      strcpy(char *__s1, const char *__s2);
extern  char *      strncpy(char *__s1, const char *__s2, size_t __n);

 
extern  char *      strcat(char *__s1, const char *__s2);
extern  char *      strncat(char *__s1, const char *__s2, size_t __n);

 
extern  int         memcmp(const void *__s1, const void *__s2, size_t __n);
extern  int         strcmp(const char *__s1, const char *__s2);
extern  int         strcoll(const char *__s1, const char *__s2);
extern  int         strncmp(const char *__s1, const char *__s2, size_t __n);
extern  size_t      strxfrm(char *__s1, const char *__s2, size_t __n);

 
extern  void *      memchr(const void *__s, int __c, size_t __n);
extern  char *      strchr(const char *__s, int __c);
extern  size_t      strcspn(const char *__s1, const char *__s2);
extern  char *      strpbrk(const char *__s1, const char *__s2);
extern  char *      strrchr(const char *__s, int __c);
extern  size_t      strspn(const char *__s1, const char *__s2);
extern  char *      strstr(const char *__s1, const char *__s2);
extern  char *      strtok(char *__s1, const char *__s2);

 
extern  void *      memset(void *__s, int __c, size_t __n);

extern  char *      strerror(int __errnum);

extern  size_t      strlen(const char *__s);

 
extern  void *      _rmemcpy(void *__d, const void *__s, size_t __len);
extern  char *      _rstrcpy(char *__d, const char *__s);
extern  char *      _rstrncpy(char *__d, const char *__s, size_t __len);
extern  char *      _strncat(char *__s1, const char *__s2, size_t __len);
extern  char *      _strcats(int __count, char *__s1, const char *__s2,...);
extern  char *  _strrev(char *__s);


extern char *strdup(const char *s1);
#line 8 "/tmp_mnt/home/tools1/CenterLine/clcc/sparc-sunos4/inc/stdarg.h"
 
#line 20 "cchk_missing_stdarg.h"
 
#line 31
static char    *cchk_missing_stdarg_h_rcsid = "$Id: cchk_missing_signal.h,v 1.1 1994/08/04 17:39:19 franklin Exp $";




 
#line 1 "/usr/include/unistd.h"
 



 

 




 
#line 65
 
#line 1 "/usr/include/sys/types.h"
 



 

 
#line 13
 
#line 20
 
#line 1 "/usr/include/sys/stdtypes.h"
 



 

 
#line 16
 



typedef int  sigset_t;  

typedef unsigned int speed_t;  
typedef unsigned long tcflag_t;  
typedef unsigned char cc_t;   
typedef int  pid_t;   

typedef unsigned short mode_t;   
typedef short  nlink_t;  

typedef long  clock_t;  
typedef long  time_t;   

typedef int  size_t;   
typedef int  ptrdiff_t;  

typedef unsigned short wchar_t;  
#line 51 "/usr/include/sys/types.h"
typedef struct  _physadr_t { unsigned int r[1]; } *physadr_t;
typedef struct label_t {
 int val[2];
} label_t;
#line 62
typedef struct _quad_t { long val[2]; } quad_t;
typedef long daddr_t;
typedef char * caddr_t;
typedef unsigned long ino_t;
typedef short dev_t;
typedef long off_t;
typedef unsigned short uid_t;
typedef unsigned short gid_t;
typedef long key_t;
typedef char * addr_t;
#line 80 "/usr/include/unistd.h"
extern void _exit(                );
extern int access(                           );
extern unsigned alarm(                   );
extern int chdir(                );
extern int chmod(                             );
extern int chown(                                          );
extern int close(                );
extern char *ctermid(             );
extern char *cuserid(             );
extern int dup(                );
extern int dup2(                             );
extern int execl(                     );
extern int execle(                     );
extern int execlp(                     );
extern int execv(                              );
extern int execve(                                            );
extern int execvp(                              );
extern pid_t fork(          );
extern long fpathconf(                      );
extern char *getcwd(                         );
extern gid_t getegid(          );
extern uid_t geteuid(          );
extern gid_t getgid(          );
extern int getgroups(                                       );
extern char *getlogin(          );
extern pid_t getpgrp(          );
extern pid_t getpid(          );
extern pid_t getppid(          );
extern uid_t getuid(          );
extern int isatty(                );
extern int link(                              );
extern off_t lseek(                                          );
extern long pathconf(                          );
extern int pause(          );
extern int pipe(                   );
extern int read(                                               );
extern int rmdir(                );
extern int setgid(               );
extern int setpgid(                           );
extern pid_t setsid(          );
extern int setuid(               );
extern unsigned sleep(                          );
extern long sysconf(              );
extern pid_t tcgetpgrp(                );
extern int tcsetpgrp(                               );
extern char *ttyname(                );
extern int unlink(                );
extern int write(                                               );
#line 21 "cchk_missing_unistd.h"
 
#line 35
static char    *cchk_missing_unistd_h_rcsid = "$Id: cchk_missing_unistd.h,v 1.1 1994/08/04 17:40:25 franklin Exp $";
#line 1 "/usr/include/sys/stat.h"
 



 

 



 
#line 1 "/usr/include/sys/types.h"
 



 

 
#line 13
 
#line 18 "/usr/include/sys/stat.h"
struct stat {
 dev_t st_dev;
 ino_t st_ino;
 mode_t st_mode;
 short st_nlink;
 uid_t st_uid;
 gid_t st_gid;
 dev_t st_rdev;
 off_t st_size;
 time_t st_atime;
 int st_spare1;
 time_t st_mtime;
 int st_spare2;
 time_t st_ctime;
 int st_spare3;
 long st_blksize;
 long st_blocks;
 long st_spare4[2];
};
#line 91
int chmod(                             );
int fstat(                               );
int mkdir(                             );
int mkfifo(                             );
int stat(                                   );
mode_t umask(                 );
#line 155 "build_hoare_tree.c"
 
#line 4 "/home/tools1/uimx2.5/motif12/usr/include/Xm/Text.h"
   


   
 

 

 
#line 4 "/home/tools1/uimx2.5/motif12/usr/include/Xm/Xm.h"
   


   
 

 
#line 1 "/home/local/X11R5/include/X11/Intrinsic.h"
 
#line 25
 
#line 1 "/home/local/X11R5/include/X11/Xlib.h"
 
#line 17
 
#line 24
 
#line 1 "/usr/include/sys/types.h"
 



 

 
#line 13
 
#line 3 "/home/local/X11R5/include/X11/X.h"
 

 
#line 32
 



 

typedef unsigned long XID;

typedef XID Window;
typedef XID Drawable;
typedef XID Font;
typedef XID Pixmap;
typedef XID Cursor;
typedef XID Colormap;
typedef XID GContext;
typedef XID KeySym;

typedef unsigned long Mask;

typedef unsigned long Atom;

typedef unsigned long VisualID;

typedef unsigned long Time;

typedef unsigned char KeyCode;



 
#line 92
 


 
#line 126
 
#line 165
 
#line 178
 
#line 190
 
#line 203
 
#line 211
 
#line 219
 
 
#line 231
 
#line 237
 




 
#line 248
 




 




 




 
#line 271
 
#line 282
 
#line 290
 
#line 324
 

 
 




 
#line 350
 
#line 361
 
#line 375
 



 
#line 385
 
#line 391
 




 
#line 402
 
#line 410
 




 
#line 423
 

 
#line 444
 
#line 450
 
#line 457
 
#line 463
 
#line 470
 




 




 
#line 487
 




 
#line 498
 
#line 504
 
#line 533
 

 
#line 544
 

 
#line 554
 

 
#line 562
 
#line 570
 

 
#line 580
 
#line 589
 
#line 610
 
#line 623
 
#line 630
 

 




 
#line 644
 
#line 654
 
#line 47 "/home/local/X11R5/include/X11/Xlib.h"
 
#line 1 "/home/local/X11R5/include/X11/Xfuncproto.h"
 
#line 15
 

 
#line 24 "/home/local/X11R5/include/X11/Xosdefs.h"
 
#line 36
 
#line 74
 
#line 7 "/tmp_mnt/home/tools1/CenterLine/clcc/sparc-sunos4/inc/stddef.h"
 
#line 18
typedef int ptrdiff_t;
#line 64 "/home/local/X11R5/include/X11/Xlib.h"
typedef char *XPointer;
#line 106
 
#line 131
 
typedef struct _XExtData {
 int number;   
 struct _XExtData *next;  
 int (*free_private)();  
 XPointer private_data;  
} XExtData;



 
typedef struct {   
 int extension;   
 int major_opcode;  
 int first_event;  
 int first_error;  
} XExtCodes;



 

typedef struct {
    int depth;
    int bits_per_pixel;
    int scanline_pad;
} XPixmapFormatValues;




 
typedef struct {
 int function;   
 unsigned long plane_mask; 
 unsigned long foreground; 
 unsigned long background; 
 int line_width;   
 int line_style;    
 int cap_style; 
 
 int join_style;    
 int fill_style; 
 
 int fill_rule;     
 int arc_mode;   
 Pixmap tile;   
 Pixmap stipple;   
 int ts_x_origin;  
 int ts_y_origin;
        Font font;          
 int subwindow_mode;      
 int  graphics_exposures; 
 int clip_x_origin;  
 int clip_y_origin;
 Pixmap clip_mask;  
 int dash_offset;  
 char dashes;
} XGCValues;




 

typedef struct _XGC {
    XExtData *ext_data;  
    GContext gid;  
    int  rects;   
    int  dashes;  
    unsigned long dirty; 
    XGCValues values;  
} *GC;




 
typedef struct {
 XExtData *ext_data;  
 VisualID visualid;  



 int class;   

 unsigned long red_mask, green_mask, blue_mask;  
 int bits_per_rgb;  
 int map_entries;  
} Visual;



    
typedef struct {
 int depth;   
 int nvisuals;   
 Visual *visuals;  
} Depth;
#line 235
 
typedef struct {
 XExtData *ext_data;  
 struct _XDisplay *display; 
 Window root;   
 int width, height;  
 int mwidth, mheight;  
 int ndepths;   
 Depth *depths;   
 int root_depth;   
 Visual *root_visual;  
 GC default_gc;   
 Colormap cmap;   
 unsigned long white_pixel;
 unsigned long black_pixel;  
 int max_maps, min_maps;  
 int backing_store;  
 int  save_unders; 
 long root_input_mask;  
} Screen;



 
typedef struct {
 XExtData *ext_data;  
 int depth;   
 int bits_per_pixel;  
 int scanline_pad;  
} ScreenFormat;



 
typedef struct {
    Pixmap background_pixmap;  
    unsigned long background_pixel;  
    Pixmap border_pixmap;  
    unsigned long border_pixel;  
    int bit_gravity;   
    int win_gravity;   
    int backing_store;   
    unsigned long backing_planes; 
    unsigned long backing_pixel; 
    int  save_under;   
    long event_mask;   
    long do_not_propagate_mask;  
    int  override_redirect;  
    Colormap colormap;   
    Cursor cursor;   
} XSetWindowAttributes;

typedef struct {
    int x, y;    
    int width, height;   
    int border_width;   
    int depth;            
    Visual *visual;   
    Window root;          



    int class;    

    int bit_gravity;   
    int win_gravity;   
    int backing_store;   
    unsigned long backing_planes; 
    unsigned long backing_pixel; 
    int  save_under;   
    Colormap colormap;   
    int  map_installed;   
    int map_state;   
    long all_event_masks;  
    long your_event_mask;  
    long do_not_propagate_mask;  
    int  override_redirect;  
    Screen *screen;   
} XWindowAttributes;




 

typedef struct {
 int family;   
 int length;   
 char *address;   
} XHostAddress;



 
typedef struct _XImage {
    int width, height;   
    int xoffset;   
    int format;    
    char *data;    
    int byte_order;   
    int bitmap_unit;   
    int bitmap_bit_order;  
    int bitmap_pad;   
    int depth;    
    int bytes_per_line;   
    int bits_per_pixel;   
    unsigned long red_mask;  
    unsigned long green_mask;
    unsigned long blue_mask;
    XPointer obdata;   
    struct funcs {   
 struct _XImage *(*create_image)();

 int (*destroy_image)        (struct _XImage *);
 unsigned long (*get_pixel)  (struct _XImage *, int, int);
 int (*put_pixel)            (struct _XImage *, int, int, unsigned long);
 struct _XImage *(*sub_image)(struct _XImage *, int, int, unsigned int, unsigned int);
 int (*add_pixel)            (struct _XImage *, long);
#line 360
 } f;
} XImage;



 
typedef struct {
    int x, y;
    int width, height;
    int border_width;
    Window sibling;
    int stack_mode;
} XWindowChanges;



 
typedef struct {
 unsigned long pixel;
 unsigned short red, green, blue;
 char flags;   
 char pad;
} XColor;
#line 388
 
typedef struct {
    short x1, y1, x2, y2;
} XSegment;

typedef struct {
    short x, y;
} XPoint;
 
typedef struct {
    short x, y;
    unsigned short width, height;
} XRectangle;
 
typedef struct {
    short x, y;
    unsigned short width, height;
    short angle1, angle2;
} XArc;


 

typedef struct {
        int key_click_percent;
        int bell_percent;
        int bell_pitch;
        int bell_duration;
        int led;
        int led_mode;
        int key;
        int auto_repeat_mode;    
} XKeyboardControl;

 

typedef struct {
        int key_click_percent;
 int bell_percent;
 unsigned int bell_pitch, bell_duration;
 unsigned long led_mask;
 int global_auto_repeat;
 char auto_repeats[32];
} XKeyboardState;

 

typedef struct {
        Time time;
 short x, y;
} XTimeCoord;

 

typedef struct {
  int max_keypermod;  
  KeyCode *modifiermap;  
} XModifierKeymap;
#line 451
 
typedef struct _XDisplay {
 XExtData *ext_data;  
 struct _XFreeFuncs *free_funcs;  
 int fd;    
 int lock;   
 int proto_major_version; 
 int proto_minor_version; 
 char *vendor;   
        XID resource_base;  
 XID resource_mask;  
 XID resource_id;  
 int resource_shift;  
 XID (*resource_alloc)();  
 int byte_order;   
 int bitmap_unit;  
 int bitmap_pad;   
 int bitmap_bit_order;  
 int nformats;   
 ScreenFormat *pixmap_format;  
 int vnumber;   
 int release;   
 struct _XSQEvent *head, *tail;  
 int qlen;   
 unsigned long last_request_read;  
 unsigned long request;  
 char *last_req;   
 char *buffer;   
 char *bufptr;   
 char *bufmax;   
 unsigned max_request_size;  
 struct _XrmHashBucketRec *db;
 int (*synchandler)();  
 char *display_name;  
 int default_screen;  
 int nscreens;   
 Screen *screens;  
 unsigned long motion_buffer;  
 Window current;   
 int min_keycode;  
 int max_keycode;  
 KeySym *keysyms;  
 XModifierKeymap *modifiermap;  
 int keysyms_per_keycode; 
 char *xdefaults;  
 char *scratch_buffer;  
 unsigned long scratch_length;  
 int ext_number;   
 struct _XExten *ext_procs;  
 
#line 507
 
 int  (*event_vec[128])();   
 int    (*wire_vec[128])();  
 KeySym lock_meaning;     
 struct _XKeytrans *key_bindings;  
 Font cursor_font;     
 struct _XDisplayAtoms *atoms;  
 struct {      
     long sequence_number;
     int (*old_handler)();
     int  succeeded;
 } reconfigure_wm_window;
 unsigned long flags;     
 unsigned int mode_switch;   
 struct _XContextDB *context_db;  
 int  (**error_vec)();       
 

 
 struct {
    XPointer defaultCCCs;   
    XPointer clientCmaps;   
    XPointer perVisualIntensityMaps;
       
 } cms;
 int conn_checker;          
 struct _XIMFilter *im_filters;
} Display;
#line 542
 
typedef struct {
 int type;   
 unsigned long serial;  
 int  send_event;  
 Display *display;  
 Window window;          
 Window root;          
 Window subwindow;  
 Time time;   
 int x, y;   
 int x_root, y_root;  
 unsigned int state;  
 unsigned int keycode;  
 int  same_screen;  
} XKeyEvent;
typedef XKeyEvent XKeyPressedEvent;
typedef XKeyEvent XKeyReleasedEvent;

typedef struct {
 int type;   
 unsigned long serial;  
 int  send_event;  
 Display *display;  
 Window window;          
 Window root;          
 Window subwindow;  
 Time time;   
 int x, y;   
 int x_root, y_root;  
 unsigned int state;  
 unsigned int button;  
 int  same_screen;  
} XButtonEvent;
typedef XButtonEvent XButtonPressedEvent;
typedef XButtonEvent XButtonReleasedEvent;

typedef struct {
 int type;   
 unsigned long serial;  
 int  send_event;  
 Display *display;  
 Window window;          
 Window root;          
 Window subwindow;  
 Time time;   
 int x, y;   
 int x_root, y_root;  
 unsigned int state;  
 char is_hint;   
 int  same_screen;  
} XMotionEvent;
typedef XMotionEvent XPointerMovedEvent;

typedef struct {
 int type;   
 unsigned long serial;  
 int  send_event;  
 Display *display;  
 Window window;          
 Window root;          
 Window subwindow;  
 Time time;   
 int x, y;   
 int x_root, y_root;  
 int mode;   
 int detail;
 


 
 int  same_screen;  
 int  focus;   
 unsigned int state;  
} XCrossingEvent;
typedef XCrossingEvent XEnterWindowEvent;
typedef XCrossingEvent XLeaveWindowEvent;

typedef struct {
 int type;   
 unsigned long serial;  
 int  send_event;  
 Display *display;  
 Window window;   
 int mode;   
 int detail;
 



 
} XFocusChangeEvent;
typedef XFocusChangeEvent XFocusInEvent;
typedef XFocusChangeEvent XFocusOutEvent;

 
typedef struct {
 int type;
 unsigned long serial;  
 int  send_event;  
 Display *display;  
 Window window;
 char key_vector[32];
} XKeymapEvent; 

typedef struct {
 int type;
 unsigned long serial;  
 int  send_event;  
 Display *display;  
 Window window;
 int x, y;
 int width, height;
 int count;   
} XExposeEvent;

typedef struct {
 int type;
 unsigned long serial;  
 int  send_event;  
 Display *display;  
 Drawable drawable;
 int x, y;
 int width, height;
 int count;   
 int major_code;   
 int minor_code;   
} XGraphicsExposeEvent;

typedef struct {
 int type;
 unsigned long serial;  
 int  send_event;  
 Display *display;  
 Drawable drawable;
 int major_code;   
 int minor_code;   
} XNoExposeEvent;

typedef struct {
 int type;
 unsigned long serial;  
 int  send_event;  
 Display *display;  
 Window window;
 int state;   
} XVisibilityEvent;

typedef struct {
 int type;
 unsigned long serial;  
 int  send_event;  
 Display *display;  
 Window parent;   
 Window window;   
 int x, y;   
 int width, height;  
 int border_width;  
 int  override_redirect;  
} XCreateWindowEvent;

typedef struct {
 int type;
 unsigned long serial;  
 int  send_event;  
 Display *display;  
 Window event;
 Window window;
} XDestroyWindowEvent;

typedef struct {
 int type;
 unsigned long serial;  
 int  send_event;  
 Display *display;  
 Window event;
 Window window;
 int  from_configure;
} XUnmapEvent;

typedef struct {
 int type;
 unsigned long serial;  
 int  send_event;  
 Display *display;  
 Window event;
 Window window;
 int  override_redirect;  
} XMapEvent;

typedef struct {
 int type;
 unsigned long serial;  
 int  send_event;  
 Display *display;  
 Window parent;
 Window window;
} XMapRequestEvent;

typedef struct {
 int type;
 unsigned long serial;  
 int  send_event;  
 Display *display;  
 Window event;
 Window window;
 Window parent;
 int x, y;
 int  override_redirect;
} XReparentEvent;

typedef struct {
 int type;
 unsigned long serial;  
 int  send_event;  
 Display *display;  
 Window event;
 Window window;
 int x, y;
 int width, height;
 int border_width;
 Window above;
 int  override_redirect;
} XConfigureEvent;

typedef struct {
 int type;
 unsigned long serial;  
 int  send_event;  
 Display *display;  
 Window event;
 Window window;
 int x, y;
} XGravityEvent;

typedef struct {
 int type;
 unsigned long serial;  
 int  send_event;  
 Display *display;  
 Window window;
 int width, height;
} XResizeRequestEvent;

typedef struct {
 int type;
 unsigned long serial;  
 int  send_event;  
 Display *display;  
 Window parent;
 Window window;
 int x, y;
 int width, height;
 int border_width;
 Window above;
 int detail;   
 unsigned long value_mask;
} XConfigureRequestEvent;

typedef struct {
 int type;
 unsigned long serial;  
 int  send_event;  
 Display *display;  
 Window event;
 Window window;
 int place;   
} XCirculateEvent;

typedef struct {
 int type;
 unsigned long serial;  
 int  send_event;  
 Display *display;  
 Window parent;
 Window window;
 int place;   
} XCirculateRequestEvent;

typedef struct {
 int type;
 unsigned long serial;  
 int  send_event;  
 Display *display;  
 Window window;
 Atom atom;
 Time time;
 int state;   
} XPropertyEvent;

typedef struct {
 int type;
 unsigned long serial;  
 int  send_event;  
 Display *display;  
 Window window;
 Atom selection;
 Time time;
} XSelectionClearEvent;

typedef struct {
 int type;
 unsigned long serial;  
 int  send_event;  
 Display *display;  
 Window owner;
 Window requestor;
 Atom selection;
 Atom target;
 Atom property;
 Time time;
} XSelectionRequestEvent;

typedef struct {
 int type;
 unsigned long serial;  
 int  send_event;  
 Display *display;  
 Window requestor;
 Atom selection;
 Atom target;
 Atom property;   
 Time time;
} XSelectionEvent;

typedef struct {
 int type;
 unsigned long serial;  
 int  send_event;  
 Display *display;  
 Window window;
 Colormap colormap;  



 int  new;

 int state;   
} XColormapEvent;

typedef struct {
 int type;
 unsigned long serial;  
 int  send_event;  
 Display *display;  
 Window window;
 Atom message_type;
 int format;
 union {
  char b[20];
  short s[10];
  long l[5];
  } data;
} XClientMessageEvent;

typedef struct {
 int type;
 unsigned long serial;  
 int  send_event;  
 Display *display;  
 Window window;   
 int request; 
 
 int first_keycode;  
 int count;   
} XMappingEvent;

typedef struct {
 int type;
 Display *display;  
 XID resourceid;   
 unsigned long serial;  
 unsigned char error_code;  
 unsigned char request_code;  
 unsigned char minor_code;  
} XErrorEvent;

typedef struct {
 int type;
 unsigned long serial;  
 int  send_event;  
 Display *display; 
 Window window;  
} XAnyEvent;




 
typedef union _XEvent {
        int type;   
 XAnyEvent xany;
 XKeyEvent xkey;
 XButtonEvent xbutton;
 XMotionEvent xmotion;
 XCrossingEvent xcrossing;
 XFocusChangeEvent xfocus;
 XExposeEvent xexpose;
 XGraphicsExposeEvent xgraphicsexpose;
 XNoExposeEvent xnoexpose;
 XVisibilityEvent xvisibility;
 XCreateWindowEvent xcreatewindow;
 XDestroyWindowEvent xdestroywindow;
 XUnmapEvent xunmap;
 XMapEvent xmap;
 XMapRequestEvent xmaprequest;
 XReparentEvent xreparent;
 XConfigureEvent xconfigure;
 XGravityEvent xgravity;
 XResizeRequestEvent xresizerequest;
 XConfigureRequestEvent xconfigurerequest;
 XCirculateEvent xcirculate;
 XCirculateRequestEvent xcirculaterequest;
 XPropertyEvent xproperty;
 XSelectionClearEvent xselectionclear;
 XSelectionRequestEvent xselectionrequest;
 XSelectionEvent xselection;
 XColormapEvent xcolormap;
 XClientMessageEvent xclient;
 XMappingEvent xmapping;
 XErrorEvent xerror;
 XKeymapEvent xkeymap;
 long pad[24];
} XEvent;
#line 972
 
typedef struct {
    short lbearing;  
    short rbearing;  
    short width;   
    short ascent;   
    short descent;  
    unsigned short attributes;  
} XCharStruct;




 
typedef struct {
    Atom name;
    unsigned long card32;
} XFontProp;

typedef struct {
    XExtData *ext_data;  
    Font        fid;             
    unsigned direction;  
    unsigned min_char_or_byte2; 
    unsigned max_char_or_byte2; 
    unsigned min_byte1;  
    unsigned max_byte1;  
    int  all_chars_exist; 
    unsigned default_char;  
    int         n_properties;    
    XFontProp *properties;  
    XCharStruct min_bounds;  
    XCharStruct max_bounds;  
    XCharStruct *per_char;  
    int  ascent;   
    int  descent;  
} XFontStruct;



 
typedef struct {
    char *chars;   
    int nchars;    
    int delta;    
    Font font;    
} XTextItem;

typedef struct {   
    unsigned char byte1;
    unsigned char byte2;
} XChar2b;

typedef struct {
    XChar2b *chars;   
    int nchars;    
    int delta;    
    Font font;    
} XTextItem16;


typedef union { Display *display;
  GC gc;
  Visual *visual;
  Screen *screen;
  ScreenFormat *pixmap_format;
  XFontStruct *font; } XEDataObject;

typedef struct {
    XRectangle      max_ink_extent;
    XRectangle      max_logical_extent;
} XFontSetExtents;

typedef struct _XFontSet *XFontSet;

typedef struct {
    char           *chars;
    int             nchars;
    int             delta;
    XFontSet        font_set;
} XmbTextItem;

typedef struct {
    wchar_t        *chars;
    int             nchars;
    int             delta;
    XFontSet        font_set;
} XwcTextItem;

typedef void (*XIMProc)();

typedef struct _XIM *XIM;
typedef struct _XIC *XIC;

typedef unsigned long XIMStyle;

typedef struct {
    unsigned short count_styles;
    XIMStyle *supported_styles;
} XIMStyles;
#line 1120
typedef void *XVaNestedList;




typedef struct {
    XPointer client_data;
    XIMProc callback;
} XIMCallback;

typedef unsigned long XIMFeedback;
#line 1139
typedef struct _XIMText {
    unsigned short length;
    XIMFeedback *feedback;
    int  encoding_is_wchar; 
    union {
 char *multi_byte;
 wchar_t *wide_char;
    } string; 
} XIMText;

typedef struct _XIMPreeditDrawCallbackStruct {
    int caret;   
    int chg_first;  
    int chg_length;  
    XIMText *text;
} XIMPreeditDrawCallbackStruct;

typedef enum {
    XIMForwardChar, XIMBackwardChar,
    XIMForwardWord, XIMBackwardWord,
    XIMCaretUp, XIMCaretDown,
    XIMNextLine, XIMPreviousLine,
    XIMLineStart, XIMLineEnd, 
    XIMAbsolutePosition,
    XIMDontChange
} XIMCaretDirection;

typedef enum {
    XIMIsInvisible,                              
    XIMIsPrimary,  
    XIMIsSecondary  
} XIMCaretStyle;

typedef struct _XIMPreeditCaretCallbackStruct {
    int position;    
    XIMCaretDirection direction;  
    XIMCaretStyle style;   
} XIMPreeditCaretCallbackStruct;

typedef enum {
    XIMTextType,
    XIMBitmapType
} XIMStatusDataType;
 
typedef struct _XIMStatusDrawCallbackStruct {
    XIMStatusDataType type;
    union {
 XIMText *text;
 Pixmap  bitmap;
    } data;
} XIMStatusDrawCallbackStruct;



extern XFontStruct *XLoadQueryFont(

    Display*               ,
    const   char*  

);

extern XFontStruct *XQueryFont(

    Display*               ,
    XID    

);


extern XTimeCoord *XGetMotionEvents(

    Display*               ,
    Window         ,
    Time             ,
    Time            ,
    int*   

);

extern XModifierKeymap *XDeleteModifiermapEntry(

    XModifierKeymap*             ,

    unsigned int                    ,



    int    

);

extern XModifierKeymap *XGetModifierMapping(

    Display*   

);

extern XModifierKeymap *XInsertModifiermapEntry(

    XModifierKeymap*             ,

    unsigned int                    ,



    int                  

);

extern XModifierKeymap *XNewModifiermap(

    int    

);

extern XImage *XCreateImage(

    Display*               ,
    Visual*              ,
    unsigned int            ,
    int               ,
    int               ,
    char*            ,
    unsigned int            ,
    unsigned int             ,
    int                   ,
    int    

);
extern XImage *XGetImage(

    Display*               ,
    Drawable         ,
    int          ,
    int          ,
    unsigned int            ,
    unsigned int             ,
    unsigned long                 ,
    int    

);
extern XImage *XGetSubImage(

    Display*               ,
    Drawable         ,
    int          ,
    int          ,
    unsigned int            ,
    unsigned int             ,
    unsigned long                 ,
    int               ,
    XImage*                  ,
    int               ,
    int    

);



 
extern Display *XOpenDisplay(

    const   char*  

);

extern void XrmInitialize(

    void

);

extern char *XFetchBytes(

    Display*               ,
    int*   

);
extern char *XFetchBuffer(

    Display*               ,
    int*                     ,
    int    

);
extern char *XGetAtomName(

    Display*               ,
    Atom   

);
extern char *XGetDefault(

    Display*               ,
    const   char*              ,
    const   char*              

);
extern char *XDisplayName(

    const   char*  

);
extern char *XKeysymToString(

    KeySym   

);

extern int (*XSynchronize(

    Display*               ,
    int    

))();
extern int (*XSetAfterFunction(

    Display*               ,
    int (*) (

      Display*  

            )   

))();
extern Atom XInternAtom(

    Display*               ,
    const   char*                ,
    int                        

);
extern Colormap XCopyColormapAndFree(

    Display*               ,
    Colormap   

);
extern Colormap XCreateColormap(

    Display*               ,
    Window         ,
    Visual*              ,
    int               

);
extern Cursor XCreatePixmapCursor(

    Display*               ,
    Pixmap              ,
    Pixmap            ,
    XColor*                        ,
    XColor*                        ,
    unsigned int        ,
    unsigned int         

);
extern Cursor XCreateGlyphCursor(

    Display*               ,
    Font                   ,
    Font                 ,
    unsigned int                  ,
    unsigned int                ,
    XColor*                        ,
    XColor*   

);
extern Cursor XCreateFontCursor(

    Display*               ,
    unsigned int  

);
extern Font XLoadFont(

    Display*               ,
    const   char*  

);
extern GC XCreateGC(

    Display*               ,
    Drawable         ,
    unsigned long                ,
    XGCValues*   

);
extern GContext XGContextFromGC(

    GC    

);
extern void XFlushGC(

    Display*               ,
    GC    

);
extern Pixmap XCreatePixmap(

    Display*               ,
    Drawable         ,
    unsigned int            ,
    unsigned int             ,
    unsigned int             

);
extern Pixmap XCreateBitmapFromData(

    Display*               ,
    Drawable         ,
    const   char*           ,
    unsigned int            ,
    unsigned int  

);
extern Pixmap XCreatePixmapFromBitmapData(

    Display*               ,
    Drawable         ,
    char*            ,
    unsigned int            ,
    unsigned int             ,
    unsigned long         ,
    unsigned long         ,
    unsigned int  

);
extern Window XCreateSimpleWindow(

    Display*               ,
    Window              ,
    int          ,
    int          ,
    unsigned int            ,
    unsigned int             ,
    unsigned int                   ,
    unsigned long             ,
    unsigned long  

);
extern Window XGetSelectionOwner(

    Display*               ,
    Atom   

);
extern Window XCreateWindow(

    Display*               ,
    Window              ,
    int          ,
    int          ,
    unsigned int            ,
    unsigned int             ,
    unsigned int                   ,
    int              ,
    unsigned int            ,
    Visual*              ,
    unsigned long                ,
    XSetWindowAttributes*  

); 
extern Colormap *XListInstalledColormaps(

    Display*               ,
    Window         ,
    int*   

);
extern char **XListFonts(

    Display*               ,
    const   char*              ,
    int                 ,
    int*   

);
extern char **XListFontsWithInfo(

    Display*               ,
    const   char*              ,
    int                 ,
    int*                    ,
    XFontStruct**  

);
extern char **XGetFontPath(

    Display*               ,
    int*   

);
extern char **XListExtensions(

    Display*               ,
    int*   

);
extern Atom *XListProperties(

    Display*               ,
    Window         ,
    int*   

);
extern XHostAddress *XListHosts(

    Display*               ,
    int*                     ,
    int *   

);
extern KeySym XKeycodeToKeysym(

    Display*               ,

    unsigned int              ,



    int    

);
extern KeySym XLookupKeysym(

    XKeyEvent*                 ,
    int    

);
extern KeySym *XGetKeyboardMapping(

    Display*               ,

    unsigned int                    ,



    int                      ,
    int*   

);
extern KeySym XStringToKeysym(

    const   char*  

);
extern long XMaxRequestSize(

    Display*   

);
extern char *XResourceManagerString(

    Display*   

);
extern char *XScreenResourceString(

 Screen*   

);
extern unsigned long XDisplayMotionBufferSize(

    Display*   

);
extern VisualID XVisualIDFromVisual(

    Visual*   

);

 

extern XExtCodes *XInitExtension(

    Display*               ,
    const   char*  

);

extern XExtCodes *XAddExtension(

    Display*   

);
extern XExtData *XFindOnExtensionList(

    XExtData**                 ,
    int    

);
extern XExtData **XEHeadOfExtensionList(

    XEDataObject  

);

 
extern Window XRootWindow(

    Display*               ,
    int    

);
extern Window XDefaultRootWindow(

    Display*   

);
extern Window XRootWindowOfScreen(

    Screen*   

);
extern Visual *XDefaultVisual(

    Display*               ,
    int    

);
extern Visual *XDefaultVisualOfScreen(

    Screen*   

);
extern GC XDefaultGC(

    Display*               ,
    int    

);
extern GC XDefaultGCOfScreen(

    Screen*   

);
extern unsigned long XBlackPixel(

    Display*               ,
    int    

);
extern unsigned long XWhitePixel(

    Display*               ,
    int    

);
extern unsigned long XAllPlanes(

    void

);
extern unsigned long XBlackPixelOfScreen(

    Screen*   

);
extern unsigned long XWhitePixelOfScreen(

    Screen*   

);
extern unsigned long XNextRequest(

    Display*   

);
extern unsigned long XLastKnownRequestProcessed(

    Display*   

);
extern char *XServerVendor(

    Display*   

);
extern char *XDisplayString(

    Display*   

);
extern Colormap XDefaultColormap(

    Display*               ,
    int    

);
extern Colormap XDefaultColormapOfScreen(

    Screen*   

);
extern Display *XDisplayOfScreen(

    Screen*   

);
extern Screen *XScreenOfDisplay(

    Display*               ,
    int    

);
extern Screen *XDefaultScreenOfDisplay(

    Display*   

);
extern long XEventMaskOfScreen(

    Screen*   

);

extern int XScreenNumberOfScreen(

    Screen*   

);

typedef int (*XErrorHandler) (      

    Display*               ,
    XErrorEvent*  

);

extern XErrorHandler XSetErrorHandler (

    XErrorHandler  

);


typedef int (*XIOErrorHandler) (     

    Display*   

);

extern XIOErrorHandler XSetIOErrorHandler (

    XIOErrorHandler  

);


extern XPixmapFormatValues *XListPixmapFormats(

    Display*               ,
    int*   

);
extern int *XListDepths(

    Display*               ,
    int                      ,
    int*   

);

 
 
extern int    XReconfigureWMWindow(

    Display*               ,
    Window         ,
    int                      ,
    unsigned int           ,
    XWindowChanges*  

);

extern int    XGetWMProtocols(

    Display*               ,
    Window         ,
    Atom**                        ,
    int*   

);
extern int    XSetWMProtocols(

    Display*               ,
    Window         ,
    Atom*                 ,
    int    

);
extern int    XIconifyWindow(

    Display*               ,
    Window         ,
    int    

);
extern int    XWithdrawWindow(

    Display*               ,
    Window         ,
    int    

);
extern int    XGetCommand(

    Display*               ,
    Window         ,
    char***                   ,
    int*   

);
extern int    XGetWMColormapWindows(

    Display*               ,
    Window         ,
    Window**                      ,
    int*   

);
extern int    XSetWMColormapWindows(

    Display*               ,
    Window         ,
    Window*                        ,
    int    

);
extern void XFreeStringList(

    char**   

);
extern XSetTransientForHint(

    Display*               ,
    Window         ,
    Window   

);

 

extern XActivateScreenSaver(

    Display*   

);

extern XAddHost(

    Display*               ,
    XHostAddress*  

);

extern XAddHosts(

    Display*               ,
    XHostAddress*            ,
    int                   

);

extern XAddToExtensionList(

    struct _XExtData**                ,
    XExtData*   

);

extern XAddToSaveSet(

    Display*               ,
    Window   

);

extern int    XAllocColor(

    Display*               ,
    Colormap                ,
    XColor*   

);

extern int    XAllocColorCells(

    Display*               ,
    Colormap                ,
    int                      ,
    unsigned long*                         ,
    unsigned int              ,
    unsigned long*                    ,
    unsigned int   

);

extern int    XAllocColorPlanes(

    Display*               ,
    Colormap                ,
    int               ,
    unsigned long*                    ,
    int                ,
    int              ,
    int                ,
    int               ,
    unsigned long*                   ,
    unsigned long*                   ,
    unsigned long*  

);

extern int    XAllocNamedColor(

    Display*               ,
    Colormap                ,
    const   char*                 ,
    XColor*                         ,
    XColor*   

);

extern XAllowEvents(

    Display*               ,
    int                   ,
    Time   

);

extern XAutoRepeatOff(

    Display*   

);

extern XAutoRepeatOn(

    Display*   

);

extern XBell(

    Display*               ,
    int    

);

extern int XBitmapBitOrder(

    Display*   

);

extern int XBitmapPad(

    Display*   

);

extern int XBitmapUnit(

    Display*   

);

extern int XCellsOfScreen(

    Screen*   

);

extern XChangeActivePointerGrab(

    Display*               ,
    unsigned int                 ,
    Cursor              ,
    Time   

);

extern XChangeGC(

    Display*               ,
    GC           ,
    unsigned long                ,
    XGCValues*   

);

extern XChangeKeyboardControl(

    Display*               ,
    unsigned long                 ,
    XKeyboardControl*  

);

extern XChangeKeyboardMapping(

    Display*               ,
    int                      ,
    int                            ,
    KeySym*               ,
    int    

);

extern XChangePointerControl(

    Display*               ,
    int                 ,
    int                     ,
    int                        ,
    int                          ,
    int    

);

extern XChangeProperty(

    Display*               ,
    Window         ,
    Atom                ,
    Atom            ,
    int               ,
    int             ,
    const   unsigned char*           ,
    int    

);

extern XChangeSaveSet(

    Display*               ,
    Window         ,
    int    

);

extern XChangeWindowAttributes(

    Display*               ,
    Window         ,
    unsigned long                ,
    XSetWindowAttributes*  

);

extern int  XCheckIfEvent(

    Display*               ,
    XEvent*                    ,
    int  (*) (

        Display*                ,
               XEvent*              ,
               XPointer    

             )                 ,
    XPointer   

);

extern int  XCheckMaskEvent(

    Display*               ,
    long                  ,
    XEvent*   

);

extern int  XCheckTypedEvent(

    Display*               ,
    int                   ,
    XEvent*   

);

extern int  XCheckTypedWindowEvent(

    Display*               ,
    Window         ,
    int                   ,
    XEvent*   

);

extern int  XCheckWindowEvent(

    Display*               ,
    Window         ,
    long                  ,
    XEvent*   

);

extern XCirculateSubwindows(

    Display*               ,
    Window         ,
    int    

);

extern XCirculateSubwindowsDown(

    Display*               ,
    Window   

);

extern XCirculateSubwindowsUp(

    Display*               ,
    Window   

);

extern XClearArea(

    Display*               ,
    Window         ,
    int          ,
    int          ,
    unsigned int            ,
    unsigned int             ,
    int    

);

extern XClearWindow(

    Display*               ,
    Window   

);

extern XCloseDisplay(

    Display*   

);

extern XConfigureWindow(

    Display*               ,
    Window         ,
    unsigned int                 ,
    XWindowChanges*              

);

extern int XConnectionNumber(

    Display*   

);

extern XConvertSelection(

    Display*               ,
    Atom                 ,
    Atom               ,
    Atom                ,
    Window                 ,
    Time   

);

extern XCopyArea(

    Display*               ,
    Drawable           ,
    Drawable            ,
    GC           ,
    int              ,
    int              ,
    unsigned int            ,
    unsigned int             ,
    int               ,
    int    

);

extern XCopyGC(

    Display*               ,
    GC            ,
    unsigned long                ,
    GC    

);

extern XCopyPlane(

    Display*               ,
    Drawable           ,
    Drawable            ,
    GC           ,
    int              ,
    int              ,
    unsigned int            ,
    unsigned int             ,
    int               ,
    int               ,
    unsigned long  

);

extern int XDefaultDepth(

    Display*               ,
    int    

);

extern int XDefaultDepthOfScreen(

    Screen*   

);

extern int XDefaultScreen(

    Display*   

);

extern XDefineCursor(

    Display*               ,
    Window         ,
    Cursor   

);

extern XDeleteProperty(

    Display*               ,
    Window         ,
    Atom   

);

extern XDestroyWindow(

    Display*               ,
    Window   

);

extern XDestroySubwindows(

    Display*               ,
    Window   

);

extern int XDoesBackingStore(

    Screen*               

);

extern int  XDoesSaveUnders(

    Screen*   

);

extern XDisableAccessControl(

    Display*   

);


extern int XDisplayCells(

    Display*               ,
    int    

);

extern int XDisplayHeight(

    Display*               ,
    int    

);

extern int XDisplayHeightMM(

    Display*               ,
    int    

);

extern XDisplayKeycodes(

    Display*               ,
    int*                           ,
    int*   

);

extern int XDisplayPlanes(

    Display*               ,
    int    

);

extern int XDisplayWidth(

    Display*               ,
    int    

);

extern int XDisplayWidthMM(

    Display*               ,
    int    

);

extern XDrawArc(

    Display*               ,
    Drawable         ,
    GC           ,
    int          ,
    int          ,
    unsigned int            ,
    unsigned int             ,
    int               ,
    int    

);

extern XDrawArcs(

    Display*               ,
    Drawable         ,
    GC           ,
    XArc*            ,
    int    

);

extern XDrawImageString(

    Display*               ,
    Drawable         ,
    GC           ,
    int          ,
    int          ,
    const   char*             ,
    int    

);

extern XDrawImageString16(

    Display*               ,
    Drawable         ,
    GC           ,
    int          ,
    int          ,
    const   XChar2b*             ,
    int    

);

extern XDrawLine(

    Display*               ,
    Drawable         ,
    GC           ,
    int           ,
    int           ,
    int           ,
    int    

);

extern XDrawLines(

    Display*               ,
    Drawable         ,
    GC           ,
    XPoint*              ,
    int                ,
    int    

);

extern XDrawPoint(

    Display*               ,
    Drawable         ,
    GC           ,
    int          ,
    int    

);

extern XDrawPoints(

    Display*               ,
    Drawable         ,
    GC           ,
    XPoint*              ,
    int                ,
    int    

);

extern XDrawRectangle(

    Display*               ,
    Drawable         ,
    GC           ,
    int          ,
    int          ,
    unsigned int            ,
    unsigned int  

);

extern XDrawRectangles(

    Display*               ,
    Drawable         ,
    GC           ,
    XRectangle*                  ,
    int    

);

extern XDrawSegments(

    Display*               ,
    Drawable         ,
    GC           ,
    XSegment*                ,
    int    

);

extern XDrawString(

    Display*               ,
    Drawable         ,
    GC           ,
    int          ,
    int          ,
    const   char*             ,
    int    

);

extern XDrawString16(

    Display*               ,
    Drawable         ,
    GC           ,
    int          ,
    int          ,
    const   XChar2b*             ,
    int    

);

extern XDrawText(

    Display*               ,
    Drawable         ,
    GC           ,
    int          ,
    int          ,
    XTextItem*             ,
    int    

);

extern XDrawText16(

    Display*               ,
    Drawable         ,
    GC           ,
    int          ,
    int          ,
    XTextItem16*            ,
    int    

);

extern XEnableAccessControl(

    Display*   

);

extern int XEventsQueued(

    Display*               ,
    int    

);

extern int    XFetchName(

    Display*               ,
    Window         ,
    char**   

);

extern XFillArc(

    Display*               ,
    Drawable         ,
    GC           ,
    int          ,
    int          ,
    unsigned int            ,
    unsigned int             ,
    int               ,
    int    

);

extern XFillArcs(

    Display*               ,
    Drawable         ,
    GC           ,
    XArc*            ,
    int    

);

extern XFillPolygon(

    Display*               ,
    Drawable         ,
    GC           ,
    XPoint*              ,
    int                ,
    int              ,
    int    

);

extern XFillRectangle(

    Display*               ,
    Drawable         ,
    GC           ,
    int          ,
    int          ,
    unsigned int            ,
    unsigned int  

);

extern XFillRectangles(

    Display*               ,
    Drawable         ,
    GC           ,
    XRectangle*                  ,
    int    

);

extern XFlush(

    Display*   

);

extern XForceScreenSaver(

    Display*               ,
    int    

);

extern XFree(

    void*   

);

extern XFreeColormap(

    Display*               ,
    Colormap   

);

extern XFreeColors(

    Display*               ,
    Colormap                ,
    unsigned long*             ,
    int                ,
    unsigned long  

);

extern XFreeCursor(

    Display*               ,
    Cursor   

);

extern XFreeExtensionList(

    char**             

);

extern XFreeFont(

    Display*               ,
    XFontStruct*  

);

extern XFreeFontInfo(

    char**             ,
    XFontStruct*                ,
    int    

);

extern XFreeFontNames(

    char**   

);

extern XFreeFontPath(

    char**   

);

extern XFreeGC(

    Display*               ,
    GC    

);

extern XFreeModifiermap(

    XModifierKeymap*  

);

extern XFreePixmap(

    Display*               ,
    Pixmap   

);

extern int XGeometry(

    Display*               ,
    int               ,
    const   char*               ,
    const   char*                       ,
    unsigned int             ,
    unsigned int             ,
    unsigned int              ,
    int               ,
    int               ,
    int*                ,
    int*                ,
    int*                    ,
    int*   

);

extern XGetErrorDatabaseText(

    Display*               ,
    const   char*           ,
    const   char*              ,
    const   char*                     ,
    char*                     ,
    int    

);

extern XGetErrorText(

    Display*               ,
    int             ,
    char*                     ,
    int    

);

extern int  XGetFontProperty(

    XFontStruct*                  ,
    Atom            ,
    unsigned long*  

);

extern int    XGetGCValues(

    Display*               ,
    GC           ,
    unsigned long                ,
    XGCValues*   

);

extern int    XGetGeometry(

    Display*               ,
    Drawable         ,
    Window*                   ,
    int*                ,
    int*                ,
    unsigned int*                   ,
    unsigned int*                    ,
    unsigned int*                          ,
    unsigned int*  

);

extern int    XGetIconName(

    Display*               ,
    Window         ,
    char**   

);

extern XGetInputFocus(

    Display*               ,
    Window*                    ,
    int*   

);

extern XGetKeyboardControl(

    Display*               ,
    XKeyboardState*  

);

extern XGetPointerControl(

    Display*               ,
    int*                              ,
    int*                                ,
    int*   

);

extern int XGetPointerMapping(

    Display*               ,
    unsigned char*                 ,
    int    

);

extern XGetScreenSaver(

    Display*               ,
    int*                      ,
    int*                       ,
    int*                              ,
    int*   

);

extern int    XGetTransientForHint(

    Display*               ,
    Window         ,
    Window*   

);

extern int XGetWindowProperty(

    Display*               ,
    Window         ,
    Atom                ,
    long                   ,
    long                   ,
    int               ,
    Atom                ,
    Atom*                          ,
    int*                            ,
    unsigned long*                    ,
    unsigned long*                         ,
    unsigned char**  

);

extern int    XGetWindowAttributes(

    Display*               ,
    Window         ,
    XWindowAttributes*  

);

extern XGrabButton(

    Display*               ,
    unsigned int             ,
    unsigned int                ,
    Window                   ,
    int                     ,
    unsigned int                 ,
    int                     ,
    int                      ,
    Window                  ,
    Cursor   

);

extern XGrabKey(

    Display*               ,
    int                ,
    unsigned int                ,
    Window                   ,
    int                     ,
    int                     ,
    int    

);

extern int XGrabKeyboard(

    Display*               ,
    Window                   ,
    int                     ,
    int                     ,
    int                      ,
    Time   

);

extern int XGrabPointer(

    Display*               ,
    Window                   ,
    int                     ,
    unsigned int                 ,
    int                     ,
    int                      ,
    Window                  ,
    Cursor              ,
    Time   

);

extern XGrabServer(

    Display*   

);

extern int XHeightMMOfScreen(

    Screen*   

);

extern int XHeightOfScreen(

    Screen*   

);

extern XIfEvent(

    Display*               ,
    XEvent*                    ,
    int  (*) (

        Display*                ,
               XEvent*              ,
               XPointer    

             )                 ,
    XPointer   

);

extern int XImageByteOrder(

    Display*   

);

extern XInstallColormap(

    Display*               ,
    Colormap   

);

extern KeyCode XKeysymToKeycode(

    Display*               ,
    KeySym   

);

extern XKillClient(

    Display*               ,
    XID    

);

extern unsigned long XLastKnownRequestProcessed(

    Display*   

);

extern int    XLookupColor(

    Display*               ,
    Colormap                ,
    const   char*                 ,
    XColor*                        ,
    XColor*   

);

extern XLowerWindow(

    Display*               ,
    Window   

);

extern XMapRaised(

    Display*               ,
    Window   

);

extern XMapSubwindows(

    Display*               ,
    Window   

);

extern XMapWindow(

    Display*               ,
    Window   

);

extern XMaskEvent(

    Display*               ,
    long                  ,
    XEvent*   

);

extern int XMaxCmapsOfScreen(

    Screen*   

);

extern int XMinCmapsOfScreen(

    Screen*   

);

extern XMoveResizeWindow(

    Display*               ,
    Window         ,
    int          ,
    int          ,
    unsigned int            ,
    unsigned int  

);

extern XMoveWindow(

    Display*               ,
    Window         ,
    int          ,
    int    

);

extern XNextEvent(

    Display*               ,
    XEvent*   

);

extern XNoOp(

    Display*   

);

extern int    XParseColor(

    Display*               ,
    Colormap                ,
    const   char*           ,
    XColor*   

);

extern int XParseGeometry(

    const   char*                  ,
    int*                ,
    int*                ,
    unsigned int*                   ,
    unsigned int*  

);

extern XPeekEvent(

    Display*               ,
    XEvent*   

);

extern XPeekIfEvent(

    Display*               ,
    XEvent*                    ,
    int  (*) (

        Display*               ,
               XEvent*             ,
               XPointer   

             )                 ,
    XPointer   

);

extern int XPending(

    Display*   

);

extern int XPlanesOfScreen(

    Screen*   
 

);

extern int XProtocolRevision(

    Display*   

);

extern int XProtocolVersion(

    Display*   

);


extern XPutBackEvent(

    Display*               ,
    XEvent*   

);

extern XPutImage(

    Display*               ,
    Drawable         ,
    GC           ,
    XImage*             ,
    int              ,
    int              ,
    int               ,
    int               ,
    unsigned int            ,
    unsigned int              

);

extern int XQLength(

    Display*   

);

extern int    XQueryBestCursor(

    Display*               ,
    Drawable         ,
    unsigned int                   ,
    unsigned int             ,
    unsigned int*                   ,
    unsigned int*  

);

extern int    XQueryBestSize(

    Display*               ,
    int              ,
    Drawable                    ,
    unsigned int            ,
    unsigned int             ,
    unsigned int*                   ,
    unsigned int*  

);

extern int    XQueryBestStipple(

    Display*               ,
    Drawable                    ,
    unsigned int            ,
    unsigned int             ,
    unsigned int*                   ,
    unsigned int*  

);

extern int    XQueryBestTile(

    Display*               ,
    Drawable                    ,
    unsigned int            ,
    unsigned int             ,
    unsigned int*                   ,
    unsigned int*  

);

extern XQueryColor(

    Display*               ,
    Colormap                ,
    XColor*   

);

extern XQueryColors(

    Display*               ,
    Colormap                ,
    XColor*                   ,
    int    

);

extern int  XQueryExtension(

    Display*               ,
    const   char*           ,
    int*                           ,
    int*                          ,
    int*   

);

extern XQueryKeymap(

    Display*               ,
    char [32]   

);

extern int  XQueryPointer(

    Display*               ,
    Window         ,
    Window*                   ,
    Window*                    ,
    int*                     ,
    int*                     ,
    int*                    ,
    int*                    ,
    unsigned int*        

);

extern XQueryTextExtents(

    Display*               ,
    XID                ,
    const   char*             ,
    int               ,
    int*                        ,
    int*                          ,
    int*                           ,
    XCharStruct*                      

);

extern XQueryTextExtents16(

    Display*               ,
    XID                ,
    const   XChar2b*             ,
    int               ,
    int*                        ,
    int*                          ,
    int*                           ,
    XCharStruct*  

);

extern int    XQueryTree(

    Display*               ,
    Window         ,
    Window*                   ,
    Window*                     ,
    Window**                       ,
    unsigned int*  

);

extern XRaiseWindow(

    Display*               ,
    Window   

);

extern int XReadBitmapFile(

    Display*               ,
    Drawable          ,
    const   char*               ,
    unsigned int*                   ,
    unsigned int*                    ,
    Pixmap*                     ,
    int*                    ,
    int*   

);

extern XRebindKeysym(

    Display*               ,
    KeySym              ,
    KeySym*            ,
    int                  ,
    const   unsigned char*             ,
    int    

);

extern XRecolorCursor(

    Display*               ,
    Cursor              ,
    XColor*                        ,
    XColor*   

);

extern XRefreshKeyboardMapping(

    XMappingEvent*                 

);

extern XRemoveFromSaveSet(

    Display*               ,
    Window   

);

extern XRemoveHost(

    Display*               ,
    XHostAddress*  

);

extern XRemoveHosts(

    Display*               ,
    XHostAddress*            ,
    int    

);

extern XReparentWindow(

    Display*               ,
    Window         ,
    Window              ,
    int          ,
    int    

);

extern XResetScreenSaver(

    Display*   

);

extern XResizeWindow(

    Display*               ,
    Window         ,
    unsigned int            ,
    unsigned int  

);

extern XRestackWindows(

    Display*               ,
    Window*               ,
    int    

);

extern XRotateBuffers(

    Display*               ,
    int    

);

extern XRotateWindowProperties(

    Display*               ,
    Window         ,
    Atom*                  ,
    int                 ,
    int    

);

extern int XScreenCount(

    Display*   

);

extern XSelectInput(

    Display*               ,
    Window         ,
    long   

);

extern int    XSendEvent(

    Display*               ,
    Window         ,
    int                  ,
    long                  ,
    XEvent*   

);

extern XSetAccessControl(

    Display*               ,
    int    

);

extern XSetArcMode(

    Display*               ,
    GC           ,
    int    

);

extern XSetBackground(

    Display*               ,
    GC           ,
    unsigned long  

);

extern XSetClipMask(

    Display*               ,
    GC           ,
    Pixmap   

);

extern XSetClipOrigin(

    Display*               ,
    GC           ,
    int                      ,
    int    

);

extern XSetClipRectangles(

    Display*               ,
    GC           ,
    int                      ,
    int                      ,
    XRectangle*                  ,
    int          ,
    int    

);

extern XSetCloseDownMode(

    Display*               ,
    int    

);

extern XSetCommand(

    Display*               ,
    Window         ,
    char**            ,
    int    

);

extern XSetDashes(

    Display*               ,
    GC           ,
    int                    ,
    const   char*                ,
    int    

);

extern XSetFillRule(

    Display*               ,
    GC           ,
    int    

);

extern XSetFillStyle(

    Display*               ,
    GC           ,
    int    

);

extern XSetFont(

    Display*               ,
    GC           ,
    Font   

);

extern XSetFontPath(

    Display*               ,
    char**                   ,
    int               

);

extern XSetForeground(

    Display*               ,
    GC           ,
    unsigned long  

);

extern XSetFunction(

    Display*               ,
    GC           ,
    int    

);

extern XSetGraphicsExposures(

    Display*               ,
    GC           ,
    int    

);

extern XSetIconName(

    Display*               ,
    Window         ,
    const   char*  

);

extern XSetInputFocus(

    Display*               ,
    Window             ,
    int                  ,
    Time   

);

extern XSetLineAttributes(

    Display*               ,
    GC           ,
    unsigned int                 ,
    int                   ,
    int                  ,
    int    

);

extern int XSetModifierMapping(

    Display*               ,
    XModifierKeymap*  

);

extern XSetPlaneMask(

    Display*               ,
    GC           ,
    unsigned long  

);

extern int XSetPointerMapping(

    Display*               ,
    const   unsigned char*          ,
    int    

);

extern XSetScreenSaver(

    Display*               ,
    int                ,
    int                 ,
    int                        ,
    int    

);

extern XSetSelectionOwner(

    Display*               ,
    Atom                        ,
    Window             ,
    Time   

);

extern XSetState(

    Display*               ,
    GC           ,
    unsigned long                  ,
    unsigned long                 ,
    int                 ,
    unsigned long  

);

extern XSetStipple(

    Display*               ,
    GC           ,
    Pixmap   

);

extern XSetSubwindowMode(

    Display*               ,
    GC           ,
    int    

);

extern XSetTSOrigin(

    Display*               ,
    GC           ,
    int                    ,
    int    

);

extern XSetTile(

    Display*               ,
    GC           ,
    Pixmap   

);

extern XSetWindowBackground(

    Display*               ,
    Window         ,
    unsigned long  

);

extern XSetWindowBackgroundPixmap(

    Display*               ,
    Window         ,
    Pixmap   

);

extern XSetWindowBorder(

    Display*               ,
    Window         ,
    unsigned long  

);

extern XSetWindowBorderPixmap(

    Display*               ,
    Window         ,
    Pixmap   

);

extern XSetWindowBorderWidth(

    Display*               ,
    Window         ,
    unsigned int  

);

extern XSetWindowColormap(

    Display*               ,
    Window         ,
    Colormap   

);

extern XStoreBuffer(

    Display*               ,
    const   char*            ,
    int               ,
    int    

);

extern XStoreBytes(

    Display*               ,
    const   char*            ,
    int    

);

extern XStoreColor(

    Display*               ,
    Colormap                ,
    XColor*   

);

extern XStoreColors(

    Display*               ,
    Colormap                ,
    XColor*             ,
    int    

);

extern XStoreName(

    Display*               ,
    Window         ,
    const   char*  

);

extern XStoreNamedColor(

    Display*               ,
    Colormap                ,
    const   char*            ,
    unsigned long            ,
    int    

);

extern XSync(

    Display*               ,
    int    

);

extern XTextExtents(

    XFontStruct*                  ,
    const   char*             ,
    int               ,
    int*                        ,
    int*                          ,
    int*                           ,
    XCharStruct*  

);

extern XTextExtents16(

    XFontStruct*                  ,
    const   XChar2b*             ,
    int               ,
    int*                        ,
    int*                          ,
    int*                           ,
    XCharStruct*  

);

extern int XTextWidth(

    XFontStruct*                  ,
    const   char*             ,
    int    

);

extern int XTextWidth16(

    XFontStruct*                  ,
    const   XChar2b*             ,
    int    

);

extern int  XTranslateCoordinates(

    Display*               ,
    Window             ,
    Window              ,
    int              ,
    int              ,
    int*                     ,
    int*                     ,
    Window*   

);

extern XUndefineCursor(

    Display*               ,
    Window   

);

extern XUngrabButton(

    Display*               ,
    unsigned int             ,
    unsigned int                ,
    Window   

);

extern XUngrabKey(

    Display*               ,
    int                ,
    unsigned int                ,
    Window   

);

extern XUngrabKeyboard(

    Display*               ,
    Time   

);

extern XUngrabPointer(

    Display*               ,
    Time   

);

extern XUngrabServer(

    Display*   

);

extern XUninstallColormap(

    Display*               ,
    Colormap   

);

extern XUnloadFont(

    Display*               ,
    Font   

);

extern XUnmapSubwindows(

    Display*               ,
    Window   

);

extern XUnmapWindow(

    Display*               ,
    Window   

);

extern int XVendorRelease(

    Display*   

);

extern XWarpPointer(

    Display*               ,
    Window             ,
    Window              ,
    int              ,
    int              ,
    unsigned int                ,
    unsigned int                 ,
    int               ,
    int                

);

extern int XWidthMMOfScreen(

    Screen*   

);

extern int XWidthOfScreen(

    Screen*   

);

extern XWindowEvent(

    Display*               ,
    Window         ,
    long                  ,
    XEvent*   

);

extern int XWriteBitmapFile(

    Display*               ,
    const   char*               ,
    Pixmap              ,
    unsigned int            ,
    unsigned int             ,
    int              ,
    int               

);

extern int  XSupportsLocale(

    void

);

extern char *XSetLocaleModifiers(

    const   char*  

);

extern XFontSet XCreateFontSet(

    Display*               ,
    const   char*                          ,
    char***                            ,
    int*                             ,
    char**   

);

extern void XFreeFontSet(

    Display*               ,
    XFontSet   

);

extern int XFontsOfFontSet(

    XFontSet                ,
    XFontStruct***                       ,
    char***   

);

extern char *XBaseFontNameListOfFontSet(

    XFontSet   

);

extern char *XLocaleOfFontSet(

    XFontSet   

);

extern int  XContextDependentDrawing(

    XFontSet   

);

extern XFontSetExtents *XExtentsOfFontSet(

    XFontSet   

);

extern int XmbTextEscapement(

    XFontSet                ,
    const   char*           ,
    int    

);

extern int XwcTextEscapement(

    XFontSet                ,
    wchar_t*            ,
    int    

);

extern int XmbTextExtents(

    XFontSet                ,
    const   char*           ,
    int                   ,
    XRectangle*                          ,
    XRectangle*   

);

extern int XwcTextExtents(

    XFontSet                ,
    wchar_t*            ,
    int                   ,
    XRectangle*                          ,
    XRectangle*   

);

extern int    XmbTextPerCharExtents(

    XFontSet                ,
    const   char*           ,
    int                   ,
    XRectangle*                          ,
    XRectangle*                              ,
    int                    ,
    int*                 ,
    XRectangle*                          ,
    XRectangle*   

);

extern int    XwcTextPerCharExtents(

    XFontSet                ,
    wchar_t*            ,
    int                   ,
    XRectangle*                          ,
    XRectangle*                              ,
    int                    ,
    int*                 ,
    XRectangle*                          ,
    XRectangle*   

);

extern void XmbDrawText(

    Display*               ,
    Drawable         ,
    GC           ,
    int          ,
    int          ,
    XmbTextItem*                 ,
    int    

);

extern void XwcDrawText(

    Display*               ,
    Drawable         ,
    GC           ,
    int          ,
    int          ,
    XwcTextItem*                 ,
    int    

);

extern void XmbDrawString(

    Display*               ,
    Drawable         ,
    XFontSet                ,
    GC           ,
    int          ,
    int          ,
    const   char*           ,
    int    

);

extern void XwcDrawString(

    Display*               ,
    Drawable         ,
    XFontSet                ,
    GC           ,
    int          ,
    int          ,
    wchar_t*            ,
    int    

);

extern void XmbDrawImageString(

    Display*               ,
    Drawable         ,
    XFontSet                ,
    GC           ,
    int          ,
    int          ,
    const   char*           ,
    int    

);

extern void XwcDrawImageString(

    Display*               ,
    Drawable         ,
    XFontSet                ,
    GC           ,
    int          ,
    int          ,
    wchar_t*            ,
    int    

);

extern XIM XOpenIM(

    Display*            ,
    struct _XrmHashBucketRec*          ,
    char*                 ,
    char*    

);

extern int    XCloseIM(

    XIM  

);

extern char *XGetIMValues(

    XIM         , ...

);

extern Display *XDisplayOfIM(

    XIM  

);

extern char *XLocaleOfIM(

    XIM  

);

extern XIC XCreateIC(

    XIM         , ...

);

extern void XDestroyIC(

    XIC  

);

extern void XSetICFocus(

    XIC  

);

extern void XUnsetICFocus(

    XIC  

);

extern wchar_t *XwcResetIC(

    XIC  

);

extern char *XmbResetIC(

    XIC  

);

extern char *XSetICValues(

    XIC         , ...

);

extern char *XGetICValues(

    XIC         , ...

);

extern XIM XIMOfIC(

    XIC  

);

extern int  XFilterEvent(

    XEvent*            ,
    Window  

);

extern int XmbLookupString(

    XIC           ,
    XKeyPressedEvent*            ,
    char*                     ,
    int                     ,
    KeySym*                     ,
    int   *   

);

extern int XwcLookupString(

    XIC           ,
    XKeyPressedEvent*            ,
    wchar_t*                     ,
    int                      ,
    KeySym*                     ,
    int   *   

);

extern XVaNestedList XVaCreateNestedList(

    int           , ...

);
#line 1 "/home/local/X11R5/include/X11/Xutil.h"
 
#line 25
 




 




 
#line 48
 
typedef struct {
     long flags;  
 int x, y;   
 int width, height;  
 int min_width, min_height;
 int max_width, max_height;
     int width_inc, height_inc;
 struct {
  int x;  
  int y;  
 } min_aspect, max_aspect;
 int base_width, base_height;   
 int win_gravity;    
} XSizeHints;




 

 
#line 82
 




typedef struct {
 long flags;  
 int  input; 
 
 int initial_state;  
 Pixmap icon_pixmap;  
 Window icon_window;   
 int icon_x, icon_y;   
 Pixmap icon_mask;  
 XID window_group;  
  
} XWMHints;

 
#line 112
 
#line 119
 



    
#line 129
 
typedef struct {
    unsigned char *value;   
    Atom encoding;    
    int format;     
    unsigned long nitems;   
} XTextProperty;
#line 141
typedef enum {
    XStringStyle,   
    XCompoundTextStyle,   
    XTextStyle,    
    XStdICCTextStyle   
} XICCEncodingStyle;

typedef struct {
 int min_width, min_height;
 int max_width, max_height;
 int width_inc, height_inc;
} XIconSize;

typedef struct {
 char *res_name;
 char *res_class;
} XClassHint;




 
#line 176
 
typedef struct _XComposeStatus {
    XPointer compose_ptr;  
    int chars_matched;   
} XComposeStatus;



 
#line 206
 
typedef struct _XRegion *Region; 

 
 



 




 

typedef struct {
  Visual *visual;
  VisualID visualid;
  int screen;
  int depth;



  int class;

  unsigned long red_mask;
  unsigned long green_mask;
  unsigned long blue_mask;
  int colormap_size;
  int bits_per_rgb;
} XVisualInfo;
#line 253
 
typedef struct {
 Colormap colormap;
 unsigned long red_max;
 unsigned long red_mult;
 unsigned long green_max;
 unsigned long green_mult;
 unsigned long blue_max;
 unsigned long blue_mult;
 unsigned long base_pixel;
 VisualID visualid;   
 XID killid;    
} XStandardColormap;
#line 272
 
#line 282
 


 
#line 291
typedef int XContext;
#line 298
 

extern XClassHint *XAllocClassHint (

    void

);

extern XIconSize *XAllocIconSize (

    void

);

extern XSizeHints *XAllocSizeHints (

    void

);

extern XStandardColormap *XAllocStandardColormap (

    void

);

extern XWMHints *XAllocWMHints (

    void

);

extern XClipBox(

    Region         ,
    XRectangle*   

);

extern Region XCreateRegion(

    void

);

extern char *XDefaultString(

    void

);

extern int XDeleteContext(

    Display*               ,
    XID            ,
    XContext   

);

extern XDestroyRegion(

    Region   

);

extern XEmptyRegion(

    Region   

);

extern XEqualRegion(

    Region          ,
    Region   

);

extern int XFindContext(

    Display*               ,
    XID            ,
    XContext               ,
    XPointer*   

);

extern int    XGetClassHint(

    Display*               ,
    Window         ,
    XClassHint*   

);

extern int    XGetIconSizes(

    Display*               ,
    Window         ,
    XIconSize**                        ,
    int*   

);

extern int    XGetNormalHints(

    Display*               ,
    Window         ,
    XSizeHints*   

);

extern int    XGetRGBColormaps(

    Display*               ,
    Window         ,
    XStandardColormap**                     ,
    int*                    ,
    Atom   

);

extern int    XGetSizeHints(

    Display*               ,
    Window         ,
    XSizeHints*                    ,
    Atom   

);

extern int    XGetStandardColormap(

    Display*               ,
    Window         ,
    XStandardColormap*                      ,
    Atom                 

);

extern int    XGetTextProperty(

    Display*               ,
    Window              ,
    XTextProperty*                       ,
    Atom   

);

extern XVisualInfo *XGetVisualInfo(

    Display*               ,
    long                  ,
    XVisualInfo*                     ,
    int*   

);

extern int    XGetWMClientMachine(

    Display*               ,
    Window         ,
    XTextProperty*  

);

extern XWMHints *XGetWMHints(

    Display*               ,
    Window          

);

extern int    XGetWMIconName(

    Display*               ,
    Window         ,
    XTextProperty*  

);

extern int    XGetWMName(

    Display*               ,
    Window         ,
    XTextProperty*  

);

extern int    XGetWMNormalHints(

    Display*               ,
    Window         ,
    XSizeHints*                    ,
    long*                        

);

extern int    XGetWMSizeHints(

    Display*               ,
    Window         ,
    XSizeHints*                    ,
    long*                       ,
    Atom   

);

extern int    XGetZoomHints(

    Display*               ,
    Window         ,
    XSizeHints*   

);

extern XIntersectRegion(

    Region           ,
    Region           ,
    Region   

);

extern int XLookupString(

    XKeyEvent*                    ,
    char*                     ,
    int                     ,
    KeySym*                     ,
    XComposeStatus*  

);

extern int    XMatchVisualInfo(

    Display*               ,
    int               ,
    int              ,
    int              ,
    XVisualInfo*  

);

extern XOffsetRegion(

    Region         ,
    int           ,
    int    

);

extern int  XPointInRegion(

    Region         ,
    int          ,
    int    

);

extern Region XPolygonRegion(

    XPoint*              ,
    int          ,
    int    

);

extern int XRectInRegion(

    Region         ,
    int          ,
    int          ,
    unsigned int            ,
    unsigned int  

);

extern int XSaveContext(

    Display*               ,
    XID            ,
    XContext               ,
    const   char*  

);

extern XSetClassHint(

    Display*               ,
    Window         ,
    XClassHint*   

);

extern XSetIconSizes(

    Display*               ,
    Window         ,
    XIconSize*                 ,
    int               

);

extern XSetNormalHints(

    Display*               ,
    Window         ,
    XSizeHints*   

);

extern void XSetRGBColormaps(

    Display*               ,
    Window         ,
    XStandardColormap*               ,
    int              ,
    Atom   

);

extern XSetSizeHints(

    Display*               ,
    Window         ,
    XSizeHints*             ,
    Atom   

);

extern XSetStandardProperties(

    Display*               ,
    Window         ,
    const   char*                  ,
    const   char*                ,
    Pixmap                   ,
    char**            ,
    int             ,
    XSizeHints*   

);

extern void XSetTextProperty(

    Display*               ,
    Window         ,
    XTextProperty*                ,
    Atom   

);

extern void XSetWMClientMachine(

    Display*               ,
    Window         ,
    XTextProperty*  

);

extern XSetWMHints(

    Display*               ,
    Window         ,
    XWMHints*   

);

extern void XSetWMIconName(

    Display*               ,
    Window         ,
    XTextProperty*  

);

extern void XSetWMName(

    Display*               ,
    Window         ,
    XTextProperty*  

);

extern void XSetWMNormalHints(

    Display*               ,
    Window         ,
    XSizeHints*   

);

extern void XSetWMProperties(

    Display*               ,
    Window         ,
    XTextProperty*                  ,
    XTextProperty*                ,
    char**            ,
    int             ,
    XSizeHints*                    ,
    XWMHints*                ,
    XClassHint*   

);

extern void XmbSetWMProperties(

    Display*               ,
    Window         ,
    const   char*                  ,
    const   char*                ,
    char**            ,
    int             ,
    XSizeHints*                    ,
    XWMHints*                ,
    XClassHint*   

);

extern void XSetWMSizeHints(

    Display*               ,
    Window         ,
    XSizeHints*             ,
    Atom   

);

extern XSetRegion(

    Display*               ,
    GC           ,
    Region   

);

extern void XSetStandardColormap(

    Display*               ,
    Window         ,
    XStandardColormap*               ,
    Atom   

);

extern XSetZoomHints(

    Display*               ,
    Window         ,
    XSizeHints*   

);

extern XShrinkRegion(

    Region         ,
    int           ,
    int    

);

extern int    XStringListToTextProperty(

    char**            ,
    int              ,
    XTextProperty*  

);

extern XSubtractRegion(

    Region           ,
    Region           ,
    Region   

);

extern int XmbTextListToTextProperty(

    Display*               ,
    char**            ,
    int              ,
    XICCEncodingStyle            ,
    XTextProperty*  

);

extern int XwcTextListToTextProperty(

    Display*               ,
    wchar_t**            ,
    int              ,
    XICCEncodingStyle            ,
    XTextProperty*  

);

extern void XwcFreeStringList(

    wchar_t**   

);

extern int    XTextPropertyToStringList(

    XTextProperty*                ,
    char***                   ,
    int*   

);

extern int XmbTextPropertyToTextList(

    Display*               ,
    XTextProperty*                ,
    char***                   ,
    int*   

);

extern int XwcTextPropertyToTextList(

    Display*               ,
    XTextProperty*                ,
    wchar_t***                   ,
    int*   

);

extern XUnionRectWithRegion(

    XRectangle*                 ,
    Region                  ,
    Region   

);

extern XUnionRegion(

    Region           ,
    Region           ,
    Region   

);

extern int XWMGeometry(

    Display*               ,
    int                      ,
    const   char*                    ,
    const   char*                       ,
    unsigned int                   ,
    XSizeHints*             ,
    int*                ,
    int*                ,
    int*                    ,
    int*                     ,
    int*   

);

extern XXorRegion(

    Region           ,
    Region           ,
    Region   

);
#line 1 "/home/local/X11R5/include/X11/Xresource.h"
 
#line 25
 




 
#line 40
 
#line 48
 

extern char *Xpermalloc(

    unsigned int  

);
#line 60
 

typedef int     XrmQuark, *XrmQuarkList;


typedef char *XrmString;


 
extern XrmQuark XrmStringToQuark(

    const   char*   

);

extern XrmQuark XrmPermStringToQuark(

    const   char*   

);

 
extern XrmString XrmQuarkToString(

    XrmQuark    

);

extern XrmQuark XrmUniqueQuark(

    void

);
#line 101
 

typedef enum {XrmBindTightly, XrmBindLoosely} XrmBinding, *XrmBindingList;

extern void XrmStringToQuarkList(

    const   char*             ,
    XrmQuarkList  

);

extern void XrmStringToBindingQuarkList(

    const   char*             ,
    XrmBindingList                      ,
    XrmQuarkList  

);
#line 124
 

typedef XrmQuark     XrmName;
typedef XrmQuarkList XrmNameList;




typedef XrmQuark     XrmClass;
typedef XrmQuarkList XrmClassList;
#line 144
 

typedef XrmQuark     XrmRepresentation;



typedef struct {
    unsigned int    size;
    XPointer     addr;
} XrmValue, *XrmValuePtr;
#line 160
 

typedef struct _XrmHashBucketRec *XrmHashBucket;
typedef XrmHashBucket *XrmHashTable;
typedef XrmHashTable XrmSearchList[];
typedef struct _XrmHashBucketRec *XrmDatabase;


extern void XrmDestroyDatabase(

    XrmDatabase                 

);

extern void XrmQPutResource(

    XrmDatabase*               ,
    XrmBindingList               ,
    XrmQuarkList             ,
    XrmRepresentation           ,
    XrmValue*   

);

extern void XrmPutResource(

    XrmDatabase*               ,
    const   char*                ,
    const   char*           ,
    XrmValue*   

);

extern void XrmQPutStringResource(

    XrmDatabase*               ,
    XrmBindingList                    ,
    XrmQuarkList             ,
    const   char*  

);

extern void XrmPutStringResource(

    XrmDatabase*               ,
    const   char*                ,
    const   char*  

);

extern void XrmPutLineResource(

    XrmDatabase*               ,
    const   char*  

);

extern  XrmQGetResource(

    XrmDatabase                ,
    XrmNameList                  ,
    XrmClassList                  ,
    XrmRepresentation*                        ,
    XrmValue*   

);

extern int  XrmGetResource(

    XrmDatabase                ,
    const   char*               ,
    const   char*                ,
    char**                       ,
    XrmValue*   

);

extern int  XrmQGetSearchList(

    XrmDatabase                ,
    XrmNameList             ,
    XrmClassList              ,
    XrmSearchList                  ,
    int    

);

extern int  XrmQGetSearchResource(

    XrmSearchList           ,
    XrmName            ,
    XrmClass             ,
    XrmRepresentation*                  ,
    XrmValue*   

);
#line 261
 

extern void XrmSetDatabase(

    Display*               ,
    XrmDatabase   

);

extern XrmDatabase XrmGetDatabase(

    Display*   

);

extern XrmDatabase XrmGetFileDatabase(

    const   char*  

);

extern int    XrmCombineFileDatabase(

    const   char*                ,
    XrmDatabase*             ,
    int    

);

extern XrmDatabase XrmGetStringDatabase(

    const   char*              

);

extern void XrmPutFileDatabase(

    XrmDatabase                ,
    const   char*  

);

extern void XrmMergeDatabases(

    XrmDatabase                 ,
    XrmDatabase*  

);

extern void XrmCombineDatabase(

    XrmDatabase                 ,
    XrmDatabase*                ,
    int    

);




extern int  XrmEnumerateDatabase(

    XrmDatabase          ,
    XrmNameList                   ,
    XrmClassList                   ,
    int             ,
    int  (*)(

      XrmDatabase*         ,
      XrmBindingList               ,
      XrmQuarkList             ,
      XrmRepresentation*           ,
      XrmValue*             ,
      XPointer   

      )            ,
    XPointer   

);

extern char *XrmLocaleOfDatabase(

    XrmDatabase   

);
#line 352
 

typedef enum {
    XrmoptionNoArg,  
    XrmoptionIsArg,      
    XrmoptionStickyArg,  
    XrmoptionSepArg,     
    XrmoptionResArg,  
    XrmoptionSkipArg,    
    XrmoptionSkipLine,   
    XrmoptionSkipNArgs 
 
} XrmOptionKind;

typedef struct {
    char     *option;      
    char     *specifier;      
    XrmOptionKind   argKind;      
    XPointer     value;      
} XrmOptionDescRec, *XrmOptionDescList;


extern void XrmParseCommand(

    XrmDatabase*               ,
    XrmOptionDescList            ,
    int                    ,
    const   char*           ,
    int*                   ,
    char**                    

);




 
#line 1 "/home/local/X11R5/include/X11/Xfuncproto.h"
 
#line 15
 

 
#line 24 "/home/local/X11R5/include/X11/Xosdefs.h"
 
#line 8 "/tmp_mnt/home/tools1/CenterLine/clcc/sparc-sunos4/inc/string.h"
 
#line 51 "/home/local/X11R5/include/X11/Intrinsic.h"
typedef char *String;
#line 59
 


 
#line 98
typedef struct _WidgetRec *Widget;
typedef Widget *WidgetList;
typedef struct _WidgetClassRec *WidgetClass;
typedef struct _CompositeRec *CompositeWidget;
typedef struct _XtActionsRec *XtActionList;
typedef struct _XtEventRec *XtEventTable;
typedef struct _XtBoundAccActionRec *XtBoundAccActions;

typedef struct _XtAppStruct *XtAppContext;
typedef unsigned long XtValueMask;
typedef unsigned long XtIntervalId;
typedef unsigned long XtInputId;
typedef unsigned long XtWorkProcId;
typedef unsigned int XtGeometryMask;
typedef unsigned long XtGCMask;    
typedef unsigned long Pixel;      
typedef int  XtCacheType;
#line 140
 
#line 146
typedef char  Boolean;
typedef long  XtArgVal;
typedef unsigned char XtEnum;


typedef unsigned int Cardinal;
typedef unsigned short Dimension;   
typedef short  Position;    


typedef void*  XtPointer;




 
 
typedef XtPointer Opaque;
#line 4 "/home/local/X11R5/include/X11/Core.h"
 
#line 28
 




typedef struct _WidgetClassRec *CoreWidgetClass;
typedef struct _WidgetRec *CoreWidget;
extern      WidgetClass coreWidgetClass;


extern      WidgetClass widgetClass;




 
#line 1 "/home/local/X11R5/include/X11/Composite.h"
 
#line 25
 




typedef struct _CompositeClassRec *CompositeWidgetClass;

typedef Cardinal (*XtOrderProc)(

    Widget   

);



extern void XtManageChildren(

    WidgetList                 ,
    Cardinal    

);

extern void XtManageChild(

    Widget    

);

extern void XtUnmanageChildren(

    WidgetList                 ,
    Cardinal    

);

extern void XtUnmanageChild(

    Widget    

);




extern      WidgetClass compositeWidgetClass;



 
#line 1 "/home/local/X11R5/include/X11/Constraint.h"
 
 
#line 25
 




typedef struct _ConstraintClassRec *ConstraintWidgetClass;


extern      WidgetClass constraintWidgetClass;



 
#line 1 "/home/local/X11R5/include/X11/Object.h"
 
 
#line 25
 




typedef struct _ObjectRec *Object;
typedef struct _ObjectClassRec *ObjectClass;


extern      WidgetClass objectClass;


 
#line 1 "/home/local/X11R5/include/X11/RectObj.h"
 
 
#line 25
 




typedef struct _RectObjRec *RectObj;
typedef struct _RectObjClassRec *RectObjClass;


extern      WidgetClass rectObjClass;


 
#line 171 "/home/local/X11R5/include/X11/Intrinsic.h"
typedef struct _TranslationData *XtTranslations;
typedef struct _TranslationData *XtAccelerators;
typedef unsigned int Modifiers;

typedef void (*XtActionProc)(

    Widget               ,
    XEvent*             ,
    String*              ,
    Cardinal*   

);

typedef XtActionProc* XtBoundActions;

typedef struct _XtActionsRec{
    String  string;
    XtActionProc proc;
} XtActionsRec;

typedef enum {
 
 
    XtAddress,   
    XtBaseOffset,  
    XtImmediate,  
    XtResourceString,  
    XtResourceQuark,  
    XtWidgetBaseOffset,  
    XtProcedureArg  
} XtAddressMode;

typedef struct {
    XtAddressMode   address_mode;
    XtPointer     address_id;
    Cardinal     size;
} XtConvertArgRec, *XtConvertArgList;

typedef void (*XtConvertArgProc)(

    Widget               ,
    Cardinal*            ,
    XrmValue*   

);

typedef struct {
    XtGeometryMask request_mode;
    Position x, y;
    Dimension width, height, border_width;
    Widget sibling;
    int stack_mode;    
} XtWidgetGeometry;

 


 


typedef void (*XtConverter)(  

    XrmValue*            ,
    Cardinal*                ,
    XrmValue*            ,
    XrmValue*   

);

typedef Boolean (*XtTypeConverter)(

    Display*           ,
    XrmValue*            ,
    Cardinal*                ,
    XrmValue*            ,
    XrmValue*          ,
    XtPointer*   

);

typedef void (*XtDestructor)(

    XtAppContext          ,
    XrmValue*          ,
    XtPointer                       ,
    XrmValue*            ,
    Cardinal*   

);

typedef Opaque XtCacheRef;

typedef Opaque XtActionHookId;

typedef void (*XtActionHookProc)(

    Widget         ,
    XtPointer                   ,
    String                   ,
    XEvent*             ,
    String*              ,
    Cardinal*   

);

typedef void (*XtKeyProc)(

    Display*           ,
    unsigned int              ,
    Modifiers                 ,
    Modifiers*                        ,
    KeySym*   

);

typedef void (*XtCaseProc)(

    Display*               ,
    KeySym              ,
    KeySym*                    ,
    KeySym*   

);

typedef void (*XtEventHandler)(

    Widget               ,
    XtPointer                ,
    XEvent*             ,
    Boolean*   

);
typedef unsigned long EventMask;

typedef enum {XtListHead, XtListTail } XtListPosition;

typedef unsigned long XtInputMask;
#line 313
typedef void (*XtTimerCallbackProc)(

    XtPointer                ,
    XtIntervalId*  

);

typedef void (*XtInputCallbackProc)(

    XtPointer                ,
    int*              ,
    XtInputId*   

);

typedef struct {
    String name;
    XtArgVal value;
} Arg, *ArgList;

typedef XtPointer XtVarArgsList;

typedef void (*XtCallbackProc)(

    Widget               ,
    XtPointer                ,  
    XtPointer                    

);

typedef struct _XtCallbackRec {
    XtCallbackProc  callback;
    XtPointer     closure;
} XtCallbackRec, *XtCallbackList;

typedef enum {
 XtCallbackNoList,
 XtCallbackHasNone,
 XtCallbackHasSome
} XtCallbackStatus;

typedef enum  {
    XtGeometryYes,    
    XtGeometryNo,    
    XtGeometryAlmost,    
    XtGeometryDone    
} XtGeometryResult;

typedef enum {XtGrabNone, XtGrabNonexclusive, XtGrabExclusive} XtGrabKind;

typedef struct {
    Widget  shell_widget;
    Widget  enable_widget;
} XtPopdownIDRec, *XtPopdownID;

typedef struct _XtResource {
    String resource_name;  
    String resource_class;  
    String resource_type;  
    Cardinal resource_size;  
    Cardinal resource_offset; 
    String default_type;  
    XtPointer default_addr;  
} XtResource, *XtResourceList;

typedef void (*XtResourceDefaultProc)(

    Widget             ,
    int              ,
    XrmValue*  

);

typedef String (*XtLanguageProc)(

    Display*          ,
    String          ,
    XtPointer  

);

typedef void (*XtErrorMsgHandler)(

    String             ,
    String            ,
    String             ,
    String               ,
    String*              ,
    Cardinal*   

);

typedef void (*XtErrorHandler)(

  String   

);

typedef void (*XtCreatePopupChildProc)(

    Widget  

);

typedef Boolean (*XtWorkProc)(

    XtPointer                  

);

typedef struct {
    char match;
    String substitution;
} SubstitutionRec, *Substitution;

typedef Boolean (*XtFilePredicate)(

   String  

);

typedef XtPointer XtRequestId;

typedef Boolean (*XtConvertSelectionProc)(

    Widget               ,
    Atom*                 ,
    Atom*              ,
    Atom*                   ,
    XtPointer*                    ,
    unsigned long*                    ,
    int*   

);

typedef void (*XtLoseSelectionProc)(

    Widget               ,
    Atom*   

);

typedef void (*XtSelectionDoneProc)(

    Widget               ,
    Atom*                 ,
    Atom*   

);

typedef void (*XtSelectionCallbackProc)(

    Widget               ,
    XtPointer                ,
    Atom*                 ,
    Atom*            ,
    XtPointer              ,
    unsigned long*             ,
    int*   

);

typedef void (*XtLoseSelectionIncrProc)(

    Widget               ,
    Atom*                 ,
    XtPointer    

);

typedef void (*XtSelectionDoneIncrProc)(

    Widget               ,
    Atom*                 ,
    Atom*              ,
    XtRequestId*                  ,
    XtPointer    

);

typedef Boolean (*XtConvertSelectionIncrProc)(

    Widget               ,
    Atom*                 ,
    Atom*              ,
    Atom*            ,
    XtPointer*             ,
    unsigned long*             ,
    int*              ,
    unsigned long*                 ,
    XtPointer                    ,
    XtRequestId*  

);

typedef void (*XtCancelConvertSelectionProc)(

    Widget               ,
    Atom*                 ,
    Atom*              ,
    XtRequestId*                  ,
    XtPointer    

);
#line 522
 



extern Boolean XtConvertAndStore(

    Widget               ,
    const   char*                     ,
    XrmValue*            ,
    const   char*                   ,
    XrmValue*   

);

extern Boolean XtCallConverter(

    Display*           ,
    XtTypeConverter                 ,
    XrmValuePtr            ,
    Cardinal                 ,
    XrmValuePtr            ,
    XrmValue*                 ,
    XtCacheRef*   

);

extern Boolean XtDispatchEvent(

    XEvent*    

);

extern Boolean XtCallAcceptFocus(

    Widget               ,
    Time*   

);

extern Boolean XtPeekEvent(  

    XEvent*   

);

extern Boolean XtAppPeekEvent(

    XtAppContext                   ,
    XEvent*   

);

extern Boolean XtIsSubclass(

    Widget               ,
    WidgetClass   

);

extern Boolean XtIsObject(

    Widget    

);

extern Boolean _XtCheckSubclassFlag(  

    Widget              ,
    unsigned int  

);

extern Boolean _XtIsSubclassOf(  

    Widget              ,
    WidgetClass                    ,
    WidgetClass                  ,
    unsigned int  

);

extern Boolean XtIsManaged(

    Widget    

);

extern Boolean XtIsRealized(

    Widget    

);

extern Boolean XtIsSensitive(

    Widget    

);

extern Boolean XtOwnSelection(

    Widget               ,
    Atom                  ,
    Time             ,
    XtConvertSelectionProc              ,
    XtLoseSelectionProc           ,
    XtSelectionDoneProc  

);

extern Boolean XtOwnSelectionIncremental(

    Widget               ,
    Atom                  ,
    Time             ,
    XtConvertSelectionIncrProc                       ,
    XtLoseSelectionIncrProc                    ,
    XtSelectionDoneIncrProc                    ,
    XtCancelConvertSelectionProc                      ,
    XtPointer    

);

extern XtGeometryResult XtMakeResizeRequest(

    Widget               ,
    unsigned int            ,
    unsigned int             ,
    Dimension*                    ,
    Dimension*   

);

extern void XtTranslateCoords(

    Widget               ,
    int                 ,
    int                 ,
    Position*                    ,
    Position*   

);

extern KeySym* XtGetKeysymTable(

    Display*           ,
    KeyCode*                          ,
    int*   

);

extern void XtKeysymToKeycodeList(

    Display*           ,
    KeySym               ,
    KeyCode**                       ,
    Cardinal*   

);

extern void XtStringConversionWarning(  

    const   char*                     ,
    const   char*      

);

extern void XtDisplayStringConversionWarning(

    Display*            ,
    const   char*                     ,
    const   char*      

);


extern      XtConvertArgRec const colorConvertArgs[];
extern      XtConvertArgRec const screenConvertArg[];
#line 705
extern void XtAppAddConverter(  

    XtAppContext                  ,
    const   char*                    ,
    const   char*                  ,
    XtConverter                 ,
    XtConvertArgList                   ,
    Cardinal    

);

extern void XtAddConverter(  

    const   char*                    ,
    const   char*                   ,
    XtConverter                 ,
    XtConvertArgList                    ,
    Cardinal    

);

extern void XtSetTypeConverter(

    const   char*                     ,
    const   char*                   ,
    XtTypeConverter                 ,
    XtConvertArgList                    ,
    Cardinal                 ,
    XtCacheType                  ,
    XtDestructor   

);

extern void XtAppSetTypeConverter(

    XtAppContext                   ,
    const   char*                     ,
    const   char*                   ,
    XtTypeConverter                 ,
    XtConvertArgList                    ,
    Cardinal                 ,
    XtCacheType                  ,
    XtDestructor   

);

extern void XtConvert(  

    Widget               ,
    const   char*                     ,
    XrmValue*            ,
    const   char*                   ,
    XrmValue*   

);

extern void XtDirectConvert(  

    XtConverter                 ,
    XrmValuePtr            ,
    Cardinal                 ,
    XrmValuePtr            ,
    XrmValue*   

);
#line 775
 

extern XtTranslations XtParseTranslationTable(

    const   char*      

);

extern XtAccelerators XtParseAcceleratorTable(

    const   char*      

);

extern void XtOverrideTranslations(

    Widget               ,
    XtTranslations   

);

extern void XtAugmentTranslations(

    Widget               ,
    XtTranslations   

);

extern void XtInstallAccelerators(

    Widget                    ,
    Widget   

);

extern void XtInstallAllAccelerators(

    Widget                    ,
    Widget   

);

extern void XtUninstallTranslations(

    Widget    

);

extern void XtAppAddActions(

    XtAppContext                   ,
    XtActionList               ,
    Cardinal    

);

extern void XtAddActions(  

    XtActionList               ,
    Cardinal    

);

extern XtActionHookId XtAppAddActionHook(

    XtAppContext                   ,
    XtActionHookProc            ,
    XtPointer    

);

extern void XtRemoveActionHook(

    XtActionHookId   

);

extern void XtGetActionList(

    WidgetClass                    ,
    XtActionList*                     ,
    Cardinal*   

);

extern void XtCallActionProc(

    Widget              ,
    const   char*                 ,
    XEvent*             ,
    String*              ,
    Cardinal   

);

extern void XtRegisterGrabAction(

    XtActionProc                   ,
    int                            ,
    unsigned int                  ,
    int                     ,
    int     

);

extern void XtSetMultiClickTime(

    Display*           ,
    int    

);

extern int XtGetMultiClickTime(

    Display*   

);

extern KeySym XtGetActionKeysym(

    XEvent*             ,
    Modifiers*   

);
#line 904
 

extern void XtTranslateKeycode(

    Display*           ,
    unsigned int              ,
    Modifiers                  ,
    Modifiers*                        ,
    KeySym*   

);

extern void XtTranslateKey(

    Display*           ,
    unsigned int             ,
    Modifiers                 ,
    Modifiers*                        ,
    KeySym*   

);

extern void XtSetKeyTranslator(

    Display*           ,
    XtKeyProc    

);

extern void XtRegisterCaseConverter(

    Display*           ,
    XtCaseProc             ,
    KeySym              ,
    KeySym    

);

extern void XtConvertCase(

    Display*           ,
    KeySym               ,
    KeySym*                    ,
    KeySym*   

);
#line 955
 



 


extern void XtAddEventHandler(

    Widget               ,
    EventMask                   ,
    int                           ,
    XtEventHandler            ,
    XtPointer    

);

extern void XtRemoveEventHandler(

    Widget               ,
    EventMask                   ,
    int                           ,
    XtEventHandler            ,
    XtPointer    

);

extern void XtAddRawEventHandler(

    Widget               ,
    EventMask                   ,
    int                           ,
    XtEventHandler            ,
    XtPointer    

);

extern void XtRemoveRawEventHandler(

    Widget               ,
    EventMask                   ,
    int                           ,
    XtEventHandler            ,
    XtPointer    

);

extern void XtInsertEventHandler(

    Widget               ,
    EventMask                   ,
    int                           ,
    XtEventHandler            ,
    XtPointer                ,
    XtListPosition   

);

extern void XtInsertRawEventHandler(

    Widget               ,
    EventMask                   ,
    int                           ,
    XtEventHandler            ,
    XtPointer                ,
    XtListPosition   

);

extern EventMask XtBuildEventMask(

    Widget    

);

extern void XtAddGrab(

    Widget               ,
    int                         ,
    int           

);

extern void XtRemoveGrab(

    Widget    

);

extern void XtProcessEvent(  

    XtInputMask    

);

extern void XtAppProcessEvent(

    XtAppContext                    ,
    XtInputMask    

);

extern void XtMainLoop(  

    void

);

extern void XtAppMainLoop(

    XtAppContext    

);

extern void XtAddExposureToRegion(

    XEvent*             ,
    Region    

);

extern void XtSetKeyboardFocus(

    Widget               ,
    Widget    

);

extern Time XtLastTimestampProcessed(

    Display*   

);
#line 1093
 

extern XtIntervalId XtAddTimeOut(  

    unsigned long                ,
    XtTimerCallbackProc           ,
    XtPointer    

);

extern XtIntervalId XtAppAddTimeOut(

    XtAppContext                   ,
    unsigned long                ,
    XtTimerCallbackProc           ,
    XtPointer    

);

extern void XtRemoveTimeOut(

    XtIntervalId   

);

extern XtInputId XtAddInput(  

    int               ,
    XtPointer                  ,
    XtInputCallbackProc           ,
    XtPointer    

);

extern XtInputId XtAppAddInput(

    XtAppContext                         ,
    int               ,
    XtPointer                  ,
    XtInputCallbackProc           ,
    XtPointer    

);

extern void XtRemoveInput(

    XtInputId    

);

extern void XtNextEvent(  

    XEvent*    

);

extern void XtAppNextEvent(

    XtAppContext                   ,
    XEvent*   

);
#line 1161
extern XtInputMask XtPending(  

    void

);

extern XtInputMask XtAppPending(

    XtAppContext   

);
#line 1177
 
#line 1199
extern void XtRealizeWidget(

    Widget    

);

void XtUnrealizeWidget(

    Widget    

);

extern void XtDestroyWidget(

    Widget    

);

extern void XtSetSensitive(

    Widget               ,
    int           

);

extern void XtSetMappedWhenManaged(

    Widget               ,
    int           

);

extern Widget XtNameToWidget(

    Widget                  ,
    const   char*      

);

extern Widget XtWindowToWidget(

    Display*               ,
    Window    

);
#line 1249
 
#line 1255
extern ArgList XtMergeArgLists(

    ArgList              ,
    Cardinal                  ,
    ArgList              ,
    Cardinal    

);
#line 1268
 




extern XtVarArgsList XtVaCreateArgsList(

    XtPointer            , ...

);
#line 1283
 



 

extern Display *XtDisplay(

    Widget    

);

extern Display *XtDisplayOfObject(

    Widget    

);

extern Screen *XtScreen(

    Widget    

);

extern Screen *XtScreenOfObject(

    Widget    

);

extern Window XtWindow(

    Widget    

);

extern Window XtWindowOfObject(

    Widget    

);

extern String XtName(

    Widget    

);

extern WidgetClass XtSuperclass(

    Widget    

);

extern WidgetClass XtClass(

    Widget    

);

extern Widget XtParent(

    Widget    

);
#line 1355
extern void XtAddCallback(

    Widget               ,
    const   char*                         ,
    XtCallbackProc                ,
    XtPointer    

);

extern void XtRemoveCallback(

    Widget               ,
    const   char*                         ,
    XtCallbackProc                ,
    XtPointer    

);

extern void XtAddCallbacks(

    Widget               ,
    const   char*                        ,
    XtCallbackList   

);

extern void XtRemoveCallbacks(

    Widget               ,
    const   char*                         ,
    XtCallbackList   

);

extern void XtRemoveAllCallbacks(

    Widget               ,
    const   char*       

);


extern void XtCallCallbacks(

    Widget               ,
    const   char*                         ,
    XtPointer    

);

extern void XtCallCallbackList(

    Widget              ,
    XtCallbackList                 ,
    XtPointer    

);

extern XtCallbackStatus XtHasCallbacks(

    Widget               ,
    const   char*       

);
#line 1424
 


extern XtGeometryResult XtMakeGeometryRequest(

    Widget               ,
    XtWidgetGeometry*              ,
    XtWidgetGeometry*  

);

extern XtGeometryResult XtQueryGeometry(

    Widget               ,
    XtWidgetGeometry*               ,
    XtWidgetGeometry*  

);

extern Widget XtCreatePopupShell(

    const   char*               ,
    WidgetClass                   ,
    Widget               ,
    ArgList             ,
    Cardinal    

);

extern Widget XtVaCreatePopupShell(

    const   char*               ,
    WidgetClass                   ,
    Widget              ,
    ...

);

extern void XtPopup(

    Widget                    ,
    XtGrabKind    

);

extern void XtPopupSpringLoaded(

    Widget    

);

extern void XtCallbackNone(

    Widget               ,
    XtPointer                ,
    XtPointer    

);

extern void XtCallbackNonexclusive(

    Widget               ,
    XtPointer                ,
    XtPointer    

);

extern void XtCallbackExclusive(

    Widget               ,
    XtPointer                ,
    XtPointer    

);

extern void XtPopdown(

    Widget    

);

extern void XtCallbackPopdown(

    Widget               ,
    XtPointer                ,
    XtPointer    

);

extern void XtMenuPopupAction(

    Widget               ,
    XEvent*             ,
    String*              ,
    Cardinal*   

);

extern Widget XtCreateWidget(

    const   char*                ,
    WidgetClass                    ,
    Widget               ,
    ArgList             ,
    Cardinal    

);

extern Widget XtCreateManagedWidget(

    const   char*                ,
    WidgetClass                    ,
    Widget               ,
    ArgList             ,
    Cardinal    

);

extern Widget XtVaCreateWidget(

    const   char*               ,
    WidgetClass              ,
    Widget              ,
    ...

);

extern Widget XtVaCreateManagedWidget(

    const   char*               ,
    WidgetClass                    ,
    Widget              ,
    ...

);

extern Widget XtCreateApplicationShell(  

    const   char*                ,
    WidgetClass                    ,
    ArgList             ,
    Cardinal    

);

extern Widget XtAppCreateShell(

    const   char*                           ,
    const   char*                            ,
    WidgetClass                    ,
    Display*               ,
    ArgList             ,
    Cardinal    

);

extern Widget XtVaAppCreateShell(

    const   char*                           ,
    const   char*                            ,
    WidgetClass                    ,
    Display*               ,
    ...

);
#line 1594
 

extern void XtToolkitInitialize(

    void

);

extern XtLanguageProc XtSetLanguageProc(

    XtAppContext                  ,
    XtLanguageProc           ,
    XtPointer   

);

extern void XtDisplayInitialize(

    XtAppContext                   ,
    Display*           ,
    const   char*                           ,
    const   char*                            ,
    XrmOptionDescRec*               ,
    Cardinal                    ,
    int*            ,
    char**   

);

extern Widget XtAppInitialize(

    XtAppContext*                         ,
    const   char*                            ,
    XrmOptionDescList               ,
    Cardinal                    ,
    int*                   ,
    String*                   ,
    String*                          ,
    ArgList             ,
    Cardinal    

);

extern Widget XtVaAppInitialize(

    XtAppContext*                         ,
    const   char*                            ,
    XrmOptionDescList              ,
    Cardinal                   ,
    int*                   ,
    String*                   ,
    String*                          ,
    ...

);

extern Widget XtInitialize(  

    const   char*                      ,
    const   char*                             ,
    XrmOptionDescRec*               ,
    Cardinal                    ,
    int*            ,
    char**   

);

extern Display *XtOpenDisplay(

    XtAppContext                   ,
    const   char*                         ,
    const   char*                           ,
    const   char*                            ,
    XrmOptionDescRec*              ,
    Cardinal                    ,
    int*            ,
    char**   

);

extern XtAppContext XtCreateApplicationContext(

    void

);

extern void XtAppSetFallbackResources(

    XtAppContext                   ,
    String*   

);

extern void XtDestroyApplicationContext(

    XtAppContext   

);

extern void XtInitializeWidgetClass(

    WidgetClass   

);

extern XtAppContext XtWidgetToApplicationContext(

    Widget    

);

extern XtAppContext XtDisplayToApplicationContext(

    Display*   

);

extern XrmDatabase XtDatabase(

    Display*   

);

extern XrmDatabase XtScreenDatabase(

    Screen*   

);

extern void XtCloseDisplay(

    Display*   

);

extern void XtGetApplicationResources(

    Widget               ,
    XtPointer             ,
    XtResourceList                 ,
    Cardinal                      ,
    ArgList             ,
    Cardinal    

);

extern void XtVaGetApplicationResources(

    Widget              ,
    XtPointer            ,
    XtResourceList                ,
    Cardinal                     ,
    ...

);

extern void XtGetSubresources(

    Widget               ,
    XtPointer             ,
    const   char*                ,
    const   char*                 ,
    XtResourceList                 ,
    Cardinal                      ,
    ArgList             ,
    Cardinal    

);

extern void XtVaGetSubresources(

    Widget              ,
    XtPointer            ,
    const   char*               ,
    const   char*                ,
    XtResourceList                ,
    Cardinal                     ,
    ...

);

extern void XtSetValues(

    Widget               ,
    ArgList             ,
    Cardinal    

);

extern void XtVaSetValues(

    Widget              ,
    ...

);

extern void XtGetValues(

    Widget               ,
    ArgList             ,
    Cardinal    

);

extern void XtVaGetValues(

    Widget              ,
    ...

);

extern void XtSetSubvalues(

    XtPointer             ,
    XtResourceList                 ,
    Cardinal                      ,
    ArgList             ,
    Cardinal    

);

extern void XtVaSetSubvalues(

    XtPointer            ,
    XtResourceList                ,
    Cardinal                     ,
    ...

);

extern void XtGetSubvalues(

    XtPointer             ,
    XtResourceList                 ,
    Cardinal                      ,
    ArgList             ,
    Cardinal    

);

extern void XtVaGetSubvalues(

    XtPointer            ,
    XtResourceList                ,
    Cardinal                     ,
    ...

);

extern void XtGetResourceList(

    WidgetClass                    ,
    XtResourceList*                       ,
    Cardinal*   

);

extern void XtGetConstraintResourceList(

    WidgetClass                    ,
    XtResourceList*                       ,
    Cardinal*   

);
#line 1899
 

extern XtErrorMsgHandler XtAppSetErrorMsgHandler(

    XtAppContext                   ,
    XtErrorMsgHandler   

);

extern void XtSetErrorMsgHandler(  

    XtErrorMsgHandler   

);

extern XtErrorMsgHandler XtAppSetWarningMsgHandler(

    XtAppContext                   ,
    XtErrorMsgHandler   

);

extern void XtSetWarningMsgHandler(  

    XtErrorMsgHandler   

);

extern void XtAppErrorMsg(

    XtAppContext                   ,
    const   char*                ,
    const   char*               ,
    const   char*                ,
    const   char*                  ,
    String*              ,
    Cardinal*   

);

extern void XtErrorMsg(  

    const   char*                ,
    const   char*               ,
    const   char*                ,
    const   char*                  ,
    String*              ,
    Cardinal*   

);

extern void XtAppWarningMsg(

    XtAppContext                   ,
    const   char*                ,
    const   char*                ,
    const   char*                 ,
    const   char*                   ,
    String*              ,
    Cardinal*   

);

extern void XtWarningMsg(  

    const   char*               ,
    const   char*               ,
    const   char*                ,
    const   char*                  ,
    String*              ,
    Cardinal*   

);

extern XtErrorHandler XtAppSetErrorHandler(

    XtAppContext                   ,
    XtErrorHandler   

);

extern void XtSetErrorHandler(  

    XtErrorHandler   

);

extern XtErrorHandler XtAppSetWarningHandler(

    XtAppContext                   ,
    XtErrorHandler   

);

extern void XtSetWarningHandler(  

    XtErrorHandler   

);

extern void XtAppError(

    XtAppContext                   ,
    const   char*      

);

extern void XtError(  

    const   char*      

);

extern void XtAppWarning(

    XtAppContext                   ,
    const   char*      

);

extern void XtWarning(  

    const   char*      

);

extern XrmDatabase *XtAppGetErrorDatabase(

    XtAppContext   

);

extern XrmDatabase *XtGetErrorDatabase(  

    void

);

extern void XtAppGetErrorDatabaseText(

    XtAppContext                   ,
    const   char*               ,
    const   char*               ,
    const   char*                ,
    const   char*                   ,
    String                      ,
    int               ,
    XrmDatabase   

);

extern void XtGetErrorDatabaseText(  

    const   char*               ,
    const   char*               ,
    const   char*                ,
    const   char*                   ,
    String                      ,
    int    

);
#line 2065
 

extern char *XtMalloc(

    Cardinal    

);

extern char *XtCalloc(

    Cardinal           ,
    Cardinal    

);

extern char *XtRealloc(

    char*            ,
    Cardinal    

);

extern void XtFree(

    char*   

);
#line 2142
 

extern XtWorkProcId XtAddWorkProc(  

    XtWorkProc             ,
    XtPointer    

);

extern XtWorkProcId XtAppAddWorkProc(

    XtAppContext                   ,
    XtWorkProc             ,
    XtPointer    

);

extern void  XtRemoveWorkProc(

    XtWorkProcId   

);
#line 2169
 

extern GC XtGetGC(

    Widget               ,
    XtGCMask                  ,
    XGCValues*    

);

extern GC XtAllocateGC(

    Widget               ,
    Cardinal             ,
    XtGCMask                  ,
    XGCValues*               ,
    XtGCMask                   ,
    XtGCMask   

);




 
extern void XtDestroyGC(  

    GC     

);

extern void XtReleaseGC(

    Widget               ,
    GC     

);



extern void XtAppReleaseCacheRefs(

    XtAppContext                  ,
    XtCacheRef*   

);

extern void XtCallbackReleaseCacheRef(

    Widget               ,
    XtPointer                ,  
    XtPointer    

);

extern void XtCallbackReleaseCacheRefList(

    Widget               ,
    XtPointer                ,  
    XtPointer    

);

extern void XtSetWMColormapWindows(

    Widget               ,
    Widget*            ,
    Cardinal   

);

extern String XtFindFile(

    const   char*               ,
    Substitution                    ,
    Cardinal                          ,
    XtFilePredicate  

);

extern String XtResolvePathname(

    Display*           ,
    const   char*               ,
    const   char*                   ,
    const   char*                 ,
    const   char*               ,
    Substitution                    ,
    Cardinal                         ,
    XtFilePredicate   

);
#line 2266
 


 
extern void XtDisownSelection(

    Widget               ,
    Atom                  ,
    Time    

);

extern void XtGetSelectionValue(

    Widget               ,
    Atom                  ,
    Atom               ,
    XtSelectionCallbackProc               ,
    XtPointer                ,
    Time    

);

extern void XtGetSelectionValues(

    Widget               ,
    Atom                  ,
    Atom*               ,
    int              ,
    XtSelectionCallbackProc               ,
    XtPointer*                ,
    Time    

);

extern void XtAppSetSelectionTimeout(

    XtAppContext                   ,
    unsigned long   

);

extern void XtSetSelectionTimeout(  

    unsigned long   

);

extern unsigned long XtAppGetSelectionTimeout(

    XtAppContext   

);

extern unsigned long XtGetSelectionTimeout(  

    void

);

extern XSelectionRequestEvent *XtGetSelectionRequest(

    Widget               ,
    Atom                  ,
    XtRequestId   

);

extern void XtGetSelectionValueIncremental(

    Widget               ,
    Atom                  ,
    Atom               ,
    XtSelectionCallbackProc                         ,
    XtPointer                    ,
    Time    

);

extern void XtGetSelectionValuesIncremental(

    Widget               ,
    Atom                  ,
    Atom*               ,
    int              ,
    XtSelectionCallbackProc               ,
    XtPointer*                   ,
    Time    

);

extern void XtGrabKey(

    Widget               ,
    unsigned int              ,
    Modifiers                  ,
    int                            ,
    int                     ,
    int    

);

extern void XtUngrabKey(

    Widget               ,
    unsigned int              ,
    Modifiers    

);

extern int XtGrabKeyboard(

    Widget               ,
    int                            ,
    int                     ,
    int                      ,
    Time    

);

extern void XtUngrabKeyboard(

    Widget               ,
    Time    

);

extern void XtGrabButton(

    Widget               ,
    int               ,
    Modifiers                  ,
    int                            ,
    unsigned int                 ,
    int                     ,
    int                      ,
    Window                   ,
    Cursor    

);

extern void XtUngrabButton(

    Widget               ,
    unsigned int             ,
    Modifiers    

);

extern int XtGrabPointer(

    Widget               ,
    int                            ,
    unsigned int                 ,
    int                     ,
    int                      ,
    Window                   ,
    Cursor               ,
    Time    

);

extern void XtUngrabPointer(

    Widget               ,
    Time    

);

extern void XtGetApplicationNameAndClass(

    Display*           ,
    String*                   ,
    String*   

);




 


 

extern Boolean XtCvtStringToAcceleratorTable(

    Display*          ,
    XrmValuePtr           ,  
    Cardinal*                 , 
    XrmValuePtr              ,
    XrmValuePtr            ,
    XtPointer*  

);

extern Boolean XtCvtStringToAtom(

    Display*          ,
    XrmValuePtr           ,  
    Cardinal*                 , 
    XrmValuePtr              ,
    XrmValuePtr            ,
    XtPointer*  

);

extern Boolean XtCvtStringToBoolean(

    Display*          ,
    XrmValuePtr           ,  
    Cardinal*                 , 
    XrmValuePtr              ,
    XrmValuePtr            ,
    XtPointer*  

);

extern Boolean XtCvtStringToBool(

    Display*          ,
    XrmValuePtr           ,  
    Cardinal*                 , 
    XrmValuePtr              ,
    XrmValuePtr            ,
    XtPointer*  

);

extern Boolean XtCvtStringToCursor(

    Display*          ,
    XrmValuePtr           ,  
    Cardinal*                 , 
    XrmValuePtr              ,
    XrmValuePtr            ,
    XtPointer*  

);

extern Boolean XtCvtStringToDimension(

    Display*          ,
    XrmValuePtr           ,  
    Cardinal*                 , 
    XrmValuePtr              ,
    XrmValuePtr            ,
    XtPointer*  

);

extern Boolean XtCvtStringToDisplay(

    Display*          ,
    XrmValuePtr           ,  
    Cardinal*                 , 
    XrmValuePtr              ,
    XrmValuePtr            ,
    XtPointer*  

);

extern Boolean XtCvtStringToFile(

    Display*          ,
    XrmValuePtr           ,  
    Cardinal*                 , 
    XrmValuePtr              ,
    XrmValuePtr            ,
    XtPointer*  

);

extern Boolean XtCvtStringToFloat(

    Display*          ,
    XrmValuePtr           ,  
    Cardinal*                 , 
    XrmValuePtr              ,
    XrmValuePtr            ,
    XtPointer*  

);

extern Boolean XtCvtStringToFont(

    Display*          ,
    XrmValuePtr           ,  
    Cardinal*                 , 
    XrmValuePtr              ,
    XrmValuePtr            ,
    XtPointer*  

);

extern Boolean XtCvtStringToFontSet(

    Display*          ,
    XrmValuePtr           ,  
    Cardinal*                 , 
    XrmValuePtr              ,
    XrmValuePtr            ,
    XtPointer*  

);

extern Boolean XtCvtStringToFontStruct(

    Display*          ,
    XrmValuePtr           ,  
    Cardinal*                 , 
    XrmValuePtr              ,
    XrmValuePtr            ,
    XtPointer*  

);

extern Boolean XtCvtStringToInt(

    Display*          ,
    XrmValuePtr           ,  
    Cardinal*                 , 
    XrmValuePtr              ,
    XrmValuePtr            ,
    XtPointer*  

);

extern Boolean XtCvtStringToInitialState(

    Display*          ,
    XrmValuePtr           ,  
    Cardinal*                 , 
    XrmValuePtr              ,
    XrmValuePtr            ,
    XtPointer*  

);

extern Boolean XtCvtStringToPixel(

    Display*          ,
    XrmValuePtr           ,  
    Cardinal*                 , 
    XrmValuePtr              ,
    XrmValuePtr            ,
    XtPointer*  

);



extern Boolean XtCvtStringToShort(

    Display*          ,
    XrmValuePtr           ,  
    Cardinal*                 , 
    XrmValuePtr              ,
    XrmValuePtr            ,
    XtPointer*  

);

extern Boolean XtCvtStringToTranslationTable(

    Display*          ,
    XrmValuePtr           ,  
    Cardinal*                 , 
    XrmValuePtr              ,
    XrmValuePtr            ,
    XtPointer*  

);

extern Boolean XtCvtStringToUnsignedChar(

    Display*          ,
    XrmValuePtr           ,  
    Cardinal*                 , 
    XrmValuePtr              ,
    XrmValuePtr            ,
    XtPointer*  

);

extern Boolean XtCvtStringToVisual(

    Display*          ,
    XrmValuePtr           ,  
    Cardinal*                 , 
    XrmValuePtr              ,
    XrmValuePtr            ,
    XtPointer*  

);

 

extern Boolean XtCvtIntToBoolean(

    Display*          ,
    XrmValuePtr           ,  
    Cardinal*                 , 
    XrmValuePtr              ,
    XrmValuePtr            ,
    XtPointer*  

);

extern Boolean XtCvtIntToBool(

    Display*          ,
    XrmValuePtr           ,  
    Cardinal*                 , 
    XrmValuePtr              ,
    XrmValuePtr            ,
    XtPointer*  

);

extern Boolean XtCvtIntToColor(

    Display*          ,
    XrmValuePtr           ,  
    Cardinal*                 , 
    XrmValuePtr              ,
    XrmValuePtr            ,
    XtPointer*  

);



extern Boolean XtCvtIntToFloat(

    Display*          ,
    XrmValuePtr           ,  
    Cardinal*                 , 
    XrmValuePtr              ,
    XrmValuePtr            ,
    XtPointer*  

);

extern Boolean XtCvtIntToFont(

    Display*          ,
    XrmValuePtr           ,  
    Cardinal*                 , 
    XrmValuePtr              ,
    XrmValuePtr            ,
    XtPointer*  

);

extern Boolean XtCvtIntToPixel(

    Display*          ,
    XrmValuePtr           ,  
    Cardinal*                 , 
    XrmValuePtr              ,
    XrmValuePtr            ,
    XtPointer*  

);

extern Boolean XtCvtIntToPixmap(

    Display*          ,
    XrmValuePtr           ,  
    Cardinal*                 , 
    XrmValuePtr              ,
    XrmValuePtr            ,
    XtPointer*  

);



extern Boolean XtCvtIntToShort(

    Display*          ,
    XrmValuePtr           ,  
    Cardinal*                 , 
    XrmValuePtr              ,
    XrmValuePtr            ,
    XtPointer*  

);

extern Boolean XtCvtIntToUnsignedChar(

    Display*          ,
    XrmValuePtr           ,  
    Cardinal*                 , 
    XrmValuePtr              ,
    XrmValuePtr            ,
    XtPointer*  

);

 

extern Boolean XtCvtColorToPixel(

    Display*          ,
    XrmValuePtr           ,  
    Cardinal*                 , 
    XrmValuePtr              ,
    XrmValuePtr            ,
    XtPointer*  

);

 
#line 2788
 
#line 3 "/home/local/X11R5/include/X11/Shell.h"
 
#line 26
 
#line 35
 


 

 
 
#line 127
extern const     char XtShellStrings[];
#line 362
 

typedef struct _ShellClassRec *ShellWidgetClass;
typedef struct _OverrideShellClassRec *OverrideShellWidgetClass;
typedef struct _WMShellClassRec *WMShellWidgetClass;
typedef struct _TransientShellClassRec *TransientShellWidgetClass;
typedef struct _TopLevelShellClassRec *TopLevelShellWidgetClass;
typedef struct _ApplicationShellClassRec *ApplicationShellWidgetClass;


extern      WidgetClass shellWidgetClass;
extern      WidgetClass overrideShellWidgetClass;
extern      WidgetClass wmShellWidgetClass;
extern      WidgetClass transientShellWidgetClass;
extern      WidgetClass topLevelShellWidgetClass;
extern      WidgetClass applicationShellWidgetClass;



 
#line 7 "/home/local/X11R5/include/X11/Xatom.h"
 
#line 4 "/home/tools1/uimx2.5/motif12/usr/include/Xm/XmStrDefs.h"
   


   
 

 

 
 
 
#line 886
extern          char _XmStrings[];
#line 1 "/home/local/X11R5/include/X11/StringDefs.h"
 

 
 
#line 228
extern const     char XtStrings[];
#line 4 "/home/tools1/uimx2.5/motif12/usr/include/Xm/VirtKeys.h"
   


   
 

 
#line 4 "/home/tools1/uimx2.5/motif12/usr/include/Xm/Xm.h"
   


   
 

 
#line 1439
  
#line 61 "/home/tools1/uimx2.5/motif12/usr/include/Xm/VirtKeys.h"
 
#line 68
extern void XmTranslateKey( 
                        Display *dpy,

                        unsigned int keycode,



                        Modifiers modifiers,
                        Modifiers *modifiers_return,
                        KeySym *keysym_return) ;


 
#line 40 "/home/tools1/uimx2.5/motif12/usr/include/Xm/Xm.h"
extern int xmUseVersion;


 
#line 52
 
#line 65
extern  char    _XmSDEFAULT_FONT[];             
extern  char    _XmSDEFAULT_BACKGROUND[];       
#line 73
 
typedef enum{ XmFONT_IS_FONT, XmFONT_IS_FONTSET } XmFontType;

enum{ XmSTRING_DIRECTION_L_TO_R, XmSTRING_DIRECTION_R_TO_L
 } ;


typedef unsigned char * XmString;   
typedef XmString * XmStringTable;   
typedef char *  XmStringCharSet;  
typedef unsigned char XmStringComponentType;  
typedef unsigned char  XmStringDirection;

typedef struct _XmFontListRec       *XmFontListEntry;   
typedef struct _XmFontListRec       *XmFontList;        
typedef struct __XmStringContextRec *_XmStringContext;  
typedef struct __XmStringRec        *_XmString;         
typedef struct _XmtStringContextRec *XmStringContext;   
typedef struct _XmFontListContextRec *XmFontContext;    

enum{ XmSTRING_COMPONENT_UNKNOWN, XmSTRING_COMPONENT_CHARSET,
 XmSTRING_COMPONENT_TEXT, XmSTRING_COMPONENT_DIRECTION,
        XmSTRING_COMPONENT_SEPARATOR,   XmSTRING_COMPONENT_LOCALE_TEXT
  
 } ;




    
#line 111
 


 


extern      WidgetClass xmPrimitiveWidgetClass;


typedef struct _XmPrimitiveClassRec * XmPrimitiveWidgetClass;
typedef struct _XmPrimitiveRec      * XmPrimitiveWidget;


 


extern      WidgetClass xmGadgetClass;


typedef struct _XmGadgetClassRec * XmGadgetClass;
typedef struct _XmGadgetRec      * XmGadget;


 



extern      WidgetClass xmManagerWidgetClass;


typedef struct _XmManagerClassRec * XmManagerWidgetClass;
typedef struct _XmManagerRec      * XmManagerWidget;




 
#line 164
 

 

enum{ XmCHANGE_ALL,   XmCHANGE_NONE,
 XmCHANGE_WIDTH,   XmCHANGE_HEIGHT
 } ;

 

enum{ XmPIXELS,   Xm100TH_MILLIMETERS,
 Xm1000TH_INCHES,  Xm100TH_POINTS,
 Xm100TH_FONT_UNITS
 } ;

 

enum{ XmDESTROY,   XmUNMAP,
 XmDO_NOTHING
 } ;
enum{ XmEXPLICIT,   XmPOINTER
 } ;


 

enum{ XmNONE,    XmTAB_GROUP,
 XmSTICKY_TAB_GROUP,  XmEXCLUSIVE_TAB_GROUP
 } ;
#line 198
 

enum{                XmBELL = 1
 } ;



 

enum{ XmNO_ORIENTATION,  XmVERTICAL,
 XmHORIZONTAL
 } ;
enum{ XmWORK_AREA,   XmMENU_BAR,
 XmMENU_PULLDOWN,  XmMENU_POPUP,
 XmMENU_OPTION
 } ;
enum{ XmNO_PACKING,   XmPACK_TIGHT,
 XmPACK_COLUMN,   XmPACK_NONE
 } ;
enum{
                                 XmALIGNMENT_CONTENTS_TOP = 3,
 XmALIGNMENT_CONTENTS_BOTTOM
 } ;
enum{ XmTEAR_OFF_ENABLED,  XmTEAR_OFF_DISABLED
 } ;
enum{ XmUNPOST,    XmUNPOST_AND_REPLAY
 } ;
enum{   XmLAST_POSITION = -1,           XmFIRST_POSITION
 } ;


 

enum{ XmALIGNMENT_BEGINNING,  XmALIGNMENT_CENTER,
 XmALIGNMENT_END
 } ;
enum{   XmALIGNMENT_BASELINE_TOP,     
 XmALIGNMENT_BASELINE_BOTTOM = 2, XmALIGNMENT_WIDGET_TOP,
 XmALIGNMENT_WIDGET_BOTTOM
    } ;


 

enum{ XmFRAME_GENERIC_CHILD,          XmFRAME_WORKAREA_CHILD,
        XmFRAME_TITLE_CHILD
 } ;


 

enum{ XmN_OF_MANY = 1,  XmONE_OF_MANY
 } ;


 

enum{ XmATTACH_NONE,   XmATTACH_FORM,
 XmATTACH_OPPOSITE_FORM,  XmATTACH_WIDGET,
 XmATTACH_OPPOSITE_WIDGET, XmATTACH_POSITION,
 XmATTACH_SELF
 } ;
enum{ XmRESIZE_NONE,   XmRESIZE_GROW,
 XmRESIZE_ANY
 } ;


 

enum{ XmCR_NONE,   XmCR_HELP,
 XmCR_VALUE_CHANGED,  XmCR_INCREMENT,
 XmCR_DECREMENT,   XmCR_PAGE_INCREMENT,
 XmCR_PAGE_DECREMENT,  XmCR_TO_TOP,
 XmCR_TO_BOTTOM,   XmCR_DRAG,
 XmCR_ACTIVATE,   XmCR_ARM,
 XmCR_DISARM,   XmCR_MAP = 16,
 XmCR_UNMAP,   XmCR_FOCUS,
 XmCR_LOSING_FOCUS,  XmCR_MODIFYING_TEXT_VALUE,
 XmCR_MOVING_INSERT_CURSOR, XmCR_EXECUTE,
 XmCR_SINGLE_SELECT,  XmCR_MULTIPLE_SELECT,
 XmCR_EXTENDED_SELECT,  XmCR_BROWSE_SELECT,
 XmCR_DEFAULT_ACTION,  XmCR_CLIPBOARD_DATA_REQUEST,
 XmCR_CLIPBOARD_DATA_DELETE, XmCR_CASCADING,
 XmCR_OK,   XmCR_CANCEL,
 XmCR_APPLY = 34,  XmCR_NO_MATCH,
 XmCR_COMMAND_ENTERED,  XmCR_COMMAND_CHANGED,
 XmCR_EXPOSE,   XmCR_RESIZE,
 XmCR_INPUT,   XmCR_GAIN_PRIMARY,
 XmCR_LOSE_PRIMARY,  XmCR_CREATE,
 XmCR_TEAR_OFF_ACTIVATE,  XmCR_TEAR_OFF_DEACTIVATE,
 XmCR_OBSCURED_TRAVERSAL
 } ;


 

typedef struct
{
    int     reason;
    XEvent  *event;
} XmAnyCallbackStruct;

typedef struct
{
    int     reason;
    XEvent  *event;
    int     click_count;
} XmArrowButtonCallbackStruct;

typedef struct
{
    int     reason;
    XEvent  *event;
    Window  window;
} XmDrawingAreaCallbackStruct;

typedef struct
{
    int     reason;
    XEvent  *event;
    Window  window;
    int     click_count;
} XmDrawnButtonCallbackStruct;

typedef struct
{
    int     reason;
    XEvent  *event;
    int     click_count;
} XmPushButtonCallbackStruct;

typedef struct
{
    int     reason;
    XEvent  *event;
    Widget  widget;
    char    *data;
    char    *callbackstruct;
} XmRowColumnCallbackStruct;

typedef struct
{
   int reason;
   XEvent * event;
   int value;
   int pixel;
} XmScrollBarCallbackStruct;

typedef struct
{
   int reason;
   XEvent * event;
   int set;
} XmToggleButtonCallbackStruct;

typedef struct
{
   int       reason;
   XEvent    *event;
   XmString  item;
   int       item_length;
   int       item_position;
   XmString  *selected_items;
   int       selected_item_count;
   int       *selected_item_positions;
   char      selection_type;
} XmListCallbackStruct;

typedef struct
{
    int reason;
    XEvent *event;
    XmString value;
    int  length;
} XmSelectionBoxCallbackStruct;

typedef struct
{
    int reason;
    XEvent *event;
    XmString value;
    int  length;
} XmCommandCallbackStruct;

typedef struct
{
    int  reason;
    XEvent *event;
    XmString value;
    int  length;
    XmString mask;
    int  mask_length;
    XmString dir ;
    int  dir_length ;
    XmString    pattern ;
    int  pattern_length ;
} XmFileSelectionBoxCallbackStruct;


typedef struct 
{
   int reason;
   XEvent * event;
   int value;
} XmScaleCallbackStruct;




 

enum{ XmMULTICLICK_DISCARD,  XmMULTICLICK_KEEP
 } ;


 

enum{ XmSHADOW_IN = 7,  XmSHADOW_OUT
 } ;


 

enum{ XmARROW_UP,   XmARROW_DOWN,
 XmARROW_LEFT,   XmARROW_RIGHT
 } ;



 

enum{ XmNO_LINE,   XmSINGLE_LINE,
 XmDOUBLE_LINE,   XmSINGLE_DASHED_LINE,
 XmDOUBLE_DASHED_LINE,  XmSHADOW_ETCHED_IN,
 XmSHADOW_ETCHED_OUT,  XmSHADOW_ETCHED_IN_DASH,
 XmSHADOW_ETCHED_OUT_DASH, XmINVALID_SEPARATOR_TYPE
 } ;

enum{ XmPIXMAP = 1,   XmSTRING
 } ;



 

enum{ XmWINDOW,        
 XmCURSOR = 2
 } ;



 

enum{ XmMAX_ON_TOP,   XmMAX_ON_BOTTOM,
 XmMAX_ON_LEFT,   XmMAX_ON_RIGHT
 } ;




 

enum{ XmSINGLE_SELECT,  XmMULTIPLE_SELECT,
 XmEXTENDED_SELECT,  XmBROWSE_SELECT
 } ;
enum{ XmSTATIC,   XmDYNAMIC
 } ;




 

enum{ XmVARIABLE,   XmCONSTANT,
 XmRESIZE_IF_POSSIBLE
 } ;
enum{ XmAUTOMATIC,   XmAPPLICATION_DEFINED
 } ;
enum{                  XmAS_NEEDED = 1
 } ;
#line 493
 

enum{ XmCOMMAND_ABOVE_WORKSPACE, XmCOMMAND_BELOW_WORKSPACE
 } ;




 

enum{ XmMULTI_LINE_EDIT,  XmSINGLE_LINE_EDIT
 } ;

typedef enum{
 XmTEXT_FORWARD,
 XmTEXT_BACKWARD
 } XmTextDirection;

typedef long XmTextPosition;
typedef Atom XmTextFormat;
#line 520
typedef enum{
 XmSELECT_POSITION,  XmSELECT_WHITESPACE,
 XmSELECT_WORD,   XmSELECT_LINE,
 XmSELECT_ALL,   XmSELECT_PARAGRAPH
 } XmTextScanType ;

typedef enum{
 XmHIGHLIGHT_NORMAL,  XmHIGHLIGHT_SELECTED,
 XmHIGHLIGHT_SECONDARY_SELECTED
 } XmHighlightMode ;

 

typedef struct {
    char *ptr;                   
    int length;                  
    XmTextFormat format;        
} XmTextBlockRec, *XmTextBlock;

typedef struct
{
    int reason;
    XEvent  *event;
    Boolean doit;
    long currInsert, newInsert;
    long startPos, endPos;
    XmTextBlock text;
} XmTextVerifyCallbackStruct, *XmTextVerifyPtr;


 

typedef struct {
    wchar_t *wcsptr;             
    int length;                  
} XmTextBlockRecWcs, *XmTextBlockWcs;

typedef struct
{
    int reason;
    XEvent  *event;
    Boolean doit;
    long currInsert, newInsert;
    long startPos, endPos;
    XmTextBlockWcs text;
} XmTextVerifyCallbackStructWcs, *XmTextVerifyPtrWcs;

 
#line 580
 

 

enum{ XmDIALOG_NONE,   XmDIALOG_APPLY_BUTTON,
 XmDIALOG_CANCEL_BUTTON,  XmDIALOG_DEFAULT_BUTTON,
 XmDIALOG_OK_BUTTON,  XmDIALOG_FILTER_LABEL,
 XmDIALOG_FILTER_TEXT,  XmDIALOG_HELP_BUTTON,
 XmDIALOG_LIST,   XmDIALOG_LIST_LABEL,
 XmDIALOG_MESSAGE_LABEL,  XmDIALOG_SELECTION_LABEL,
 XmDIALOG_SYMBOL_LABEL,  XmDIALOG_TEXT,
 XmDIALOG_SEPARATOR,  XmDIALOG_DIR_LIST,
 XmDIALOG_DIR_LIST_LABEL
 } ;
#line 602
 

enum{ XmDIALOG_MODELESS,  XmDIALOG_PRIMARY_APPLICATION_MODAL,
 XmDIALOG_FULL_APPLICATION_MODAL,XmDIALOG_SYSTEM_MODAL
 } ;


 




 


 
enum{ XmPLACE_TOP,   XmPLACE_ABOVE_SELECTION,
 XmPLACE_BELOW_SELECTION
 } ;


 
#line 629
 
enum{ XmDIALOG_WORK_AREA,  XmDIALOG_PROMPT,
 XmDIALOG_SELECTION,  XmDIALOG_COMMAND,
 XmDIALOG_FILE_SELECTION
 } ;



 

 

enum{ XmDIALOG_TEMPLATE,  XmDIALOG_ERROR,
 XmDIALOG_INFORMATION,  XmDIALOG_MESSAGE,
 XmDIALOG_QUESTION,  XmDIALOG_WARNING,
 XmDIALOG_WORKING
 } ;

 

typedef enum{
 XmVISIBILITY_UNOBSCURED, XmVISIBILITY_PARTIALLY_OBSCURED,
 XmVISIBILITY_FULLY_OBSCURED
 } XmVisibility ;


typedef enum{
 XmTRAVERSE_CURRENT,  XmTRAVERSE_NEXT,
 XmTRAVERSE_PREV,  XmTRAVERSE_HOME,
 XmTRAVERSE_NEXT_TAB_GROUP, XmTRAVERSE_PREV_TAB_GROUP,
 XmTRAVERSE_UP,   XmTRAVERSE_DOWN,
 XmTRAVERSE_LEFT,  XmTRAVERSE_RIGHT
 } XmTraversalDirection ;

typedef struct _XmTraverseObscuredCallbackStruct
{ int   reason ;
 XEvent *  event ;
 Widget   traversal_destination ;
 XmTraversalDirection direction ;
 } XmTraverseObscuredCallbackStruct ;

typedef unsigned char   XmNavigationType;
#line 677
 

typedef unsigned char XmButtonType;
typedef XmButtonType * XmButtonTypeTable;
typedef KeySym * XmKeySymTable;
typedef XmStringCharSet * XmStringCharSetTable;

enum{ XmPUSHBUTTON = 1,  XmTOGGLEBUTTON,
 XmRADIOBUTTON,   XmCASCADEBUTTON,
 XmSEPARATOR,   XmDOUBLE_SEPARATOR,
 XmTITLE
 } ;



 



typedef XtPointer (*XmResourceBaseProc)( Widget, XtPointer) ;


typedef struct _XmSecondaryResourceDataRec{
    XmResourceBaseProc base_proc;
    XtPointer  client_data;
    String  name;
    String  res_class;
    XtResourceList resources;
    Cardinal  num_resources;
}XmSecondaryResourceDataRec, *XmSecondaryResourceData;

 
#line 715
extern Cardinal XmGetSecondaryResourceData( 
                        WidgetClass w_class,
                        XmSecondaryResourceData **secondaryDataRtn) ;


 

 
#line 733
extern Boolean XmInstallImage( 
                        XImage *image,
                        char *image_name) ;
extern Boolean XmUninstallImage( 
                        XImage *image) ;
extern Pixmap XmGetPixmap( 
                        Screen *screen,
                        char *image_name,
                        Pixel foreground,
                        Pixel background) ;
extern Pixmap XmGetPixmapByDepth( 
                        Screen *screen,
                        char *image_name,
                        Pixel foreground,
                        Pixel background,
   int depth) ;
extern Boolean XmDestroyPixmap( 
                        Screen *screen,
                        Pixmap pixmap) ;


 

 
#line 763
extern void XmUpdateDisplay( 
                        Widget w) ;


 

 

typedef long XmOffset;
typedef XmOffset *XmOffsetPtr;

 
#line 783
extern void XmResolvePartOffsets( 
                        WidgetClass w_class,
                        XmOffsetPtr *offset) ;
extern void XmResolveAllPartOffsets( 
                        WidgetClass w_class,
                        XmOffsetPtr *offset,
                        XmOffsetPtr *constraint_offset) ;
extern Boolean XmWidgetGetBaselines(
                        Widget wid,
                        Dimension **baselines,
                        int *line_count);
extern Boolean XmWidgetGetDisplayRect(
                        Widget wid,
                        XRectangle *displayrect);


 

 
#line 815
extern void XmRegisterConverters( void ) ;
extern void XmCvtStringToUnitType( 
                        XrmValuePtr args,
                        Cardinal *num_args,
                        XrmValue *from_val,
                        XrmValue *to_val) ;
extern char * XmRegisterSegmentEncoding( 
                        char *fontlist_tag,
                        char *ct_encoding) ;
extern char * XmMapSegmentEncoding( 
                        char *fontlist_tag) ;
extern XmString XmCvtCTToXmString( 
                        char *text) ;
extern Boolean XmCvtTextToXmString( 
                        Display *display,
                        XrmValuePtr args,
                        Cardinal *num_args,
                        XrmValue *from_val,
                        XrmValue *to_val,
                        XtPointer *converter_data) ;
extern char * XmCvtXmStringToCT( 
                        XmString string) ;
extern Boolean XmCvtXmStringToText( 
                        Display *display,
                        XrmValuePtr args,
                        Cardinal *num_args,
                        XrmValue *from_val,
                        XrmValue *to_val,
                        XtPointer *converter_data) ;


 

 
#line 861
extern int XmConvertUnits( 
                        Widget widget,
                        int dimension,
                        register int from_type,
                        register int from_val,
                        register int to_type) ;
extern int XmCvtToHorizontalPixels( 
                        Screen *screen,
                        register int from_val,
                        register int from_type) ;
extern int XmCvtToVerticalPixels( 
                        Screen *screen,
                        register int from_val,
                        register int from_type) ;
extern int XmCvtFromHorizontalPixels( 
                        Screen *screen,
                        register int from_val,
                        register int to_type) ;
extern int XmCvtFromVerticalPixels( 
                        Screen *screen,
                        register int from_val,
                        register int to_type) ;
extern void XmSetFontUnits( 
                        Display *display,
                        int h_value,
                        int v_value) ;
extern void XmSetFontUnit( 
                        Display *display,
                        int value) ;


 

 
#line 902
extern void XmSetMenuCursor( 
                        Display *display,
                        Cursor cursorId) ;
extern Cursor XmGetMenuCursor( 
                        Display *display) ;


 

 
#line 923
extern Widget XmCreateSimpleMenuBar( 
                        Widget parent,
                        String name,
                        ArgList args,
                        Cardinal arg_count) ;
extern Widget XmCreateSimplePopupMenu( 
                        Widget parent,
                        String name,
                        ArgList args,
                        Cardinal arg_count) ;
extern Widget XmCreateSimplePulldownMenu( 
                        Widget parent,
                        String name,
                        ArgList args,
                        Cardinal arg_count) ;
extern Widget XmCreateSimpleOptionMenu( 
                        Widget parent,
                        String name,
                        ArgList args,
                        Cardinal arg_count) ;
extern Widget XmCreateSimpleRadioBox( 
                        Widget parent,
                        String name,
                        ArgList args,
                        Cardinal arg_count) ;
extern Widget XmCreateSimpleCheckBox( 
                        Widget parent,
                        String name,
                        ArgList args,
                        Cardinal arg_count) ;


 

 
#line 966
extern Widget XmVaCreateSimpleMenuBar( 
   Widget parent,
   String name,
   ...) ;
extern Widget XmVaCreateSimplePopupMenu(
   Widget parent,
   String name,
   XtCallbackProc callback,
   ...) ;
extern Widget XmVaCreateSimplePulldownMenu( 
   Widget parent,
   String name,
   int post_from_button,
   XtCallbackProc callback,
   ...) ;
extern Widget XmVaCreateSimpleOptionMenu(
   Widget parent,
   String name,
                        XmString option_label,
                        KeySym option_mnemonic,
                        int button_set,
                        XtCallbackProc callback,
   ...) ;
extern Widget XmVaCreateSimpleRadioBox( 
   Widget parent,
   String name,
   int button_set,
   XtCallbackProc callback,
   ...) ;
extern Widget XmVaCreateSimpleCheckBox( 
   Widget parent,
   String name,
   XtCallbackProc callback,
   ...) ;

 

 
#line 1011
extern Widget XmTrackingEvent( 
                        Widget widget,
                        Cursor cursor,

                        int confineTo,



                        XEvent *pev) ;
extern Widget XmTrackingLocate( 
                        Widget widget,
                        Cursor cursor,

                        int confineTo) ;
#line 1030
 

 



typedef void (*XmColorProc) (XColor *bg_color, XColor *fg_color,
 XColor *sel_color, XColor *ts_color, XColor *bs_color);


 
#line 1050
extern XmColorProc XmSetColorCalculation( 
                        XmColorProc proc) ;
extern XmColorProc XmGetColorCalculation( void ) ;
extern void XmGetColors( 
                        Screen *screen,
                        Colormap color_map,
                        Pixel background,
                        Pixel *foreground_ret,
                        Pixel *top_shadow_ret,
                        Pixel *bottom_shadow_ret,
                        Pixel *select_ret) ;
extern void XmChangeColor(
                        Widget widget,
                        Pixel background) ;


 

 
#line 1122
extern XmString XmStringCreate( 
                        char *text,
                        XmStringCharSet charset) ;
extern XmString XmStringCreateSimple( 
                        char *text) ;
extern XmString XmStringCreateLocalized( 
                        String text) ;
extern XmString XmStringDirectionCreate( 

                        int direction) ;



extern XmString XmStringSeparatorCreate( void ) ;
extern XmString XmStringSegmentCreate( 
                        char *text,
                        XmStringCharSet charset,

                        int direction,
                        int separator) ;




extern XmString XmStringLtoRCreate( 
                        char *text,
                        XmStringCharSet charset) ;
extern XmString XmStringCreateLtoR( 
                        char *text,
                        XmStringCharSet charset) ;
extern Boolean XmStringInitContext( 
                        XmStringContext *context,
                        XmString string) ;
extern void XmStringFreeContext( 
                        XmStringContext context) ;
extern XmStringComponentType XmStringGetNextComponent( 
                        XmStringContext context,
                        char **text,
                        XmStringCharSet *charset,
                        XmStringDirection *direction,
                        XmStringComponentType *unknown_tag,
                        unsigned short *unknown_length,
                        unsigned char **unknown_value) ;
extern XmStringComponentType XmStringPeekNextComponent( 
                        XmStringContext context) ;
extern Boolean XmStringGetNextSegment( 
                        XmStringContext context,
                        char **text,
                        XmStringCharSet *charset,
                        XmStringDirection *direction,
                        Boolean *separator) ;
extern Boolean XmStringGetLtoR( 
                        XmString string,
                        XmStringCharSet charset,
                        char **text) ;
extern XmFontListEntry XmFontListEntryCreate( 
                        char *tag,
                        XmFontType type,
                        XtPointer font) ;
extern void XmFontListEntryFree( 
                        XmFontListEntry *entry) ;
extern XtPointer XmFontListEntryGetFont( 
                        XmFontListEntry entry,
                        XmFontType *typeReturn) ;
extern char * XmFontListEntryGetTag( 
                        XmFontListEntry entry) ;
extern XmFontList XmFontListAppendEntry( 
                        XmFontList old,
                        XmFontListEntry entry) ;
extern XmFontListEntry XmFontListNextEntry( 
                        XmFontContext context) ;
extern XmFontList XmFontListRemoveEntry( 
                        XmFontList old,
                        XmFontListEntry entry) ;
extern XmFontListEntry XmFontListEntryLoad( 
                        Display *display,
                        char *fontName,
                        XmFontType type,
                        char *tag) ;
extern XmFontList XmFontListCreate( 
                        XFontStruct *font,
                        XmStringCharSet charset) ;
extern XmFontList XmStringCreateFontList( 
                        XFontStruct *font,
                        XmStringCharSet charset) ;
extern void XmFontListFree( 
                        XmFontList fontlist) ;
extern XmFontList XmFontListAdd( 
                        XmFontList old,
                        XFontStruct *font,
                        XmStringCharSet charset) ;
extern XmFontList XmFontListCopy( 
                        XmFontList fontlist) ;
extern Boolean XmFontListInitFontContext( 
                        XmFontContext *context,
                        XmFontList fontlist) ;
extern Boolean XmFontListGetNextFont( 
                        XmFontContext context,
                        XmStringCharSet *charset,
                        XFontStruct **font) ;
extern void XmFontListFreeFontContext( 
                        XmFontContext context) ;
extern XmString XmStringConcat( 
                        XmString a,
                        XmString b) ;
extern XmString XmStringNConcat( 
                        XmString first,
                        XmString second,
                        int n) ;
extern XmString XmStringCopy( 
                        XmString string) ;
extern XmString XmStringNCopy( 
                        XmString str,
                        int n) ;
extern Boolean XmStringByteCompare( 
                        XmString a1,
                        XmString b1) ;
extern Boolean XmStringCompare( 
                        XmString a,
                        XmString b) ;
extern int XmStringLength( 
                        XmString string) ;
extern Boolean XmStringEmpty( 
                        XmString string) ;
extern Boolean XmStringHasSubstring( 
                        XmString string,
                        XmString substring) ;
extern void XmStringFree( 
                        XmString string) ;
extern Dimension XmStringBaseline( 
                        XmFontList fontlist,
                        XmString string) ;
extern Dimension XmStringWidth( 
                        XmFontList fontlist,
                        XmString string) ;
extern Dimension XmStringHeight( 
                        XmFontList fontlist,
                        XmString string) ;
extern void XmStringExtent( 
                        XmFontList fontlist,
                        XmString string,
                        Dimension *width,
                        Dimension *height) ;
extern int XmStringLineCount( 
                        XmString string) ;
extern void XmStringDraw( 
                        Display *d,
                        Window w,
                        XmFontList fontlist,
                        XmString string,
                        GC gc,

                        int x,
                        int y,
                        int width,
                        unsigned int align,
                        unsigned int lay_dir,
#line 1286
                        XRectangle *clip) ;
extern void XmStringDrawImage( 
                        Display *d,
                        Window w,
                        XmFontList fontlist,
                        XmString string,
                        GC gc,

                        int x,
                        int y,
                        int width,
                        unsigned int align,
                        unsigned int lay_dir,
#line 1306
                        XRectangle *clip) ;
extern void XmStringDrawUnderline( 
                        Display *d,
                        Window w,
                        XmFontList fntlst,
                        XmString str,
                        GC gc,

                        int x,
                        int y,
                        int width,
                        unsigned int align,
                        unsigned int lay_dir,
#line 1326
                        XRectangle *clip,
                        XmString under) ;


 

 
#line 1339
extern Widget XmGetDestination( 
                        Display *display) ;


 

 
#line 1358
extern Boolean XmIsTraversable( 
                        Widget wid) ;
extern XmVisibility XmGetVisibility( 
                        Widget wid) ;
extern Widget XmGetTabGroup( 
                        Widget wid) ;
extern Widget XmGetFocusWidget( 
                        Widget wid) ;
extern Boolean XmProcessTraversal( 
                        Widget w,
                        XmTraversalDirection dir) ;
extern void XmAddTabGroup( 
                        Widget tabGroup) ;
extern void XmRemoveTabGroup( 
                        Widget w) ;


 


 
#line 1393
extern void XmImRegister( 
                        Widget w,
   unsigned int reserved) ;
extern void XmImUnregister( 
                        Widget w) ;
extern void XmImSetFocusValues( 
                        Widget w,
                        ArgList args,
                        Cardinal num_args) ;
extern void XmImSetValues( 
                        Widget w,
                        ArgList args,
                        Cardinal num_args) ;
extern void XmImUnsetFocus( 
                        Widget w) ;
extern XIM XmImGetXIM( 
                        Widget w) ;
extern int XmImMbLookupString( 
                        Widget w,
                        XKeyPressedEvent *event,
                        char *buf,
                        int nbytes,
                        KeySym *keysym,
                        int *status) ;
extern void XmImVaSetFocusValues( 
                        Widget w,
                        ...) ;
extern void XmImVaSetValues( 
                        Widget w,
                        ...) ;


 

 
#line 1435
 
#line 4 "/home/tools1/uimx2.5/motif12/usr/include/Xm/VendorS.h"
   


   
 

 

 

 

 
#line 4 "/home/tools1/uimx2.5/motif12/usr/include/Xm/Xm.h"
   


   
 

 
#line 1439
  
#line 31 "/home/tools1/uimx2.5/motif12/usr/include/Xm/VendorS.h"
typedef struct _XmVendorShellRec *XmVendorShellWidget;
typedef struct _XmVendorShellClassRec *XmVendorShellWidgetClass;
extern      WidgetClass vendorShellWidgetClass;


 
#line 43
extern Boolean XmIsMotifWMRunning( 
                        Widget shell) ;


 
#line 55
 
#line 1439 "/home/tools1/uimx2.5/motif12/usr/include/Xm/Xm.h"
  
#line 7 "/tmp_mnt/home/tools1/CenterLine/clcc/sparc-sunos4/inc/stdio.h"
 
#line 25 "/home/tools1/uimx2.5/motif12/usr/include/Xm/Text.h"
 
typedef struct _XmTextSourceRec *XmTextSource;
typedef struct _XmTextClassRec *XmTextWidgetClass;
typedef struct _XmTextRec *XmTextWidget;



 
extern      WidgetClass       xmTextWidgetClass;




 
#line 47
 

 
#line 101
extern void XmTextSetHighlight( 
                        Widget w,
                        XmTextPosition left,
                        XmTextPosition right,
                        XmHighlightMode mode) ;
extern Widget XmCreateScrolledText( 
                        Widget parent,
                        char *name,
                        ArgList arglist,
                        Cardinal argcount) ;
extern Widget XmCreateText( 
                        Widget parent,
                        char *name,
                        ArgList arglist,
                        Cardinal argcount) ;
extern int XmTextGetSubstring( 
                        Widget widget,
                        XmTextPosition start,
                        int num_chars,
                        int buf_size,
                        char *buffer) ;
extern int XmTextGetSubstringWcs( 
                        Widget widget,
                        XmTextPosition start,
                        int num_chars,
                        int buf_size,
                        wchar_t *buffer) ;
extern char * XmTextGetString( 
                        Widget widget) ;
extern wchar_t * XmTextGetStringWcs( 
                        Widget widget) ;
extern XmTextPosition XmTextGetLastPosition( 
                        Widget widget) ;
extern void XmTextSetString( 
                        Widget widget,
                        char *value) ;
extern void XmTextSetStringWcs( 
                        Widget widget,
                        wchar_t *wc_value) ;
extern void XmTextReplace( 
                        Widget widget,
                        XmTextPosition frompos,
                        XmTextPosition topos,
                        char *value) ;
extern void XmTextReplaceWcs( 
                        Widget widget,
                        XmTextPosition frompos,
                        XmTextPosition topos,
                        wchar_t *value) ;
extern void XmTextInsert( 
                        Widget widget,
                        XmTextPosition position,
                        char *value) ;
extern void XmTextInsertWcs( 
                        Widget widget,
                        XmTextPosition position,
                        wchar_t *wc_value) ;
extern void XmTextSetAddMode( 
                        Widget widget,

                        int state) ;



extern Boolean XmTextGetAddMode( 
                        Widget widget) ;
extern Boolean XmTextGetEditable( 
                        Widget widget) ;
extern void XmTextSetEditable( 
                        Widget widget,

                        int editable) ;



extern int XmTextGetMaxLength( 
                        Widget widget) ;
extern void XmTextSetMaxLength( 
                        Widget widget,
                        int max_length) ;
extern XmTextPosition XmTextGetTopCharacter( 
                        Widget widget) ;
extern void XmTextSetTopCharacter( 
                        Widget widget,
                        XmTextPosition top_character) ;
extern XmTextPosition XmTextGetCursorPosition( 
                        Widget widget) ;
extern XmTextPosition XmTextGetInsertionPosition( 
                        Widget widget) ;
extern void XmTextSetInsertionPosition( 
                        Widget widget,
                        XmTextPosition position) ;
extern void XmTextSetCursorPosition( 
                        Widget widget,
                        XmTextPosition position) ;
extern Boolean XmTextRemove( 
                        Widget widget) ;
extern Boolean XmTextCopy( 
                        Widget widget,
                        Time copy_time) ;
extern Boolean XmTextCut( 
                        Widget widget,
                        Time cut_time) ;
extern Boolean XmTextPaste( 
                        Widget widget) ;
extern char * XmTextGetSelection( 
                        Widget widget) ;
extern wchar_t * XmTextGetSelectionWcs( 
                        Widget widget) ;
extern void XmTextSetSelection( 
                        Widget widget,
                        XmTextPosition first,
                        XmTextPosition last,
                        Time set_time) ;
extern void XmTextClearSelection( 
                        Widget widget,
                        Time clear_time) ;
extern Boolean XmTextGetSelectionPosition( 
                        Widget widget,
                        XmTextPosition *left,
                        XmTextPosition *right) ;
extern XmTextPosition XmTextXYToPos( 
                        Widget widget,

                        int x,
                        int y) ;




extern Boolean XmTextPosToXY( 
                        Widget widget,
                        XmTextPosition position,
                        Position *x,
                        Position *y) ;
extern XmTextSource XmTextGetSource( 
                        Widget widget) ;
extern void XmTextSetSource( 
                        Widget widget,
                        XmTextSource source,
                        XmTextPosition top_character,
                        XmTextPosition cursor_position) ;
extern void XmTextShowPosition( 
                        Widget widget,
                        XmTextPosition position) ;
extern void XmTextScroll( 
                        Widget widget,
                        int n) ;
extern int XmTextGetBaseline( 
                        Widget widget) ;
extern void XmTextDisableRedisplay( 
                        Widget widget) ;
extern void XmTextEnableRedisplay( 
                        Widget widget) ;
extern Boolean XmTextFindString( 
                        Widget w,
                        XmTextPosition start,
                        char *search_string,
                        XmTextDirection direction,
                        XmTextPosition *position) ;
extern Boolean XmTextFindStringWcs( 
                        Widget w,
                        XmTextPosition start,
                        wchar_t *wc_string,
                        XmTextDirection direction,
                        XmTextPosition *position) ;


 
#line 277
 
#line 24 "desc_struct.h"
 
#line 107
static char    *desc_struct_h_rcsid = "@(#) $Id: desc_struct.h,v 1.19 1994/08/04 16:23:21 franklin Exp $";


extern struct stat DESC_File_Stat;
#line 135
 
#line 145
 

extern char     DESC_New_File_Name[512         ];
extern char     DESC_Line_Str[1024         ];
extern FILE    *DESC_File_Ptr;
extern char     Hoare_Table_Name[512         ];  

 
extern char     User_Msg[1024         ];




 

extern int      error_counter;
extern short    return_flag;         
extern short    concurrent;
#line 185
 
#line 195
 


 
#line 206
 
#line 223
 
#line 229
typedef enum
{
 FIRST,
 NEXT,
 SUCCEED,
 FAIL
}               processing_situation_tt;

extern processing_situation_tt Activity;  

typedef enum
{
 ANALYSIS,
 SYNTHESIS,
 SYNTHESIS1
}               tree_tt;         

extern tree_tt  Tree_Type;         
typedef char    DATA;

struct stack
{
 DATA            d;
 struct stack   *next;
};

struct link_list
{
 char           *name;
 struct link_list *next;
};

typedef struct stack STACK_ELEMENT;     
typedef STACK_ELEMENT *TOP;

struct Template_Node
{

 struct Template_Node *ancestor; 
 struct Template_Node *level_point;  
 struct Template_Node *front;    
 struct Template_Node *back;     

 
 struct Template_Node *extra_front;  
 struct Template_Node *extra_back;

 
 struct Stack_Node *ttop_of_stack;

 char           *name;         

 
 char           *module_name;    
 struct link_list *para;

 int             level_no;       
#line 291
 
 int             row;         
 int             col;         
 int             type;         
#line 314
 

 int             lower;         
 int             upper;         

};

extern struct Template_Node *Hoare_Root_Dummy,
               *Temp_Node,
               *Current_Node,
               *Prev_Node,
               *pre_root,
               *F_Hoare_Root_Dummy;

struct Stack_Node
{
 
 struct Template_Node *template_node_ptr;

 int             no_of_elements; 

 int             begin,
                 end;         
 



 
 struct Stack_Node *prev_stack_element;  
 struct Stack_Node *bound_buddy; 

 
 struct Stack_Node *forward_stack_ptr;
 struct Stack_Node *backward_stack_ptr;

 
 struct Stack_Node *tcp_save;

 int             from_tree_type; 

};
extern struct Stack_Node *Root_Stack,
               *Temp_Stack,
               *Current_Stack,
               *Prev_Stack;

struct maxval_struct
{
 int             col;
 int             row;
};
extern struct maxval_struct Max_Value_of;
#line 14 "desc_table.h"
 
#line 45
static char    *desc_table_h_rcsid = "@(#) $Id: desc_table.h,v 1.6 1994/08/03 17:00:32 franklin Exp $";
#line 53
 

static char    *error_supplement[]
= {
          "Control Character",
          "Special Character",
          "Digit Number",
          "Upper-case Letter",
          "Lower-case Letter",
          "Carriage Return",
          "Blank",
          "Single Quote",
          "Underscore",
          "Left Parenthesis",
           "Right Parenthesis",
           "Period",
           "Asterisk",
           "Plus",
           "Pound Sign"
};
#line 80
 

static char    *error_code[] = {
          "",          
          "%s used is not part of reference node (or module title)",
          "invalid %s used for either reference or match node",
          "invalid %s used in literal node",
          "missing %s at the end of literal node",
          "an invalid %s occurred in literal node",
          "an invalid %s occurred in match node",
          "an invalid %s occurred in match node (direct product)",
          "an invalid %s occurred in match node (discriminated union)",
          "an invalid %s occurred in match node (sequence)",
           "an invalid %s occurred in match node (sequence union)",
           "an invalid %s occurred in match node (sequence range)",
           "illegal indentation occurred; must be a multiple of 5",
           "illegal format for sequence range; use either (1..100) or (1..) as example"
                 ,
           "illegal lower bound; lower bound must be > 0",
           "illegal lower bound because lower bound > upper bound",
           "incomplete reference node",
           "an invalid %s occurred in reference node",
 "NOT  YET"
};
#line 18 "build_rtn.h"
 
#line 68
static char    *build_rtn_h_rcsid = "@(#) $Id: build_rtn.h,v 1.11, h4_3_2 1994/07/05 02:28:10 franklin Exp $";

extern void     Show_Hoare_Tree (Widget dummywidget, void *dummyptr1, XmPushButtonCallbackStruct * dummyptr2);

extern void     Print_Hoare_Tree (Widget dummywidget, void *dummyptr1, XmPushButtonCallbackStruct * dummyptr2);

extern int      Build_Proc (void);
#line 9 "mesg.h"
 
#line 36
static char    *mesg_h_rcsid = "@(#) $Id: mesg.h,v 1.6, h4_3_2, h4_3_1, h4_3_0, h4_2_7, h4_2_6, h4_2_5, h4_2_4 1994/06/01 16:43:51 franklin Exp $";

 
 
 
 

 
 
#line 50
typedef struct my_msgbuf_struct
{
 int             mesg_len;
 long            mesg_type;
 char            mesg_data[4080       ];
}               Mesg;



extern void     mesg_send (int id, Mesg * mesgptr);
extern int      mesg_recv (int id, Mesg * mesgptr);
extern int      mesg_arecv (int id, Mesg * mesgptr);
#line 20 "wid1.h"
 
#line 112
static char    *wid1_h_rcsid = "@(#) $Id: wid1.h,v 1.21 1994/08/04 00:06:13 franklin Exp $";



 
extern GC       gc;
extern GC       inv_gc;          
extern Dimension width;
extern Dimension height;
extern Widget   drawing_a;
extern Widget   rd_spec_text_w;
extern Pixmap   Current_pix;
extern Dimension win_width;
extern Dimension win_height;
extern Mesg     mesg_d;
extern int      msgid;
extern int      Delay_Time;         


 
extern void     Display_Build_User_Msg (Widget text, char *msg);
extern void     popup_error_dialog (const char *printf_fmt_str,...);
extern void     read_file (char *filename);
extern void     parse (void);
extern void     clear_drawing_area (void);  
extern void     install_shell_widgets_icon (Widget shellwidget);
#line 143
 
#line 22 "analysis1.h"
 
#line 59
static char    *analysis1_h_rcsid = "@(#) $Id: analysis1.h,v 1.8 1994/08/03 16:27:32 franklin Exp $";



 




 
#line 74
 
extern int      p_cnt;          
extern Pixmap   para[5];         



 
extern void     execution_proc (struct Template_Node * cur_node);
extern void     Get_Parameters (void);
#line 20 "build_hoare_tree.h"
 
#line 65
static char    *build_hoare_tree_h_rcsid = "@(#) $Id: build_hoare_tree.h,v 1.10 1994/08/03 21:38:13 franklin Exp $";



 
extern int      Screen_Row;         
extern int      Max_Name_Size;         


 
extern struct Template_Node *Allocate_Hoare_Root_Dummy (void);


 
extern void     Build_Hoare_Tree ( char *fmt, int type, char *name, int level_no, ... );


 
extern struct Template_Node *Find_Ancestor (struct Template_Node * prev_node, int level_no);


 
extern void     Scan_Tree_For_Seq (struct Template_Node * cur_node);


 
extern void     Add_One_More_Node (struct Template_Node * cur_node);


 
extern void     Free_Hoare_Tree (struct Template_Node * cur_node);


 
extern void     Generate_String_Format (int size);


 
extern void     Make_One_Blank_Line (void);


 
extern void     Write_Hoare_Table_To_Disk (char *msg);


 
extern void     Write_Hoare_Tree (struct Template_Node * cur_node);


 
extern void     Write_Tree_Node (struct Template_Node * cur_node);


 
extern void     Free_String_Format (void);


 
extern void     Display_Error_Code (int line_no, int location, int errcode, int col, char *mystr);
#line 20 "some_utils.h"
 
#line 67
static char    *some_utils_h_rcsid = "@(#) $Id: some_utils.h,v 1.11 1994/08/03 16:00:02 franklin Exp $";

typedef int     SDATA;

struct qlinked_list
{
 SDATA           d;
 struct qlinked_list *next;
};

typedef struct qlinked_list SELEMENT;
typedef SELEMENT *SLINK;

struct queue
{
 SLINK           front;
 SLINK           rear;
};

typedef struct queue QUEUE;

typedef struct growbuf_t_struct
{
 size_t          cur_len;
 char           *buf;
}               growbuf_tt;

extern void     util_abort (int line, char *file, char *printf_fmt_str,...);

extern int      qisempty (QUEUE * q);
extern SDATA    vfront (QUEUE * q);
extern void     dequeue (QUEUE * q, SDATA * x);
extern void     enqueue (QUEUE * q, SDATA x);

extern void     dump_bits (FILE * outf, unsigned long int val);

extern void     growbuf_init (growbuf_tt ** gbuf);
extern void     growbuf_strcpy (growbuf_tt * gbuf, char *in_str);
extern void     growbuf_strcat (growbuf_tt * gbuf, char *in_str);
extern char    *growbuf_str (growbuf_tt * gbuf);
extern void     growbuf_free (growbuf_tt ** gbuf);
extern const char *get_base_filename (const char *fullpathname);
extern char    *load_file_into_charbuf (const char *pathname, int *len);
#line 181 "build_hoare_tree.c"
 
int             Screen_Row;         
int             Max_Name_Size;         

 
static int      Screen_Col;
static char    *String_Header;
static char    *String_Border;
static char     String_Format[1024];
static int      Number_of_Nodes;
static struct Template_Node *Sub_Root_Dummy;  
#line 197
 


struct Template_Node *Allocate_Hoare_Root_Dummy (void)
{
 struct Template_Node *Root_Dummy; 
 

 Root_Dummy = (struct Template_Node *) calloc (1, sizeof (struct Template_Node));
 if (Root_Dummy == ((void*)0))
  abort ();

 Prev_Node = Root_Dummy;

 
 Screen_Col = -110;  
 Prev_Node->row = Screen_Row;
 Prev_Node->col = Screen_Col;

 Max_Value_of.col = Screen_Col + 2 + strlen ("ROOT_DUMMY") * 8 + 2;
 Max_Value_of.row = Screen_Row + 18 + 30;

 Prev_Node->name = (char *) calloc (strlen ("ROOT_DUMMY") + 1, sizeof (char));
 Prev_Node->name = "ROOT_DUMMY";

 
 Prev_Node->level_no = -1;

 
 Max_Name_Size = strlen ("ROOT_DUMMY");

 error_counter = 0;
 Number_of_Nodes = 0;
 return (Root_Dummy);
}
#line 244
 

void            Build_Hoare_Tree (char *fmt, int type, char *name, int level_no,...)
{
 va_list         args; 
 
 char           *lower;
 char           *upper;




 

 printf ("Build_Hoare_Tree(): type = ");
 dump_bits ((&_iob[1]), type);
 printf (" = 0x%X; name = %s; level = %d\n", type, name, level_no);


 
 if (Max_Name_Size < (int) strlen (name))
  Max_Name_Size = strlen (name);

 Current_Node = (struct Template_Node *)
  calloc (1, sizeof (struct Template_Node));

 Current_Node->name = (char *) calloc (strlen (name) + 1, sizeof (char));
 sprintf (Current_Node->name, "%s", name);
 Current_Node->level_no = level_no;
 Current_Node->type = type;

 

 printf ("Current_Node->name = \"%s\"\n", Current_Node->name);
 if (type == 0x82        )
 {
  printf ("\tMODULE_TITLE\n");
  Sub_Root_Dummy = Allocate_Hoare_Root_Dummy ();
  pre_root->front = Sub_Root_Dummy;
  Sub_Root_Dummy->back = pre_root;
  pre_root = Sub_Root_Dummy;

  

 }
 
 if ((type & 0x80          ) && (type != 0x81   ))
  Get_Parameters ();

 switch (type)
 {
  case 0x44          :
  case 0x45                :
  case 0x46                :
  case 0x85              :
  case 0x86                    :
  case 0x87                    :

   (args=(__vararg_char*)&level_no+sizeof(level_no));  
   lower = ((char**)__builtin_va_arg_incr((char**)args))[0];
   upper = ((char**)__builtin_va_arg_incr((char**)args))[0];
                ;  

   Current_Node->lower = atoi (lower);
   Current_Node->upper = atoi (upper);
   break;

  default:
   ;
 }

 if (level_no > Prev_Node->level_no)  
 {
  printf ("level_no = %d Immediate son of \"%s\"\n", level_no, Prev_Node->name);
  Prev_Node->level_point = Current_Node;
  Current_Node->ancestor = Prev_Node;
  Screen_Col = Prev_Node->col + 2 + (8 * strlen (Prev_Node->name)) + 2 + 36;
 }
 else if (level_no < Prev_Node->level_no)  
 {
  printf ("level_no = %d  Another sibling of \"%s\"\n", level_no, Prev_Node->name);
  Temp_Node = Find_Ancestor (Prev_Node, level_no);
  Current_Node->ancestor = Temp_Node->ancestor;
  Temp_Node->front = Current_Node;
  Current_Node->back = Temp_Node;
  Screen_Col = Temp_Node->col;
 }




 
 else if (level_no == Prev_Node->level_no)  
 {
  printf ("level_no = %d  Immediate sibling of %s\n", level_no, Prev_Node->name);
  Current_Node->ancestor = Prev_Node->ancestor;
  Prev_Node->front = Current_Node;
  Current_Node->back = Prev_Node;
 }

 if (Max_Value_of.col < (Screen_Col + 2 + (int) strlen (name) * 8 + 2))
 {
  Max_Value_of.col = Screen_Col + 2 + strlen (name) * 8 + 2;
 }

 Screen_Row = Prev_Node->row + 25;  
 Max_Value_of.row = Screen_Row + 18 + 30;

 Current_Node->col = Screen_Col;
 Current_Node->row = Screen_Row;

 Number_of_Nodes++;

 
 Prev_Node = Current_Node;

}            
#line 367
 
struct Template_Node *Find_Ancestor (struct Template_Node * prev_node, int level_no)
{
 struct Template_Node *cur;

 
 for
  (cur = prev_node; cur->ancestor->level_no > level_no; cur = cur->ancestor)
 {
  printf ("cur->name = \"%s\" level_no = %d\n", cur->name, level_no);
 }
 printf ("level_no = %d\n", level_no);
 return (cur->ancestor);
}




 
void            Scan_Tree_For_Seq (struct Template_Node * cur_node)
{
 if (cur_node->level_point == ((void*)0) && cur_node->front == ((void*)0))
 {
  Add_One_More_Node (cur_node);
  return;
 }

 if (cur_node != ((void*)0))
 {
  Add_One_More_Node (cur_node);
  if (cur_node->level_point != ((void*)0))
   Scan_Tree_For_Seq (cur_node->level_point);
 }

 if (cur_node->front != ((void*)0))
 {
  Scan_Tree_For_Seq (cur_node->front);
 }
 return;
}




 
void            Add_One_More_Node (struct Template_Node * cur_node)
{


 switch (cur_node->type)
 {

   case 0x44          :
   case 0x45                :
   case 0x46                :
   case 0x85              :
   case 0x86                    :
   case 0x87                    :

   Current_Node = (struct Template_Node *)
   calloc (1, sizeof (struct Template_Node));
   cur_node->extra_front = Current_Node;
   Current_Node->extra_back = cur_node;

   if (cur_node->type & 0x40      )
   {
    sprintf (User_Msg, "match_dummy");
    Current_Node->name = (char *) calloc (strlen (User_Msg) + 1, sizeof (char));
    sprintf (Current_Node->name, "%s", User_Msg);
    Current_Node->level_no = -2         ;
   }
   else
   {
    sprintf (User_Msg, "reference_dummy");
    Current_Node->name = (char *) calloc (strlen (User_Msg) + 1, sizeof (char));
    sprintf (Current_Node->name, "%s", User_Msg);
    Current_Node->level_no = -2         ;
   }

   switch (cur_node->type)
   {

    case 0x44          :  
     Current_Node->type = 0x41                ;
     break;
    case 0x45                :
     Current_Node->type = 0x42                     ;
     break;
    case 0x46                :  
     Current_Node->type = 0x41                ;
     break;
    case 0x85              :
     Current_Node->type = 0x83                    ;
     break;
    case 0x86                    :
     Current_Node->type = 0x84                         ;
     break;
    case 0x87                    :
     Current_Node->type = 0x83                    ;
     break;
   }

  default:
   break;

 }    
}
#line 479
 
void            Free_Hoare_Tree (struct Template_Node * cur_node)
{
 if (cur_node)
 {
  if (cur_node->level_point == ((void*)0) && cur_node->front == ((void*)0))
  {
   printf ("Node name - %s is freed\n", cur_node->name);
   if (cur_node->extra_front)
   {
    free (cur_node->extra_front->name);
    free (cur_node->extra_front);
   }
   free (cur_node->name);
   free (cur_node);
   cur_node = ((void*)0);
   return;
  }

  if (cur_node->level_point != ((void*)0))
   Free_Hoare_Tree (cur_node->level_point);

  if (cur_node->front != ((void*)0))
   Free_Hoare_Tree (cur_node->front);

  printf ("Node name - %s is freed\n", cur_node->name);
  if (cur_node->extra_front)
  {
   free (cur_node->extra_front->name);
   free (cur_node->extra_front);
  }
  free (cur_node->name);
  free (cur_node);
  cur_node = ((void*)0);
 }
 return;
}




 

void            Generate_String_Format (int size)
{
 int             i;

 i = size;
 sprintf (String_Format, "|%%-%ds|%%-%ds|%%-%ds|%%-%ds|%%-%ds|\n", i, i, i, i, i);
 String_Header = (char *) calloc (5 * size + 6 + 2, sizeof (char));
 sprintf (String_Header, String_Format,
   "[Node]", "[Ancestor]", "[Level]", "[Front]", "[Back]");
 String_Border = (char *) calloc (5 * size + 6 + 2, sizeof (char));
 for (i = 0; i < (5 * size + 6); i++)
  *(String_Border + i) = '-';
 for (i = 0; i <= 5; i++)
  *(String_Border + (i + (size * i))) = '+';




 


 
 DESC_File_Ptr = fopen (Hoare_Table_Name, "w");
 printf ("Writing the Hoare table to \"%s\".\n", Hoare_Table_Name);
 Make_One_Blank_Line ();
 sprintf (User_Msg, "The name of a Descartes Specification is [%s].\n",
   DESC_New_File_Name);
 Write_Hoare_Table_To_Disk (User_Msg);
 Make_One_Blank_Line ();
 sprintf (User_Msg, "The name of template tree table is [%s].\n", Hoare_Table_Name);
 Write_Hoare_Table_To_Disk (User_Msg);
 Make_One_Blank_Line ();
 sprintf (User_Msg, "The width of this table is %d.\n", (5 * size + 6));
 Write_Hoare_Table_To_Disk (User_Msg);
 Make_One_Blank_Line ();

 sprintf (User_Msg, "%s\n", String_Border);
 Write_Hoare_Table_To_Disk (User_Msg);
 sprintf (User_Msg, "%s\n", String_Header);  
 Write_Hoare_Table_To_Disk (User_Msg);

 for (i = 0; i < (5 * size + 6); i++)
  *(String_Border + i) = '=';
 for (i = 0; i <= 5; i++)
  *(String_Border + (i + (size * i))) = '+';

 sprintf (User_Msg, "%s\n", String_Border);
 Write_Hoare_Table_To_Disk (User_Msg);

 for (i = 0; i < (5 * size + 6); i++)
  *(String_Border + i) = '-';
 for (i = 0; i <= 5; i++)
  *(String_Border + (i + (size * i))) = '+';
}




 
void            Make_One_Blank_Line (void)
{
 sprintf (User_Msg, "\n");
 Write_Hoare_Table_To_Disk (User_Msg);
}




 
void            Write_Hoare_Table_To_Disk (char *msg)
{

 fputs (msg, DESC_File_Ptr);
}




 

void            Write_Hoare_Tree (struct Template_Node * cur_node)
{
 
 if (cur_node->level_point == ((void*)0) && cur_node->front == ((void*)0))
 {
  Write_Tree_Node (cur_node);
  return;
 }

 if (cur_node != ((void*)0))
 {
  Write_Tree_Node (cur_node);
  if (cur_node->level_point != ((void*)0))
   Write_Hoare_Tree (cur_node->level_point);
 }

 if (cur_node->front != ((void*)0))
 {
  Write_Hoare_Tree (cur_node->front);
 }
 return;
}




 

void            Write_Tree_Node (struct Template_Node * cur_node)
{
 char           *level,
                *front,
                *back;

 if (cur_node->level_point == ((void*)0))
  level = "null";
 else
  level = cur_node->level_point->name;

 if (cur_node->front == ((void*)0))
  front = "null";
 else
  front = cur_node->front->name;

 if (cur_node->back == ((void*)0))
  back = "null";
 else
  back = cur_node->back->name;

 sprintf (User_Msg, String_Format,
   cur_node->name, cur_node->ancestor->name, level, front, back);
 Write_Hoare_Table_To_Disk (User_Msg);

 sprintf (User_Msg, "%s\n", String_Border);
 Write_Hoare_Table_To_Disk (User_Msg);
}



 
void            Free_String_Format (void)
{
 free (String_Header);
 String_Header = ((void*)0);
 free (String_Border);
 String_Border = ((void*)0);
 fclose (DESC_File_Ptr);
}



 
void            Display_Error_Code (int line_no, int location, int errcode, int col, char *mystr)
{
 int             i;

 sprintf (User_Msg, "%s<< at Line %d", mystr, line_no);
 Display_Build_User_Msg (rd_spec_text_w, User_Msg);

 if ((errcode != 14) && (errcode != 15))
 {
  for (i = 0; i < sizeof (User_Msg); i++)
   User_Msg[i] = '\0';
  for (i = 0; i < location; i++)
   User_Msg[i] = ' ';
  User_Msg[strlen (User_Msg)] = '^';
  Display_Build_User_Msg (rd_spec_text_w, User_Msg);
 }
 if ((errcode >= 12) && (errcode <= 16))
  sprintf (User_Msg, error_code[errcode]);
 else
  sprintf (User_Msg, error_code[errcode], error_supplement[col]);

 Display_Build_User_Msg (rd_spec_text_w, User_Msg);
}
