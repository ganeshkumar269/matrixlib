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
    Dim d = getDim();
    uint _size = this->size();
    vector<bool> changed(_size,false);
    uint i = 1;
    while(i < _size-1){
        uint cycleBegin = i;
        T tmp = arr[i];
        do{
            uint newValIndex = (i*d.first) % (_size - 1); 
            swap(tmp,arr[newValIndex]);
            changed[i] = true;
            i = newValIndex;
        }while(i != cycleBegin);
        for(i = 1; i < _size-1 && changed[i];i++);
    }
    setDim({d.second,d.first});
}




template<typename T>
T Matrix<T>::det(){ 
//https://www.geeksforgeeks.org/determinant-of-a-matrix/
	T num1,num2,det = 1,index,total = 1;
	T temp[n + 1]; 
	Dim dim = getDim();
    Matrix tempMatrix(dim,getData());
	for(uint i = 0; i < dim.first; i++) 
	{ 
		index = i;
		while(tempMatrix.getElement(index,i) == 0 && index < dim.first)
			index++;	 
		if(index == dim.first)  
            continue; 
		if(index != i) 
		{ 
			for(uint j = 0; j < dim.first; j++){
                T _t = tempMatrix.getElement(index,j);
                tempMatrix.setElement(index,j,tempMatrix.getElement(i,j));
                tempMatrix.setElement(i,j,_t);
            }
            det = det*pow(-1,index-i);	 
    	} 
        for(int j = 0; j < n; j++) 
            temp[j] = tempMatrix.getElement(i,j); 
        for(int j = i+1; j < n; j++) 
        { 
            num1 = temp[i]; //value of diagonal element 
            num2 = tempMatrix.getElement(j,i); //value of next row element 
            for(uint k = 0; k < dim.first; k++) 
                tempMatrix.setElement(j,k, (num1 * tempMatrix.getElement(j,k)) - (num2 * temp[k])); 
            total = total * num1; // Det(kA)=kDet(A); 
        }           
    }        
	for(int i = 0; i < n; i++) 
		det = det * tempMatrix.getElement(i,i); 
	return (det/total);
} 