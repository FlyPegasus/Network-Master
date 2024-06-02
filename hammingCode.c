#include <stdio.h>
#include <string.h>
#include <math.h>
int main(void)
{
    char data[50];
    printf("Enter dataword: ");
    gets(data);
    int dlen = strlen(data);
    printf("Size of dataword: %d\n", dlen);
    int r = 0;
    while (dlen + r + 1 > pow(2, r))
    {
        r++;
    }
    printf("No of redundant bits required: %d\n", r);
    // create codeword structure
    char codeword[50];
    int t = 0; // power tracker of 2 for below while loop
    int j = 0;
    for (int i = 1; i <= dlen + r; i++)
    {
        if (i == pow(2, t))
        {
            codeword[i] = 'x';
            t++;
        }
        else
        {
            codeword[i] = data[j];
            j++;
        }
    }
    printf("Size of codeword: %d\n", strlen(codeword));
    printf("Codeword: %s\n", codeword);
    // placing parity bits and creating code word

    /*
    Outer for loop:
    there are 'r' parity bits that need to be calculated
    so running loop r times to calculate each bit
    */
    for (int i = 0; i < r; i++)
    {
        /*
        'z' will give the position of each parity bit in each iteration
        */
        int z = pow(2, i);
        // jump variable used to hop the gap
        // ex: 4 5 6 7 ...... 12 13 14 15 ..... in case of r = 2 i.e 2^2 = 4
        int jump = z + 1;

        int xorSum = 0;
        // parity bit calculation er jnno
        /*
       In this loop we calculate xorSum, so we need to get values where
       there is 2^r
       Thus starting from 'z' and jumping by (jump + u) u is the max k [try on copy]
       */
        int u = 0;
        for (int j = z; j <= dlen + r; j = j + jump + u)
        {
            int k = 0;
            while (k < z && k + j <= dlen + r)
            {
                if (codeword[j + k] != 'x')
                {
                    xorSum += codeword[j + k] - 48;
                }

                k++;
            }
            u = k - 1;
        }

        codeword[z] = xorSum % 2 + 48;
    }
    printf("Codeword: %s\n", codeword);

    return 0;
}