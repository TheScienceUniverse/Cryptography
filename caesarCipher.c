/*
 * $ gcc -Wall caesarCipher.c[ENTER] => a.out
 * $ ./a.out <msg_strng> <E/D>[ENTER]
 * string only cinsists of English letter space {A-Z}, key=-3 [No need to provide]
 * options{E,D}, "E"=>Encryption, "D"=>Decryption
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(int argc,char *argv[]){
	char *m;
	int n,i;
	if(argc<3){
		printf("Insufficient data\nFormat: $ ./a.out <msg_strng> <key_letter> <E/D>\n");
		exit(1);
	}
	m=(char *)argv[1], n=strlen(m);
	for(i=0;i<n;m[i++]-='A');
	// Encryption
	if(strcmp(argv[2],"E")==0){
		for(i=0;i<n;i++)
			m[i]=(m[i]+23)%26+'A';	// k=-|3-26|
		printf("%s\n",m);
	}
	// Decryption
	else if(strcmp(argv[2],"D")==0){
		for(i=0;i<n;i++)
			m[i]=(m[i]+3)%26+'A';
		printf("%s\n",m);
	}
	return 0;
}
