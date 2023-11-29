#include <stdio.h>
#include <stdlib.h>
const int N = 10000;
int main(){
	double factor =1;
	double sum = 0.0;
	for(int e = 0 ; e < N ; e++, factor = -factor){
		sum += factor/(2*e+1);
	}
	sum *= 4;
	printf("The value of the double is: %lf\n", sum);
	return 0;
}