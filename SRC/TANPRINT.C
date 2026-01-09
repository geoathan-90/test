/***********************************************************
*
*    PROGRAMMER.: X_SOFTWARE
*    PROGRAM....: TAN
*    FILE/DATE..: TANS5.C / 890815-18
*    DESCRIPTION: ‚€‹‹€ „Š—Œ ‰€ˆ ’€Œ“‘„—Œ
*
***********************************************************/
# include "src\tans5.h"


char *starline="\
***********************************************************************";

extern char flpyn,	/* 'n'/'y': £ «¬§é¤œ ª/«ç§à©œ */
	 anyn, pyapo[5], pyevs[5],
	 thyn,
	 agyn;
extern int beg, ith, iter, itowr, j, iso, isn,
	ityp, flp,	/* flp=  1: „‹”€Œˆ‘† ‹„Œ“ „‰’“—‘„—Œ
			   flp=  0: „€”€Œˆ‘† ‹„Œ“ „‰’“—‘„—Œ
			   flp= F2: ‘“Œ„•†‘ „‰’“—‘† */
	leitoyrgia, prline,  prlineapo, prlineevs,
	anapo, anevs,       /* ˜/˜ ˜¤¦ š£˜«¦ª ˜§¦ - œàª */
	thapo, thevs, 	/* Ÿœ¨£¦¡¨. ˜§¦ - œàª */
	agapo, agevs;       /* ®˜¨˜¡«. ˜šàš¦¬ */
extern int	grammh,
	prost[6],		/* ˜¤«å©«¦ ®¦  ˜šàš¦å §¨¦©«˜©å˜ª */
	th[THERM];	/* Ÿœ¨£¦¡¨˜©åœª */
extern struct	pinvars {
	unsigned char	py[NMAX][6],
		 	epik[65];
	int	itype;
	float	an[NMAX], hh[NMAX];	/* ˜¤¦ š£.,¬¯¦£. */
	} v;
extern float tsa[NMAX], at[NMAX-1], f[NMAX-1], tsp[NMAX], dda[NMAX],
	tt[THERM],      /*«˜¤¬©œ ª š ˜ « ª 5 Ÿœ¨£. œ¤¦ª ˜šàš¦¬ */
        xx, sl,
	b[NMAX-1], tor[NMAX-1],
	w, sec,		/* sec §¨é¤ s */
	da[NMAX],
    	dt, xc, aaa, dd, cc, bb, aa, ax, dtmon, slt, xy;
extern double e,
    	sqrt(), pow(), fabs();
extern FILE *fp, *fpc, *fopen();
/*
=========================================================================
L 1989,ˆ“Šˆ‘,24,
------------------------------------------------------------------------- */
print_data(
	int tmhma,
	int c		/* entolh xeiristh */
	)
{
    char *pro="‘’€‘ˆ€‘";

    if(leitoyrgia == F4 && flpyn == 'n')  return;
    if(ityp <= 5)	pro = "”€‘„—‘";

    fprintf(c == ESC || c == TAB ? fpc : fp, "\r********%s\n\
    ‚€‹‹†: %-s\n\
    %doª ˆŒ€‰€‘ ƒ„ƒ‹„Œ—Œ    %do ’‹†‹€ ‚€‹‹†‘\n********%s\n\
    ’“‘   €‚—‚“ ................... = %-d (€‚—‚‘ %s)\n\
    €‘ €‚—‚“ ..................... = %-14.3f kp/m\n\
    ‹„’ „Š€‘’ˆ‰’†’€‘ .............. = %-14.7g kp/m2\n\
    ƒˆ€’‹† €‚—‚“ ................... = %-14.3f cm\n\
    ƒˆ‡—‘† ’€Œ“‘„—‘................. = %-14.2f kp\n\
    €•ˆ‰† ˆ…. ’€Œ“‘† 1¦¬ €Œˆ‚‹€’‘ = %-14.1f kp\n\
    €ˆ‡‹‘ 1¦¬ “‚“ ............... = %-s\n\
    ÚÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄ¿\n\
    ³           ³       ³        ³ ’€Œ“‘† ³ ’€Œ“‘† ³  „Š‘ ³ „Š‘  ³ ’‹†‹€  ³\n\
    ³           ³       ³        ³   --   ³   --   ³   --   ³   --   ³ €‚—‚“ ³\n\
    ³           ³       ³        ³   ‹„   ³ €‚—‚ˆ ³   ‹„   ³ €‚—‚ˆ ³  ‚ˆ€   ³\n\
    ³ “  ‚  ˆ³       ³“–‹„’.³‰€’€‰.³  ‘’ˆ‘  ³‰€’€‰.³  ‘’ˆ‘  ³ƒˆ‡—‘†³\n\
    ³€  -  „—‘³€Œˆ‚‹€³ƒˆ€”€ ³‹Œ—’†.³ ’•€Š.³‹Œ—’†.³ ’•€Š.³ ’€Œ“‘†‘³\n\
    ÀÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÙ\n",
	starline, v.epik, grammh, tmhma, starline,
	ityp+1, pro, w, e, 10000*sec, dt, tt[0], v.py[beg]);
}
/*
=========================================================================
LL 1989,ˆ“Šˆ‘,24,
------------------------------------------------------------------------- */
print_results(n)
int n;		/* ¡à› ¡¦ª ©¬©¡œ¬ª œ¥¦›¦¬:
                   0=¦Ÿ¦¤, 1=˜¨®œ ¦, 2=œ¡«¬§à«ª, -1=˜¡ç¨à© œ¡«¬§. */
{
    int it;
    char *pro="‘’€‘ˆ€‘";

    if(leitoyrgia != F4 || flpyn == 'y')
    {
	if(ityp <= 5)	pro = "”€‘„—‘";

	fprintf(n == -1 ? fpc : fp, "\r\
    €‚—‚‘ %s - ˆ…Œ’ˆ€ ’€Œ“‘† = %6.1f ‰€ˆ ‡„‹‰€‘ˆ€ = %2døC   \n",
	pro, tt[ith], th[ith]);

	if(n == -1)	return -1;
	fputs("\
    ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\n",
	fp);
    }
    for(it=beg; v.an[it]>0.1; it++)		/* DO 501 I=1,N */
    {
	prline++;
	if(leitoyrgia == F4)
	{
	    if(prline < prlineapo)  	 continue;
	    else if(prline == prlineapo) flpyn = 'y';
	    else if(prline > prlineevs)
	    {   flpyn = 'n';    return flpyn;    }
	}
	fprintf(fp,
"%4d %5s-%-5s %5.0f    %4.0f    %6.0f   %6.0f  %7.2f  %7.2f   %7.2f\n",
	prline,
	v.py[it],v.py[it+1], v.an[it],v.hh[it+1]-v.hh[it], tt[ith],tor[it],
	tsa[it],f[it], dda[it]);
	if((it-beg+1) % 21 == 0 && n == 0 && flp !=F2)
	    cprintf(" ˜¨˜¡˜¢é §á«˜ <RETURN>\r"),    getch();
    }
    if(flpyn == 'y')  fprintf(fp, "(%5d) %s\n", prline, starline);
    return 0;
}
/*
========================= END OF PROGRAM LIST ========================== */

