#ifndef SECKEYSS
#define SECKEYSS

#include "LinkedList.h"
//#include <string>

using namespace std;

class SecKeySS {
private:
	string data;
	LinkedList<int> duplicates;
public:
	SecKeySS();
	SecKeySS( SecKeySS& s);
	~SecKeySS();
	string getData() { return data; };
	LinkedList<int> getDuplicates();
	void setData(const string s) { data = s; };
	void setDuplicates( LinkedList<int> dup);
	bool operator <(const string &s)const { return data < s; };
	bool operator <(const SecKeySS& s)const { return data < s.data; };
	bool operator >(const string &s)const { return data > s; };
	bool operator >(const SecKeySS &s)const { return data > s.data; };
	bool operator ==(const string &s)const { return data == s; };
	bool operator ==(const SecKeySS &s)const { return data == s.data; };
	void operator = (const SecKeySS &s);
};
SecKeySS::SecKeySS (SecKeySS& s) { data = s.getData(); setDuplicates(s.getDuplicates()); }
SecKeySS::SecKeySS () { }
SecKeySS::~SecKeySS() { duplicates.clear(); }

bool operator <(const string s1, SecKeySS &s2) {
	return s1 < s2.getData();
}
bool operator >(const string s1, SecKeySS s2) {
	return s1 > s2.getData();
}
bool operator ==(const string s1, SecKeySS s2) {
	return s1 == s2.getData();
}
void SecKeySS::operator = (const SecKeySS &s){
	data = s.data;
	duplicates = s.duplicates;
}
LinkedList<int> SecKeySS::getDuplicates()  {
	LinkedList<int> list;
	int temp;
	for (int i = 1; i < duplicates.getItemCount() + 1; i++) {
		temp = duplicates.getEntry(i);
		list.insert(i, temp);
	}
	return list;
}
void SecKeySS::setDuplicates(LinkedList<int> list) {
	int temp;
	duplicates.clear();
	for (int i = 1; i < list.getItemCount() + 1; i++) {
		temp = list.getEntry(i);
		duplicates.insert(i, temp);
	}
}

#endif