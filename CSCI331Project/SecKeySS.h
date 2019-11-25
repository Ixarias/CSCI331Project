#ifndef SecKeySS
#define SecKeySS

#include "LinkedList.h"
#include <string>

using namespace std;

class SecKeySS {
private:
	string data;
	LinkedList<int> duplicates;
public:
	SecKeySS();
	SecKeySS(const SecKeySS& s);
	~SecKeySS();
	string getData() const { return data; };
	LinkedList<int> getDuplicates()const;
	void setData(const string s) { data = s; };
	void setDuplicates(const LinkedList<int> dup);
	bool operator <(const string& s)const { return data < s; };
	bool operator <(const SecKeySS& s)const { return data < s.getData; };
	bool operator >(const string& s)const { return data > s; };
	bool operator >(const SecKeySS& s)const { return data > s.getData; };
	bool operator ==(const string& s)const { return data == s; };
	bool operator ==(const SecKeySS& s)const { return data == s.getData; };
	void operator = (const SecKeySS& s)const;
};
SecKeySS::SecKeySS (const SecKeySS &s) { data = s.getData(); duplicates = LinkedList(s.getDuplicates()); }
SecKeySS::SecKeySS () { duplicates = LinkedList<int>(); }
SecKeySS::~SecKeySS () { ~duplicates(); }

bool operator <(const string& s1, const SecKeySS& s2)const {
	return s1 < s2.getData();
}
bool operator >(const string& s1, const SecKeySS& s2)const {
	return s1 > s2.getData();
}
bool operator ==(const string& s1, const SecKeySS& s2)const {
	return s1 == s2.getData();
}
void SecKeySS::operator = (const SecKeySS& s)const {
	s.data = data;
	int temp;
	for (int i = 1; i < duplicates.getItemCount() + 1; i++) {
		temp = duplicates.getEntry(i);
		s.insert(i, temp);
	}
}
LinkedList SecKeySS::getDuplicates() const {
	LinkedList<int> list;
	int temp;
	for (int i = 1; i < duplicates.getItemCount() + 1; i++) {
		temp = duplicates.getEntry(i);
		list.insert(i, temp);
	}
	return list;
}
void SecKeySS::setDuplicates(const LinkedList<int> list) {
	int temp;
	duplicates.clear();
	for (int i = 1; i < list.getItemCount() + 1; i++) {
		temp = list.getEntry(i);
		duplicates.insert(i, temp);
	}
}

#endif