#ifndef MATRIXLIB_HPP
#define MATRIXLIB_HPP
    #include <iostream>
    #include <assert.h>
    #include <algorithm>
    #include <string.h>
    #include <random>
    #define uint uint32_t
    using namespace std;
    typedef pair<uint32_t,uint32_t> Dim;
    struct PrintStyle{
        char sep;
        char end;
        char tip[2];
    };
    template <typename T>
    class Matrix{
        private:
            uint32_t m; // m - no.of rows
            uint32_t n; // n - no.of cols
            T* arr;
            uint32_t allocSize;
            int id;
            static int id_gen;
            PrintStyle printStyle;
        public:
        //Constructors
            static bool verbose;
            Matrix();
            Matrix(uint32_t m,uint32_t n);   
            Matrix(Dim dim);
            Matrix(const Matrix<T>& t);
            Matrix(Matrix<T>&& t);
            Matrix(Dim dim,const T* const data);
            Matrix(uint32_t m,uint32_t n,const T* const data);
            Matrix(uint32_t m,uint32_t n, T t);
            ~Matrix();
            static Matrix nMatrix(uint32_t m , uint32_t n, T f){Matrix<T> t(m,n,f);return t;}

        //Access Functions
            void generateId();
            int getId()const;
            Dim getDim()const;
            void setDim(Dim dim);
            T* getData()const;
            void setData(T* const data);
            void copy(const T* const data);
            void copy_n(const T* const data,uint n);
            void resetData();
            void fill(T t);
            T getElement(uint32_t m,uint32_t n)const;
            T setElement(uint32_t m,uint32_t n,T t);
            T operator()(uint32_t m,uint32_t n)const;
            T operator()(uint32_t m,uint32_t n,T t);
            
        //Arithmetic
            Matrix operator*(const Matrix<T>& t);
            Matrix operator+(const Matrix<T>& t);
            Matrix operator+(Matrix<T>&& t);
            Matrix operator-(const Matrix<T>& t);
            Matrix operator-(Matrix<T>&& t);
            void operator = (const Matrix<T>& t);
            void operator = (Matrix<T>&& t);

        //Operations
            T det();
            static Matrix<T> transpose(const Matrix& t); // return transpose of the argument 
            void transpose(); // transpose of current matrix
            static Matrix<T> dot(const Matrix& t1,const Matrix& t2);
            void dot(const Matrix& t); //dot product with t (Hadamard product)

        //Memory Management
            void alloc(uint32_t size);
            void dealloc();
            void resize(uint32_t size); //only place where alloc is called

        //Utils
            uint32_t size()const;
            void print(ostream& out = std::cout)const; 
            void setPrintStyle(PrintStyle printStyle);
            void setPrintStyle(char sep,char end,const char tip[2]);
            PrintStyle getPrintStyle()const;
            friend ostream& operator << (ostream& out, const Matrix<T>& t){t.print(out);return out;}
            static Matrix Identity(uint32_t n); //return identity matrix of size n 
            
        //To Do
            static Matrix<T> inverse(Matrix& t); // return inverse of the argument 
            void inverse(); // inverse of current matrix
    };
#include "matrix.cpp"
#endif
