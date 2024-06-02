#include <stdio.h>
#include <math.h>
#include <string.h>
int main(void)
{
    char codeword[50] = "x011001011011"; // 1 bit error present
    // no of redundant bits(value of r)
    int r = 0;
    while (pow(2, r) <= strlen(codeword))
    {
        r++;
    }
    int t = 0;
    for (int i = 1; i <= strlen(codeword); i++)
    {
        if (i != pow(2, t))
        {
            /* code */
        }
        t++;
    }
    int dlen = strlen(codeword);
    // printf("dlen: %d\n", dlen);
    char parityCheck[10];
    int h = 0; // new parity indexing
    for (int i = 0; i < r; i++)
    {
        int z = pow(2, i);
        int jump = z + 1;

        int xorSum = 0;
        int u = 0;
        for (int j = z; j <= dlen; j = j + jump + u)
        {
            int k = 0;
            while (k < z && k + j < dlen)
            {
                if (codeword[j + k] != 'x')
                {
                    xorSum += codeword[j + k] - 48;
                    // printf("%d ", j + k);
                }

                k++;
            }
            // printf("\n");
            u = k - 1;
        }
        parityCheck[h++] = xorSum % 2 + 48;
        // printf("%d\n", xorSum);
    }
    parityCheck[h] = '\0';
    printf("%s", parityCheck);
    return 0;
}