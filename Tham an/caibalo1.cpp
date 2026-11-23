#include <stdio.h>
#include <malloc.h>
#include <string.h>
typedef struct{
	char TenDV[20];
	float TL,GT,DG;
	int PA;
}DoVat;
void Swap(DoVat *a, DoVat *b){
	DoVat Temp;
	Temp = *a;
	*a = *b;
	*b = Temp;
}
void BubbleSort(DoVat *dsdv,int n){
	int i,j;
	for(i = 0;i<=n-2;i++){
		for(j=n-1;j>=i+1;j--){
			if(dsdv[j].DG >dsdv[j-1].DG)
				Swap(&dsdv[j],&dsdv[j-1]);
		}
	}
}
DoVat *ReadFromFile(float *w ,int *n){
	FILE *f;
	f = fopen("balo1.txt","r");
	fscanf(f,"%f",w);
	DoVat * dsdv;
	dsdv = (DoVat*)malloc(sizeof(DoVat));
	int i = 0;
	while(!feof(f)){
		fscanf(f,"%f %f %[^\n]",&dsdv[i].TL,&dsdv[i].GT,&dsdv[i].TenDV);
		dsdv[i].DG = dsdv[i].GT / dsdv[i].TL;
		dsdv[i++].PA = 0;
		dsdv = (DoVat*)realloc(dsdv,sizeof(DoVat)*(i+1));
	}
	*n = i;
	fclose(f);
	return dsdv;
}
void InDS(DoVat *dsdv,int n,float w){
	int i;
	float TongTL = 0.0, TongGT = 0.0;
	printf("\nPhuong an Cai balo 1 dung thuat toan THAM AN nhu sau:\n");
	printf("Trong luong cua cai balo =%-9.2f\n",w);
	printf("|---|--------------------|-------------|---------|---------|-----------|\n");
	printf("|STT|     TEN DO VAT     | TRONG LUONG | GIA TRI | DON GIA | PHUONG AN |\n");
	printf("|---|--------------------|-------------|---------|---------|-----------|\n");
	for(i=0;i<n;i++){
		printf("|%-3d|%-20s|%-13.2f|%-9.2f|%-9.2f|%-11d|\n",i+1,dsdv[i].TenDV,dsdv[i].TL,dsdv[i].GT,dsdv[i].DG,dsdv[i].PA);
		TongTL = TongTL + dsdv[i].PA * dsdv[i].TL;
		TongGT = TongGT + dsdv[i].PA * dsdv[i].GT;
	}
	printf("|---|--------------------|-------------|---------|---------|-----------|\n");
	printf("Phuong an (theo thu tu DG giam dan): X (");
	for(i=0;i<n-1;i++){
		printf("%d,",dsdv[i].PA);	
	}
	printf("%d)",dsdv[n-1].PA);
	printf("\nTong trong luong = %-9.2f\n",TongTL);
		printf("Tong gia tri = %-9.2f",TongGT);
}
void Greedy(DoVat *dsdv,int n,float w){
	int i;
	for(i=0;i<n;i++){
		dsdv[i].PA = w / dsdv[i].TL;
		w = w - dsdv[i].PA * dsdv[i].TL;
	}
}
int main(){
	int n;
	float w;
	DoVat *dsdv;
	
	dsdv=ReadFromFile(&w,&n);
	BubbleSort(dsdv,n);
	Greedy(dsdv,n,w);
	InDS(dsdv,n,w);
	free(dsdv);
	return 0;
}
