/*
 * Alex Baker
 * alexebaker
 * 101372834
 *
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */


#include <stdio.h>
#include "cachelab.h"


int is_transpose(int M, int N, int A[N][M], int B[M][N]);

void trans(int M, int N, int A[N][M], int B[M][N]);
void transpose_z_curve(int M, int N, int A[N][M], int B[M][N]);
void transpose_hilbert_curve(int M, int N, int A[N][M], int B [M][N]);


/*
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded.
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    transpose_z_curve(M, N, A, B);
    return;
}


/*
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started.
 */


char transpose_z_curve_desc[] = "Transpose using Z-curve";
void transpose_z_curve(int M, int N, int A[N][M], int B[M][N])
{
    /* Use Z-order curve to traverse the matrix */

    unsigned int row = 0;
    unsigned int col = 0;
    unsigned int shift = 0;
    unsigned int shift_limit = sizeof(int) * 8;
    unsigned int z_value = 0;
    unsigned int z_limit = M > N ? M*M : N*N;
    for (z_value = 0; z_value < z_limit; z_value++)
    {
        row = 0;
        col = 0;
        for (shift = 0; shift < shift_limit; shift += 2)
        {
            row |= ((z_value & (2<<shift)) >> ((shift/2)+1));
            col |= ((z_value & (1<<shift)) >> (shift/2));
        }
        if ((row < N) && (col < M)) B[col][row] = A[row][col];
    }
    return;
}


char transpose_hilbert_curve_desc[] = "Transpose using a hilbert curve";
void transpose_hilbert_curve(int M, int N, int A[N][M], int B[M][N])
{
    /* Use a hilbert curve to traverse the matrix */
    return;
}


/*
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }
}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc);

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc);
}

/*
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}
