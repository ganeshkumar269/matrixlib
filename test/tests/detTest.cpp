#include <iostream>
#include "../../matrix.hpp"
using namespace std;

int main(){
    {
        Matrix<int>::verbose = false;
        int arr[16] = {1, 0, 2, -1, 
                     3, 0, 0, 5, 
                     2, 1, 4, -3, 
                     1, 0, 5, 0 
                    };
        Matrix<int> m(4,4,arr);
        int val = m.det();
        if(val != 30)
            cout << "DET_TEST FAILED" << endl;
        else 
            cout << "DET_TEST PASSED" << endl;
    }
    return 0;
}