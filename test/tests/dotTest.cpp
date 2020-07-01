#include <iostream>
#include "../../matrix.hpp"
using namespace std;

int main(){
    Matrix<int>::verbose = false;
    int arr[25];
    for(int i =0;i<25;i++) arr[i] = i;
    Matrix<int> m1(5,5,arr);
    Matrix<int> m2(5,5,arr);
    Matrix<int> temp(Matrix<int>::dot(m1,m2));
    bool flag = true;
    for(int i =0 ; i < m1.getDim().first;i++)
    for(int j =0 ; j < m1.getDim().second;j++)
        if(temp.getElement(i,j) != m1.getElement(i,j)*m2.getElement(i,j)){
                cout << "DOT_TEST a FAILED" << endl;
                flag = false;
                break;
        }
    if(flag)cout << "DOT_TEST a PASSED" << endl;
    flag = true;
    temp = m1;
    temp.dot(m2);
    for(int i =0 ; i < m1.getDim().first;i++)
    for(int j =0 ; j < m1.getDim().second;j++)
        if(temp.getElement(i,j) != m1.getElement(i,j)*m2.getElement(i,j)){
                cout << "DOT_TEST b FAILED" << endl;
                flag = false;
                break;
        }
    if(flag)cout << "DOT_TEST b PASSED" << endl;
    return 0;
}