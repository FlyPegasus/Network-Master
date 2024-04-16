#include<stdio.h>
#include<string.h>
int main(void){
    char word[50];
    char zero[50];
    char divisor[50];
    char codeword[50];
    printf("Enter word: ");
    gets(word);
    printf("Enter divisor: ");
    gets(divisor);
    int zeroPad = strlen(divisor);
    printf("pad zero: %d\n", zeroPad);

    //pad zeroes to the end
    for (int i = 0; i < zeroPad-1; i++)
    {
        zero[i] = '0';
    }
    //codeword
    strcat(word, zero);
    
    char dividend[50];
    strcpy(dividend, word);
    printf("dividend: %s\n", dividend);
    //now performing crc
    int dividendLen = strlen(word);
    // bit containers
    int bit1, bit2;
    // i is the pointer
    int i = 0,j;
    while (i < dividendLen - strlen(divisor))
    {
        if(word[i] == '1'){
            for(j =0; j < strlen(divisor); j++){
                bit1 = word[i+j] - 48;
                bit2 = divisor[j] - 48;
                //printf("bit1: %d bit2: %d, div: %c word: %c\n", bit1, bit2, divisor[j], word[i+j]);
                word[i+j] = bit1^bit2 + 48;
            }
        }
        if (word[i] == '0') // increment pointer only if bit at i is 0 else perform xor sum again
        {
            i++;
        }
        
    }
    // Append the CRC bits to get the code word: can do by dividend + word
    for(int i = strlen(dividend) - zeroPad + 1; i < strlen(dividend); i++){
        int n = (word[i] - 48) + (dividend[i] - 48);
        dividend[i] = n + 48;
    }
    
    strcpy(codeword, dividend);
    printf("codeword: %s\n", codeword);
    
    
    return 0;
}
