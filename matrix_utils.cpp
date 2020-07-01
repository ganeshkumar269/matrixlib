template<typename T>
uint32_t Matrix<T>::size()const{return m*n;}

template<typename T>
void Matrix<T>::print(ostream& out)const {
    for(uint32_t i = 0;i < m;++i){
        out << printStyle.tip[0];
        for(uint32_t j =0; j < n-1; ++j)
            out << getElement(i,j) << printStyle.sep;
        out << getElement(i,n-1);
        out << printStyle.tip[1] << printStyle.end;
    }
} 
template<typename T>
void Matrix<T>::setPrintStyle(PrintStyle printStyle){
    this->printStyle.tip[0] = printStyle.tip[0];
    this->printStyle.tip[1] = printStyle.tip[1];
    this->printStyle.sep = printStyle.sep;
    this->printStyle.end = printStyle.end;
}
template<typename T>
void Matrix<T>::setPrintStyle(char sep,char end,const char tip[2]){
    printStyle.sep = sep;
    printStyle.end = end;
    printStyle.tip[0]=tip[0];
    printStyle.tip[1]=tip[1];
}
template<typename T>
PrintStyle Matrix<T>::getPrintStyle()const{return printStyle;}
