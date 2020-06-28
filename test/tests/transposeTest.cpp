#include <iostream>
#include "../../matrix.hpp"
using namespace std;

int main(){
    {
        Matrix<int>::verbose = false;
        Matrix<int> m1(2,4,2);
        Matrix<int> m2;
        m2 = Matrix<int>::transpose(m1);
        bool flag=true;
        for(int i =0 ; i < 4;i++)
        for(int j =0 ; j < 2;j++){
            if(m2.getElement(i,j) != m1.getElement(j,i)){
                cout << "TRANSPOSE_TEST a FAILED" << endl;
                flag = false;
                break;
            }
            if(!flag)break;
        }
        if(flag)cout << "TRANSPOSE_TEST a PASSED" << endl;
        m2.transpose();
        flag = true;
        for(int i =0 ; i < 2;i++)
        for(int j =0 ; j < 4;j++){
            if(m2.getElement(i,j) != m1.getElement(i,j)){
                cout << "TRANSPOSE_TEST b FAILED" << endl;
                flag = false;
                break;
            }
            if(!flag)break;
        }
        if(flag)cout << "TRANSPOSE_TEST b PASSED" << endl;
    }
    return 0;
}