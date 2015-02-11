
// g++ -std=c++11 ukkonen.cpp -o ukk_algo
// g++ -std=c++11 ukkonen.cpp -o ukk_algo -DNDEBUG



#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cassert>



namespace NMSUkkonenAlgo {
	//
	class CNode;
	struct State {
		std::shared_ptr <CNode> node;
		size_t length;
		char ch;
	};


	struct Ret {
		std::shared_ptr <CNode> new_node;
		std::shared_ptr <CNode> internal_node;
	};


	class CNode {
	private:
		static const size_t chars_number = 256;
		static const unsigned char junior_ch = 0;
		// substring is [m_i, m_j)
		size_t m_i;
		// if m_j equals -1, then this node is a leaf
		size_t m_j; 
		std::weak_ptr <CNode> m_parent;
		std::weak_ptr <CNode> m_suff_link;
		std::vector <std::shared_ptr <CNode>> m_childs;
		
	public:
		size_t GetCharIndex (char ch) const {
			return static_cast <unsigned char> (ch) - junior_ch;
		}
		
		size_t GetEdgeLength (size_t current_end = -1) const {
			if (m_j == -1)
				assert (current_end != -1);
				return current_end - m_i;
				
			return m_j - m_i;
		}
		
		size_t GetBegin () const {
			return m_i;
		}
		
		size_t GetEnd () const {
			return m_j;
		}
		
		std::shared_ptr <CNode> GetParent () const {
			return m_parent.lock();
		}
		
		std::shared_ptr <CNode> GetSuffLink () const {
			return m_suff_link.lock();
		}
		
		void SetSuffLink (const std::shared_ptr <CNode> &ptr_link) {
			m_suff_link = ptr_link;
			return;
		}
		
		std::shared_ptr <CNode> GetChild (char ch) const {
			assert (m_j != -1);
			return m_childs[GetCharIndex (ch)];
		}
		
		void SetChild (const std::shared_ptr <CNode> &ptr_link, char ch) {
			m_childs[GetCharIndex (ch)] = ptr_link;			
			return;
		}
		
		
		CNode (size_t i, size_t j, const std::shared_ptr <CNode> & parent):
			m_i(i), m_j(j), m_parent(parent)
		{
			if (j != -1)
				m_childs.resize (chars_number);
			else
				m_childs.resize (0);
			
			return;
		}
		
		~ CNode () {}
	};



	class CSuffixTree {
	private:
		std::shared_ptr <CNode> m_root;
		std::string m_str;
		
		bool IsRoot (const std::shared_ptr <CNode> & ptr_link) const {
			return (ptr_link->GetBegin () == 0) && (ptr_link->GetEnd () == 0);
		}
		
	public:
	
		CSuffixTree (const std::string & str): m_root (new CNode (0, 0, std::shared_ptr <CNode> ())) {
			m_str = str;
			m_root->SetSuffLink (std::shared_ptr <CNode> ());
			
			return;
		}
		
		~ CSuffixTree () {}
		
		void ConstructTree () {
			State ret_inf = {m_root, 0, 0};
			
			for (size_t i = 0; i < m_str.length (); ++i)
				ret_inf = AppendChar (ret_inf.node, ret_inf.length, ret_inf.ch, i);
			
			return;
		}
		
		;
		
		State AppendChar (
			const std::shared_ptr <CNode> & node,
			size_t length,
			char ch,
			size_t i
		);
		
		//
	};
	
	
	State CSuffixTree::AppendChar (
		const std::shared_ptr <CNode> & node,
		size_t length,
		char ch,
		size_t i
	)
	{
		State ret_dat;
		
		//
		
		return ret_dat;
	}
	//
}



int main (int argc, char **argv) {
	std::string test_str = "ababc";
	test_str += '$';
	NMSUkkonenAlgo::CSuffixTree suff_tree (test_str);
	
	
	std::shared_ptr <NMSUkkonenAlgo::CNode> p;
	
	
	std::cout << p.get() << std::endl;
	
	
	return 0;
}







