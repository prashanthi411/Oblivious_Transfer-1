#include<stdio.h> 
#include<stdlib.h>
#include<gmp.h>
#include "rsa.h"
int main(){
	FILE *fptr, *fp1, *fp2, *fp3, *fp4;
	fptr = fopen("randomx.txt", "w"); //file to store randomly generated x_0, x_1
	fp1 = fopen("private_key.txt", "r"); //private key d is extracted from "private_key.txt"
	fp2 = fopen("bob_c.txt", "r"); //c, generated by Bob is extracted from "bob_c.txt" --> c = (x_b + k^e) mod n
	fp3 = fopen("strings.txt", "r"); //the two strings are read from "strings.txt"
	fp4 = fopen("enc_messages.txt", "w"); // to write m'_0 (= m_0 - v_0) and m'_1 (= m_1 - v_1) to "enc_messages.txt"
	mpz_t x_0, x_1, v_0, v_1, n, d, c, m_0, m_1;
	mpz_init(x_0);
	mpz_init(x_1);
	mpz_init(v_0);
	mpz_init(v_1);
	mpz_init(n);
	mpz_init(d);
	mpz_init(c);
	mpz_init(m_0);
	mpz_init(m_1);
	gmp_randstate_t state;
	gmp_randinit_mt(state);
	mpz_urandomb(x_0, state, 500); //generating random 500-bit x_0
	mpz_urandomb(x_1, state, 500); //generating random 500-bit x_1
	gmp_fprintf(fptr, "%Zd", x_0); //writing x_0 to file "randomx.txt"
	gmp_fprintf(fptr, "\n");
	gmp_fprintf(fptr, "%Zd", x_1); //writing x_1 to file "randomx.txt"
	gmp_fscanf(fp1, "%Zd", n); //extracting the value of n generated by keygen.c in "private_key.txt"
	gmp_fscanf(fp1, "\n");
	gmp_fscanf(fp1, "%Zd", d); //extracting the value of d generated by keygen.c in "private_key.txt"
 	gmp_fscanf(fp2, "%Zd", c); //extracting the value of c from "bobc.txt"
	mpz_sub(v_0, c, x_0);
	mpz_sub(v_1, c, x_1);
	pmod(v_0, v_0, d, n);
	pmod(v_1, v_1, d, n); 
	gmp_fscanf(fp3, "%Zd", m_0); //extracting the value of m_0 (first string) from "strings.txt"
	gmp_fscanf(fp3, "\n");
	gmp_fscanf(fp3, "%Zd", m_1); //extracting the value of m_1 (second string) from "strings.txt"
	mpz_sub(m_0, m_0, v_0);
	mpz_sub(m_1, m_1, v_1);
	gmp_fprintf(fp4, "%Zd", x_0); //writing m'_0 to file "enc_messages.txt"
	gmp_fprintf(fp4, "\n");
	gmp_fprintf(fp4, "%Zd", x_1); //writing m'_1 to file "enc_messages.txt"
}