#include <stdio.h>
#include <string.h>
#include <malloc.h>
typedef struct {
	char TenTien[25];
	int MG,PA;
}Tien;
Tien *read_data(int *n){
	FILE *f;
	f = fopen("atm.txt","r");
	Tien *dslt;
	dslt = (Tien*)malloc(sizeof(Tien));
	int i=0;
	while(!feof(f)){
		fscanf(f,"%d %[^\n]",&dslt[i].MG,&dslt[i].TenTien);
		dslt[i++].PA = 0;
		dslt = (Tien*)realloc(dslt,sizeof(Tien)*(i+1));
	}
	fclose(f);
	*n = i;
	return dslt;
}
void swap(Tien *a, Tien *b)
{
	Tien temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
void BubbleSort(Tien *dslt, int n){
	int i,j;
	for(i=0;i<=n-2;i++){
		for(j=n-1;j>=i+1;j--){
			if(dslt[j].MG > dslt[j-1].MG)
				swap(&dslt[j],&dslt[j-1]);
		}
	}
}
void print_data(Tien *dslt,int n, int TienCanRut){
	int i;
	int TongTienTra=0;
	printf("|---|-------------------------|---------|---------|----------|\n");
	printf("|%-3s|%-25s|%-9s|%-9s|%-10s|\n","STT","TEN TIEN","MENH GIA","SO TO","THANH TIEN");
	printf("|---|-------------------------|---------|---------|----------|\n");
	for(i=0;i<n;i++){
		if(dslt[i].PA!=0){
			printf("|%-3d",i+1);
			printf("|%-25s",dslt[i].TenTien);
			printf("|%-9d",dslt[i].MG);
			printf("|%-9d",dslt[i].PA);
			printf("|%-10d|\n",dslt[i].PA * dslt[i].MG);
			TongTienTra = TongTienTra + dslt[i].PA * dslt[i].MG;
		}
		else continue;
	}
	printf("|---|-------------------------|---------|---------|----------|\n");
	printf("So tien can rut la:%9d\n",TienCanRut);
	printf("SO tien tra lai :%9d\n",TongTienTra);
}
void Greedy(Tien *dslt,int n, int TienCanRut){
	int i=0;
	while(i<n && TienCanRut >0){
		dslt[i].PA = TienCanRut/dslt[i].MG;
		TienCanRut = TienCanRut - dslt[i].PA* dslt[i].MG;
		i++;
	}
}
int main(){
	int i;
	int n;
	int TienCanRut;
	printf("Nhap so tien can rut: "); scanf("%d",&TienCanRut);
	Tien *dslt;
	dslt = read_data(&n);
	BubbleSort(dslt,n);
	Greedy(dslt,n,TienCanRut);
	print_data(dslt,n,TienCanRut);
	free(dslt);
}
	
