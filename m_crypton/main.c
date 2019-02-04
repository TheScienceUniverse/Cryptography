#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include"myLib.h"
#include"mCrypton.h"
int main(void){
	unsigned char T[N],K[8],k[8];
	int nT,i;
	clock_t start,end;
	double cpu_time_used;
	getIP(T,K,&nT,8);
	printf("Inserted Values:\n");
	dsplTK(T,K,nT);
	for(i=0;i<8;i++)
		k[i]=K[i];
	start=clock();
	eMC(T,K,nT);
	end=clock();
	cpu_time_used=((double)(end-start))/CLOCKS_PER_SEC;
	printf("Encrypted Values:\n");
	dsplTK(T,K,nT);
	printf("Time used for Encryption=%lf s\n",cpu_time_used);
	for(i=0;i<8;i++)
		K[i]=k[i];
	start=clock();
	dMC(T,K,nT);
	end=clock();
	cpu_time_used=((double)(end-start))/CLOCKS_PER_SEC;
	printf("Decrypted Values:\n");
	dsplTK(T,K,nT);
	printf("Time used for Decryption=%lf s\n",cpu_time_used);
	return 0;
}
