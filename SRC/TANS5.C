/***********************************************************
*
*    PROGRAMMER.: X_SOFTWARE
*    PROGRAM....: TAN
*    FILE/DATE..: TANS5.C / 890815-18
*    DESCRIPTION: ‚€‹‹€ „Š—Œ ‰€ˆ ’€Œ“‘„—Œ
*
*    TANS3.C:
*    ¨æš¨˜££˜ œ ©˜šàšãª ›œ›¦£â¤à¤.............: 1222  š¨˜££âª
*    ¨¦š¨á££˜«˜ œ ©˜š. ®˜¨˜¡«¨ ©« ¡é¤ ˜šàšé¤ :  156  š¨˜££âª
*    ¨¦š¨. ¬§¦¢¦š ©£¦ç (™œ¢« à£.§¨æš¨.Šœ¡˜«©á):  215  š¨˜££âª
*    ¨æš¨˜££˜ œ¡«¬§é©œà¤......................:   55  š¨˜££âª
*    ---------------------------------------------------------
*    ‘ç¤¦¢¦ §¨¦š¨˜££á«à¤...................... : 1648  š¨˜££âª
*    ‘ç¤¦¢¦ §¨¦š¨˜££á«à¤ VERSION 1.27......... : 1740  š¨˜££âª
*    €¨®œå˜ ¦Ÿ¦¤é¤ ¡˜  ›œ›¦£â¤à¤...............: 7771  bytes
*
***********************************************************/

# include "src\tans5.h"

char	scr[4001],
	file[17]={0};
int	grammh, maxgrammh,
	prost[6]={6,7,6,7,8,9},		/* ˜¤«å©«¦ ®¦  ˜šàš¦å §¨¦©«˜©å˜ª */
	th[THERM]={0,10,20,30,40};	/* Ÿœ¨£¦¡¨˜©åœª */
struct	pinvars {
	unsigned char	py[NMAX][6],
		 	epik[65];
	int	itype;
	float	an[NMAX], hh[NMAX];	/* ˜¤¦ š£.,¬¯¦£. */
	} v;
static struct	param{
	char    xarakt[5][8];		/* „Š€”“‘/€“‘ ˜šàšæª */
	int	tash[5],
		basan[2],
		tq[AGVGOI][THERM];	/* «˜¤ç©œ ª ˜šàšé¤ ©« ª › ˜­. Ÿœ¨£. */
	float	typos[5],		/* «ç§¦ª ˜šàš¦ç ©œ CM (=cyclic mils) */
		baros[5],		/* ™á¨¦ª ˜šàš¦ç */
		diatomh[5];             /* › ˜«¦£ã ˜šàš¦ç */
	double	m_elast[5];             /* £â«¨¦ œ¢˜©« ¡æ««˜ª */
	} p;
long	recv = sizeof(v), recp = sizeof(p);

/*
=========================================================================
1989,ˆ“Šˆ‘,24,
«˜¤ ¥œ¡ ¤á š ˜ §¨é« ­¦¨á «¦ §¨æš¨˜££˜ ¡˜  ˜¤¦åšœ  ¤â¦ ˜¨®œå¦ «æ«œ v.itype=0
§¦¬ ›œ¤ œå¤˜  œ§ «¨œ§«ã. ‚ ˜¬«æ ›å¤œ«˜  ˜¨® ¡ã « £ã:
	v.itype = 1;		/**/
------------------------------------------------------------------------- */
main()
{
    int i, select=1;

    v.itype = 1;						/**/
    if(get_from_disk_parameters())	exit(1);
    /* ------------------ DEFINE FIRST SCREEN'S INITIAL FORM */
    for(i=0;i<2000;i++)
	scr[2*i+1] = 7;

    cursor(0);
    get_from_disk_screen(80,25,PAROYS);
    screenin(&scr[2323], "B2.0H06");
    puttext(1,1,80,25,scr);
    getch();

    while(select != '0' && select != HOME && select != ESC)
    {
	get_from_disk_screen(53,12,MENU);
	clrscr();
	puttext(17,7,69,18,scr);
	gotoxy(28,17);
	cursor(1);
/*
gotoxy(3,24); printf("   %d   ",select); getch();
*/
	switch(select=gchar())
	{
	case '1':
            dedomena();
	    break;
	case '2':
	    calctens(0);
	    break;
	case '3':
	    calctens(1);
	    break;
	case '4':
	    calctens(2);
	    break;
	}
    }
    cursor(1);
    clrscr();
}
/*
=========================================================================
L 1989,ˆ“Šˆ‘,24,
------------------------------------------------------------------------- */
dedomena()
{
    char dfile[17]={'d','a','t','\\',0};
    int *ier,
	*pinaj_input(), *pinaj(),
	i=0,
	ret,
	k, l, m;
    float f=1.1;

    while(1)
    {
	display_screen(1,1,80,5,"\
ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿\
³                                                                              ³\
³                   „ ˆ ‘ € ‚ — ‚ †       ƒ „ ƒ  ‹ „ Œ — Œ                    ³\
³                                                                              ³\
ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ\
",1);

	if((ret=get_from_user_filename(dfile,".dat")) == HOME || ret == ESC)
	    return;

    	/* -------------------- DATA INPUT */
	get_from_disk_screen(80,25,PIN);
	puttext(1,1,80,25,scr);
	grammh = 1;
	get_from_disk_data(dfile);
	display_page();
    	while((ier=pinaj_input(
		2,15,"",&i,&f,v.epik,0,63,"","éé",0,'m',"%-s"))[1] != HOME)
    	{
	    if(ier[0] == -1)	changepage(dfile,ier[1]);
	    if(ier[0] >= -2)	continue;

	    while((ier=pinaj_input(
		3,17,"",&(v.itype),&f," ",1,2,"1","6",0,'n',"%-d"))[0] != -2)
	    {
	        if(ier[1] == AGVGOS || ier[1] == F2)
		{
		    int n = v.itype - 1;
                    if(get_from_disk_parameters())	return;
		    dsplagvgos(n);
		    if(put_to_disk_parameters())	return;
		    continue;
		}
		if(ier[0] == -1)
		{
		    changepage(dfile,ier[1]);
		    break;
		}
		if((ier=pinaj(dfile))[1] == HOME)	continue;
		if(ier[0] == -1)			break;
	    }
	    if(ier[1] == HOME)	break;
        }
	if(v.an[0]>0.1)	put_to_disk_data(dfile);
    }
}
/*
---------------------------------------------------------------------------
L
--------------------------------------------------------------------------- */
changepage(
char *dfile,
int ier)
{
    switch(ier)
    {
	case PAGE_UP:
	    prevpage(dfile);
	    return;
	case PAGE_DOWN:
	    nextpage(dfile);
	    return;
     }
}
/*
---------------------------------------------------------------------------
L 1989,ˆ“Šˆ‘,28
------------------------------------------------------------------------- */
help()
{
	char		tabl[1120];
       	static int	s[4]={44,9,78,24};

	gettext(s[0],s[1],s[2],s[3],tabl);
	display_screen(s[0],s[1],s[2],s[3],"\
ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»\
º    Š†‰’€  •„ˆˆ‘‹“  ˆŒ€‰€   º\
ÇÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¶\
º  PgUp   ¨¦š¦ç£. «£ã£˜ š¨˜££ãª º\
º  PgDn   „§æ£œ¤¦ «£ã£˜ š¨˜££ãª.. º\
º  â¢   ‰å¤© ›œå¡« ©«˜ §œ›å˜ º\
º  Tab    €¢¢˜šã ©«ã¢ª/«ç§¦¬_›œ› º\
º  Home   „¥¦›¦ª ˜§æ «¦¤ §å¤˜¡˜.. º\
º F1 ã ^A ›šåœª ®œ ¨ ©£¦ç...... º\
º F2 ã ^B •˜¨˜¡«¨ ©« ¡á ˜šàš¦ç.. º\
º F3 ã ^O ˜¨œ£™¦¢ã ›œ›¦£â¤¦¬.... º\
º F4 ã ^D ƒ ˜š¨˜­ã ›œ›¦£â¤¦¬..... º\
º F5 ã ^R €¤˜¡˜«á¥ ˜¨ Ÿ£. §ç¨šà¤ º\
º F9      ˜¨œ£™¦¢ã §å¤˜¡˜....... º\
º F10     ƒ ˜š¨˜­ã §å¤˜¡˜........ º\
ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼", 0);
	cursor(0);
	bioskey(0);
	puttext(s[0],s[1],s[2],s[3],tabl);
	cursor(1);
}
/*
---------------------------------------------------------------------------
L
--------------------------------------------------------------------------- */
int *pinaj(char *dfile)
{
    int t=0, *ier  , i=0, k,
	row, col, *pinaj_input(),
	sthl=NMAX/3, syn=NMAX-sthl,
	col0[3]={4, 10, 19};

    while(1)
    {
        row = 6 + i % sthl;
        col = col0[t] + 26 * (i / sthl);
	switch(t)
	{
	case 0:
    	    ier = pinaj_input(
		row,col,"",&i,&v.hh[i],v.py[i],1,5,"0","9999é",0,'m',"%5s");
	    gotoxy(col,row);
	    for(k=0;k<5 && v.py[i][k];k++)
		;
	    if(k)	k--;
            if(v.py[i][k] >= '0' && v.py[i][k] <= '9')
		cprintf("%4s ", v.py[i]);
	    break;
	case 1:
    	    ier = pinaj_input(
		row,col,"",&i,&v.hh[i],v.py[i],0,7,"0","9999.99",0,'f',"%7.2f");
	    if(v.hh[i] == 0. && v.an[i==0?0:i-1] == 0.)
	    {
		gotoxy(col,row);
		cprintf(".......");
	    }
	    break;
	case 2:
    	    ier = pinaj_input(
		row,col,"",&i,&v.an[i],v.py[i],0,6,"0","999.99",0,'f',"%6.2f");
            if(v.an[i] == 0)
	    {
		gotoxy(col,row);
		cprintf("......");
	    }
	    break;
	}

	switch(ier[1])
	{
	case LEFT_ARROW:
	    i = i < sthl ? syn + i : i - sthl;
	    break;
	case RIGHT_ARROW:
	    i = i >= syn ? i - syn : i + sthl;
	    break;
	case UP_ARROW:
	    i = i == 0 ? syn+sthl-1 : i - 1;
	    break;
	case PAGE_UP:
	    prevpage(dfile);
	    ier[0] = -1;
	    return ier;
	case PAGE_DOWN:
	    nextpage(dfile);
	    ier[0] = -1;
	    return ier;
	case F9:		/* insert PAGE */
	    inspage(dfile);
	    ier[0] = -1;									/**/
	    return ier;                                     /**/
	case F10:		/* delete PAGE */
	    delpage(dfile);
	    ier[0] = -1;
	    return ier;
	case HOME:
	    if(i == 0)
	    {
	    	ier[0] = -1;
	    	return ier;
	    }
	    i = 0;
	    break;
	case TAB:
	    t = t == 2 ? 0 : t + 1;
	    break;
	case RMITM:
	case F4:
	    delitem(i,t);
	    break;
	case F3:
	case INSITM:
	    insitem(i,t);
	    break;
	case F5:
	case REARNG:
	    rearrange(i);
	    break;
	default:
	    i = i == syn+sthl-1 ? 0 : i + 1;
	    break;
	}
    }
}
 /*
---------------------------------------------------------------------------
L
--------------------------------------------------------------------------- */
prevpage(char *dfile)
{
    if(grammh > 1)
    {
	if(v.an[0]>0.1)	 put_to_disk_data(dfile);
	grammh--;        get_from_disk_data(dfile);    display_page();
    }
}
 /*
---------------------------------------------------------------------------
L
--------------------------------------------------------------------------- */
nextpage(char *dfile)
{
    if(v.an[0]>0.1)
    {
		     put_to_disk_data(dfile);
	grammh++;    get_from_disk_data(dfile);    display_page();
    }
}
 /*
---------------------------------------------------------------------------
L
--------------------------------------------------------------------------- */
inspage(char *dfile)
{
    int gr=grammh;

    if(v.an[0] == 0)	return;
    while(v.an[0]>0.1)
    {
	grammh++;    get_from_disk_data(dfile);
    }
    while(grammh != gr)
    {
	grammh--;    get_from_disk_data(dfile);
	grammh++;    put_to_disk_data(dfile);
	grammh--;
    }
    initialize_data();    v.an[0] = 350.;    display_page();
}
 /*                       clreol()
---------------------------------------------------------------------------
L
global int grammh
--------------------------------------------------------------------------- */
delpage(char *dfile)
{
    int gr=grammh;

    if(v.an[0] == 0)	return;
    while(v.an[0]>0.1)
    {
	grammh++;    get_from_disk_data(dfile);
	grammh--;    put_to_disk_data(dfile);
	grammh++;
    }
    grammh = gr;     get_from_disk_data(dfile);    display_page();
}
 /*
---------------------------------------------------------------------------
L
--------------------------------------------------------------------------- */
int *pinaj_input(r,c,prmt,pn,pf,pm,ne,nm,mi,ma,prt,ty,format)
unsigned char	*pm, *mi, *ma;
char	*prmt,
	ty,
	*format;
int	r, c,
	*pn,
	ne, nm,
	prt;
float	*pf;
{
	static int ier[2]={0,0};
	unsigned char	str[81], *rr=str;
	double atof();

	if(ty == 'n')		sprintf(rr, "%-d", *pn);
	else if(ty == 'f')	sprintf(rr, "%-g", *pf);
	else			rr = pm;

	ier[1]=input(r,c,prmt,rr,ne,nm,mi,ma,prt,ty,format);

	if(ty == 'n')		*pn = atoi(rr);
	else if(ty == 'f')      *pf = atof(rr);

	switch(ier[1])
	{
	case PAGE_UP:
	case PAGE_DOWN:
	case HOME:
		ier[0] = -1;
		return ier;
	case UP_ARROW:
	case LEFT_ARROW:
		ier[0] = -2;
		return ier;
	default:
		ier[0] = -3;
		return ier;
	}
}
/*
------------------------------------------------------------
L
------------------------------------------------------------ */
put_to_disk_data(char *dfile)
{
    int i, fh;

    fh = open(dfile, O_WRONLY | O_BINARY);
    if(lseek(fh, (grammh-1)*recv, SEEK_SET) == -1)
	ferr("put_to_disk_data: lseek error");
    if(write(fh, &v, recv) == -1)
	ferr("put_to_disk_data: write error");
    if(close(fh) == -1)
	ferr("put_to_disk_data: close error");
}
/*
------------------------------------------------------------

------------------------------------------------------------ */
get_from_disk_data(char *dfile)
{
    int i, fh;

    if((fh=open(dfile, O_RDONLY | O_BINARY)) == -1)
	ferr("get_from_disk_data: open error");
    if(lseek(fh, (grammh-1)*recv, SEEK_SET) == -1)
	ferr("get_from_disk_data: lseek error");
    if((i=read(fh, &v, recv)) == 0)
	initialize_data();
    else if(i == -1 || i != recv)
	ferr("get_from_disk_data: read error");
    if(close(fh) == -1)
	ferr("get_from_disk_data: close error");
    return i;	/* i=0:EOF, i>0:data exists */
}
/*
------------------------------------------------------------

------------------------------------------------------------ */

display_page()
{
    gettext(1,2,80,22,&scr[160]);
    put_to_screen_data();		/* ˜¤«å š ˜ getvars(scr); */
    puttext(1,2,80,22,&scr[160]);
}
/*
------------------------------------------------------------

-------------------------------------------------------------------- */
checkrange(s,r,t)
unsigned char	*s,	/* min */
	 	*r,	/* str var */
		*t;	/* max */
{
	unsigned char *rr=r;

	for(;*s && *rr;s++,rr++)
	{
             	if(*s > *rr)
			return -1;
		else if(*s < *r)
			break;
	}
	if(*rr == '\0')	return -1;
	for(;*r && *t;r++,t++)
	{
             	if(*r > *t)
			return -1;
		else if(*r < *t)
			return 0;
	}
	if(*t == '\0')	return -1;
	return 0;
}
/*
====================================================================

------------------------------------------------------------
n >= 0: "previous_error" input_error_style   [error(0) remove prev_err_message]
n <0  : "look_until_press_a_key" error_style [error(0) remove any err_message]
----------------------------------------------------------------- */
error(n)
int n;
{
    char msg[77];

    if(n)
    {
	int k = abs(n);
	get_from_disk_message(k, msg);
	gotoxy(3,24);
        printf("%c%s%s%s", BELL, BLNK, msg, ATOFF);
    }
    if(n <= 0)
    {

	if(n)	getch();
	gotoxy(3,24);
	printf("%76s", " ");
    }
}
/*
==================================================================== */
char *cline(n, c)          /* -----n < 80----- */
int n;
char c;
{
        static char s[81];

        s[n] = '\0';
        while(n--)      s[n] = c;
        return(s);
}
/*
==================================================================== */
dpoint(s)
char *s;
{
        char    *t=s;
        int     n=0;
        while(*t)
                if(*t++ == '.')
                        n++;
        return(n);
}
/*
-------------------------------------------------------
L ƒœ¤ œ¢œš®œ  š ˜ «¦ «â¢¦ª «¦¬ string §¨¦¦¨ ©£¦¬
==================================================================== */
scpy(d,s)
char *d, *s;
{
        int n=0;
        do
                d[n] = s[n];
        while(s[n++]);
        return(--n);
}
/*
---------------------------
L €¤« š¨á­œ  â¤˜ ¦¢¦¡¢¨¦ string ©«¦ £â©¦ œ¤æª (£œš˜¢ç«œ¨¦¬) string.
   ƒœ¤ œ¢âš®œ  š ˜ «¦ «â¢¦ª «¦¬ string §¨¦¦¨ ©£¦ç, › æ«  £§¦¨œå £œ¤ ¤˜ â®œ 
     ¦¨ ©«œå ˜¨¡œ«á £œšá¢¦ ˜¢¢á ¤˜ œ£­˜¤åœ«˜  £ ¡¨æ«œ¨¦:
     §.®. char s[81]={0};                     --> strlen = 0
     ã    char s[81], *t="123"; strcpy(s, t); --> strlen = 3
==================================================================== */
stringin(char *d, char *s)
{
        int n;

        for(n=0; s[n]; n++)
                d[n] = s[n];
        return(n);
}
/*
---------------------------
L €¤« š¨á­œ  â¤˜ ¦¢¦¡¢¨¦ string ©œ £ á ¦Ÿæ¤.
==================================================================== */
screenin(char *scrn, char *s)
{
        int n;

        for(n=0; s[n]; n++)
                scrn[2*n] = s[n];
        return(n);
}
/*
-----------------------------------------------------------------------------
-------------------------------------------------------------------------- */
initialize_data()
{
    int i;

    for(i=0;i<NMAX;i++)						/**/
    {
	sprintf(v.py[i],"%d", i+1);
	v.hh[i] = 0.;
	v.an[i] = 0.;
    }
}
/*
-----------------------------------------------------------------------
L 1989/7/25,27
----------------------------------------------------------------------- */
put_to_screen_data()
{
    char *s="1234567";

    sprintf(s, "%2d", grammh);		screenin(&scr[164], s);
					screenin(&scr[188], v.epik);
    sprintf(s, "%-2d", v.itype);	screenin(&scr[352], s);
    put_to_screen_py();
    put_to_screen_hh();
    put_to_screen_an();
}
/*
-----------------------------------------------------------------------
L
----------------------------------------------------------------------- */
rearrange(int sitem)
{
    int i, k;

    k = atoi(v.py[sitem]);
    for(i=sitem+1;i<NMAX;i++)
	sprintf(v.py[i], "%d", i-sitem+k);
    display_py();
}
/*
-----------------------------------------------------------------------
L 1989/7/25
----------------------------------------------------------------------- */
put_to_screen_py()
{
    int i, j, k, l, m, n;
    char s[6];

    for(l=0;l<3;l++)
	for(m=0;m<17;m++)
	{
	    i = 17 * l + m;
	    j = 806 + 52 * l + 160 * m;
	    n = strlen(v.py[i]) - 1;
		/* š ˜ v.py[i]="" -> n<0 and v.py[i][n] has no meaning but it does
		not produces an error and does'nt matter what format the
		sprintf	has */
	    if(v.py[i][n] >= '0' && v.py[i][n] <= '9')
	    	sprintf(s, "%4s", v.py[i]);
	    else
                sprintf(s, "%5s", v.py[i]);
	    screenin(&scr[j], s);
	}
}
/*
-----------------------------------------------------------------------
L 1989/7/25
----------------------------------------------------------------------- */
display_py()
{
    gettext(1,6,80,22,&scr[800]);
    put_to_screen_py();
    puttext(1,6,80,22,&scr[800]);
}
/*
-----------------------------------------------------------------------

----------------------------------------------------------------------- */
delitem(
int sitem,	/* starting item */
 int var)	/* 0=v.py[], 1=v.hh[], 2=v.an[] */
{
    int i, j, k, l, m, n;
    char s[6];

    switch(var)
    {
    case 0:
	for(i=sitem;i<NMAX-1;i++)
	    scpy(v.py[i], v.py[i+1]);
	sprintf(v.py[NMAX-1], "%-d", atoi(v.py[NMAX-2])+1);
	display_py();
        break;
    case 1:
	for(i=sitem;i<NMAX-1;i++)
	    v.hh[i] = v.hh[i+1];
	v.hh[NMAX-1] = 0.;
	display_hh();
        break;
    case 2:
	for(i=sitem;i<NMAX-1;i++)
	    v.an[i] = v.an[i+1];
	v.an[NMAX-1] = 0.;
	display_an();
        break;
    }
}
/*
-----------------------------------------------------------------------

----------------------------------------------------------------------- */
insitem(
	int sitem,	/* starting item */
	int var)	/* 0=v.py[], 1=v.hh[], 2=v.an[] */
{
    int i, j, k, l, m, n;
    char s[6];

    switch(var)
    {
    case 0:
	for(i=NMAX-1;i>=sitem+1;i--)
	    scpy(v.py[i], v.py[i-1]);
	v.py[sitem][0] = 0;
	display_py();
        break;
    case 1:
	for(i=NMAX-1;i>=sitem+1;i--)
	    v.hh[i] = v.hh[i-1];
	v.hh[sitem] = 0.;
	display_hh();
        break;
    case 2:
	for(i=NMAX-1;i>=sitem+1;i--)
	    v.an[i] = v.an[i-1];
	v.an[sitem] = 0.;
	display_an();
        break;
    }
}
/*
-----------------------------------------------------------------------
L 1989/7/25
----------------------------------------------------------------------- */
put_to_screen_hh()
{
    int i, j, k, l, m;
    char s[8];
    for(l=0;l<3;l++)
	for(m=0;m<17;m++)
	{
	    i = 17 * l + m;
	    j = 818 + 52 * l + 160 * m;
	    if(v.hh[i] == 0. && v.an[i==0?0:i-1] == 0.)
		strcpy(s, ".......");
	    else
	    	sprintf(s, "%7.2f", v.hh[i]);
	    screenin(&scr[j], s);
	}
}
/*
-----------------------------------------------------------------------
L 1989/7/25
----------------------------------------------------------------------- */
display_hh()
{
    gettext(1,6,80,22,&scr[800]);
    put_to_screen_hh();
    puttext(1,6,80,22,&scr[800]);
}
/*
-----------------------------------------------------------------------
L 1989/7/25
----------------------------------------------------------------------- */
put_to_screen_an()
{
    int i, j, k, l, m;
    char t[7];
    for(l=0;l<3;l++)
	for(m=0;m<17;m++)
	{
	    i = 17 * l + m;
	    j = 836 + 52 * l + 160 * m;
	    if(v.an[i] == 0.)
		strcpy(t, "......");
	    else
		sprintf(t, "%6.2f", v.an[i]);
	    screenin(&scr[j], t);
	}
}
/*
-----------------------------------------------------------------------
L 1989/7/25
----------------------------------------------------------------------- */
display_an()
{
    gettext(1,6,80,22,&scr[800]);
    put_to_screen_an();
    puttext(1,6,80,22,&scr[800]);
}
/*
=========================================================================

------------------------------------------------------------
1989,ˆ“Šˆ‘,29
------------------------------------------------------------------------- */
display_screen(	int x1,
	int y1,
	int x2,
	int y2,
	char *icon,
	int flg)
{
	int	i;

	for(i=0;icon[i];i++)
		scr[2*i] = icon[i];

	if(flg)		clrscr();
       	puttext(x1,y1,x2,y2,scr);
}
/*
=========================================================================
 1989,€“‚“‘’‘,1
------------------------------------------------------------------------- */
get_from_disk_message(int k, char *msg)
{
	int fh,ier;

	if((fh=open(MSGS, O_RDONLY | O_TEXT)) == -1)
		ferr("get_from_disk_message: open error");
	if(lseek(fh, k*80, SEEK_SET) == -1)
	    ferr("get_from_disk_message: lseek error");
	if(read(fh, msg, 76) < 76)
	    ferr("get_from_disk_message: read error");
	msg[76] = '\0';
	close(fh);
}
/*
=========================================================================
 1989,€“‚“‘’‘,1
------------------------------------------------------------------------- */
get_from_disk_screen(
        int c,		/* §¢˜«¦ª §å¤˜¡˜ ©œ ®˜¨˜¡«ã¨œª */
	int r,		/* ç¯¦ª §å¤˜¡˜ ©œ š¨˜££âª */
	char *pindf)    /* ˜¨®œ ¦ §¦¬ §œ¨ â®œ  «¦¤ §å¤˜¡˜ */
{
	int fh, ic, ir, k;
	char buf[83];

	if((fh=open(pindf, O_RDONLY | O_TEXT)) == -1)
		ferr("get_from_disk_screen: open error");
	for(ir=0;ir<r;ir++)
	{
	    if(read(fh, buf, c+1) < c+1)
		ferr("get_from_disk_screen: read error");
	    k = 2 * ir * c;
	    for(ic=0;ic<c;ic++)
		scr[k+2*ic] = buf[ic];
	}
	close(fh);
}
/*
---------------------------------------------------------------------------
L
--------------------------------------------------------------------------- */
inpagv(int n)     	/* n = ¡à›. ˜šàš¦¬ */
{
    int	u=4,		/* ˜/˜ Ÿœ¨£¦¡¨˜© ˜ª */
	i=n/2, j,
	r=5+11*(n/6),
	ier=0;		/* retrurn value */
    char	rr[15];
    double	atof();

    j = (n < 6 ? prost[n] : n) / 2;

    while(ier != AGVGOS && ier != F2)
    {
	u = (u == 4 ? -7 : u + 1);
	switch(u)
	{
	case -7:
	    sprintf(rr,"%-d",p.tash[j]);
	    ier = input(r,29,"",rr,0,3,"0","999",0,'n',"%-3d");
	    p.tash[j] = atoi(rr);
	    break;
	case -6:
	    ier = input(r,45,"",p.xarakt[i],0,7,"","éé",0,'m',"%-7s");
	    break;
	case -5:
	    sprintf(rr,"%-f",p.typos[i]);
	    ier = input(r+1,38,"",rr,0,7,"0","999.999",0,'f',"%-7.3f");
	    p.typos[i] = atof(rr);
	    break;

	case -4:
	    sprintf(rr,"%-d",p.basan[n%2]);
	    ier = input(r+2,38,"",rr,0,3,"0","999",0,'n',"%-3d");
	    p.basan[n%2] = atoi(rr);
	    break;
	case -3:
	    sprintf(rr,"%-f",p.baros[i]);
	    ier = input(r+3,38,"",rr,0,7,"0","9.9999",0,'f',"%-6.4f");
	    p.baros[i] = atof(rr);
	    break;
	case -2:
	    sprintf(rr,"%-f",p.diatomh[i]);
	    ier = input(r+4,38,"",rr,0,4,"0","9.99",0,'f',"%-4.2f");
	    p.diatomh[i] = atof(rr);
	    break;
	case -1:
	    sprintf(rr,"%-G",p.m_elast[i]);
	    ier = input(r+5,38,"",rr,0,11,"0","1e+11",0,'f',"%-6.4E");
	    p.m_elast[i] = atof(rr);
	    break;
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	    gotoxy(49,r+6);    cprintf("%-2d",th[u]);
	    sprintf(rr,"%-d",p.tq[n][u]);
	    ier = input(r+6,38,"",rr,0,4,"0","9999",0,'n',"%-4d");
	    p.tq[n][u] = atoi(rr);
	    break;
	}
    }
}
/*
---------------------------------------------------------------------------

--------------------------------------------------------------------------- */
dsplagvgos(int n)
{
	int	i=n/2, j, k=n/6;
       	static int	s[2][4]={20,2,56,12,   20,13,56,23};
	char	*tabl=&scr[2000+k*1000],
		rr[15],
		*ag= &scr[k*1000];
	static char	*title[2]={
			"  •€€‰’†ˆ‘’ˆ‰€ €‚—‚“  ”€‘„—‘  ",
			"•€€‰’†ˆ‘’ˆ‰€ €‚—‚“  ‘’€‘ˆ€‘"};

						screenin(ag, "\
ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»\
º       •€€‰’†ˆ‘’ˆ‰€ €‚—‚“       º\
ÇÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¶\
º ‚¨˜££ã    KV ** €šàšæª            º\
º ’ç§¦ª         =             CM    º\
º ˜©. €¤¦ š£˜  =             m     º\
º á¨¦ª         =             kp/m  º\
º ƒ ˜«¦£ã       =             cmı   º\
º ‹â«¨¦ „¢˜©« ¡.=             kp/mı º\
º €¨®.¨.’á¤¬© =      kp ©œ 0 øC   º\
ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼");
	j = (n < 6 ? prost[n] : n) / 2;
						screenin(&ag[78], title[k]);
	sprintf(rr,"%-3d",p.tash[j]);		screenin(&ag[240], rr);
	sprintf(rr,"%-10s",p.xarakt[i]);	screenin(&ag[272], rr);
	sprintf(rr,"%-7.3f",p.typos[i]);	screenin(&ag[332], rr);
	sprintf(rr,"%-3d",p.basan[n%2]);	screenin(&ag[406], rr);
	sprintf(rr,"%-6.4f",p.baros[i]);	screenin(&ag[480], rr);
	sprintf(rr,"%-4.2f",p.diatomh[i]);	screenin(&ag[554], rr);
	sprintf(rr,"%-6.4E",p.m_elast[i]);	screenin(&ag[628], rr);
	sprintf(rr,"%-4d",p.tq[n][0]);		screenin(&ag[702], rr);

	gettext(s[k][0],s[k][1],s[k][2],s[k][3],tabl);
	puttext(s[k][0],s[k][1],s[k][2],s[k][3],ag);
	inpagv(n);
	if(n < 6)	dsplagvgos(prost[n]);
	puttext(s[k][0],s[k][1],s[k][2],s[k][3],tabl);
}
/*
=========================================================================
 1989,€“‚“‘’‘,1
------------------------------------------------------------------------- */
get_from_disk_parameters()
{
	int fh, ier=0;

	if((fh=open(PARAMDF, O_RDWR | O_BINARY)) == -1)
	{
		if((ier=fh=_creat(PARAMDF, FA_ARCH)) == -1)
			error(-12);
		else	ier = 0;
	}
	else if((ier=read(fh, &p, recp)) == 0 || ier == recp)
		ier = 0;
	else if(ier < recp)
		error(-14);
	close(fh);
	return ier;
}
/*
=========================================================================
L 1989,€“‚“‘’‘,1
------------------------------------------------------------------------- */
put_to_disk_parameters()
{
	int fh;

	if((fh=open(PARAMDF, O_WRONLY | O_RDWR | O_BINARY)) == -1)
	{
		error(-13);
		return -1;
	}
	if(write(fh, &p, recp) < recp)
	{
		error(-15);
		close(fh);
		return -1;
	}
	close(fh);
	return 0;
}
/*
=========================================================================
L
------------------------------------------------------------------------- */
ferr(unsigned char *s)
{
    gotoxy(3,24);
    printf("%s", s);
    getch();
    exit(1);
}
/*
------------------- ’„Š‘ ‚€‹‹€’‘ „ˆ‘€‚—‚†‘ ƒ„ƒ‹„Œ—Œ --------------

------------------- €•† ‚€‹‹€’‘ “Š‚ˆ‘‹“ ‰€ˆ „‰’“—‘„—Œ ---- */

     char flpyn='n',	/* 'n'/'y': £ «¬§é¤œ ª/«ç§à©œ */
	 anyn='n', pyapo[5], pyevs[5],
	 thyn='n',
	 agyn='n';
    int beg, ith, iter, itowr, j, iso, isn,
	ityp, flp=1,	/* flp=  1: „‹”€Œˆ‘† ‹„Œ“ „‰’“—‘„—Œ
			   flp=  0: „€”€Œˆ‘† ‹„Œ“ „‰’“—‘„—Œ
			   flp= F2: ‘“Œ„•†‘ „‰’“—‘† */
	leitoyrgia=1, prline, prlineapo=0, prlineevs=0,
	anapo=0, anevs=0,       /* ˜/˜ ˜¤¦ š£˜«¦ª ˜§¦ - œàª */
	thapo=0, thevs=0, 	/* Ÿœ¨£¦¡¨. ˜§¦ - œàª */
	agapo=0, agevs=0;       /* ®˜¨˜¡«. ˜šàš¦¬ */
    float tsa[NMAX], at[NMAX-1], f[NMAX-1], tsp[NMAX], dda[NMAX],
	tt[THERM],      /*«˜¤¬©œ ª š ˜ « ª 5 Ÿœ¨£. œ¤¦ª ˜šàš¦¬ */
        xx, sl,
	b[NMAX-1], tor[NMAX-1],
	w, sec,		/* sec §¨é¤ s */
	da[NMAX],
    	dt, xc, aaa, dd, cc, bb, aa, ax, dtmon, slt, xy;
    double e,
    	sqrt(), pow(), fabs();
    FILE *fp, *fpc, *fopen();
/*
=========================================================================

------------------------------------------------------------
1989,ˆ“Šˆ‘,24,
------------------------------------------------------------------------- */
calctens(
int n)			/* ©¬©¡œ¬ã œ¡«¬§é©œàª 0,1,2 */
{
    char name[13], dfile[17]={'d','a','t','\\',0};

    int i, tmhma=0, c=0;

    leitoyrgia=1, prline=0;
    display_screen(1,1,80,5,"\
ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿\
³                                                                              ³\
³              “   Š  ‚ ˆ ‘ ‹  ˆ    ‰€ˆ   „ ‰ ’ “  — ‘ „ ˆ ‘              ³\
³                                                                              ³\
ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ\
",1);
    if((i=get_from_user_filename(dfile,".dat")) == HOME || i == ESC)
	return;
    if(n == 2)
	strcpy(name, "LPT1");
    else if(n == 1)
    {
        strcpy(name, "apotel");
        cursor(0);
        gotoxy(1,10);
	puts("\
             ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»\n\
             º                                                     º\n\
             º                                                     º\n\
             º      ‚€”— ’€ €’„Š„‘‹€’€ ‘’ €•„ˆ 'APOTEL'      º\n\
             º                                                     º\n\
             º                                                     º\n\
             ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼");
    }
    else
	strcpy(name, "CON");

    if((fp = fopen(name, "wt")) == NULL)
    {
        error(11);
	return;
    }
    if((fpc = fopen("CON", "wt")) == NULL)
    {
        error(11);
	return;
    }

    if(n != 1) clrscr();
/*    if((c=xeirismos(n)) == '0')	return; */
    for(grammh = 1; get_from_disk_data(dfile); grammh++)				/**/
    {
	beg = 0;	/* beg increment step = j+1 */
	while(v.an[beg] > 0.1 && beg < NMAX)
        {
	    int metr = 1;	/* 1=­˜©œàª 2=§¨¦©«˜© ˜ª */
            for(ityp=v.itype-1; metr <= 2; metr++, ityp=prost[v.itype-1])
            {
		int cp;

		if(metr == 1) tmhma++;
		cp = (c == F4 ? F4 : n);
		if((c=xeirismos(cp)) == '0')	return;
/*
		else if(c == F4)
		{
		    if(anapo == 0)
		    {
			if(strcmp(pyapo, v.py[beg]))     continue;
			else		anapo = beg;
		    }
		    else if(anevs)    continue;
		    else if(strcmp(pyevs, v.py[beg]) == 0)    anevs = beg;
		}
*/
                w = p.baros[ityp/2];
                sec = p.diatomh[ityp/2] / 10000.;
                e = p.m_elast[ityp/2] * 100000 * 100000;		/**/
		dt = 99.;
                for(i=0; i<5; i++)		/*DO 42 I=1,5*/
                    tt[i] = p.tq[ityp][i];
                dtmon = dt;
/*        	ITOWR=TOWR		*/
		for(j=beg; v.an[j] > 0.1; j++)	/*DO 31 J=1,N*/
		{
	            b[j] = sqrt((double) (v.an[j] * v.an[j]) +
		 	pow((double) (v.hh[j+1] - v.hh[j]), (double)2.));
		}

		if(n != 1)   putchar('\r'),      clreol();
		print_data(tmhma, c);
/*
		if(c == TAB)	break;

                c = 0;
*/
		for(ith=0; ith<THERM; ith++)		/* D0 300 K=1,5 */
		{
		  if((c=xeirismos(c == TAB ? -1 : n)) == '0')
		      return;
		  if(c != ESC && c != TAB)
		  {
/*
*/
		    dt = dtmon;
        	    xx = tt[ith] / w;
	            sl = 0.;
        	    for(j=beg; v.an[j]>0.1; j++)		/* D0 3 J=1,N */
		    {
			tor[j] = tt[ith];
			sl += sqrt(pow((double)b[j], (double)2.) + pow(
			    (double)v.an[j], (double)4.) / (12. * xx * xx));
	            }			/* 3   continue */
        	    iter = 0;
	            tor[beg] = tt[ith];			/* TOR(1)=TT(K) */
		    do
		    {
        	        j = beg;                          /* J=1 */
                	xx = tor[j] / w;
	                at[j] = v.an[j] - 2. * (v.hh[j+1] - v.hh[j]) * xx / v.an[j];
        	        f[j] = at[j] * at[j] / (8. * xx);
                	tsa[j] = tor[j] + w * f[j];
	                tsp[j] = tor[j] + w * (f[j] + (v.hh[j+1] - v.hh[j]));
        	        slt = 0;
			slt += sqrt(b[j] * b[j] + pow(
			    (double)v.an[j], (double)4.) / (12. * xx * xx));
	                for(j=beg+1; v.an[j]>0.1; j++)	/* DO 100 J=2,N */
        	        {
                	    xx =  tor[j] / w;
	                    at[j] = v.an[j] - 2. * (v.hh[j+1] - v.hh[j]) * xx / v.an[j];
        	            tsa[j] = tsp[j-1];
                	    ax = (v.hh[j+1] - v.hh[j]) / v.an[j];
	                    aa = 0.5 * ax * ax + 1.;
        	            bb = -tsa[j] - 0.5 * w * (v.hh[j+1] - v.hh[j]);
                	    cc = w * w * v.an[j] * v.an[j] / 8.;
	                    dd = sqrt(bb * bb - 4. * aa * cc);
        	            tor[j] = (dd - bb) / (2. * aa);
                	    xx = tor[j] / w;
	                    at[j] = v.an[j] - 2. * (v.hh[j+1] - v.hh[j]) * xx / v.an[j];
        	            f[j] = at[j] * at[j] / (8. * xx);
                	    tsp[j] = tor[j] + w * (f[j] + (v.hh[j+1] - v.hh[j]));
			    slt += sqrt(b[j] * b[j] + pow(
				(double)v.an[j], (double)4.) / (12. * xx * xx));
			}				/* 100   continue */

			if(fabs((double)sl - slt) <= PROSEGISH)	   break;

			if(slt <= sl)
			{
			    if(iter == 0)	iso = -1;
			    isn = -1;
			    if(isn != iso)	dt /= 2.;	/* DT=DT/2. */
			    tor[beg] -= dt;		/* TOR(1)=TOR(1)-DT */
			    iso = isn;
			}
			else
			{
			   if(iter == 0)	iso = 1;
			   isn = 1;
			   if(isn != iso)	dt /= 2.;	/* DT=DT/2. */
			   tor[beg] += dt;		/* TOR(1)=TOR(1)+DT */
			   iso = isn;
		       }
		       iter++;
		  } while(iter < 9999);

	            for(j=beg; v.an[j]>0.1; j++)		/* DO 400 J=1,N */
        	    {
                	xx = tor[j] / w;
			f[j] = b[j] * v.an[j] / (8. * xx) + b[j] * pow(
			    (double)(v.an[j] / xx), (double)3.) / 384.;
	                aaa = pow((double)v.an[j], (double)4.) * w * w / 12.;
        	        xc = sqrt(b[j] * b[j] + aaa / (tor[j] * tor[j]));
                	xc -= sqrt(b[j] * b[j] + aaa / (tt[ith] * tt[ith]));
	                da[j] = b[j] * b[j] * b[j] * (tor[j] - tt[ith]) /
				              (sec * e * v.an[j] * v.an[j]);
        	        da[j] -= xc;
	            }				/* 400   continue */
        	    dda[beg] = da[beg];		/* DDA(1)=DA(1) */
	            j = beg;			/* J=1 */
        	    xy = tt[ith] / w;
		    tsa[j] = b[j] * v.an[j] / (8. * xy) +
			b[j] * pow((double)(v.an[j] / xy), (double)3.) / 384.;
	            for(j=beg+1; v.an[j]>0.1; j++)		/* DO 500 J=2,N */
        	    {
                	tsa[j] = b[j] * v.an[j] / (8. * xy) + b[j] * pow(
			    (double)(v.an[j] / xy), (double)3.) / 384.;
	                dda[j] = dda[j-1] + da[j];
        	    }
		  }        /* end of if(c!=27&&c!=9) */
		  /* n=0:¦Ÿ¦¤,n=1:˜¨®œ ¦,n=2:œ¡«¬§,n=-1:œ¡«¬§.¦®  */

		  if(n != 1)  putchar('\r'),      clreol();
		  if(print_results(c==ESC || c==TAB ? -1 : n) == 'n')
		      return;
		}	   /* end of for(ith=0; ith<THERM; ith++) */
		if(n == 2 && c == F2)   fputc('\f', fp);
	    }
	    beg = j + 1;   /* ¦ â¢œš®¦ª beg < NMAX šå¤œ«˜  ©«¤ ˜¨®ã */
	}		   /* end of while(v.an[beg] > 0.1 && beg < NMAX) */
    }

    fclose(fp);
    fclose(fpc);
    if(n == 1)
    {
	gotoxy(20,13);
	cprintf("          †  „‚€‘ˆ€  Š‰Š†—‡†‰„        ");
    }
}
/*
=========================================================================
L 1990,ˆ“Œˆ‘,21,
------------------------------------------------------------------------- */
xeirismos(int n)	/* n = 0,1,2 ©¬©¡œ¬ œ¥¦›¦¬, -1 §˜¨˜¡˜£¯ ®œ ¨ */
{
    int c = 13, i;

    if(n == -1)    return TAB;
    if((n == 1 || flp == F2) && kbhit())   /* „¢âš®œ  ˜¤ §˜«ãŸ¡œ §¢ã¡«¨¦ */
    {
/*        if(n != 1)    clrscr(); */
	cursor(0);
        if(n == 1)
	    gotoxy(21,13),
	    cprintf("‡„Š„ˆ‘ Œ€ ƒˆ€‰–— (F1 = Œ€ˆ, F2 = OXI) ; ");
        else
            cprintf("\r‡â¢œ ª ¤˜ › ˜¡æ¯à (F1 = Œ˜ , F2 = O® ) ; "),
            clreol();
	cursor(0);
	while(kbhit())	    c = gchar();
	while((c=gchar()) != F1 && c != F2)	    ;
	if(c == F1)
        {
	    if(n == 1) return '0';
            putchar('\r');      clreol();
	    flp = 1;
        }
        else if(n == 1)
        {
	    gotoxy(21,13);
	    cprintf("‚€”— ’€ €’„Š„‘‹€’€ ‘’ €•„ˆ 'APOTEL'");
	}
	else
            cprintf("\r„§˜¤˜¢˜£™á¤à « ©¬¤œ®ã œ¡«ç§à©"),    clreol();
    }

    if(n != 1 || flpyn == 'y')
    {
	if(flp != F2 && leitoyrgia != F4)
	{
	    xeirmask(flp==1 ? 1 : -1);
	    do
	    {
		int  ier;
		char rr[6];

		switch(c=gchar())
		{
		case F1 :
		    flp = 1 - flp;
		    xeirmask(flp);
		    break;
		case F2:
		    xeirmask(flp==1 ? 0 : -1);
		    leitoyrgia = F2;
		    flp = F2;
		    cprintf("\r€¨®åà ©¬¤œ®ã œ¡«ç§à©...");
		    clreol();
                    break;
                case F3:
                    if(n == 2)  fputc('\f',fp);
	  cprintf("\rH œ§æ£œ¤ œ¡«ç§à© Ÿ˜ ˜¨®å©œ  £œ ˜¢¢˜šã ©œ¢å›˜ª");
		    clreol();
                    break;
		case F4 :
		    leitoyrgia = F4;
		    gotoxy(1,24);
		    putchar('\r');      clreol();
		    do
		    {
			sprintf(rr,"%-d",prlineapo);
			ier =
			   input(24,6,"€§¦: ",rr,1,5,"1","32000",0,'n',"%-5d");
			prlineapo = atoi(rr);
			if(ier == HOME)  break;
			sprintf(rr,"%-d",prlineevs);
			ier =
			  input(24,17,"„àª: ",rr,1,5,"1","32000",0,'n',"%-5d");
			prlineevs = atoi(rr);
		    } while(ier != HOME);
		    break;
		case ESC:
		case '0':
		case TAB:
		    xeirmask(flp==1 ? 0 : -1);
		    break;
		default:
		    xeirmask(flp==1 ? 0 : -1);
                cprintf("\r‰á¤à ¬§¦¢¦š ©£¦çª. ˜¨˜¡˜¢é §œ¨å£œ¤œ ¢åš¦...");
		    clreol();
		    break;
                }
	    } while(c == F1 || c == F3);
        }       /* end of if(c != F2) */
        else
	    cprintf("\r‰á¤à ¬§¦¢¦š ©£¦çª. ˜¨˜¡˜¢é §œ¨å£œ¤œ ¢åš¦..."),
	    clreol();
    }
    return c;
}
/*
========================= END OF PROGRAM LIST ========================== */
