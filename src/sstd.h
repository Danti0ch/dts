#include <stdlib.h>
#include <string.h>
#include <iostream>

namespace dts{
template <typename T, size_t N> class array{

private:
    T data_[N];
public:

    array(const T& obj){
        for(uint n_elem = 0; n_elem < N; n_elem++){
            data_[n_elem] = obj;
        }
    }
    //----------------------------------------------------------------------------------------//

    array(const array& obj){
        for(uint n_elem = 0; n_elem < N; n_elem++){
            data_[n_elem] = obj[n_elem];
        }
    }
    //----------------------------------------------------------------------------------------//

    array<T, N> operator=(const array& obj){

        if(&obj == this) return obj;
        
        for(uint n_elem = 0; n_elem < N; n_elem++){
            data_[n_elem] = obj[n_elem];
        }

        return obj;
    }
    //----------------------------------------------------------------------------------------//

    T& operator[](uint n_elem){
        
        return data_[n_elem];
    }
    //----------------------------------------------------------------------------------------//

    T operator[](uint n_elem) const{
        return data_[n_elem];
    }
    //----------------------------------------------------------------------------------------//

    void* operator new(std::size_t size){
        std::cout << "new was called\n";
        return ::operator new(size);
    }
    //----------------------------------------------------------------------------------------//
    
    void operator delete(void* ptr){
        std::cout << "delete was called\n";
        ::operator delete(ptr);
    }
    //----------------------------------------------------------------------------------------//
    
    void* operator new[](std::size_t size){
        std::cout << "operator new[] was called\n";
        return ::operator new[](size);
    }
    //----------------------------------------------------------------------------------------//
    
    void operator delete[](void* ptr){
        std::cout << "operator delete[] was called\n";
        ::operator delete[](ptr);
    }
    //----------------------------------------------------------------------------------------//
    
};
//----------------------------------------------------------------------------------------//

const uint INCREASE_RATIO = 2;
const uint REDUCE_RATIO   = 8;

template <typename T> class vector{
private:
    T* data_;
    size_t size_, capacity_;

    void increase_capacity(){

        T* tmp_data = new T[capacity_ * INCREASE_RATIO];

        memcpy(tmp_data, data_, size_ * sizeof(T));

        delete [] data_;

        data_     = tmp_data;
        capacity_ = capacity_ * INCREASE_RATIO;
    }
    //----------------------------------------------------------------------------------------//
    
    void reduce_capacity(){

        T* tmp_data = new T[capacity_ / REDUCE_RATIO];

        memcpy(tmp_data, data_, size_ * sizeof(T));

        delete [] data_;

        data_     = tmp_data;
        capacity_ = capacity_ / REDUCE_RATIO;
    }
    
public:

    vector(){
        data_     = new T[1];
        size_     = 0;
        capacity_ = 1;
    }
    //----------------------------------------------------------------------------------------//

    vector(size_t size){
        data_     = new T[size];
        size_     = 0;
        capacity_ = 1;
    }
    //----------------------------------------------------------------------------------------//

    vector(const vector& obj){

        size_     = obj.size();
        capacity_ = size_;

        data_ = new T[capacity_];

        for(uint n_elem = 0; n_elem < size_; n_elem++){
            data_[n_elem] = obj[n_elem];
        }
    }
    //----------------------------------------------------------------------------------------//

    ~vector(){ delete[] data_; }

    vector operator=(const vector& obj){

        if(&obj == this) return obj;

        delete [] data_;

        size_     = obj->size();
        capacity_ = size_;

        data_ = new T[capacity_];

        for(uint n_elem = 0; n_elem < size_; n_elem++){
            data_[n_elem] = obj[n_elem];
        }

        return obj;
    }
    //----------------------------------------------------------------------------------------//

    T& operator[](uint n_elem){

        if(n_elem > size_) throw std::out_of_range;

        return data_[n_elem];
    }
    //----------------------------------------------------------------------------------------//

    T operator[](uint n_elem) const{

        if(n_elem > size_) throw std::out_of_range;

        return data_[n_elem];
    }
    //----------------------------------------------------------------------------------------//

    void push_back(const T& val){

        if(size_ + 1 >= capacity_) increase_capacity();

        data_[size_++] = val;
    }
    //----------------------------------------------------------------------------------------//
    
    T pop_back(){
        
        if(size_ == 0) throw std::out_of_range;

        if((size_ - 1) * 8 <= capacity_) reduce_capacity();
        size_--;

        return data_[size_];
    }
    //----------------------------------------------------------------------------------------//
    
    void resize(size_t new_size){
        
        T* tmp_data = new T[new_size];

        size_t min_size = new_size < size_ ? new_size : size_;

        memcpy(tmp_data, data_, min_size * sizeof(T));
        delete [] data_;

        data_     = tmp_data;
        size_     = new_size;
        capacity_ = size_;
    }
    //----------------------------------------------------------------------------------------//
    
    void* operator new(std::size_t size){
        std::cout << "array new was called\n";

        void* p_new_mem = calloc(size, size);
        if(p_new_mem == NULL)  throw std::bad_alloc();

        return p_new_mem
    }
    //----------------------------------------------------------------------------------------//
    
    void operator delete(void* ptr){
        std::cout << "array delete was called\n";
        free(ptr);
    }
    //----------------------------------------------------------------------------------------//
    
    void* operator new[](std::size_t size){
        std::cout << "array new[] was called\n";
    
        void* p_new_mem = calloc(1, size);
        if(p_new_mem == NULL)  throw std::bad_alloc();

        return p_new_mem
    }
    //----------------------------------------------------------------------------------------//
    
    void operator delete[](void* ptr){
        std::cout << "X delete[]\n";
        free(ptr);
    }
    //----------------------------------------------------------------------------------------//
    
    // TODO: insert
    size_t size() const { return size_; }
    bool   empty() const { return size_ == 0; }

};
//----------------------------------------------------------------------------------------//
}
