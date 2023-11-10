#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1000000;
double f(double x){
	// f(x) = x^2
	//return x*x;
	return 4*x*x*x + 2*x;
}

void solve(){
	double a,b; cin>>a>>b;
	double h = (b-a)/N;
	double approx = (f(a)+f(b))/2.0;
	for(int i = 1; i < N-1; i++){
		double x_i = a+i*h;
		approx += f(x_i);
	}
	approx *= h;
	cout.precision(3);
	cout << fixed << setprecision(3) << approx << endl;
	// cout << "Area with " << N << " trapezois: " << approx << endl;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}