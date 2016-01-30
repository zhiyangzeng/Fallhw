#include "My_vec.h"
#include <stdexcept>
using namespace std;


My_vec::My_vec()
:capacity(0),size(0),ptr(NULL){}

My_vec::My_vec(const My_vec& vec){
	size=vec.get_size();
	capacity=vec.get_capacity();
	ptr=new char[capacity];  //shallow copy
    for (int i=0; i<capacity;i++){
        ptr[i]=vec.ptr[i];
    }
}

My_vec::~My_vec(){
	delete[] ptr;
}

My_vec& My_vec::operator=(const My_vec& vec){ //deep copy gets error on destructor: pointer being freed was not allocated, trying shallow copy
	
    size=vec.get_size();
    capacity=vec.get_capacity();
    for (int i=0; i<capacity;i++){
        ptr[i]=vec.ptr[i];
    }
    return *this;
}

int My_vec::get_size() const {return size;}

int My_vec::get_capacity() const {return capacity;}

char& My_vec::operator[](int i) const {
    return ptr[i];
}
char& My_vec::operator[](int i) {
    return ptr[i];
}
	
bool My_vec::is_empty() const {return size==0;}	

char& My_vec::elem_at_rank(int r) const{
    return ptr[r];
}
void My_vec::insert_at_rank(int r, const char& elem) {
    //check if capacity is big enough, double if needed
    
    while (r+1>capacity || size+1>capacity) {double_size();} //
    //move everything to the right
    if (ptr[r]==NULL){
        ptr[r]=elem;
    } else {
        for (int i = capacity-1; i>=r; i--){
            ptr[i+1]=ptr[i];
        }
        ptr[r]=elem;

    }
    size++;     //change size
}
void My_vec::replace_at_rank(int r, const char& elem) {
    while (r+1>capacity || size+1>capacity) {double_size();} 
    if (ptr[r]==NULL) {size+=1;} //increment size when "replacing" an empty space
    ptr[r]=elem;
}

void My_vec::remove_at_rank(int r) {
    
//if it's not null string or rank is invalid index (grater than size-1), do nothing
   if (ptr[r]!=NULL && r<capacity) {
        size--;
        if (My_vec::is_empty()) {
            ptr=NULL; //without having to resize
        }
        else {
            for (int i=r; i<capacity-1; i++){
                ptr[i]=ptr[i+1];
            }
			ptr[r]=NULL;
        }
        
        
    }
}

void My_vec::double_size() {
    //if original capacity is 0, make it 1
    if (My_vec::is_empty()){
        ptr=new char;
        capacity+=1;
    } else {
        char *new_ptr=new char[capacity*2];
        for (int i=0; i<capacity; i++){  //<= capacity: when capacity is 1, r=1 is not allocated
            new_ptr[i]=ptr[i];
        }
        capacity*=2;
        if (ptr!=NULL) delete[] ptr; //delete original
        ptr=new_ptr; //assign pointer to new
    }
}

int My_vec::next_nonvoid(int start) const{
    int target=start+1;
    while (ptr[target]==NULL){
        target+=1;
    }
    
    return target;
}
	
	//non-class method
ostream& operator<<(ostream& out, const My_vec& vec){
    for (int i=0; i<vec.get_capacity();i++){  //if initialized to bigger than size, size can be 3 but print is outside of 3 at 10
        if (vec.elem_at_rank(i)!=NULL) {
            out<<vec.elem_at_rank(i)<<" ";
        }
    }
    return out;
}

int find_max_index(const My_vec& v,int size){
    int max_index=(v.elem_at_rank(0)!=NULL)?0:v.next_nonvoid(0);  //start at the first nonvoid
    int next_search=v.next_nonvoid(max_index); //compare the first nonvoid the the next
    for (int i=0; i<size-1; i++){ //iterate as as many time as size of the array
        if (v.elem_at_rank(max_index)<(v.elem_at_rank(next_search))){ //update max index
            max_index=next_search;
        }
        next_search=v.next_nonvoid(next_search); //move on to next nonvoid
    }
    return max_index;
}

void sort_max(My_vec& vec){
    int max;
    int size=vec.get_size();
    My_vec vec2(vec); //create a new vec using copy constructor to remember all the member locations
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