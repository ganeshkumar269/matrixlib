#include <iostream>
#include <vector>
#include "matrix.cpp"
using namespace std;

int main(){
    vector<int> t(10000,1);
    int arr[10000] = {0};
    for(int i =0;i<10000;i++) arr[i] = 1;
    Matrix<int> t2(100,100,t.data());
    Matrix<int> t1(100,100,arr);
	cout << t1*t2 << endl;
    return 0;
}
