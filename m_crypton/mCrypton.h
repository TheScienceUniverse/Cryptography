u_char SB[4][16]={
{4,15,3,8,13,10,12,0,11,5,7,14,2,6,1,9},
{1,12,7,10,6,13,5,3,15,11,2,0,8,4,9,14},
{7,14,12,2,0,9,13,10,3,15,5,8,6,4,11,1},
{11,0,10,7,13,6,4,2,12,14,3,9,1,5,15,8}};
u_char m[4]={14,13,11,7};
u_char M[16]={15,0,0,0,0,15,0,0,0,0,15,0,0,0,0,15};
u_char U[16],V[16];
void mkIP(u_char A[],u_char X[],int n){
	for(int i=0;i<n;i++)
		nibblize(A[i],&X[2*i],&X[2*i+1]);
}
void mkOP(u_char X[],u_char A[],int n){
	for(int i=0;i<n;i++)
		deNibblize(X[2*i],X[2*i+1],&A[i]);
}
void subBytes(u_char X[],int nX){
	int p,i,j;
	for(p=0;p<nX;p+=16)
		for(i=0;i<4;i++)
			for(j=0;j<4;j++)
				X[p+4*j+i]=SB[(i+j)%4][X[p+4*j+i]];
}
void _subBytes(u_char X[],int nX){
	int p,i,j;
	for(p=0;p<nX;p+=16)
		for(i=0;i<4;i++)
			for(j=0;j<4;j++)
				X[p+4*j+i]=SB[(i+j+2)%4][X[p+4*j+i]];
}
void bitPermutation(u_char X[],int nX){
	u_char x[16],c;
	int p,i,j,k;
	for(p=0;p<nX;p+=16){
		for(i=0;i<4;i++){
			for(j=0;j<4;j++){
				c=0;
				for(k=0;k<4;k++)
					c^=(m[(i+j+k)%4]&X[p+4*k+i]);
				x[4*j+i]=c;
			}
		}
		for(i=0;i<16;i++)
			X[p+i]=x[i];
	}
}
void c2rTransposition(u_char X[],int nX){
	int i,j,p;
	u_char x[16];
	for(p=0;p<nX;p+=16){
		for(i=0;i<4;i++){
			for(j=0;j<4;j++)
				x[i*4+j]=X[p+j*4+i];
		}
		for(i=0;i<16;i++)
			X[p+i]=x[i];
	}
}
void keySchedule(int r,u_char K[]){
	int i,j;
	u_char t[4];
	if(r==0)
		for(i=0;i<16;i++)
			U[i]=K[i];
	for(j=0;j<4;j++)
		t[j]=U[4*j];
	for(i=0;i<3;i++)
		for(j=0;j<4;j++)
			U[4*j+i]=U[4*j+i+1];
	for(j=0;j<4;j++)
		U[4*j+3]=t[j];
	for(i=0;i<16;i++)
		K[i]=U[i];
	for(i=0;i<4;i++)
		K[5*i]^=SB[0][t[i]];
	rotateWord(&U[3],&U[7],&U[11],&U[15],-3);
}
void _keySchedule(int r,u_char K[]){
	int i,j;
	u_char t[4];
	if(r==0){
		for(i=0;i<16;i++)
			V[i]=K[i];
		for(i=0;i<4;i++)
			rotateWord(&V[i],&V[4+i],&V[8+i],&V[12+i],-9);
	}
	rotateWord(&V[3],&V[7],&V[11],&V[15],3);
	for(i=0;i<16;i++)
		K[i]=V[i];
	t[0]=V[3],t[1]=V[7],t[2]=V[11],t[3]=V[15];
	for(i=0;i<4;i++)
		K[5*i]^=SB[0][t[i]];
	for(i=0;i<4;i++)
		for(j=3;j>0;j--)
			V[4*i+j]=V[4*i+j-1];
	for(i=0;i<4;i++)
		V[4*i]=t[i];
}
void keyAddition(u_char X[],u_char K[],int nX){
	for(int p=0;p<nX;p++)
		X[p]^=K[p%16];
}
void eMC(u_char T[],u_char K[],int nT){
	int nX=2*nT,r;
	u_char X[nX],xK[16];
	mkIP(T,X,nT);
	mkIP(K,xK,8);
	for(r=0;r<12;r++){
		subBytes(X,nX);
		bitPermutation(X,nX);
		c2rTransposition(X,nX);
		keySchedule(r,xK);
		keyAddition(X,xK,nX);
	}
	mkOP(X,T,nT);
	mkOP(xK,K,8);
}
void dMC(u_char T[],u_char K[],int nT){
	int nX=2*nT,r;
	u_char X[nX],xK[16];
	mkIP(T,X,nT);
	mkIP(K,xK,8);
	for(r=0;r<12;r++){
		_keySchedule(r,xK);
		keyAddition(X,xK,nX);
		c2rTransposition(X,nX);
		bitPermutation(X,nX);
		_subBytes(X,nX);
	}
	mkOP(X,T,nT);
	mkOP(xK,K,8);
}
