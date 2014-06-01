
#include <iostream>
#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/weak_ptr.hpp>



class CNode;
//
// Substring is: [beg, end)
//
typedef struct _DATA {
	size_t beg;
	size_t end;
	size_t *leaf_ind; // if NULL - a node is an internal node, otherwise is a leaf
	CNode *parent;
	
	_DATA (size_t i, size_t j, size_t *pl, CNode *par):
		beg (i), end (j), leaf_ind (pl), parent (par) {}
} DATA, *PDATA;


class CNode {
public:
	//
	// System methods
	//
	CNode (DATA * ptr): m_dat (ptr) {}
	virtual ~CNode () {}
	CNode (const CNode  &ref): m_dat (new DATA (*ref.m_dat.get ())) {}
	void swap (CNode & ref) {
		ref.m_dat.swap (m_dat);
	}
	CNode & operator = (const CNode & ref) {
		CNode tmp (ref);
		
		swap (tmp);
		
		return *this;
	}
	
	//
	// Set/get methods
	//
	;
	
	//
	// Working methods
	//
	;
	
private:
	boost::scoped_ptr <DATA> m_dat;
};















