
//
// g++ -std=c++11 -I /usr/local/include/boost-1_54/ ukkonen.cpp -o ukk
//

#include <iostream>
#include <string>
#include <vector>
#include <map>



namespace NMUkkonen {
	//
	// Substring is: [i, j)
	//
	struct CNode {
		const static size_t ALPHABET_SIZE = 26; // for a-z characters
		size_t m_i;
		size_t m_j; // if -1, that the node is a leaf and j equals the length of all string
		CNode* m_parent;
		CNode* m_sufLink;
		CNode* m_childArr[ALPHABET_SIZE];
		
		CNode (size_t i, size_t j, CNode *par, CNode *sflink = NULL):
			m_i (i), m_j (j), m_parent (par), m_sufLink(sflink)
		{
			for (int i = 0; i < ALPHABET_SIZE; ++i) m_childArr[i] = NULL;
		}
		~ CNode () {
			for (int i = 0; i < ALPHABET_SIZE; ++i)
				if (m_childArr[i]) delete m_childArr[i];
		}
		
		size_t CharIndex(char ch) const {return ch - 'a';}
		bool IsRoot(CNode * pNode) const {return !(pNode->m_j - pNode->m_i);}
	};
	typedef CNode* PCNode;
	
	//
	// Algo class
	//
	class CUkkonenAlgo {
	public:
		CUkkonenAlgo (const std::string & str): m_text(str) {
			m_root = new CNode(0, 0, NULL);
		}
		~ CUkkonenAlgo() {if (m_root) delete m_root;}
		
	private:
		PCNode m_root;
		std::string m_text;
	};
}



int main (int argc, char *argv[]) {
	std::string dat = "ababc";
	
	
	
	return 0;
}
















