/*My_vec.h
 Zhiyang Zeng
 
 Header file for a vector data structure.
 */


#include <ostream>

using namespace std;

template <typename T>
class My_vec {
    
    //member variables
    int size, capacity;
    T *ptr;
    void double_size();
public:
    //member functions
    My_vec();
    ~My_vec();
    My_vec(const My_vec<T>& vec);
    My_vec<T>& operator=(const My_vec<T>& vec);
    int get_size() const;
    int get_capacity() const;
    T& operator[](int i) const;
    T& operator[](int i);
    bool is_empty() const;
    T& elem_at_rank(int r) const;
    void insert_at_rank(int r, const T& elem);
    void replace_at_rank(int r, const T& elem);
    void remove_at_rank(int r);
    int next_nonvoid(int start) const; //unable to put back to private, need to be accessed by non-class member
    
};

template <typename T>
ostream& operator<<(ostream& out, const My_vec<T>& vec);

template <typename T>
int find_max_index(const My_vec<T>& v,int size);

template <typename T>
void sort_max(My_vec<T>& vec);

template <typename T>
My_vec<T>::My_vec()
:capacity(0),size(0),ptr(0){}

template <typename T>
My_vec<T>::My_vec(const My_vec<T>& vec){
    size=vec.get_size();
    capacity=vec.get_capacity();
    ptr=new T[capacity];  //shallow copy
    for (int i=0; i<capacity;i++){
        ptr[i]=vec.ptr[i];
    }
}


template <typename T>
My_vec<T>::~My_vec(){
    delete[] ptr;
}

template <typename T>
My_vec<T>& My_vec<T>::operator=(const My_vec<T>& vec){ //deep copy gets error on destructor: pointer being freed was not allocated, trying shallow copy
    
    size=vec.get_size();
    capacity=vec.get_capacity();
    for (int i=0; i<capacity;i++){
        ptr[i]=vec.ptr[i];
    }
    return *this;
}

template <typename T>
int My_vec<T>::get_size() const {return size;}

template <typename T>
int My_vec<T>::get_capacity() const {return capacity;}

template <typename T>
T& My_vec<T>::operator[](int i) const {
    return ptr[i];
}

template <typename T>
T& My_vec<T>::operator[](int i) {
    return ptr[i];
}

template <typename T>
bool My_vec<T>::is_empty() const {return size==0;}

template <typename T>
T& My_vec<T>::elem_at_rank(int r) const{
    return ptr[r];
}

template <typename T>
void My_vec<T>::insert_at_rank(int r, const T& elem) {
    //check if capacity is big enough, double if needed
    
    while (r+1>capacity || size+1>capacity) {double_size();} //
    
    //move everything to the right unless the insertion is 0
    if (ptr[r]==0){
        ptr[r]=elem;
    } else {
        for (int i = capacity-1; i>=r; i--){ //from i=size-1 to i=capacity-1
            ptr[i+1]=ptr[i];
        }
        ptr[r]=elem;
        
    }
    size++;
}

template <typename T>
void My_vec<T>::replace_at_rank(int r, const T& elem) {
    while (r+1>capacity || size+1>capacity) {double_size();} 
    if (ptr[r]==0) {size+=1;} //increment size when "replacing" an empty space
    ptr[r]=elem;
}

template <typename T>
void My_vec<T>::remove_at_rank(int r) {
    
    //if it's not 0 string or rank is invalid index (grater than size-1), do nothing
    if (ptr[r]!=0 && r<capacity) {
        size--;
        if (My_vec::is_empty()) {
            ptr=0; //without having to resize
        }
        else {
            for (int i=r; i<capacity-1; i++){  //from size to capacity
                ptr[i]=ptr[i+1];
            }
            ptr[r]=0;
        }
        
        
    }
}

//something wrong with double_size, does not handle 0 well

template <typename T>
void My_vec<T>::double_size() {
    //if original capacity is 0, make it 1
    if (My_vec::is_empty()){
        ptr=new T;
        capacity+=1;
    }
    else {
        T *new_ptr=new T[capacity*2];
        for (int i=0; i<capacity; i++){  //<= capacity: when capacity is 1, r=1 is not allocated
            new_ptr[i]=ptr[i];
        }
        capacity*=2;
        if (ptr!=0) delete[] ptr; //delete original
        ptr=new_ptr; //assign pointer to new
    }
}

template <typename T>
int My_vec<T>::next_nonvoid(int start) const{
    int target=start+1;
    while (ptr[target]==0){
        target+=1;
    }
    
    return target;
}


//non-class method
template <typename T>
ostream& operator<<(ostream& out, const My_vec<T>& vec){
    for (int i=0; i<vec.get_capacity();i++){  //if initialized to outside, size can be 3 but print is outside of 3 at 10
        
        if (vec.elem_at_rank(i)!=0) {
            out<<vec.elem_at_rank(i)<<" ";
        }
    }
    return out;
}

template <typename T>
int find_max_index(const My_vec<T>& v,int size){
    int max_index=(v.elem_at_rank(0)!=0)?0:v.next_nonvoid(0);  //start at the first nonvoid
    int next_search=v.next_nonvoid(max_index); //compare the first nonvoid the the next
    for (int i=0; i<size-1; i++){ //iterate as as many time as size of the array
        if (v.elem_at_rank(max_index)<(v.elem_at_rank(next_search))){ //update max index
            max_index=next_search;
        }
        next_search=v.next_nonvoid(next_search); //move on to next nonvoid
    }
    return max_index;
}

template <typename T>
void sort_max(My_vec<T>& vec){
    int max;
    int size=vec.get_size();
    My_vec<T> vec2(vec); //create a new vec using copy constructor to remember all the member locations
    int next_sort=(vec2.elem_at_rank(0)!=NULL)?0:vec2.next_nonvoid(0); //start at the first nonvoid
    for (int i=0; i<vec.get_size(); i++){ //iterate as many times as the size of array
        max=find_max_index(vec, size);  //find max index of current array
        vec2.replace_at_rank(next_sort, vec.elem_at_rank(max));  //replace the max at the first nonvoid location of vec2
        vec.replace_at_rank(max, 0);  //remove the max from old array to sort the next max
        size-=1; //1 less comparison at findmax
        next_sort=vec2.next_nonvoid(next_sort); //move the insertion location to the next nonvoid
        
    }
    vec=vec2;
}


