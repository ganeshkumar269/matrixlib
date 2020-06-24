template<typename T>
void Matrix<T>::generateId(){id = id_gen++;}
template<typename T>
int Matrix<T>::getId()const{return id;}
template<typename T>
T Matrix<T>::getElement(uint32_t _m,uint32_t _n)const {return arr[(_m*this->n) + _n];}
template<typename T>
T Matrix<T>::setElement(uint32_t _m,uint32_t _n,T t){arr[(_m*this->n) + _n] = t; return t;}
template<typename T>
T Matrix<T>::operator()(uint32_t _m,uint32_t _n)const{return this->getElement(_m,_n);}
template<typename T>
T Matrix<T>::operator()(uint32_t _m,uint32_t _n,T t){return this->setElement(_m,_n,t);}
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
void Matrix<T>::fill(T t){std::fill(this->arr,arr+this->m*this->n,t);}

