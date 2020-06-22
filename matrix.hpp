#ifndef MATRIXLIB_HPP
#define MATRIXLIB_HPP
    #include <iostream>
    #include <assert.h>
    #include <algorithm>
    #include <string.h>
    #include <random>
    // #include "cust_rand_gen.hpp"
    using namespace std;
    typedef pair<uint32_t,uint32_t> Dim;
    // RandGen randgen; 
    template <typename T>
    class Matrix{
        private:
            uint32_t m; // m - no.of rows
            uint32_t n; // n - no.of cols
            T* arr;
            uint32_t allocSize;
            int id;
            static int id_gen;
        public:
        //Constructors
            Matrix();
            Matrix(uint32_t m,uint32_t n);   
            Matrix(Dim dim);
            Matrix(const Matrix<T>& t);
            Matrix(Matrix<T>&& t);
            Matrix(Dim dim,T* data);
            Matrix(uint32_t m,uint32_t n,T* data);
            Matrix(uint32_t m,uint32_t n, T t);
            ~Matrix(){cout << "Matrix Deleted " << getId() << endl;delete[] arr; cout << "Memory deallocated: "<< allocSize << endl; }
            static Matrix nMatrix(uint32_t m , uint32_t n, T f){Matrix<T> t(m,n,f);return t;}

        //Access Functions
            void generateId();
            int getId()const;
            Dim getDim()const;
            void setDim(Dim dim);
            T* getData()const;
            void setData(T* const data);
            void copy(const T* const data);
            void resetData();
            void fill(T t);
            T getElement(uint32_t m,uint32_t n)const;
            T setElement(uint32_t m,uint32_t n,T t);
            
        //Overloads
            T operator()(uint32_t m,uint32_t n)const;
            T operator()(uint32_t m,uint32_t n,T t);
            Matrix operator*(const Matrix<T>& t);
            Matrix operator+(const Matrix<T>& t);
            Matrix operator+(Matrix<T>&& t);
            Matrix operator-(const Matrix<T>& t);
            Matrix operator-(Matrix<T>&& t);

        //Utils
            void allocMem(uint32_t size);
            void resize(uint32_t size); //only place where allocMem is called
            uint32_t size()const;
            void print(ostream& out = std::cout,char sep = ' ',string tip = "  ")const; 
            friend ostream& operator << (ostream& out, const Matrix<T>& t){t.print(out);return out;}
            void operator = (const Matrix<T>& t);
            void operator = (Matrix<T>&& t);
            
        //To Do
            T det();
            static Matrix<T> inverse(Matrix& t); // return inverse of the argument 
            void inverse(); // inverse of current matrix
            void dot(Matrix& t); //dot product with t (Hadamard product)
            static Matrix Identity(uint32_t n); //return identity matrix of size n 
            static Matrix<T> transpose(Matrix& t); // return transpose of the argument 
            void transpose(); // transpose of current matrix
            

    };
#endif
#include "matrix.cpp"