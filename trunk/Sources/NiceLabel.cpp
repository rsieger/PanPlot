/*
 * Nice Numbers for Graph Labels
 * by Paul Heckbert
 * from "Graphics Gems", Academic Press, 1990
 */

/*
 * label.c: demonstrate nice graph labeling
 *
 * Paul Heckbert	2 Dec 88
 */

/*
 * NiceLabel.cpp
 *
 * Rainer Sieger, PANGAEA, 2009-12-15
 *
 */

#include "Application.h"

/* desired number of tick marks */

const int NTICK = 5;

/* expt(a,n)=a^n for integer n */

double MainWindow::expt( const double a, int n )
{
    double x;

    x = 1.;
    if (n>0) for (; n>0; n--) x *= a;
    else for (; n<0; n++) x /= a;
    return x;
}

/*
 * loose_label: demonstrate loose labeling of data range from min to max.
 * (tight method is similar)
 */

void MainWindow::calcLooseLabel( const double min, const double max, int &nfrac, double &spacing, double &graphmin, double &graphmax )
{
    double range = 0.;

    /* we expect min!=max */
    range    = nicenum( max-min, false );
    spacing  = nicenum( range/(NTICK-1), true );
    graphmin = floor(min/spacing)*spacing;
    graphmax = ceil(max/spacing)*spacing;
    nfrac    = (int) qMax( -floor( log10( spacing ) ), 0. );	/* # of fractional digits to show */
}

/*
 * nicenum: find a "nice" number approximately equal to x.
 * Round the number if round=true, take ceiling if round=false
 */

double MainWindow::nicenum( const double x, const bool round )
{
    int     expv;			/* exponent of x */
    double  f;				/* fractional part of x */
    double  nf;				/* nice, rounded fraction */

    expv = floor(log10(x));
    f = x/expt(10., expv);		/* between 1 and 10 */
    if ( round == true )
    if (f<1.5) nf = 1.;
    else if (f<3.) nf = 2.;
    else if (f<7.) nf = 5.;
    else nf = 10.;
    else
    if (f<=1.) nf = 1.;
    else if (f<=2.) nf = 2.;
    else if (f<=5.) nf = 5.;
    else nf = 10.;

    return ( nf*expt(10., expv) );
}
