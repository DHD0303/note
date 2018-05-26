#include<stdio.h>

void sort(int * a, int len) {
	if( len <= 1 ) return;

	int i=0, j=len-1, temp = a[0], t;
	while( i<j ) {
		while( a[j]>temp && j>i ) j--;
		while( a[i]<=temp && i<j ) i++;
		if(i != j) { //i等于j时交换没有意义,否则使小数到前面，大数到后面
			t = a[i];
			a[i]=a[j];
			a[j]=a[i];
		}
	}
	//由于是先从后面往前扫描，所以无论何时，从后往前扫描停止时，当时的a[j]必定不大于temp,则退出时a[i]必定不大于temp
	//使标准值到中间形成 小数数组 标准值 大数数组
	a[0]=a[i];
	a[i]=temp;
	sort(a, i);
	sort(a+i+1, len-i-1);

	return;
}

//void sort(int * a, int len) {
//	if( len <= 1 ) return;
//
//	int i=0, j=len-1, t, temp = a[0], k;
//	while( i<j ) {
//		while( a[j]>temp && j>i ) j--; a[i] = a[j];
//		while( a[i]<=temp && i<j ) i++; a[j] = a[i];
//	}
//	a[i] = temp;
//	sort(a, i);
//	sort(a+i+1, len-i-1);
//
//	return;
//}

int main(void) {
	int i, a[13] = {-100, 4, 6, -10, 9, 46, -4, 3, 6, 5, 8, 44, 20};
	sort(a, 13);
	for(i=0; i<13; i++) {
		printf("%d ", a[i]);
	}

	return 0;
}
