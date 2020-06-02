#include <iostream>
#include <assert.h>
#include <algorithm>
#include <string.h>
using namespace std;
typedef pair<int,int> Dim;

template <typename T>
class Matrix{
    private:
        int m; // m - no.of rows
        int n; // n - no.of cols
        T* arr;
        int allocSize;
    public:
        Matrix():m(0),n(0),allocSize(0),arr(nullptr){}

        Matrix(int m,int n):Matrix(){this->m = m;this->n = n;if(m*n > 0)allocMem(m*n);}   //only place where allocMem is called
        
        Matrix(Dim dim):Matrix(dim.first,dim.second){}

        Matrix(const Matrix<T>& t):Matrix(t.getDim()){this->setData(t.getData());cout << "Copy of Matrix" << endl;}
        
        Matrix(Matrix<T>&& t):Matrix(t.getDim()){this->arr = t.getData(); t.resetData();cout << "Move of Matrix" << endl;};

        Matrix(Dim dim,T* data):Matrix(dim){this->setData(data);}

        Matrix(int m,int n,T* data):Matrix(m,n){this->setData(data);}

        Matrix(int m,int n, T t):Matrix(m,n){this->fill(t);}

        ~Matrix(){cout << "Matrix Deleted " << endl;delete[] arr; cout << "Memory deallocated: "<<allocSize << endl; }


        T operator()(int m,int n)const{return this->getElement(m,n);}
        T operator()(int m,int n,T t){return this->setElement(m,n,t);}

        T getElement(int m,int n)const {return arr[(m*this->n) + n];}
        T setElement(int m,int n,T t){arr[(m*this->n) + n] = t; return t;}

        Dim getDim()const {return {this->m,this->n};}
        Dim setDim(Dim dim){this->m = dim.first;this->n = dim.second;if(allocSize < m*n)allocMem(m*n);return dim;}

        T* getData()const {return this->arr;};
        void setData(const T* data){copy(data,data+this->m*this->n,this->arr);}   

        void pointToData();
        void resetData(){this->arr = nullptr;this->m = 0; this->n = 0;}
        

        static Matrix nMatrix(int m , int n, T f){Matrix<T> t(m,n,f);return t;}

        void allocMem(uint32_t size){
		    allocSize = m*n; 
            if(this->arr != nullptr){
                cout << "Memory deallocated: "<<allocSize << endl;
                delete[] arr;
            }
            this->arr = new T[size+1];
            cout << "Memory Allocated: " << size << endl;
	    }

        void fill(T t){std::fill(this->arr,arr+this->m*this->n,t);}

        Matrix operator*(const Matrix<T>& t){
            cout << "Multiply by lvalue" << endl;
            Dim dim1 = this->getDim() , dim2 = t.getDim();
            assert(dim1.second == dim2.first);
            Matrix<T> temp(dim1.first,dim2.second);
            for(int i = 0 ; i < dim1.first; i++)  
                for(int j = 0; j < dim2.second; j++){
                    T sum = 0;
                    for(int k  =0; k < dim1.second; k++)
                        sum+= this->getElement(i,k) * t(k,j);
                    temp.setElement(i,j,sum);   
                }
            return std::exchange(temp,Matrix<T>(0,0,nullptr));
        }

        Matrix operator+(const Matrix<T>& t){
            cout << "Add by lvalue" << endl;
            assert(this->getDim() == t.getDim());
            Matrix<T> temp(t.getDim());
            transform(this->getData(), this->getData()+this->m*this->n, t.getData(), temp.getData(), plus<T>());
            return temp;
        }
        Matrix operator+(Matrix<T>&& t){
            cout << "Add by rvalue" << endl;
            assert(this->getDim() == t.getDim());
            transform(this->getData(), this->getData()+this->m*this->n, t.getData(), t.getData(), plus<T>());
            return std::move(t);
        }
        
        Matrix operator-(const Matrix<T>& t){
            cout << "Subtract by lvalue" << endl;
            assert(this->getDim() == t.getDim());
            Matrix<T> temp(t.getDim());
            transform(this->getData(), this->getData()+this->m*this->n, t.getData(), temp.getData(), minus<T>());
            return temp;
        }
        Matrix operator-(Matrix<T>&& t){
            cout << "Subtract by rvalue" << endl;
            assert(this->getDim() == t.getDim());
            transform(this->getData(), this->getData()+this->m*this->n, t.getData(), t.getData(), minus<T>());
            return std::move(t);
        }

        void print(ostream& out = std::cout,char sep = ' ',string tip = "  ")const {
            Dim dim = this->getDim();
            for(int i = 0;i < dim.first;i++){
                out << tip[0];
                for(int j =0; j < dim.second-1; j++)
                    out << this->getElement(i,j) << sep;
                out << this->getElement(i,dim.second-1);
                out << tip[1] << endl;
            }
        } 
        friend ostream& operator << (ostream& out, const Matrix<T>& t){t.print(out);return out;}

        Matrix<T> operator = (const Matrix<T>& t)
        {this->setDim(t.getDim());this->setData(t.getData());cout << "Copy of Matrix" << endl;return *this;}      
        Matrix<T>&& operator = (Matrix<T>&& t)
        {this->setDim(t.getDim());this->setData(t.getData());t.resetData();cout << "Move of Matrix" << endl;return std::move(*this);}      
};


