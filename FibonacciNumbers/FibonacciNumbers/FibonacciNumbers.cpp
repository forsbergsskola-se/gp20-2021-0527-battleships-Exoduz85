#include <iostream>
#include <chrono>
using namespace std;
using namespace chrono;

int fib(int n);
int fibRec(int);
int fibNon(int);
int fibMatrix(int n);
void multiply(int F[2][2], int M[2][2]);
void power(int F[2][2], int n);

const int MAX = 1000;
int f[MAX] = {0};

int main(){
	while (true){
        int number = 0;
        cout << "Enter fibonacci number:\n";
        cin >> number;
        if(number == 0) return 0;

        auto t1 = high_resolution_clock::now();
        cout << fibRec(number) << endl;
        auto t2 = high_resolution_clock::now();
        duration<double, milli> recursiveTimer = t2 - t1;
		
        auto t3 = high_resolution_clock::now();
        cout << fibNon(number) << endl;
        auto t4 = high_resolution_clock::now();
        duration<double, milli> nonRecursiveTimer = t4 - t3;
		
        auto t5 = high_resolution_clock::now();
        cout << fibNon(number) << endl;
        auto t6 = high_resolution_clock::now();
        duration<double, milli> matrixTimer = t6 - t5;

        auto t7 = high_resolution_clock::now();
        cout << fib(number) << endl;
        auto t8 = high_resolution_clock::now();
        duration<double, milli> advanced = t8 - t7;

        cout << "Ms. for recursive: " << recursiveTimer.count() << endl;
        cout << "Ms. for non-recursive: " << nonRecursiveTimer.count() << endl;
        cout << "Ms. for matrix fibonacci: " << matrixTimer.count() << endl;
        cout << "Ms. for advanced fibonacci: " << advanced.count() << endl;
	}
}
int fib(int n){
    if(n == 0)
        return 0;
    if(n == 1 || n == 2)
        return (f[n] = 1);
    if(f[n])
        return f[n];
    int k = (n & 1) ? (n + 1) / 2 : n / 2;
    f[n] = (n & 1) ? (fib(k) * fib(k) + fib(k - 1) * fib(k - 1))
        : (2 * fib(k - 1) + fib(k)) * fib(k);
    return f[n];
}
int fibMatrix(int n){
    int F[2][2] = {{1, 1}, {1, 0}};

    if(n == 0)
        return 0;

    power(F, n - 1);

    return F[0][0];
}
int fibRec(int n){
    if(n < 2)
        return n;
    return fibRec(n - 1) + fibRec(n - 2);
}
int fibNon(int n){
    int f1 = 0, f2 = 1, f3;
    if(n == 0)
        return f1;
    for(int i = 2; i <= n; i++){
        f3 = f1 + f2;
        f1 = f2;
        f2 = f3;
    }
    return f2;
}
void multiply(int F[2][2], int M[2][2]){
    int x = F[0][0] * M[0][0] + F[0][1] * M[1][0];
    int y = F[0][0] * M[0][1] + F[0][1] * M[1][1];
    int z = F[1][0] * M[0][0] + F[1][1] * M[1][0];
    int w = F[1][0] * M[0][1] + F[1][1] * M[1][1];

    F[0][0] = x;
    F[0][1] = y;
    F[1][0] = z;
    F[1][1] = w;
}
void power(int F[2][2], int n){
    int i;
    int M[2][2] = {{1, 1}, {1, 0}};
    for(i = 2; i <= n; i++)
        multiply(F, M);
}