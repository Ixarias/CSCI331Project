/**
	\class SecKeySS SecKeySS.h "SecKeySS.h"
	\brief This is the class for Section Keys of the SS class
*/

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
	/** Default constructor */
	SecKeySS() { duplicates = LinkedList<int>(); };
	
	/** Constructor */
	SecKeySS(const SecKeySS& s);

	/** Deconstuctor */
	~SecKeySS();

	/** Gets data
	    \return data the data to be returned
	*/
	string getData() const { return data; };

	/** Gets duplicates
	    \returns LinkedList of itemType
	*/
	LinkedList<int> getDuplicates()const;

	/** Sets the data equal to argument 1
	    \param s a string to set data to
	*/
	void setData(const string s) { data = s; };

	/** Sets duplicates
	    \param LinkedList dup
	*/
	void setDuplicates( LinkedList<int> dup);

	/** Operator less than
	    \param s a reference to a string to check if than
	    \return true is data < s
	*/
	bool operator <(const string &s)const { return data < s; };


	/** Operator less than to check Sec key
	    \param s a string to check if than
	    \return true is data < s.data
	*/
	bool operator <(const SecKeySS& s)const { return data < s.data; };


	/** Operator geater than
	    \param s a reference to a string to check if > than
	    \return true is data > s
	*/
	bool operator >(const string &s)const { return data > s; };


	/** Operator greater than to check a Sec key
	    \param s a string to check if greater than
	    \return true is data > s.data
	*/
	bool operator >(const SecKeySS &s)const { return data > s.data; };

	/** Operator is equal
	    \param s a reference to a string
	    \return true if data is equal to s
	*/
	bool operator ==(const string &s)const { return data == s; };


	/** Operator is equal
	    \param s a reference to a secKeySS
	    \return true if data is equal to s.data
	*/
	bool operator ==(const SecKeySS &s)const { return data == s.data; };

	/** Operator equal for copy constructor
	    \param s a reference to a SecKeySS
	*/
	void operator = (const SecKeySS &s);
};

SecKeySS::SecKeySS(const SecKeySS& s) { data = s.getData(); setDuplicates(s.getDuplicates()); }
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
LinkedList<int> SecKeySS::getDuplicates() const {
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
