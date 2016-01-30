/*My_vec.h
Zhiyang Zeng
 
Header file for a vector data structure.
*/

#include <ostream>

using namespace std;

class My_vec {
	
	//member variables
	int size, capacity;
	char *ptr;
	void double_size();
	
public:	
	//member functions
	My_vec();
	~My_vec();
	My_vec(const My_vec& vec);
	My_vec& operator=(const My_vec& vec);
	int get_size() const;
	int get_capacity() const;
	char& operator[](int i) const;
	char& operator[](int i);
	bool is_empty() const;
	char& elem_at_rank(int r) const;
	void insert_at_rank(int r, const char& elem);
	void replace_at_rank(int r, const char& elem);
	void remove_at_rank(int r);
    int next_nonvoid(int start) const; //unable to put back to private, need to be accessed by non-class member
	
};
	
	ostream& operator<<(ostream& out, const My_vec& vec);
	int find_max_index(const My_vec& v,int size);
	void sort_max(My_vec& vec);