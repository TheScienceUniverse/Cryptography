#define N 50
typedef unsigned char u_char; 
u_char Bfr[N];
u_char rcon[256]={
0x8d,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1b,0x36,0x6c,0xd8,0xab,0x4d,0x9a, 
0x2f,0x5e,0xbc,0x63,0xc6,0x97,0x35,0x6a,0xd4,0xb3,0x7d,0xfa,0xef,0xc5,0x91,0x39,
0x72,0xe4,0xd3,0xbd,0x61,0xc2,0x9f,0x25,0x4a,0x94,0x33,0x66,0xcc,0x83,0x1d,0x3a,
0x74,0xe8,0xcb,0x8d,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1b,0x36,0x6c,0xd8,
0xab,0x4d,0x9a,0x2f,0x5e,0xbc,0x63,0xc6,0x97,0x35,0x6a,0xd4,0xb3,0x7d,0xfa,0xef,
0xc5,0x91,0x39,0x72,0xe4,0xd3,0xbd,0x61,0xc2,0x9f,0x25,0x4a,0x94,0x33,0x66,0xcc,
0x83,0x1d,0x3a,0x74,0xe8,0xcb,0x8d,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1b,
0x36,0x6c,0xd8,0xab,0x4d,0x9a,0x2f,0x5e,0xbc,0x63,0xc6,0x97,0x35,0x6a,0xd4,0xb3,
0x7d,0xfa,0xef,0xc5,0x91,0x39,0x72,0xe4,0xd3,0xbd,0x61,0xc2,0x9f,0x25,0x4a,0x94,
0x33,0x66,0xcc,0x83,0x1d,0x3a,0x74,0xe8,0xcb,0x8d,0x01,0x02,0x04,0x08,0x10,0x20,
0x40,0x80,0x1b,0x36,0x6c,0xd8,0xab,0x4d,0x9a,0x2f,0x5e,0xbc,0x63,0xc6,0x97,0x35,
0x6a,0xd4,0xb3,0x7d,0xfa,0xef,0xc5,0x91,0x39,0x72,0xe4,0xd3,0xbd,0x61,0xc2,0x9f,
0x25,0x4a,0x94,0x33,0x66,0xcc,0x83,0x1d,0x3a,0x74,0xe8,0xcb,0x8d,0x01,0x02,0x04,
0x08,0x10,0x20,0x40,0x80,0x1b,0x36,0x6c,0xd8,0xab,0x4d,0x9a,0x2f,0x5e,0xbc,0x63,
0xc6,0x97,0x35,0x6a,0xd4,0xb3,0x7d,0xfa,0xef,0xc5,0x91,0x39,0x72,0xe4,0xd3,0xbd,
0x61,0xc2,0x9f,0x25,0x4a,0x94,0x33,0x66,0xcc,0x83,0x1d,0x3a,0x74,0xe8,0xcb,0x8d
};
void clrArr(u_char A[],int n){
	for(int i=0;i<n;A[i++]=0);
}
void getIP(u_char A[],u_char K[],int *nA,int u){
	char c='\0',e;
	int i=0,n;
	printf("Enter the termintion character for Text message: ");
	scanf("%c",&e);
	getchar();//fetches the ENTER from buffer
	printf("Enter the Text: ");
	while(c!=e){
		c=getchar();
		Bfr[i++]=c;
	}
	n=i-1;
	*nA=(n%u==0)?n:(n+u-(n%u));
	clrArr(A,*nA);	//clears the array
	clrArr(K,8);
	for(i=0;i<n;i++)
		A[i]=Bfr[i];
	fflush(stdin);
	i=0;
	c='\0';
	printf("Enter the termintion character for Key: ");
	scanf("%c",&e);
	getchar();
	printf("Enter the Key: ");
	getchar();
        while(c!=e){
		c=getchar();
		Bfr[i++]=c;
	}
	printf("%d\n",i);
	n=8;
	if(i-2<8)
		n=i-2;
	//n=(i<10)?(i-2):8;
	for(i=0;i<n;i++)
		K[i]=Bfr[i];
}
void copyArr(u_char S[],u_char D[],int f,int l){
	for(int i=f;i<l;i++)
		D[i]=S[i];
}
void dsplOP(u_char A[],u_char K[],int n){
	int i;
	printf("\nText:\t");
	for(i=0;i<n;printf("%c",A[i++]));
	printf("\nKey:\t");
	for(i=0;i<n;printf("%c",K[i++]));
	printf("\n");
}
void dsplStrng(u_char A[],int n){
	for(int i=0;i<n;printf("%c",A[i++]));
	printf("\n");
}
void dsplArr(u_char A[],int n){
	for(int i=0;i<n;printf("%02X ",A[i++]));
	printf("\n");
}
void dsplBlck(u_char A[],int n){
	int i,j,p;
	for(p=0;p<n;p+=16){
		for(j=0;j<4;j++){
			for(i=0;i<4;printf("%X ",A[p+4*j+(i++)]));
			printf("\n");
		}
		printf("\n");			
	}
}
void dsplTK(u_char X[],u_char K[],int n){
	printf("\nText:\t");
	dsplArr(X,n);
	printf("Key: \t");
	dsplArr(K,8);
	printf("\n");
}
void nibblize(u_char c,u_char *a,u_char *b){
	*a=(c & 0xf0)>>4,*b=c & 0x0f;
}
void deNibblize(u_char a,u_char b,u_char *c){
	*c=(a<<4)|b;
}
void rotateWord(u_char *a,u_char *b,u_char *c,u_char *d,int n){
	unsigned short x,y;
	x=(*a<<4)|*b,x<<=8;
	x|=(*c<<4)|*d;
	y=x;
	if(n<0)
		n*=-1,x<<=n,y>>=(16-n);
	else
		x>>=n,y<<=(16-n);
	x|=y;
	*d=x & 0x000f;
	*c=(x & 0x00f0)>>4;
	*b=(x & 0x0f00)>>8;
	*a=(x & 0xf000)>>12;
}
