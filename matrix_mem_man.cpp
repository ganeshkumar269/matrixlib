template<typename T>
void Matrix<T>::alloc(uint32_t _size){
    if(this->arr != nullptr)
        dealloc();
    this->arr = new T[_size];
    allocSize=_size;
    if(verbose)cout << "Memory Allocated: " << _size <<" "<< getId()<< endl;
}
template<typename T>
void Matrix<T>::dealloc(){
    if(verbose)cout << "Memory deallocated: "<< size() << " "<< getId()<< endl;
    delete[] arr;
}

template<typename T>
void Matrix<T>::resize(uint32_t _size){ //only place where alloc is called
    T* tmp = arr;
    arr = nullptr;
    alloc(_size);
    if(tmp != nullptr)  std::copy_n(tmp,m*n < _size ? m*n : _size,arr);
    delete[] tmp;
}
