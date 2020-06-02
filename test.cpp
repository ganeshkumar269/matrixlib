#include <iostream>
#include "matrix.cpp"
using namespace std;

Matrix<int> createMatrix(){
    Matrix<int> m(2,2,1);
    return m;
}

int main(){
    int arr[10] = {1,1,1,1,1,1,1,1};
    int arr2[10] = {1,1,1,1,1,1,1,1};
    Matrix<int> m1(2,4,arr);
    Matrix<int> m2(2,4,arr2);
    Matrix<int> m3;
    m3 = m1*Matrix<int>(4,2,1);
    cout << m3 << endl;
    cout << m2 << endl;
    cout << m1 << endl;
    // cout << createMatrix() << endl;
}