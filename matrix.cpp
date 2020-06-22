template<typename T>
Matrix<T>::Matrix():m(0),n(0),allocSize(0),arr(nullptr){cout << "Matrix reference created ";generateId(); cout << getId() <<'\n';}
template<typename T>
Matrix<T>::Matrix(uint32_t m,uint32_t n):Matrix(){this->m = m;this->n = n; if(m*n > 0)allocMem(m*n);}   //only place where allocMem is called
template<typename T>
Matrix<T>::Matrix(Dim dim):Matrix(dim.first,dim.second){}
template<typename T>
Matrix<T>::Matrix(const Matrix<T>& t):Matrix(t.getDim()){
    cout << "constructor: Copy of Matrix "<< id << " " << t.getId() << endl;
    this->setData(t.getData());
}
template<typename T>
Matrix<T>::Matrix(Matrix<T>&& t):Matrix(t.getDim()){
    cout << "constructor: Move of Matrix "<< id << " " << t.getId() << endl;
    setData(t.getData());
    t.resetData();
}
template<typename T>
Matrix<T>::Matrix(Dim dim,T* data):Matrix(dim){this->setData(data);}
template<typename T>
Matrix<T>::Matrix(uint32_t m,uint32_t n,T* data):Matrix(m,n){this->setData(data);}
template<typename T>
Matrix<T>::Matrix(uint32_t m,uint32_t n, T t):Matrix(m,n){fill(t);}
template<typename T>
void Matrix<T>::generateId(){id = int(randgen()*1000);}
template<typename T>
int Matrix<T>::getId()const{return id;}
template<typename T>
T Matrix<T>::operator()(uint32_t _m,uint32_t _n)const{return this->getElement(_m,_n);}
template<typename T>
T Matrix<T>::operator()(uint32_t _m,uint32_t _n,T t){return this->setElement(_m,_n,t);}
template<typename T>
T Matrix<T>::getElement(uint32_t _m,uint32_t _n)const {return arr[(_m*this->n) + _n];}
template<typename T>
T Matrix<T>::setElement(uint32_t _m,uint32_t _n,T t){arr[(_m*this->n) + _n] = t; return t;}

template<typename T>
Dim Matrix<T>::getDim()const {return {this->m,this->n};}
template<typename T>
void Matrix<T>::setDim(Dim dim){this->m = dim.first;this->n = dim.second;}
template<typename T>
T* Matrix<T>::getData()const {return this->arr;};
template<typename T>
void Matrix<T>::setData(T*const data){arr = data;}   
template<typename T>
void Matrix<T>::copy(const T* const data){copy(data,data+m*n,arr);}
template<typename T>
void Matrix<T>::resetData(){
    arr = nullptr;
    m = 0;n = 0;allocSize=0;
}
template<typename T>
void Matrix<T>::allocMem(uint32_t size){
    allocSize = m*n; 
    if(this->arr != nullptr){
        cout << "Memory deallocated: "<< allocSize<<" "<< getId()<< endl;
        delete[] arr;
    }
    this->arr = new T[size+1];allocSize=size;
    cout << "Memory Allocated: " << size <<" "<< getId()<< endl;
}

template<typename T>
void Matrix<T>::resize(uint32_t size){
    T* tmp = arr;
    arr = nullptr;
    allocMem(size);
    copy_n(tmp,m*n < size ? m*n : size,arr);
    delete[] tmp;
}
template<typename T>
uint32_t Matrix<T>::size()const{return m*n;}


template<typename T>
void Matrix<T>::fill(T t){std::fill(this->arr,arr+this->m*this->n,t);}


template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& t){
    cout << "Multiply by lvalue " << id << " " << t.getId()<< endl;
    Dim dim1 = this->getDim() , dim2 = t.getDim();
    assert(dim1.second == dim2.first);
    Matrix<T> temp(dim1.first,dim2.second);
    for(uint32_t i = 0 ; i < dim1.first; i++)  
        for(uint32_t j = 0; j < dim2.second; j++){
            T sum = 0;
            for(uint32_t k  =0; k < dim1.second; k++)
                sum+= this->getElement(i,k) * t(k,j);
            temp.setElement(i,j,sum);   
        }
    return std::exchange(temp,Matrix<T>());
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& t){
    cout << "Add by lvalue " << this->getId() << " " << t.getId()<< endl;
    assert(this->getDim() == t.getDim());
    Matrix<T> temp(t.getDim());
    // for(uint32_t i=0;i<size();++i)
    //     temp.setElement(i/n,i%n,getElement(i/n,i%n)+t.getElement(i/n,i%n));
    transform(getData(), getData()+m*n, t.getData(), temp.getData(), plus<T>());
    return temp;
}
template<typename T>
Matrix<T> Matrix<T>::operator+(Matrix<T>&& t){
    cout << "Add by rvalue " << getId() << " " << t.getId()<< endl;
    assert(this->getDim() == t.getDim());
    transform(this->getData(), this->getData()+this->m*this->n, t.getData(), t.getData(), plus<T>());
    return t;
}
        
template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& t){
    cout << "Subtract by lvalue "<< id << " " << t.getId() << endl;
    assert(this->getDim() == t.getDim());
    Matrix<T> temp(t.getDim());
    transform(this->getData(), this->getData()+this->m*this->n, t.getData(), temp.getData(), minus<T>());
    return temp;
}
template<typename T>
Matrix<T> Matrix<T>::operator-(Matrix<T>&& t){
    cout << "Subtract by rvalue " << endl;
    assert(this->getDim() == t.getDim());
    transform(this->getData(), this->getData()+this->m*this->n, t.getData(), t.getData(), minus<T>());
    return t;
}



template<typename T>
void Matrix<T>::print(ostream& out,char sep,string tip)const {
    for(uint32_t i = 0;i < m;++i){
        out << tip[0];
        for(uint32_t j =0; j < n-1; ++j)
            out << this->getElement(i,j) << sep;
        out << this->getElement(i,n-1);
        out << tip[1] << endl;
    }
} 

template<typename T>
void Matrix<T>::operator = (const Matrix<T>& t){
    cout << "Copy of Matrix "<< id << " " << t.getId() << endl;
    setDim(t.getDim());
    resize(t.size());
    copy(t.getData());
    // return *this;
}      
template<typename T>
void Matrix<T>::operator = (Matrix<T>&& t){
    cout << "Move of Matrix "<< id << " " << t.getId() << endl;
    setDim(t.getDim());
    allocSize = t.size();
    setData(t.getData());
    t.resetData();
    // return *this;
}      

