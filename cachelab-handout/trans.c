/*
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

/*
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded.
 */

/*
学号：21302010042
姓名：侯斌洋
*/

char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    // M==32,N==32
    if (M == 32 && N == 32)
    {
        //共11个变量
        int i, j, k;
        int temp0, temp1, temp2, temp3, temp4, temp5, temp6, temp7;

        //进行分块处理，分成8×8的块
        //这里为了处理对角线上的8×8块A和B数组同时占用缓存导致大量不命中的情况
        //故一次读取A中的一行8个数据并存入临时变量中，这样A每块只有一次冷不命中
        //而B对角线上的块部分有两次不命中，其他位置的块也是只有一次冷不命中，已达到要求
        for (i = 0; i < 32; i += 8)
        {
            for (j = 0; j < 32; j += 8)
            {
                for (k = i; k < i + 8; k++)
                {
                    temp0 = A[k][j];
                    temp1 = A[k][j + 1];
                    temp2 = A[k][j + 2];
                    temp3 = A[k][j + 3];
                    temp4 = A[k][j + 4];
                    temp5 = A[k][j + 5];
                    temp6 = A[k][j + 6];
                    temp7 = A[k][j + 7];

                    B[j][k] = temp0;
                    B[j + 1][k] = temp1;
                    B[j + 2][k] = temp2;
                    B[j + 3][k] = temp3;
                    B[j + 4][k] = temp4;
                    B[j + 5][k] = temp5;
                    B[j + 6][k] = temp6;
                    B[j + 7][k] = temp7;
                }
            }
        }
    }

    // M==64,N==64
    if (M == 64 && N == 64)
    {
        //共11个变量
        int temp0, temp1, temp2, temp3, temp4, temp5, temp6, temp7;
        int i, j, k;

        //这里也是尝试分块，8×8的块miss太多，不可行
        //4×4的分块虽然减少了很多miss，但仍达不到要求
        //经分析得4×4的块每次读取只利用了cache的一半空间，
        //故从此方面入手，考虑分成8×8的块以充分利用缓存
        //空间，但在块内部用4×4的方法处理以减少miss
        //下面是一种方案
        for (i = 0; i < 64; i += 8)
        {
            for (j = 0; j < 64; j += 8)
            {
                //读取8×8的块中的前四行
                for (k = i; k < i + 4; k++)
                {
                    //将A中一整行8个数据存入临时变量中
                    temp0 = A[k][j];
                    temp1 = A[k][j + 1];
                    temp2 = A[k][j + 2];
                    temp3 = A[k][j + 3];
                    temp4 = A[k][j + 4];
                    temp5 = A[k][j + 5];
                    temp6 = A[k][j + 6];
                    temp7 = A[k][j + 7];

                    //将上面A的一行中前四个数据存放在B中正确的位置
                    B[j][k] = temp0;
                    B[j + 1][k] = temp1;
                    B[j + 2][k] = temp2;
                    B[j + 3][k] = temp3;

                    //A的后四个数据暂时存放在B在cache中的其余空闲位置
                    B[j][k + 4] = temp4;
                    B[j + 1][k + 4] = temp5;
                    B[j + 2][k + 4] = temp6;
                    B[j + 3][k + 4] = temp7;
                }

                //读取A中后四行的前四列
                for (k = j; k < j + 4; k++)
                {
                    //读取A后四行的一列4个数据
                    temp0 = A[i + 4][k];
                    temp1 = A[i + 5][k];
                    temp2 = A[i + 6][k];
                    temp3 = A[i + 7][k];

                    //读取之前存放在B的空闲位置的数据
                    temp4 = B[k][i + 4];
                    temp5 = B[k][i + 5];
                    temp6 = B[k][i + 6];
                    temp7 = B[k][i + 7];

                    //将上述A的后四行的一列数据放入正确的位置
                    B[k][i + 4] = temp0;
                    B[k][i + 5] = temp1;
                    B[k][i + 6] = temp2;
                    B[k][i + 7] = temp3;

                    //将之前存放在B的空闲位置的数据存放在B的正确的位置
                    B[k + 4][i] = temp4;
                    B[k + 4][i + 1] = temp5;
                    B[k + 4][i + 2] = temp6;
                    B[k + 4][i + 3] = temp7;
                }

                //读取A中后四行的后四列
                //并直接将其放到B中的正确位置
                for (k = i + 4; k < i + 8; k++)
                { 
                    temp0 = A[k][j + 4];
                    temp1 = A[k][j + 5];
                    temp2 = A[k][j + 6];
                    temp3 = A[k][j + 7];

                    B[j + 4][k] = temp0;
                    B[j + 5][k] = temp1;
                    B[j + 6][k] = temp2;
                    B[j + 7][k] = temp3;
                }
            }
        }
    }

    // M==62,N==67
    if (M == 61 && N == 67)
    {
        //共4个变量
        int i, j, k, l;

        //直接进行分块处理，分成17×17的块便已达到要求
        for (i = 0; i < 61; i += 17)
        {
            for (j = 0; j < 67; j += 17)
            {
                for (k = i; k < 61 && k < i + 17; k++)
                {
                    for (l = j; l < 67 && l < j + 17; l++)
                    {
                        B[k][l] = A[l][k];
                    }
                }
            }
        }
    }
}

/*
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started.
 */

/*
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
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

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; ++j)
        {
            if (A[i][j] != B[j][i])
            {
                return 0;
            }
        }
    }
    return 1;
}
