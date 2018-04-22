/* 
 * $ gcc -Wall shiftCipher.c[ENTER] => a.out
 * $ ./a.out <msg_strng> <key_letter> <E/D>[ENTER]
 * string only cinsists of English letter space {A-Z}, 
 * options{E,D}, "E"=>Encryption, "D"=>Decryption
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(int argc,char *argv[]){
	char *m,k;
	int n,i;
	if(argc<4){
		printf("Not Sufficient data\nFormat: $ ./a.out <msg_strng> <key_letter> <E/D>\n");
		exit(1);
	}
	m=(char *)argv[1], n=strlen(m);
	for(i=0;i<n;i++)	m[i]-='A';
	k=argv[2][0]-'A';
	// Encryption
	if(strcmp(argv[3],"E")==0){
		for(i=0;i<n;i++)
			m[i]=(m[i]+k)%26+'A';
		printf("%s\n",m);
	}
	// Decryption
	else if(strcmp(argv[3],"D")==0){
		for(i=0;i<n;i++)
			m[i]=(26+m[i]-k)%26+'A';
		printf("%s\n",m);
	}
	return 0;
}
