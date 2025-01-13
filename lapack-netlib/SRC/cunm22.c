#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <complex.h>
#ifdef complex
#undef complex
#endif
#ifdef I
#undef I
#endif

#if defined(_WIN64)
typedef long long BLASLONG;
typedef unsigned long long BLASULONG;
#else
typedef long BLASLONG;
typedef unsigned long BLASULONG;
#endif

#ifdef LAPACK_ILP64
typedef BLASLONG blasint;
#if defined(_WIN64)
#define blasabs(x) llabs(x)
#else
#define blasabs(x) labs(x)
#endif
#else
typedef int blasint;
#define blasabs(x) abs(x)
#endif

typedef blasint integer;

typedef unsigned int uinteger;
typedef char *address;
typedef short int shortint;
typedef float real;
typedef double doublereal;
typedef struct { real r, i; } complex;
typedef struct { doublereal r, i; } doublecomplex;
#ifdef _MSC_VER
static inline _Fcomplex Cf(complex *z) {_Fcomplex zz={z->r , z->i}; return zz;}
static inline _Dcomplex Cd(doublecomplex *z) {_Dcomplex zz={z->r , z->i};return zz;}
static inline _Fcomplex * _pCf(complex *z) {return (_Fcomplex*)z;}
static inline _Dcomplex * _pCd(doublecomplex *z) {return (_Dcomplex*)z;}
#else
static inline _Complex float Cf(complex *z) {return z->r + z->i*_Complex_I;}
static inline _Complex double Cd(doublecomplex *z) {return z->r + z->i*_Complex_I;}
static inline _Complex float * _pCf(complex *z) {return (_Complex float*)z;}
static inline _Complex double * _pCd(doublecomplex *z) {return (_Complex double*)z;}
#endif
#define pCf(z) (*_pCf(z))
#define pCd(z) (*_pCd(z))
typedef blasint logical;

typedef char logical1;
typedef char integer1;

#define TRUE_ (1)
#define FALSE_ (0)

/* Extern is for use with -E */
#ifndef Extern
#define Extern extern
#endif

/* I/O stuff */

typedef int flag;
typedef int ftnlen;
typedef int ftnint;

/*external read, write*/
typedef struct
{	flag cierr;
	ftnint ciunit;
	flag ciend;
	char *cifmt;
	ftnint cirec;
} cilist;

/*internal read, write*/
typedef struct
{	flag icierr;
	char *iciunit;
	flag iciend;
	char *icifmt;
	ftnint icirlen;
	ftnint icirnum;
} icilist;

/*open*/
typedef struct
{	flag oerr;
	ftnint ounit;
	char *ofnm;
	ftnlen ofnmlen;
	char *osta;
	char *oacc;
	char *ofm;
	ftnint orl;
	char *oblnk;
} olist;

/*close*/
typedef struct
{	flag cerr;
	ftnint cunit;
	char *csta;
} cllist;

/*rewind, backspace, endfile*/
typedef struct
{	flag aerr;
	ftnint aunit;
} alist;

/* inquire */
typedef struct
{	flag inerr;
	ftnint inunit;
	char *infile;
	ftnlen infilen;
	ftnint	*inex;	/*parameters in standard's order*/
	ftnint	*inopen;
	ftnint	*innum;
	ftnint	*innamed;
	char	*inname;
	ftnlen	innamlen;
	char	*inacc;
	ftnlen	inacclen;
	char	*inseq;
	ftnlen	inseqlen;
	char 	*indir;
	ftnlen	indirlen;
	char	*infmt;
	ftnlen	infmtlen;
	char	*inform;
	ftnint	informlen;
	char	*inunf;
	ftnlen	inunflen;
	ftnint	*inrecl;
	ftnint	*innrec;
	char	*inblank;
	ftnlen	inblanklen;
} inlist;

#define VOID void

union Multitype {	/* for multiple entry points */
	integer1 g;
	shortint h;
	integer i;
	/* longint j; */
	real r;
	doublereal d;
	complex c;
	doublecomplex z;
	};

typedef union Multitype Multitype;

struct Vardesc {	/* for Namelist */
	char *name;
	char *addr;
	ftnlen *dims;
	int  type;
	};
typedef struct Vardesc Vardesc;

struct Namelist {
	char *name;
	Vardesc **vars;
	int nvars;
	};
typedef struct Namelist Namelist;

#define abs(x) ((x) >= 0 ? (x) : -(x))
#define dabs(x) (fabs(x))
#define f2cmin(a,b) ((a) <= (b) ? (a) : (b))
#define f2cmax(a,b) ((a) >= (b) ? (a) : (b))
#define dmin(a,b) (f2cmin(a,b))
#define dmax(a,b) (f2cmax(a,b))
#define bit_test(a,b)	((a) >> (b) & 1)
#define bit_clear(a,b)	((a) & ~((uinteger)1 << (b)))
#define bit_set(a,b)	((a) |  ((uinteger)1 << (b)))

#define abort_() { sig_die("Fortran abort routine called", 1); }
#define c_abs(z) (cabsf(Cf(z)))
#define c_cos(R,Z) { pCf(R)=ccos(Cf(Z)); }
#ifdef _MSC_VER
#define c_div(c, a, b) {Cf(c)._Val[0] = (Cf(a)._Val[0]/Cf(b)._Val[0]); Cf(c)._Val[1]=(Cf(a)._Val[1]/Cf(b)._Val[1]);}
#define z_div(c, a, b) {Cd(c)._Val[0] = (Cd(a)._Val[0]/Cd(b)._Val[0]); Cd(c)._Val[1]=(Cd(a)._Val[1]/df(b)._Val[1]);}
#else
#define c_div(c, a, b) {pCf(c) = Cf(a)/Cf(b);}
#define z_div(c, a, b) {pCd(c) = Cd(a)/Cd(b);}
#endif
#define c_exp(R, Z) {pCf(R) = cexpf(Cf(Z));}
#define c_log(R, Z) {pCf(R) = clogf(Cf(Z));}
#define c_sin(R, Z) {pCf(R) = csinf(Cf(Z));}
//#define c_sqrt(R, Z) {*(R) = csqrtf(Cf(Z));}
#define c_sqrt(R, Z) {pCf(R) = csqrtf(Cf(Z));}
#define d_abs(x) (fabs(*(x)))
#define d_acos(x) (acos(*(x)))
#define d_asin(x) (asin(*(x)))
#define d_atan(x) (atan(*(x)))
#define d_atn2(x, y) (atan2(*(x),*(y)))
#define d_cnjg(R, Z) { pCd(R) = conj(Cd(Z)); }
#define r_cnjg(R, Z) { pCf(R) = conjf(Cf(Z)); }
#define d_cos(x) (cos(*(x)))
#define d_cosh(x) (cosh(*(x)))
#define d_dim(__a, __b) ( *(__a) > *(__b) ? *(__a) - *(__b) : 0.0 )
#define d_exp(x) (exp(*(x)))
#define d_imag(z) (cimag(Cd(z)))
#define r_imag(z) (cimagf(Cf(z)))
#define d_int(__x) (*(__x)>0 ? floor(*(__x)) : -floor(- *(__x)))
#define r_int(__x) (*(__x)>0 ? floor(*(__x)) : -floor(- *(__x)))
#define d_lg10(x) ( 0.43429448190325182765 * log(*(x)) )
#define r_lg10(x) ( 0.43429448190325182765 * log(*(x)) )
#define d_log(x) (log(*(x)))
#define d_mod(x, y) (fmod(*(x), *(y)))
#define u_nint(__x) ((__x)>=0 ? floor((__x) + .5) : -floor(.5 - (__x)))
#define d_nint(x) u_nint(*(x))
#define u_sign(__a,__b) ((__b) >= 0 ? ((__a) >= 0 ? (__a) : -(__a)) : -((__a) >= 0 ? (__a) : -(__a)))
#define d_sign(a,b) u_sign(*(a),*(b))
#define r_sign(a,b) u_sign(*(a),*(b))
#define d_sin(x) (sin(*(x)))
#define d_sinh(x) (sinh(*(x)))
#define d_sqrt(x) (sqrt(*(x)))
#define d_tan(x) (tan(*(x)))
#define d_tanh(x) (tanh(*(x)))
#define i_abs(x) abs(*(x))
#define i_dnnt(x) ((integer)u_nint(*(x)))
#define i_len(s, n) (n)
#define i_nint(x) ((integer)u_nint(*(x)))
#define i_sign(a,b) ((integer)u_sign((integer)*(a),(integer)*(b)))
#define pow_dd(ap, bp) ( pow(*(ap), *(bp)))
#define pow_si(B,E) spow_ui(*(B),*(E))
#define pow_ri(B,E) spow_ui(*(B),*(E))
#define pow_di(B,E) dpow_ui(*(B),*(E))
#define pow_zi(p, a, b) {pCd(p) = zpow_ui(Cd(a), *(b));}
#define pow_ci(p, a, b) {pCf(p) = cpow_ui(Cf(a), *(b));}
#define pow_zz(R,A,B) {pCd(R) = cpow(Cd(A),*(B));}
#define s_cat(lpp, rpp, rnp, np, llp) { 	ftnlen i, nc, ll; char *f__rp, *lp; 	ll = (llp); lp = (lpp); 	for(i=0; i < (int)*(np); ++i) {         	nc = ll; 	        if((rnp)[i] < nc) nc = (rnp)[i]; 	        ll -= nc;         	f__rp = (rpp)[i]; 	        while(--nc >= 0) *lp++ = *(f__rp)++;         } 	while(--ll >= 0) *lp++ = ' '; }
#define s_cmp(a,b,c,d) ((integer)strncmp((a),(b),f2cmin((c),(d))))
#define s_copy(A,B,C,D) { int __i,__m; for (__i=0, __m=f2cmin((C),(D)); __i<__m && (B)[__i] != 0; ++__i) (A)[__i] = (B)[__i]; }
#define sig_die(s, kill) { exit(1); }
#define s_stop(s, n) {exit(0);}
static char junk[] = "\n@(#)LIBF77 VERSION 19990503\n";
#define z_abs(z) (cabs(Cd(z)))
#define z_exp(R, Z) {pCd(R) = cexp(Cd(Z));}
#define z_sqrt(R, Z) {pCd(R) = csqrt(Cd(Z));}
#define myexit_() break;
#define mycycle() continue;
#define myceiling(w) {ceil(w)}
#define myhuge(w) {HUGE_VAL}
//#define mymaxloc_(w,s,e,n) {if (sizeof(*(w)) == sizeof(double)) dmaxloc_((w),*(s),*(e),n); else dmaxloc_((w),*(s),*(e),n);}
#define mymaxloc(w,s,e,n) {dmaxloc_(w,*(s),*(e),n)}

/* procedure parameter types for -A and -C++ */


#ifdef __cplusplus
typedef logical (*L_fp)(...);
#else
typedef logical (*L_fp)();
#endif

static float spow_ui(float x, integer n) {
	float pow=1.0; unsigned long int u;
	if(n != 0) {
		if(n < 0) n = -n, x = 1/x;
		for(u = n; ; ) {
			if(u & 01) pow *= x;
			if(u >>= 1) x *= x;
			else break;
		}
	}
	return pow;
}
static double dpow_ui(double x, integer n) {
	double pow=1.0; unsigned long int u;
	if(n != 0) {
		if(n < 0) n = -n, x = 1/x;
		for(u = n; ; ) {
			if(u & 01) pow *= x;
			if(u >>= 1) x *= x;
			else break;
		}
	}
	return pow;
}
#ifdef _MSC_VER
static _Fcomplex cpow_ui(complex x, integer n) {
	complex pow={1.0,0.0}; unsigned long int u;
		if(n != 0) {
		if(n < 0) n = -n, x.r = 1/x.r, x.i=1/x.i;
		for(u = n; ; ) {
			if(u & 01) pow.r *= x.r, pow.i *= x.i;
			if(u >>= 1) x.r *= x.r, x.i *= x.i;
			else break;
		}
	}
	_Fcomplex p={pow.r, pow.i};
	return p;
}
#else
static _Complex float cpow_ui(_Complex float x, integer n) {
	_Complex float pow=1.0; unsigned long int u;
	if(n != 0) {
		if(n < 0) n = -n, x = 1/x;
		for(u = n; ; ) {
			if(u & 01) pow *= x;
			if(u >>= 1) x *= x;
			else break;
		}
	}
	return pow;
}
#endif
#ifdef _MSC_VER
static _Dcomplex zpow_ui(_Dcomplex x, integer n) {
	_Dcomplex pow={1.0,0.0}; unsigned long int u;
	if(n != 0) {
		if(n < 0) n = -n, x._Val[0] = 1/x._Val[0], x._Val[1] =1/x._Val[1];
		for(u = n; ; ) {
			if(u & 01) pow._Val[0] *= x._Val[0], pow._Val[1] *= x._Val[1];
			if(u >>= 1) x._Val[0] *= x._Val[0], x._Val[1] *= x._Val[1];
			else break;
		}
	}
	_Dcomplex p = {pow._Val[0], pow._Val[1]};
	return p;
}
#else
static _Complex double zpow_ui(_Complex double x, integer n) {
	_Complex double pow=1.0; unsigned long int u;
	if(n != 0) {
		if(n < 0) n = -n, x = 1/x;
		for(u = n; ; ) {
			if(u & 01) pow *= x;
			if(u >>= 1) x *= x;
			else break;
		}
	}
	return pow;
}
#endif
static integer pow_ii(integer x, integer n) {
	integer pow; unsigned long int u;
	if (n <= 0) {
		if (n == 0 || x == 1) pow = 1;
		else if (x != -1) pow = x == 0 ? 1/x : 0;
		else n = -n;
	}
	if ((n > 0) || !(n == 0 || x == 1 || x != -1)) {
		u = n;
		for(pow = 1; ; ) {
			if(u & 01) pow *= x;
			if(u >>= 1) x *= x;
			else break;
		}
	}
	return pow;
}
static integer dmaxloc_(double *w, integer s, integer e, integer *n)
{
	double m; integer i, mi;
	for(m=w[s-1], mi=s, i=s+1; i<=e; i++)
		if (w[i-1]>m) mi=i ,m=w[i-1];
	return mi-s+1;
}
static integer smaxloc_(float *w, integer s, integer e, integer *n)
{
	float m; integer i, mi;
	for(m=w[s-1], mi=s, i=s+1; i<=e; i++)
		if (w[i-1]>m) mi=i ,m=w[i-1];
	return mi-s+1;
}
static inline void cdotc_(complex *z, integer *n_, complex *x, integer *incx_, complex *y, integer *incy_) {
	integer n = *n_, incx = *incx_, incy = *incy_, i;
#ifdef _MSC_VER
	_Fcomplex zdotc = {0.0, 0.0};
	if (incx == 1 && incy == 1) {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc._Val[0] += conjf(Cf(&x[i]))._Val[0] * Cf(&y[i])._Val[0];
			zdotc._Val[1] += conjf(Cf(&x[i]))._Val[1] * Cf(&y[i])._Val[1];
		}
	} else {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc._Val[0] += conjf(Cf(&x[i*incx]))._Val[0] * Cf(&y[i*incy])._Val[0];
			zdotc._Val[1] += conjf(Cf(&x[i*incx]))._Val[1] * Cf(&y[i*incy])._Val[1];
		}
	}
	pCf(z) = zdotc;
}
#else
	_Complex float zdotc = 0.0;
	if (incx == 1 && incy == 1) {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc += conjf(Cf(&x[i])) * Cf(&y[i]);
		}
	} else {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc += conjf(Cf(&x[i*incx])) * Cf(&y[i*incy]);
		}
	}
	pCf(z) = zdotc;
}
#endif
static inline void zdotc_(doublecomplex *z, integer *n_, doublecomplex *x, integer *incx_, doublecomplex *y, integer *incy_) {
	integer n = *n_, incx = *incx_, incy = *incy_, i;
#ifdef _MSC_VER
	_Dcomplex zdotc = {0.0, 0.0};
	if (incx == 1 && incy == 1) {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc._Val[0] += conj(Cd(&x[i]))._Val[0] * Cd(&y[i])._Val[0];
			zdotc._Val[1] += conj(Cd(&x[i]))._Val[1] * Cd(&y[i])._Val[1];
		}
	} else {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc._Val[0] += conj(Cd(&x[i*incx]))._Val[0] * Cd(&y[i*incy])._Val[0];
			zdotc._Val[1] += conj(Cd(&x[i*incx]))._Val[1] * Cd(&y[i*incy])._Val[1];
		}
	}
	pCd(z) = zdotc;
}
#else
	_Complex double zdotc = 0.0;
	if (incx == 1 && incy == 1) {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc += conj(Cd(&x[i])) * Cd(&y[i]);
		}
	} else {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc += conj(Cd(&x[i*incx])) * Cd(&y[i*incy]);
		}
	}
	pCd(z) = zdotc;
}
#endif	
static inline void cdotu_(complex *z, integer *n_, complex *x, integer *incx_, complex *y, integer *incy_) {
	integer n = *n_, incx = *incx_, incy = *incy_, i;
#ifdef _MSC_VER
	_Fcomplex zdotc = {0.0, 0.0};
	if (incx == 1 && incy == 1) {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc._Val[0] += Cf(&x[i])._Val[0] * Cf(&y[i])._Val[0];
			zdotc._Val[1] += Cf(&x[i])._Val[1] * Cf(&y[i])._Val[1];
		}
	} else {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc._Val[0] += Cf(&x[i*incx])._Val[0] * Cf(&y[i*incy])._Val[0];
			zdotc._Val[1] += Cf(&x[i*incx])._Val[1] * Cf(&y[i*incy])._Val[1];
		}
	}
	pCf(z) = zdotc;
}
#else
	_Complex float zdotc = 0.0;
	if (incx == 1 && incy == 1) {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc += Cf(&x[i]) * Cf(&y[i]);
		}
	} else {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc += Cf(&x[i*incx]) * Cf(&y[i*incy]);
		}
	}
	pCf(z) = zdotc;
}
#endif
static inline void zdotu_(doublecomplex *z, integer *n_, doublecomplex *x, integer *incx_, doublecomplex *y, integer *incy_) {
	integer n = *n_, incx = *incx_, incy = *incy_, i;
#ifdef _MSC_VER
	_Dcomplex zdotc = {0.0, 0.0};
	if (incx == 1 && incy == 1) {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc._Val[0] += Cd(&x[i])._Val[0] * Cd(&y[i])._Val[0];
			zdotc._Val[1] += Cd(&x[i])._Val[1] * Cd(&y[i])._Val[1];
		}
	} else {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc._Val[0] += Cd(&x[i*incx])._Val[0] * Cd(&y[i*incy])._Val[0];
			zdotc._Val[1] += Cd(&x[i*incx])._Val[1] * Cd(&y[i*incy])._Val[1];
		}
	}
	pCd(z) = zdotc;
}
#else
	_Complex double zdotc = 0.0;
	if (incx == 1 && incy == 1) {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc += Cd(&x[i]) * Cd(&y[i]);
		}
	} else {
		for (i=0;i<n;i++) { /* zdotc = zdotc + dconjg(x(i))* y(i) */
			zdotc += Cd(&x[i*incx]) * Cd(&y[i*incy]);
		}
	}
	pCd(z) = zdotc;
}
#endif
/*  -- translated by f2c (version 20000121).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/




/* Table of constant values */

static complex c_b1 = {1.f,0.f};

/* > \brief \b CUNM22 multiplies a general matrix by a banded unitary matrix. */

/*  =========== DOCUMENTATION =========== */

/* Online html documentation available at */
/*            http://www.netlib.org/lapack/explore-html/ */

/* > \htmlonly */
/* > Download CUNM22 + dependencies */
/* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.tgz?format=tgz&filename=/lapack/lapack_routine/cunm22.
f"> */
/* > [TGZ]</a> */
/* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.zip?format=zip&filename=/lapack/lapack_routine/cunm22.
f"> */
/* > [ZIP]</a> */
/* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.txt?format=txt&filename=/lapack/lapack_routine/cunm22.
f"> */
/* > [TXT]</a> */
/* > \endhtmlonly */

/*  Definition: */
/*  =========== */

/*     SUBROUTINE CUNM22( SIDE, TRANS, M, N, N1, N2, Q, LDQ, C, LDC, */
/*    $                   WORK, LWORK, INFO ) */

/*     CHARACTER          SIDE, TRANS */
/*     INTEGER            M, N, N1, N2, LDQ, LDC, LWORK, INFO */
/*     COMPLEX            Q( LDQ, * ), C( LDC, * ), WORK( * ) */

/* > \par Purpose */
/*  ============ */
/* > */
/* > \verbatim */
/* > */
/* >  CUNM22 overwrites the general complex M-by-N matrix C with */
/* > */
/* >                  SIDE = 'L'     SIDE = 'R' */
/* >  TRANS = 'N':      Q * C          C * Q */
/* >  TRANS = 'C':      Q**H * C       C * Q**H */
/* > */
/* >  where Q is a complex unitary matrix of order NQ, with NQ = M if */
/* >  SIDE = 'L' and NQ = N if SIDE = 'R'. */
/* >  The unitary matrix Q processes a 2-by-2 block structure */
/* > */
/* >         [  Q11  Q12  ] */
/* >     Q = [            ] */
/* >         [  Q21  Q22  ], */
/* > */
/* >  where Q12 is an N1-by-N1 lower triangular matrix and Q21 is an */
/* >  N2-by-N2 upper triangular matrix. */
/* > \endverbatim */

/*  Arguments: */
/*  ========== */

/* > \param[in] SIDE */
/* > \verbatim */
/* >          SIDE is CHARACTER*1 */
/* >          = 'L': apply Q or Q**H from the Left; */
/* >          = 'R': apply Q or Q**H from the Right. */
/* > \endverbatim */
/* > */
/* > \param[in] TRANS */
/* > \verbatim */
/* >          TRANS is CHARACTER*1 */
/* >          = 'N':  apply Q (No transpose); */
/* >          = 'C':  apply Q**H (Conjugate transpose). */
/* > \endverbatim */
/* > */
/* > \param[in] M */
/* > \verbatim */
/* >          M is INTEGER */
/* >          The number of rows of the matrix C. M >= 0. */
/* > \endverbatim */
/* > */
/* > \param[in] N */
/* > \verbatim */
/* >          N is INTEGER */
/* >          The number of columns of the matrix C. N >= 0. */
/* > \endverbatim */
/* > */
/* > \param[in] N1 */
/* > \param[in] N2 */
/* > \verbatim */
/* >          N1 is INTEGER */
/* >          N2 is INTEGER */
/* >          The dimension of Q12 and Q21, respectively. N1, N2 >= 0. */
/* >          The following requirement must be satisfied: */
/* >          N1 + N2 = M if SIDE = 'L' and N1 + N2 = N if SIDE = 'R'. */
/* > \endverbatim */
/* > */
/* > \param[in] Q */
/* > \verbatim */
/* >          Q is COMPLEX array, dimension */
/* >                              (LDQ,M) if SIDE = 'L' */
/* >                              (LDQ,N) if SIDE = 'R' */
/* > \endverbatim */
/* > */
/* > \param[in] LDQ */
/* > \verbatim */
/* >          LDQ is INTEGER */
/* >          The leading dimension of the array Q. */
/* >          LDQ >= f2cmax(1,M) if SIDE = 'L'; LDQ >= f2cmax(1,N) if SIDE = 'R'. */
/* > \endverbatim */
/* > */
/* > \param[in,out] C */
/* > \verbatim */
/* >          C is COMPLEX array, dimension (LDC,N) */
/* >          On entry, the M-by-N matrix C. */
/* >          On exit, C is overwritten by Q*C or Q**H*C or C*Q**H or C*Q. */
/* > \endverbatim */
/* > */
/* > \param[in] LDC */
/* > \verbatim */
/* >          LDC is INTEGER */
/* >          The leading dimension of the array C. LDC >= f2cmax(1,M). */
/* > \endverbatim */
/* > */
/* > \param[out] WORK */
/* > \verbatim */
/* >          WORK is COMPLEX array, dimension (MAX(1,LWORK)) */
/* >          On exit, if INFO = 0, WORK(1) returns the optimal LWORK. */
/* > \endverbatim */
/* > */
/* > \param[in] LWORK */
/* > \verbatim */
/* >          LWORK is INTEGER */
/* >          The dimension of the array WORK. */
/* >          If SIDE = 'L', LWORK >= f2cmax(1,N); */
/* >          if SIDE = 'R', LWORK >= f2cmax(1,M). */
/* >          For optimum performance LWORK >= M*N. */
/* > */
/* >          If LWORK = -1, then a workspace query is assumed; the routine */
/* >          only calculates the optimal size of the WORK array, returns */
/* >          this value as the first entry of the WORK array, and no error */
/* >          message related to LWORK is issued by XERBLA. */
/* > \endverbatim */
/* > */
/* > \param[out] INFO */
/* > \verbatim */
/* >          INFO is INTEGER */
/* >          = 0:  successful exit */
/* >          < 0:  if INFO = -i, the i-th argument had an illegal value */
/* > \endverbatim */


/*  Authors: */
/*  ======== */

/* > \author Univ. of Tennessee */
/* > \author Univ. of California Berkeley */
/* > \author Univ. of Colorado Denver */
/* > \author NAG Ltd. */

/* > \date January 2015 */

/* > \ingroup complexOTHERcomputational */

/*  ===================================================================== */
/* Subroutine */ void cunm22_(char *side, char *trans, integer *m, integer *n, 
	integer *n1, integer *n2, complex *q, integer *ldq, complex *c__, 
	integer *ldc, complex *work, integer *lwork, integer *info)
{
    /* System generated locals */
    integer q_dim1, q_offset, c_dim1, c_offset, i__1, i__2, i__3, i__4;
    complex q__1;

    /* Local variables */
    logical left;
    integer i__;
    extern /* Subroutine */ void cgemm_(char *, char *, integer *, integer *, 
	    integer *, complex *, complex *, integer *, complex *, integer *, 
	    complex *, complex *, integer *);
    extern logical lsame_(char *, char *);
    extern /* Subroutine */ void ctrmm_(char *, char *, char *, char *, 
	    integer *, integer *, complex *, complex *, integer *, complex *, 
	    integer *);
    integer nb, nq, nw;
    extern /* Subroutine */ void clacpy_(char *, integer *, integer *, complex 
	    *, integer *, complex *, integer *);
    extern int xerbla_(char *, integer *, ftnlen);
    logical notran;
    integer ldwork, lwkopt;
    logical lquery;
    integer len;


/*  -- LAPACK computational routine (version 3.7.1) -- */
/*  -- LAPACK is a software package provided by Univ. of Tennessee,    -- */
/*  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..-- */
/*     January 2015 */



/*  ===================================================================== */



/*     Test the input arguments */

    /* Parameter adjustments */
    q_dim1 = *ldq;
    q_offset = 1 + q_dim1 * 1;
    q -= q_offset;
    c_dim1 = *ldc;
    c_offset = 1 + c_dim1 * 1;
    c__ -= c_offset;
    --work;

    /* Function Body */
    *info = 0;
    left = lsame_(side, "L");
    notran = lsame_(trans, "N");
    lquery = *lwork == -1;

/*     NQ is the order of Q; */
/*     NW is the minimum dimension of WORK. */

    if (left) {
	nq = *m;
    } else {
	nq = *n;
    }
    nw = nq;
    if (*n1 == 0 || *n2 == 0) {
	nw = 1;
    }
    if (! left && ! lsame_(side, "R")) {
	*info = -1;
    } else if (! lsame_(trans, "N") && ! lsame_(trans, 
	    "C")) {
	*info = -2;
    } else if (*m < 0) {
	*info = -3;
    } else if (*n < 0) {
	*info = -4;
    } else if (*n1 < 0 || *n1 + *n2 != nq) {
	*info = -5;
    } else if (*n2 < 0) {
	*info = -6;
    } else if (*ldq < f2cmax(1,nq)) {
	*info = -8;
    } else if (*ldc < f2cmax(1,*m)) {
	*info = -10;
    } else if (*lwork < nw && ! lquery) {
	*info = -12;
    }

    if (*info == 0) {
	lwkopt = *m * *n;
	q__1.r = (real) lwkopt, q__1.i = 0.f;
	work[1].r = q__1.r, work[1].i = q__1.i;
    }

    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("CUNM22", &i__1, (ftnlen)6);
	return;
    } else if (lquery) {
	return;
    }

/*     Quick return if possible */

    if (*m == 0 || *n == 0) {
	work[1].r = 1.f, work[1].i = 0.f;
	return;
    }

/*     Degenerate cases (N1 = 0 or N2 = 0) are handled using CTRMM. */

    if (*n1 == 0) {
	ctrmm_(side, "Upper", trans, "Non-Unit", m, n, &c_b1, &q[q_offset], 
		ldq, &c__[c_offset], ldc);
	work[1].r = 1.f, work[1].i = 0.f;
	return;
    } else if (*n2 == 0) {
	ctrmm_(side, "Lower", trans, "Non-Unit", m, n, &c_b1, &q[q_offset], 
		ldq, &c__[c_offset], ldc);
	work[1].r = 1.f, work[1].i = 0.f;
	return;
    }

/*     Compute the largest chunk size available from the workspace. */

/* Computing MAX */
    i__1 = 1, i__2 = f2cmin(*lwork,lwkopt) / nq;
    nb = f2cmax(i__1,i__2);

    if (left) {
	if (notran) {
	    i__1 = *n;
	    i__2 = nb;
	    for (i__ = 1; i__2 < 0 ? i__ >= i__1 : i__ <= i__1; i__ += i__2) {
/* Computing MIN */
		i__3 = nb, i__4 = *n - i__ + 1;
		len = f2cmin(i__3,i__4);
		ldwork = *m;

/*              Multiply bottom part of C by Q12. */

		clacpy_("All", n1, &len, &c__[*n2 + 1 + i__ * c_dim1], ldc, &
			work[1], &ldwork);
		ctrmm_("Left", "Lower", "No Transpose", "Non-Unit", n1, &len, 
			&c_b1, &q[(*n2 + 1) * q_dim1 + 1], ldq, &work[1], &
			ldwork);

/*              Multiply top part of C by Q11. */

		cgemm_("No Transpose", "No Transpose", n1, &len, n2, &c_b1, &
			q[q_offset], ldq, &c__[i__ * c_dim1 + 1], ldc, &c_b1, 
			&work[1], &ldwork);

/*              Multiply top part of C by Q21. */

		clacpy_("All", n2, &len, &c__[i__ * c_dim1 + 1], ldc, &work[*
			n1 + 1], &ldwork);
		ctrmm_("Left", "Upper", "No Transpose", "Non-Unit", n2, &len, 
			&c_b1, &q[*n1 + 1 + q_dim1], ldq, &work[*n1 + 1], &
			ldwork);

/*              Multiply bottom part of C by Q22. */

		cgemm_("No Transpose", "No Transpose", n2, &len, n1, &c_b1, &
			q[*n1 + 1 + (*n2 + 1) * q_dim1], ldq, &c__[*n2 + 1 + 
			i__ * c_dim1], ldc, &c_b1, &work[*n1 + 1], &ldwork);

/*              Copy everything back. */

		clacpy_("All", m, &len, &work[1], &ldwork, &c__[i__ * c_dim1 
			+ 1], ldc);
	    }
	} else {
	    i__2 = *n;
	    i__1 = nb;
	    for (i__ = 1; i__1 < 0 ? i__ >= i__2 : i__ <= i__2; i__ += i__1) {
/* Computing MIN */
		i__3 = nb, i__4 = *n - i__ + 1;
		len = f2cmin(i__3,i__4);
		ldwork = *m;

/*              Multiply bottom part of C by Q21**H. */

		clacpy_("All", n2, &len, &c__[*n1 + 1 + i__ * c_dim1], ldc, &
			work[1], &ldwork);
		ctrmm_("Left", "Upper", "Conjugate", "Non-Unit", n2, &len, &
			c_b1, &q[*n1 + 1 + q_dim1], ldq, &work[1], &ldwork);

/*              Multiply top part of C by Q11**H. */

		cgemm_("Conjugate", "No Transpose", n2, &len, n1, &c_b1, &q[
			q_offset], ldq, &c__[i__ * c_dim1 + 1], ldc, &c_b1, &
			work[1], &ldwork);

/*              Multiply top part of C by Q12**H. */

		clacpy_("All", n1, &len, &c__[i__ * c_dim1 + 1], ldc, &work[*
			n2 + 1], &ldwork);
		ctrmm_("Left", "Lower", "Conjugate", "Non-Unit", n1, &len, &
			c_b1, &q[(*n2 + 1) * q_dim1 + 1], ldq, &work[*n2 + 1],
			 &ldwork);

/*              Multiply bottom part of C by Q22**H. */

		cgemm_("Conjugate", "No Transpose", n1, &len, n2, &c_b1, &q[*
			n1 + 1 + (*n2 + 1) * q_dim1], ldq, &c__[*n1 + 1 + i__ 
			* c_dim1], ldc, &c_b1, &work[*n2 + 1], &ldwork);

/*              Copy everything back. */

		clacpy_("All", m, &len, &work[1], &ldwork, &c__[i__ * c_dim1 
			+ 1], ldc);
	    }
	}
    } else {
	if (notran) {
	    i__1 = *m;
	    i__2 = nb;
	    for (i__ = 1; i__2 < 0 ? i__ >= i__1 : i__ <= i__1; i__ += i__2) {
/* Computing MIN */
		i__3 = nb, i__4 = *m - i__ + 1;
		len = f2cmin(i__3,i__4);
		ldwork = len;

/*              Multiply right part of C by Q21. */

		clacpy_("All", &len, n2, &c__[i__ + (*n1 + 1) * c_dim1], ldc, 
			&work[1], &ldwork);
		ctrmm_("Right", "Upper", "No Transpose", "Non-Unit", &len, n2,
			 &c_b1, &q[*n1 + 1 + q_dim1], ldq, &work[1], &ldwork);

/*              Multiply left part of C by Q11. */

		cgemm_("No Transpose", "No Transpose", &len, n2, n1, &c_b1, &
			c__[i__ + c_dim1], ldc, &q[q_offset], ldq, &c_b1, &
			work[1], &ldwork);

/*              Multiply left part of C by Q12. */

		clacpy_("All", &len, n1, &c__[i__ + c_dim1], ldc, &work[*n2 * 
			ldwork + 1], &ldwork);
		ctrmm_("Right", "Lower", "No Transpose", "Non-Unit", &len, n1,
			 &c_b1, &q[(*n2 + 1) * q_dim1 + 1], ldq, &work[*n2 * 
			ldwork + 1], &ldwork);

/*              Multiply right part of C by Q22. */

		cgemm_("No Transpose", "No Transpose", &len, n1, n2, &c_b1, &
			c__[i__ + (*n1 + 1) * c_dim1], ldc, &q[*n1 + 1 + (*n2 
			+ 1) * q_dim1], ldq, &c_b1, &work[*n2 * ldwork + 1], &
			ldwork);

/*              Copy everything back. */

		clacpy_("All", &len, n, &work[1], &ldwork, &c__[i__ + c_dim1],
			 ldc);
	    }
	} else {
	    i__2 = *m;
	    i__1 = nb;
	    for (i__ = 1; i__1 < 0 ? i__ >= i__2 : i__ <= i__2; i__ += i__1) {
/* Computing MIN */
		i__3 = nb, i__4 = *m - i__ + 1;
		len = f2cmin(i__3,i__4);
		ldwork = len;

/*              Multiply right part of C by Q12**H. */

		clacpy_("All", &len, n1, &c__[i__ + (*n2 + 1) * c_dim1], ldc, 
			&work[1], &ldwork);
		ctrmm_("Right", "Lower", "Conjugate", "Non-Unit", &len, n1, &
			c_b1, &q[(*n2 + 1) * q_dim1 + 1], ldq, &work[1], &
			ldwork);

/*              Multiply left part of C by Q11**H. */

		cgemm_("No Transpose", "Conjugate", &len, n1, n2, &c_b1, &c__[
			i__ + c_dim1], ldc, &q[q_offset], ldq, &c_b1, &work[1]
			, &ldwork);

/*              Multiply left part of C by Q21**H. */

		clacpy_("All", &len, n2, &c__[i__ + c_dim1], ldc, &work[*n1 * 
			ldwork + 1], &ldwork);
		ctrmm_("Right", "Upper", "Conjugate", "Non-Unit", &len, n2, &
			c_b1, &q[*n1 + 1 + q_dim1], ldq, &work[*n1 * ldwork + 
			1], &ldwork);

/*              Multiply right part of C by Q22**H. */

		cgemm_("No Transpose", "Conjugate", &len, n2, n1, &c_b1, &c__[
			i__ + (*n2 + 1) * c_dim1], ldc, &q[*n1 + 1 + (*n2 + 1)
			 * q_dim1], ldq, &c_b1, &work[*n1 * ldwork + 1], &
			ldwork);

/*              Copy everything back. */

		clacpy_("All", &len, n, &work[1], &ldwork, &c__[i__ + c_dim1],
			 ldc);
	    }
	}
    }

    q__1.r = (real) lwkopt, q__1.i = 0.f;
    work[1].r = q__1.r, work[1].i = q__1.i;
    return;

/*     End of CUNM22 */

} /* cunm22_ */

