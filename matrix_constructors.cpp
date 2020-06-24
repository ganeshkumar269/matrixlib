template<typename T>
int Matrix<T>::id_gen = 0;
template<typename T>
bool Matrix<T>::verbose = true;
template<typename T>
Matrix<T>::Matrix():m(0),n(0),allocSize(0),arr(nullptr){
    if(verbose)cout << "Matrix reference created,id: ";
    generateId(); 
    if(verbose)cout << getId() <<'\n';
}
template<typename T>
Matrix<T>::Matrix(uint32_t m,uint32_t n):Matrix(){
    this->m = m;this->n = n; 
    if(m*n > 0) 
    resize(m*n);
}   
template<typename T>
Matrix<T>::Matrix(Dim dim):Matrix(dim.first,dim.second){}
template<typename T>
Matrix<T>::Matrix(const Matrix<T>& t):Matrix(t.getDim()){
    if(verbose)cout << "constructor: Copy of Matrix "<< id << " " << t.getId() << endl;
    copy_n(t.getData(),m*n,getData());
}
template<typename T>
Matrix<T>::Matrix(Matrix<T>&& t):Matrix(t.getDim()){
    if(verbose)cout << "constructor: Move of Matrix "<< id << " " << t.getId() << endl;
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
Matrix<T>::~Matrix(){
    if(verbose)cout << "Matrix Deleted " << getId() << endl;
    delete[] arr; 
    if(verbose)cout << "Memory deallocated: "<< allocSize << endl; 
}