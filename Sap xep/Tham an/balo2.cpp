#include <stdio.h>
#include <string.h>
#include <malloc.h>
typedef struct {
	char TenDV[20];
	float TL,GT,DG;
	int SL,PA;
}DoVat;
void swap(DoVat *a,DoVat *b){
	DoVat temp;
	temp = *a;
	*a =*b;
	*b=temp;
}
void BubbleSort(DoVat *dsdv,int n){
	int i,j;
	for(i=0;i<=n-2;i++){
		for(j=n-1;j>=i+1;j--){
			if(dsdv[j].DG>dsdv[j-1].DG)
				swap(&dsdv[j],&dsdv[j-1]);
		}
	}
}
DoVat *read_data(float *w,int *n){
	FILE *f;
	f = fopen("balo2.txt","r");
	fscanf(f,"%f",w);
	DoVat *dsdv;
	dsdv = (DoVat*)malloc(sizeof(DoVat));
	int i=0;
	while(!feof(f)){
		fscanf(f,"%f %f %d %[^\n]",&dsdv[i].TL,&dsdv[i].GT,&dsdv[i].SL,&dsdv[i].TenDV);
		dsdv[i].DG = dsdv[i].GT/dsdv[i].TL;
		dsdv[i++].PA =0;
		dsdv = (DoVat*)realloc(dsdv,sizeof(DoVat)*(i+1));
	}
	fclose(f);
	*n = i;
	return dsdv;
}
void print_data(DoVat *dsdv,int n,float w){
	int i;
	float TongTL =0.0, TongGT = 0.0;
	printf("\nPhuong an cai balo1 thuat toan THAM AN nhu sau:\n\n");
	printf("|---|-------------------------|-------------|---------|----------|---------|-----------|\n");
	printf("|STT|       TEN DO VAT        | TRONG LUONG | GIA TRI | SO LUONG | DON GIA | PHUONG AN |\n");
	printf("|---|-------------------------|-------------|---------|----------|---------|-----------|\n");
	for(i=0;i<n;i++){
		printf("|%-3d|%-25s|%-13.2f|%-9.2f|%-10d|%-9.2f|%-11d|\n",i+1,dsdv[i].TenDV,dsdv[i].TL,dsdv[i].GT,dsdv[i].SL,dsdv[i].DG,dsdv[i].PA);
		TongTL = TongTL + dsdv[i].PA*dsdv[i].TL;
		TongGT = TongGT + dsdv[i].PA * dsdv[i].GT;
	}
	printf("|---|-------------------------|-------------|---------|----------|---------|-----------|\n");
	printf("Tong trong luong la:%9.2f",TongTL);
	printf("Tong gia tri la:%9.2f",TongGT);
}
int min(int a,int b){
	return a<b ? a:b;
}
void Greedy(DoVat *dsdv,int n,float w){
	int i;
	for(i=0;i<n;i++){
		dsdv[i].PA = min(dsdv[i].SL,w/dsdv[i].TL);
		w = w - dsdv[i].PA * dsdv[i].TL;
	}
}
int main(){
	int n;
	float w;
	DoVat *dsdv;
	
	dsdv = read_data(&w,&n);
	BubbleSort(dsdv,n);
	Greedy(dsdv,n,w);
	print_data(dsdv,n,w);
	free(dsdv);
	return 0;
}
