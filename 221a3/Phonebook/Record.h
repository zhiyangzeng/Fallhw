#include <iostream>

using namespace std;

class Record
{
private:
string last_name;
string first_name;
string uin;
string phone_num;

public:
Record(){last_name=""; first_name=""; uin=""; phone_num="";}
Record(string l,string f,string u,string p){last_name=l; first_name=f; uin=u; phone_num=p;}
string get_last_name() const {return last_name;}
string get_first_name() const {return first_name;}
string get_uin() const {return uin;}
string get_phone_num() const {return phone_num;}
void set_last_name(string s){last_name=s;}
void set_first_name(string s){first_name=s;}
void set_uin(string s){uin=s;}
void set_phone_num(string s){phone_num=s;}
bool operator<(const Record& r) const;
};


bool Record::operator< (const Record& r) const {
	//compare last name
	if(get_last_name() != r.get_last_name())
	{
		if(get_last_name() < r.get_last_name())
			return true;
		else
			return false;
	}
	if(get_first_name() != r.get_first_name())
	{
		if(get_first_name() < r.get_first_name())
			return true;
		else
			return false;
	}
	if(get_uin() != r.get_uin())
	{
		if(get_uin() < r.get_uin())
			return true;
		else
			return false;
	}
	return false;
}

ostream& operator<<(ostream& out, const Record& r) 
{
	out<<r.get_last_name()<<", ";
	out<<r.get_first_name()<<". UIN: ";
	out<<r.get_uin()<<". Phone: ";
	out<<r.get_phone_num()<<endl;
	return out;
}