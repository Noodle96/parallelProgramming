#include <bits/stdc++.h>
#define all(x) x.begin(),x.end()
#define msg(str,str2) cout << str << str2<< endl
using namespace std;

const int MAX = 4096;
int A[MAX][MAX];
int lineal[MAX];
int container01[MAX];
int container02[MAX];

clock_t startTime;
double getCurrentTime() {
	return (double)(clock() - startTime) / CLOCKS_PER_SEC;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	/*Init A array*/
	for(int e = 0 ;e < MAX ; e++){
		for(int j = 0 ; j < MAX; j++){
			A[e][j] = e+j;
		}
	}
	/*Init lineal array*/
	for(int e = 0 ; e < MAX; e++){
		lineal[e] = e+1;
	} 

	/*First pair of loops*/
	startTime = clock();
	for(int row = 0 ; row < MAX; row++){
		for(int col = 0 ; col < MAX ; col++){
			container01[row] += A[row][col]*lineal[col];
		}
	}
	cout << "tiempo para calcular el container01: " << getCurrentTime() << endl;

	/*second pair of loops*/
	startTime = clock();
	for(int col = 0 ; col < MAX; col++){
		for(int row = 0 ; row < MAX ; row++){
			container02[row] += A[row][col]*lineal[col];
		}
	}
	cout << "tiempo para calcular el container02: " << getCurrentTime() << endl;
	return 0;
}