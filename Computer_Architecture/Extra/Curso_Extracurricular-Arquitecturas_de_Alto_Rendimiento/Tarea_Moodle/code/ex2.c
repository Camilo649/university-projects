#include <stdio.h>
#include <msa.h>

__attribute__((aligned(16))) double a[256], b[256], c[256], d[256];
__attribute__((aligned(16))) double three[] = {3.0,3.0};
__attribute__((aligned(16))) double five[] = {5.0,5.0};

int main()
{

int i,j;

// fake test image (red channel)
for (i=0; i<256; i++) {
    b[i] = c[i]= (double)(i)/10;
    d[i] = 0.0;
}

c[5] = 0.0;

//#define SIMD_VERSION

#ifdef MSA_VERSION
__asm volatile(
"		LD.D	$w7,0(%[Rthree])	\n"
"		LD.D	$w8,0(%[Rfive])		\n"
// YOUR CODE
"		LI      $4,0x100	        \n"
"       MOVE    $5,%[Ra]            \n"
"       MOVE    $6,%[Rb]            \n"
"       MOVE    $7,%[Rc]            \n"
"       MOVE    $8,%[Rd]            \n"
"		LI      $9,0x2	            \n"
"loop:  LD.D    $w1,0($6)           \n"
"       LD.D    $w2,0($7)           \n"
"       FADD.D  $w0,$w1,$w2         \n"
"       ST.D    $w0,0($5)           \n"
"       LD.D    $w4,0($8)           \n"
"       FCEQ.D  $w6,$w0,$w1         \n"
"       FMUL.D  $w5,$w0,$w7         \n"
"       BSEL.V  $w6,$w4,$w5         \n"
"       ST.D    $w6,0($8)           \n"
"       FSUB.D  $w0,$w0,$w8         \n"
"       ST.D    $w0,0($6)           \n"
"       SUB     $4,$4,$9            \n"
"       DADDIU  $5,$5,16            \n"
"		DADDIU  $6,$6,16	        \n"
"		DADDIU  $7,$7,16	        \n"
"		DADDIU  $8,$8,16	        \n"
"		BGTZ	$4,loop		        \n"
"		NOP							\n"
:
: [Ra] "r" (a),
  [Rb] "r" (b),
  [Rc] "r" (c),
  [Rd] "r" (d),
  [Rthree] "r" (three),
  [Rfive] "r" (five)
: "memory", "$4", "$5", "$6", "$7", "$8", "$9"
);
#else
for (i=0; i<256; i++) {
    a[i]=b[i]+c[i];
    if (a[i]==b[i])
       d[i]=a[i]*3;
    b[i]=a[i]-5;
}
#endif


// check output
for (i=0; i<256;i++) {
    printf(" a:%lf b:%lf c:%lf d:%lf\n",a[i],b[i],c[i],d[i]);
}

return 0;
}
