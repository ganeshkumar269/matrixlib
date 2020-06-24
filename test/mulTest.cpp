#include <iostream>
#include "../matrix.hpp"
using namespace std;

int main(){
    {
        Matrix<int> m1(4,4,2);
        Matrix<int> m2(4,4,7);
        Matrix<int> m3;
        m3 = m1*(m2*m2);
        bool flag=true;
        cout << m3 << endl;
        for(int i =0 ; i < 2;i++)
        for(int j =0 ; j < 4;j++){
            if(m3.getElement(i,j) != m2.getElement(i,j)*m2.getElement(i,j)*m1.getElement(i,j)){
                cout << "MUL_TEST FAILED" << endl;
                 cout << m3.getElement(i,j) << " " << 
                    m2.getElement(i,j) << " " << m1.getElement(i,j) << endl;

                flag = false;
                break;
            }
            if(!flag)break;
        }
        if(flag)cout << "MUL_TEST PASSED" << endl;
    }
    return 0;
}