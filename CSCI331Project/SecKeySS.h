/**
	\class SecKeySS SecKeySS.h "SecKeySS.h"
	\brief This is the class for Section Keys of the SS class
*/

#ifndef SECKEYSS
#define SECKEYSS

#include "LinkedList.h"
//#include <string>

using namespace std;
template <typename T>
class SecKeySS {
private:
	T data;
	LinkedList<T> duplicates;
	LinkedList<T> list;
public:
	/** Default constructor */
	//template <typename T>
	SecKeySS() { duplicates = LinkedList<T>(); };
	
	/** Copy Constructor */
//	template <typename T>
//	SecKeySS( SecKeySS<T> &s);

	/** Deconstuctor */
//	template <typename T>
	~SecKeySS();

	/** Gets data
	    \return data the data to be returned
	*/
//	template <typename T>
	T getData() const { return data; };

	/** Gets duplicates
	    \returns LinkedList of itemType
	*/
	//template <typename T>
	LinkedList<T> getDuplicates() ;

	/** Sets the data equal to argument 1
	    \param s a string to set data to
	*/
//	template <typename T>
	void setData(const T s) { data = s; };

	/** Sets duplicates
	    \param LinkedList dup
	*/
//	template <typename T>
	void setDuplicates( LinkedList<T> dup);

	/** Operator less than
	    \param s a reference to a string to check if than
	    \return true is data < s
	*/
//	template <typename T>
	bool operator <(const T &s)const { return data < s; };


	/** Operator less than to check Sec key
	    \param s a string to check if than
	    \return true is data < s.data
	*/
//	template <typename T>
	bool operator <(const SecKeySS<T>& s)const { return data < s.data; };


	/** Operator geater than
	    \param s a reference to a string to check if > than
	    \return true is data > s
	*/
//	template <typename T>
	bool operator >(const T &s)const { return data > s; };


	/** Operator greater than to check a Sec key
	    \param s a string to check if greater than
	    \return true is data > s.data
	*/
//	template <typename T>
	bool operator >(const SecKeySS<T> &s)const { return data > s.data; };

	/** Operator is equal
	    \param s a reference to a string
	    \return true if data is equal to s
	*/
//	template <typename T>
	bool operator ==(const T &s)const { return data == s; };


	/** Operator is equal
	    \param s a reference to a secKeySS
	    \return true if data is equal to s.data
	*/
//	template <typename T>
	bool operator ==(const SecKeySS<T> &s)const { return data == s.data; };

	/** Operator equal for copy constructor
	    \param s a reference to a SecKeySS
	*/
//	template <typename T>
	void operator = (const SecKeySS<T> &s);
};
//template <typename T>
//SecKeySS<T>::SecKeySS( SecKeySS<T> &s) { data = s.getData(); setDuplicates(s.getDuplicates()); }
template <typename T>
SecKeySS<T>::~SecKeySS() { duplicates.clear(); }
template <typename T>
bool operator <(const T s1, SecKeySS<T> &s2) {
	return s1 < s2.getData();
}
template <typename T>
bool operator >(const T s1, SecKeySS<T> s2) {
	return s1 > s2.getData();
}
template <typename T>
bool operator ==(const T s1, SecKeySS<T> s2) {
	return s1 == s2.getData();
}
template <typename T>
void SecKeySS<T>::operator = (const SecKeySS<T> &s){
	data = s.data;
	duplicates = s.duplicates;
}
template <typename T>
LinkedList<T> SecKeySS<T>::getDuplicates() {
	T temp;
	for (int i = 1; i < duplicates.getItemCount() + 1; i++) {
		temp = duplicates.getEntry(i);
		list.insert(i, temp);
	}
	return list;
}
template <typename T>
void SecKeySS<T>::setDuplicates(LinkedList<T> list) {
	T temp;
	duplicates.clear();
	for (int i = 1; i < list.getItemCount() + 1; i++) {
		temp = list.getEntry(i);
		duplicates.insert(i, temp);
	}
}

#endif
