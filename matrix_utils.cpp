template<typename T>
void Matrix<T>::alloc(uint32_t size){
    allocSize = m*n; 
    if(this->arr != nullptr)
        dealloc();
    this->arr = new T[size+1];
    allocSize=size;
    if(verbose)cout << "Memory Allocated: " << size <<" "<< getId()<< endl;
}
template<typename T>
void Matrix<T>::dealloc(){
    if(verbose)cout << "Memory deallocated: "<< allocSize<< " "<< getId()<< endl;
    delete[] arr;
}

template<typename T>
void Matrix<T>::resize(uint32_t size){ //only place where allocMem is called
    T* tmp = arr;
    arr = nullptr;
    alloc(size);
    if(tmp != nullptr)  copy_n(tmp,m*n < size ? m*n : size,arr);
    delete[] tmp;
}
template<typename T>
uint32_t Matrix<T>::size()const{return m*n;}

template<typename T>
void Matrix<T>::print(ostream& out,char sep,string tip)const {
    for(uint32_t i = 0;i < m;++i){
        out << tip[0];
        for(uint32_t j =0; j < n-1; ++j)
            out << getElement(i,j) << sep;
        out << getElement(i,n-1);
        out << tip[1] << endl;
    }
} 
