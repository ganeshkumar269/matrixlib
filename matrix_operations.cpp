template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& t){
    if(verbose)cout << "Multiply by lvalue " << id << " " << t.getId()<< endl;
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
    if(verbose)cout << "Add by lvalue " << this->getId() << " " << t.getId()<< endl;
    assert(this->getDim() == t.getDim());
    Matrix<T> temp(t.getDim());
    // for(uint32_t i=0;i<size();++i)
    //     temp.setElement(i/n,i%n,getElement(i/n,i%n)+t.getElement(i/n,i%n));
    transform(getData(), getData()+m*n, t.getData(), temp.getData(), plus<T>());
    return temp;
}
template<typename T>
Matrix<T> Matrix<T>::operator+(Matrix<T>&& t){
    if(verbose)cout << "Add by rvalue " << getId() << " " << t.getId()<< endl;
    assert(this->getDim() == t.getDim());
    transform(this->getData(), this->getData()+this->m*this->n, t.getData(), t.getData(), plus<T>());
    return t;
}
        
template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& t){
    if(verbose)cout << "Subtract by lvalue "<< id << " " << t.getId() << endl;
    assert(this->getDim() == t.getDim());
    Matrix<T> temp(t.getDim());
    transform(this->getData(), this->getData()+this->m*this->n, t.getData(), temp.getData(), minus<T>());
    return temp;
}
template<typename T>
Matrix<T> Matrix<T>::operator-(Matrix<T>&& t){
    if(verbose)cout << "Subtract by rvalue " << endl;
    assert(this->getDim() == t.getDim());
    transform(this->getData(), this->getData()+this->m*this->n, t.getData(), t.getData(), minus<T>());
    return t;
}
template<typename T>
void Matrix<T>::operator = (const Matrix<T>& t){
    if(verbose)cout << "Copy of Matrix "<< id << " " << t.getId() << endl;
    setDim(t.getDim());
    resize(t.size());
    setPrintStyle(t.getPrintStyle());
    copy(t.getData());
}      
template<typename T>
void Matrix<T>::operator = (Matrix<T>&& t){
    if(verbose)cout << "Move of Matrix "<< id << " " << t.getId() << endl;
    setDim(t.getDim());
    allocSize = t.size();
    setData(t.getData());
    setPrintStyle(t.getPrintStyle());
    t.resetData();
}      
template<typename T>
Matrix<T> Matrix<T>::transpose(const Matrix<T>& t){
    Dim d = t.getDim();
    Matrix<T> tempMatrix(d.second,d.first);    
    for(uint i =0 ;i < d.first;i++)
    for(uint j =0 ;j < d.second;j++){
        tempMatrix(j,i,t.getElement(i,j));
    }
    return tempMatrix;
}
template<typename T>
void Matrix<T>::transpose(){
// https://www.geeksforgeeks.org/inplace-m-x-n-size-matrix-transpose/
//Incorrect Implementation
    Dim d = getDim();
    uint _size = this->size();
    vector<bool> changed(_size,false);
    uint i = 1;
    while(i < _size-1){
        uint oldValIndex = i;
        uint newValIndex = (i*d.first) % (_size - 1); 
        while(changed[i])
            oldValIndex = (i*d.second) % (_size-1);  
        swap(arr[oldValIndex],arr[newValIndex]);
        changed[newValIndex] = true;
        i++;
    }
    setDim({d.second,d.first});
}