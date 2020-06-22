template<typename T>
int Matrix<T>::id_gen = 0;
template<typename T>
Matrix<T>::Matrix():m(0),n(0),allocSize(0),arr(nullptr){
    cout << "Matrix reference created,id: ";generateId(); 
    cout << getId() <<'\n';
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
