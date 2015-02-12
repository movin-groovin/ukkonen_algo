
// g++ -std=c++11 ukkonen.cpp -o ukk_algo -g
// g++ -std=c++11 ukkonen.cpp -o ukk_algo -DNDEBUG



#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <exception>
#include <stdexcept>

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
		std::shared_ptr <CNode> internal_node; // exist node
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
			if (m_j == -1) {
				assert (current_end != -1);
				return current_end - m_i;
			}
			
			return m_j - m_i;
		}
		
		size_t GetBegin () const {
			return m_i;
		}
		
		void SetBegin (size_t i) {
			m_i = i;
			return;
		}
		
		size_t GetEnd () const {
			return m_j;
		}
		
		std::shared_ptr <CNode> GetParent () const {
			return m_parent.lock();
		}
		
		void SetParent (std::shared_ptr <CNode> & node) {
			// we don't use assert, because the parent can be changed
			m_parent = node;
			
			return;
		}
		
		std::shared_ptr <CNode> GetSuffLink () const {
			return m_suff_link.lock();
		}
		
		void SetSuffLink (const std::shared_ptr <CNode> & suff_link)
		{
			assert (m_suff_link.lock().get() == NULL);
			
			m_suff_link = suff_link;
			
			return;
		}
		
		std::shared_ptr <CNode> GetChild (char ch) const {
			assert (m_j != -1);
			
			return m_childs[GetCharIndex (ch)];
		}
		
		void SetChild (
			const std::shared_ptr <CNode> & child,
			char ch
		)
		{
			// we don't use assert, because the childs can be changed
			m_childs[GetCharIndex (ch)] = child;
			
			return;
		}
		
		
		CNode (
			size_t i,
			size_t j,
			const std::shared_ptr <CNode> & parent
		):
			m_i(i),
			m_j(j),
			m_parent(parent)
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
	
		CSuffixTree ():
			m_root (new CNode (0, 0, std::shared_ptr <CNode> ()))
		{
			m_root->SetSuffLink (m_root);
			
			return;
		}
		
		~ CSuffixTree () {}
		
		void ConstructByUkkonenAlgo (const std::string & str) {
			State ret_inf = {m_root, 0, 0};
			
			m_str = str;
			for (size_t i = 0; i < m_str.length (); ++i)
				ret_inf = AppendChar (ret_inf.node, ret_inf.length, ret_inf.ch, i);
			
			return;
		}
		
		std::shared_ptr <CNode> InsertNode (std::shared_ptr <CNode> &parent, size_t i)
		{
			std::shared_ptr <CNode> new_node (new CNode (i, -1, parent));
			parent->SetChild (new_node, m_str[i]);
			
			return new_node;
		}
		
		std::shared_ptr <CNode> SplitEdge (std::shared_ptr <CNode> &base, size_t len) {
			std::shared_ptr <CNode> parent = base->GetParent ();
			std::shared_ptr <CNode> new_node {new CNode (
					base->GetBegin (),
					base->GetBegin () + len,
					parent
				)
			};
			
			new_node->SetChild (base, m_str [base->GetBegin () + len]);
			parent->SetChild (new_node, m_str[base->GetBegin ()]);
			
			base->SetBegin (base->GetBegin () + len);
			base->SetParent (new_node);
			
			return new_node;
		}
		
		Ret AddSuffix (
			std::shared_ptr <CNode> node_walk_from,
			char ch,
			size_t len,
			size_t i
		);
		
		State AppendChar (
			const std::shared_ptr <CNode> & node,
			char ch,
			size_t length,
			size_t i
		);
		
		//
	};
	
	
	Ret CSuffixTree::AddSuffix (
		std::shared_ptr <CNode> node_walk_from,
		char ch,
		size_t len,
		size_t i
	)
	{
		Ret ret_dat {nullptr, nullptr};
		
		// 'len' is everything less than 
		// 'node_walk_from->GetChild (ch)->GetEdgeLength(i)'
#ifndef NDEBUG
		if (node_walk_from->GetChild (ch))
			assert (node_walk_from->GetChild (ch)->GetEdgeLength (i) > len);
#endif
		
		if (!len)
		{
			if (node_walk_from->GetChild (m_str [i])) {
				return ret_dat;
			}
			else {
				InsertNode (node_walk_from, i);
				return Ret {nullptr, node_walk_from};
			}
		}
		else
		{
			std::shared_ptr <CNode> node_begin = node_walk_from->GetChild (ch);
			if (m_str[node_begin->GetBegin () + len] == m_str[i]) {
				return ret_dat;
			}
			else {
				std::shared_ptr <CNode> new_node = SplitEdge (node_begin, i);
				InsertNode (new_node, i);
				return Ret {new_node, nullptr};
			}
		}
		
		return ret_dat;
	}
	
	
	State CSuffixTree::AppendChar (
		const std::shared_ptr <CNode> & node,
		char ch,
		size_t length,
		size_t i
	)
	{
		Ret ret;
		std::shared_ptr <CNode> prev_node;
		std::shared_ptr <CNode> exist_node (node);
		
		
		while (true)
		{
			ret = AddSuffix (exist_node, ch, length, i);
			
			// First case: the suffix already exists at the tree
			if (!ret.new_node && !ret.internal_node) 
			{
				if (!ch) { // && !length
					assert (length == 0);
					
					return State {std::shared_ptr<CNode> (), 0, 0};
				}
				else if (exist_node->GetChild (ch)->GetEdgeLength (i) == length + 1) {
					exist_node = exist_node->GetChild (ch);
					return State {exist_node, 0, 0};
				}
				else {
					return State {exist_node, length + 1, ch};
				}
			}
			// Second case: exists edge has been splited, the edge of 
			// 1 character length has been inserted with new node
			else if (ret.new_node)
			{
				if (prev_node)
					prev_node->SetSuffLink (ret.new_node);
				prev_node = ret.new_node;
				
				if (ret.new_node->GetParent () == m_root) {
					if (ret.new_node->GetEdgeLength (i) == 1) {
						ch = 0;
						length = 0;
						exist_node = ret.new_node->GetParent (); // = m_root
						ret.new_node->SetSuffLink(m_root);
					}
					else {
						--length;
						exist_node = ret.new_node->GetParent();
						ch = m_str[ret.new_node->GetBegin() + 1];
					}
				}
				else {
					length = ret.new_node->GetEdgeLength(i);
					ch = m_str[ret.new_node->GetBegin()];
					exist_node = ret.new_node->GetParent()->GetSuffLink();
				}
			}
			// Third case: at exist (inertnal of course) node has been inserted
			// an one character length edge with the node at it's end
			else
			{
				length = 0;
				ch = 0;
				exist_node = ret.internal_node->GetSuffLink ();
			}
			//
		}
		
		
		assert (1 != 1);
		// never reachs this place
	}
	
	// namespace
}


std::string ReadFromStreamUntilEof (std::istream & in_s, char no_ch) {
	std::string buf, ret;
	
	while (std::getline (in_s, buf, '\n')) {
		if (buf.end () != std::find (buf.begin (), buf.end (), no_ch)) {
			throw std::runtime_error (
				"Incorrect symbol in input string: " + std::string () + no_ch
			);
		}
		ret += buf;
	}
	
	return ret;
}


int main (int argc, char **argv) {
	try {
		const char fin_ch = '$';
		std::string test_str = "ababc";
		NMSUkkonenAlgo::CSuffixTree suff_tree;
		
#ifdef NDEBUG
		test_str = ReadFromStreamUntilEof (std::cin, fin_ch);
#endif
		
		test_str += fin_ch;
		suff_tree.ConstructByUkkonenAlgo (test_str);
		std::cout << test_str << std::endl;
		
		return 0;
	} catch (std::exception & Exc) {
		std::cout << Exc.what() << std::endl;
		
		return 0;
	}
}







