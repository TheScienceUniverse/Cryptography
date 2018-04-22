/* 
 * $ gcc -Wall substitutionCipher.c[ENTER] => a.out
 * $ ./a.out <msg_strng> <E/D>[ENTER]
 * string only cinsists of English letter space {A-Z}, 
 * options{E,D}, "E"=>Encryption, "D"=>Decryption
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
// You can take arbitrary 1-1 mapped array
char E[]={15,25,16,6,24,7,2,23,17,3,18,22,0,8,21,4,20,14,1,19,9,13,5,10,12,11};
char D[]={12,18,6,9,15,22,3,5,13,20,23,25,24,21,17,0,2,8,10,19,16,14,11,7,4,1};
int main(int argc,char *argv[]){
	char *m;
	int n,i;
	if(argc<3){
		printf("Insufficient data\nFormat: $ ./a.out <msg_strng> <E/D>\n");
		exit(1);
	}
	m=(char *)argv[1], n=strlen(m);
	// Encryption
	if(strcmp(argv[2],"E")==0){
		for(i=0;i<n;i++)
			m[i]=E[m[i]-'A']+'A';
		printf("%s\n",m);
	}
	// Decryption
	else if(strcmp(argv[2],"D")==0){
		for(i=0;i<n;i++)
			m[i]=D[m[i]-'A']+'A';
		printf("%s\n",m);
	}
	return 0;
}
