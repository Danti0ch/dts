#include <stdlib.h>
#include <string.h>
#include <iostream>

namespace dts{
template <typename T, size_t N> class array{

private:
    char data_[N * sizeof(T)];
public:

    array(const T& obj){
        for(uint n_elem = 0; n_elem < N; n_elem++){
            new (data_ + n_elem * sizeof(T)) T(obj);
        }
    }
    //----------------------------------------------------------------------------------------//

    array(const array& obj){
        for(uint n_elem = 0; n_elem < N; n_elem++){
            new (data_ + n_elem * sizeof(T)) T(obj[n_elem]);
        }
    }
    //----------------------------------------------------------------------------------------//

    array operator=(const array& obj){

        if(&obj == this) return obj;
        
        for(uint n_elem = 0; n_elem < N; n_elem++){
            new (data_ + n_elem * sizeof(T)) T(obj[n_elem]);
        }

        return obj;
    }
    //----------------------------------------------------------------------------------------//

    T& operator[](uint n_elem){
        if(n_elem >= N) throw std::out_of_range("");
        return *(T*)(data_ + n_elem * sizeof(T));
    }
    //----------------------------------------------------------------------------------------//

    T operator[](uint n_elem) const{
        if(n_elem >= N) throw std::out_of_range("");
        return *(T*)(data_ + n_elem * sizeof(T));
    }
    //----------------------------------------------------------------------------------------//

    void* operator new(size_t size){
        std::cout << "array new was called\n";

        void* new_ptr = calloc(size, 1);

        if(new_ptr == NULL) throw std::bad_alloc();
        return new_ptr;
    }
    //----------------------------------------------------------------------------------------//
    
    void operator delete(void* ptr){
        std::cout << "delete was called\n";
        free(ptr);
    }
    //----------------------------------------------------------------------------------------//
    
    void* operator new[](std::size_t size){
        std::cout << "operator new[] was called\n";

        void* new_ptr = calloc(size, 1);

        if(new_ptr == NULL) throw std::bad_alloc();
        return new_ptr;
    }
    //----------------------------------------------------------------------------------------//
    
    void operator delete[](void* ptr){
        std::cout << "operator delete[] was called\n";
        free(ptr);
    }
    //----------------------------------------------------------------------------------------//
    
    ~array(){
        for(uint n_elem = 0; n_elem < N; n_elem++){
            ((T*)(data_ + n_elem * sizeof(T)))->~T();
        }
    }
    //----------------------------------------------------------------------------------------//
};
//----------------------------------------------------------------------------------------//

const uint INCREASE_RATIO   = 2;
const uint REDUCE_RATIO     = 8;
const uint DEFAULT_CAPACITY = 1;

template <typename T> class vector{
private:
    char* data_;
    size_t size_, capacity_;

    void free_alocated_mem(){
        for(uint n_elem = 0; n_elem < capacity_; n_elem++){
            (*(T*)(data_ + n_elem * sizeof(T))).~T();
        }
        delete [] data_;
    }
    //----------------------------------------------------------------------------------------//
    
    char* allocate_mem(size_t capacity, const T& def_val){

        char* ptr_data = new char[capacity * sizeof(T)];

        for(uint n_elem = 0; n_elem < capacity; n_elem++){
            new (ptr_data + n_elem * sizeof(T)) T(def_val);
        }

        return ptr_data;
    }
    //----------------------------------------------------------------------------------------//
    
    char* allocate_mem(size_t capacity){

        char* ptr_data = new char[capacity * sizeof(T)];

        for(uint n_elem = 0; n_elem < capacity; n_elem++){
            new (ptr_data + n_elem * sizeof(T)) T();
        }

        return ptr_data;
    }
    //----------------------------------------------------------------------------------------//
    
    char* allocate_mem(size_t capacity, const vector& from_mem){

        char* ptr_data = new char[capacity * sizeof(T)];

        size_t active_size = (capacity > from_mem.size()) ? from_mem.size() : capacity;

        for(uint n_elem = 0; n_elem < active_size; n_elem++){
            new (ptr_data + n_elem * sizeof(T)) T(from_mem[n_elem]);
        }

        return ptr_data;
    }
    //----------------------------------------------------------------------------------------//
    
    void increase_capacity(){

        char* tmp_data = allocate_mem(capacity_ * INCREASE_RATIO, *this);
        free_alocated_mem();

        data_     = tmp_data;
        capacity_ = capacity_ * INCREASE_RATIO;
    }
    //----------------------------------------------------------------------------------------//
    
    void reduce_capacity(){

        uint new_capacity = capacity_ / REDUCE_RATIO;

        char* tmp_data = allocate_mem(new_capacity, *this);
        free_alocated_mem();

        data_     = tmp_data;
        capacity_ = new_capacity;
    }
    //----------------------------------------------------------------------------------------//
    
public:

    vector():
        size_(0),
        capacity_(DEFAULT_CAPACITY)
    {
        data_ = allocate_mem(DEFAULT_CAPACITY);
    }
    //----------------------------------------------------------------------------------------//

    explicit vector(size_t capacity):
        size_(0),
        capacity_(capacity)
    {
        data_ = allocate_mem(capacity);
    }
    //----------------------------------------------------------------------------------------//

    vector(const vector& obj):
        size_(obj.size()),
        capacity_(obj.size())
    {
        data_ = allocate_mem(obj.size(), obj);
    }
    //----------------------------------------------------------------------------------------//

    ~vector(){
        free_alocated_mem();
    }
    //----------------------------------------------------------------------------------------//
    
    vector operator=(const vector& obj){

        if(&obj == this) return obj;

        free_alocated_mem();

        size_     = obj.size();
        capacity_ = size_;

        data_ = allocate_mem(capacity_, obj);
        
        return obj;
    }
    //----------------------------------------------------------------------------------------//

    T& operator[](uint n_elem){

        if(n_elem >= size_) throw std::out_of_range("");

        return *(T*)(data_ + n_elem * sizeof(T));
    }
    //----------------------------------------------------------------------------------------//

    T operator[](uint n_elem) const{

        if(n_elem >= size_) throw std::out_of_range("");

        return *(T*)(data_ + n_elem * sizeof(T));
    }
    //----------------------------------------------------------------------------------------//

    void push_back(const T& val){

        if(size_ + 1 >= capacity_) increase_capacity();

        *(T*)(data_ + (size_++) * sizeof(T)) = val;
    }
    //----------------------------------------------------------------------------------------//
    
    T pop_back(){
        
        if(size_ == 0) throw std::out_of_range("");

        if(size_ > 1 && (size_ - 1) * 8 <= capacity_) reduce_capacity();
        size_--;

        return *(T*)(data_ + (size_) * sizeof(T));
    }
    //----------------------------------------------------------------------------------------//
    
    void resize(size_t new_size){
        
        char* tmp_data = allocate_mem(new_size, *this);        
        free_alocated_mem();
        
        data_     = tmp_data;
        size_     = new_size;
        capacity_ = size_;
    }
    //----------------------------------------------------------------------------------------//
    
    void* operator new(size_t size){
        std::cout << "vector new was called\n";

        void* p_new_mem = calloc(size, 1);
        if(p_new_mem == NULL)  throw std::bad_alloc();

        return p_new_mem;
    }
    //----------------------------------------------------------------------------------------//
    
    void operator delete(void* ptr){
        std::cout << "vector delete was called\n";
        free(ptr);
    }
    //----------------------------------------------------------------------------------------//
    
    void* operator new[](size_t size){
        std::cout << "vector new[] was called\n";
    
        void* p_new_mem = calloc(size, 1);
        if(p_new_mem == NULL)  throw std::bad_alloc();

        return p_new_mem;
    }
    //----------------------------------------------------------------------------------------//
    
    void operator delete[](void* ptr){
        std::cout << "vector delete[] was called\n";
        free(ptr);
    }
    //----------------------------------------------------------------------------------------//
    
    constexpr size_t size()  const { return size_; }
    constexpr bool   empty() const { return size_ == 0; }
};
//----------------------------------------------------------------------------------------//
}
