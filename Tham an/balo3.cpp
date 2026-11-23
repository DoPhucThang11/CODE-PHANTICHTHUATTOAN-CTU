#include <stdio.h>
#include <string.h>
#include <malloc.h>
typedef struct{
	char TenDV[25];
	float TL,GT,DG;
	int PA;
}DoVat;
void swap(DoVat *a,DoVat *b){
	DoVat temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
void SeclectionSort(DoVat *dsdv, int n){
	int i,j;
	int highindex;
	float highkey;
	for(i=0;i<=n-2;i++){
		highkey = dsdv[i].DG;
		highindex = i;
		for(j=i+1;j<=n-1;j++){
			if(dsdv[j].DG > highkey){
				highkey = dsdv[j].DG;
				highindex = j;
			}
		}
		swap(&dsdv[i],&dsdv[highindex]);
	}
}
DoVat *read_data( int *n,float *w){
	FILE *f;
	f = fopen("balo3.txt","r");
	fscanf(f,"%f",w);
	DoVat *dsdv;
	dsdv = (DoVat *)malloc(sizeof(DoVat));
	int i=0;
	while(!feof(f)){
		fscanf(f,"%f %f %[^\n]",&dsdv[i].TL,&dsdv[i].GT,&dsdv[i].TenDV);
		dsdv[i].DG = dsdv[i].GT/dsdv[i].TL;
		dsdv[i++].PA = 0;
		dsdv = (DoVat *)realloc(dsdv,sizeof(DoVat)*(i+1));
	}
	fclose(f);
	*n = i;
	return dsdv;
}
void print_data(DoVat *dsdv,int n, float w){
	int i;
	float TongGT = 0.0, TongTL=0.0;
	printf("\nPhuong an cai balo 3 la:\n\n");
	printf("|---|-------------------------|-------------|---------|---------|-----------|\n");
	printf("|STT|       TEN DO VAT        | TRONG LUONG | GIA TRI | DON GIA | PHUONG AN |\n");
	printf("|---|-------------------------|-------------|---------|---------|-----------|\n");
	for(i=0;i<n;i++){
		printf("|%-3d|%-25s|%-13.2f|%-9.2f|%-9.2f|%-11d|\n",i+1,dsdv[i].TenDV,dsdv[i].TL,dsdv[i].GT,dsdv[i].DG,dsdv[i].PA);
		TongTL = TongTL + dsdv[i].PA * dsdv[i].TL;
		TongGT = TongGT + dsdv[i].PA * dsdv[i].GT;
	}
	printf("|---|-------------------------|-------------|---------|---------|-----------|\n");
	printf("Tong gia tri la: %9.2f\n",TongGT);
	printf("Tong trong luong la: %9.2f\n",TongTL);
}
int min(int a, int b){
	return a<b ?a:b;
}
void Greedy(DoVat *dsdv, int n, float w){
	int i;
	for(i=0;i<n;i++){
		dsdv[i].PA = min(1,w/dsdv[i].TL);
		w = w - dsdv[i].PA* dsdv[i].TL;
	}
}
int main(){
	int n;
	float w;
	DoVat *dsdv;
	dsdv = read_data(&n,&w);
	SeclectionSort(dsdv,n);
	Greedy(dsdv,n,w);
	print_data(dsdv,n,w);
	free(dsdv);
	return 0;
}
