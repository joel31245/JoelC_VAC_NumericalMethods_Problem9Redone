#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 200 // Set too high in case you want a system higher than the 6 specified
#define del 1
#define h .01
#define M (1/h)

void tridiagonal( float a[N], float b[N], float c[N], float f[N], int endV );
float error( float u10, float u0, float u01, float a, float b, float c, float f, int endV);
void helmtridiagonal( float a, float b, float c, int endV );

int main()
{
    int unknowns=0;
    float a[N], b[N], c[N], f[N];


    /// 9.1 Problems
    printf(" ---------- 9.1 Problems ----------\n");

    /* Problem 1 */
    printf(" Problem 1: \n");
    // STEP A: Set up the arrays of problem 1
    unknowns = 4;
    a[0] = 2.04; a[1]=2.04; a[2]=2.04; a[3]=2.04;
    b[1] = -1; b[2]=-1; b[3]=-1;
    c[0] = -1; c[1]=-1; c[2]=-1;
    f[0] = 40.8; f[1]=.8; f[2]=.8; f[3]=200.8;
    // STEP B: Tridiagonal and printing
    tridiagonal( a, b, c, f, unknowns);

    /* Problem 2 */
    printf(" Problem 2: \n");
    // STEP A: Set up the arrays of problem 1
    unknowns = 6;
    a[0] = -3.48; a[1]=2.48; a[2]=1.48; a[3]=1.48; a[4]=2.48; a[5]=3.48;
    b[1] = -.49; b[2]=-.49; b[3]=-.99; b[4]=-1.99; b[5]=-2.99;
    c[0] = -2.99; c[1]=-1.99; c[2]=-.99; c[3]=-.99; c[4]=-.49;
    f[0] = 1; f[1]=2; f[2]=3; f[3]=4; f[4]=5; f[5]=8;
    // STEP B: Tridiagonal and printing
    tridiagonal( a, b, c, f, unknowns);

    /* Problem 3 */
    // Problem 3 is to remain the same. Please see the other Numerical Methods repository for Problem 3
    printf("\n\nProblem 3 is to remain the same. Please see the other Numerical Methods repository for Problem 3\n");




    return 0;
}

void tridiagonal( float a[N], float b[N], float c[N], float f[N], int endV ){
    int i = 0; // i stands for Loop Counter
    float u[N], alpha[N], g[N];

    // STEP A: Forward Step through calculates alphas and gs (cannot overwrite due to error calculations requiring original a and f)
    alpha[0] = a[0];
    g[0] = f[0];
    for( i=1; i<endV; i++ ){
        alpha[i] = a[i] - ( b[i]/alpha[i-1] )*c[i-1];
        g[i] = f[i] - ( b[i]/a[i-1] )*g[i-1];
    }

    // STEP B: Backwards steps through and sets each unknown based on alphas and gs (cannot overwrite due to error calculations requiring original a and f)
    u[endV-1] = g[endV-1]/a[endV-1];
    for( i=endV-2; i>-1; i-- ){
        u[i] = ( g[i]-c[i]*u[i+1] )/alpha[i];
    }

    // STEP C: Prints the array to the command line
    puts("\tU\t\tError (%)");
    for( i=0; i<endV; i++ ){
        if ( i!=0 ) printf("u(%d) = %lf\t%lf\n", i+1,u[i],  error(u[i-1],u[i],u[i+1],a[i],b[i],c[i],f[i],endV)*100  );
        else printf("u(%d) = %lf\t\n", i+1,u[i]  );
    }
    printf("\n\n");
}

/// FUNCTION does the error calculation for Problems 1 and 2. Actual Value of Error may be incorrect. This calculation is directly from the NOTES though and is what we were instructed to use.
float error( float u10, float u0, float u01, float a, float b, float c, float f, int endV){
    float error;
    error = fabs( b*u10 + a*u0 + c*u01 - f);
    error = error/(  fabs(b*u10) + fabs(a*u0) + fabs(c*u01) + fabs(f) );
    return error;
}
