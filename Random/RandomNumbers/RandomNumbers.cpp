#include <iostream>
#include <chrono>
using namespace std;
using namespace chrono;

void printOutRndNumb(){
    int arr[20]{};
    for(int i = 0; i < 1000000; i++){
        int r = (rand() % 20) + 1; // rand() % 20 = 0-19, (rand() % 20) + 1 = 1-20
        arr[r - 1] += 1; // r-1 to not get out of bounds
    }
    for(int i = 0; i < 20; i++){
	    cout << "Number " << i + 1 << " occurred: " << arr[i] << "times" << endl;
    }
    cout << std::endl;
}
int main(){
    auto ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    srand(ms);
    cout << "seed number: " << ms << "." << endl;
    printOutRndNumb();
    return 0;
}