#include <stdio.h>
#include <stdlib.h>
#define ENTER 10
#define MAXKEY_LEN 100
#define MAXTEXT_LEN 1000

int mod(int a, int b)
{
	int r = a % b;
	if(r<=0 && a<=0) {
		if((~a+1)>b)
			return mod(a+b, b);
		return a+b;
	}
    return r;
}

int char_to_alph_no(char c)
{
	return ((c&(~32))-'A'+1);
}

int alph_no_to_char(char no)
{
	if(no == 0)
		return 'z';
	return 'a'-1+no;
}

char encrypt(char key, char data)
{
	return alph_no_to_char((mod(char_to_alph_no(data) + char_to_alph_no(key), 26)) + 1);
}

char decrypt(char key, char data)
{
	return alph_no_to_char((mod(char_to_alph_no(data) - char_to_alph_no(key), 26)) - 1);
}

int main()
{
    char key[MAXKEY_LEN];
    char plaintext[MAXTEXT_LEN];
    char ciphertext[MAXTEXT_LEN];
    char c, opt;
    int key_len = 0, pt_len = 0, ct_len = 0;
    int i = 0;
	int text_n, key_n;
    
    memset(key, 0, MAXKEY_LEN);
    memset(plaintext, 0, MAXTEXT_LEN);
    memset(ciphertext, 0, MAXTEXT_LEN);
    
    printf("key:");
    while((c=getchar()) != ENTER) {
        key[key_len] = c;
		key_len++;
    }
    
    printf("Is message plaintext:");
    scanf("%c", &opt);
    getchar();
    if (opt == 'y' || opt == 'Y') {
        printf("Plaintext:");
        while((c=getchar()) != ENTER) {
			if(c == ' ')continue;
            plaintext[pt_len++] = c;
			ciphertext[ct_len++] = encrypt(key[i++], c);
            if(i == key_len) {
                i = 0;
            }			
        }
        i=0;
        printf("Ciphertext: %s\n", ciphertext);
    } else if (opt == 'n' || opt == 'N') {
        printf("Ciphertext:");
        while((c=getchar()) != ENTER) {
			if(c == ' ')continue;
            ciphertext[ct_len++] = c;
			plaintext[pt_len++] = decrypt(key[i++], c);
            if(i == key_len) {
                i = 0;
            }
        }
        i=0;
        printf("Plaintext: %s\n", plaintext);
    }
    return 0;
}
