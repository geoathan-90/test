# include <stdlib.h>
# include <stdio.h>
# include <ctype.h>
# include <conio.h>
# include <bios.h>
# include <dos.h>
# include <math.h>
# include <io.h>
# include <fcntl.h>
/* # include <sys\stat.h> ›œ¤ ¬§˜¨®œ  */

# define HELP		1               /* ^A = help */
# define AGVGOS		2               /* ^B = ®˜¨˜¡«ž¨ ©« ¡˜ ˜šàš¦¬ */
# define RMITM          4		/* ^D = delete item */
# define BELL           7
# define BACKSPACE	8
# define TAB		9
# define RETURN		13
# define INSITM         15      	/* ^Ž = §˜¨œ£™¦¢ž ˜¨ Ÿ£¦¬ */
# define REARNG		18		/* ^R = ˜¤˜› ˜£¦¨­à©ž ˜/˜ §¬¨šà¤ */
# define LEFT           "\033[D"
# define RIGHT          "\033[C"
# define DEL            0x5300          /* delete char */
# define INS            0x5200          /* insert char */
# define UP_ARROW	0x4800
# define DOWN_ARROW	0x5000
# define LEFT_ARROW	0x4b00
# define RIGHT_ARROW	0x4d00
# define PAGE_UP	0x4900
# define PAGE_DOWN	0x5100
# define END            0x4f00          /* end of word */
# define F1		0x3b00          /* help */
# define F2		0x3c00          /* ®˜¨˜¡«ž¨ ©« ¡˜ ˜šàš¦¬ */
# define F3		0x3d00		/* §˜¨œ£™¦¢ž ˜¨ Ÿ£¦¬ */
# define F4		0x3e00		/* delete number */
# define F5		0x3f00		/* ˜¤˜› ˜£¦¨­à©ž ˜/˜ §¬¨šà¤ */
# define F9		0x4300		/* §˜¨œ£™¦¢ã ©œ¢å›˜ª */
# define F10		0x4400		/* › ˜š¨˜­ã ©œ¢å›˜ª */
# define BLNK		"\033[5m"
# define ATOFF		"\033[0m\033[1m"                    	/*18/8/89*/
# define KENO           22		/* ¡œ¤æ (§˜ç¢˜) ©«¦ §œ›å¦ input */
# define HI             "\033[0m"       /* half intensity */
# define FI             "\033[1m"       /* full intensity */
# define HOME           0x4700
# define ESC            27
# define CLS            clrscr()	/* clear screen */
# define NMAX 		51
# define THERM		5
# define AGVGOI		10
# define PROSEGISH	0.001
# define PARAM		struct param
# define PARAMDF	"prm\\param1.dat"
# define PIN		"prm\\pin.dat"
# define MSGS		"prm\\msgs.dat"
# define PAROYS		"prm\\paroys.dat"
# define MENU		"prm\\menu.dat"
# define DFNAME		"prm\\dfname.dat"
