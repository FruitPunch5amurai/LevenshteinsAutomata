#ifndef __LEVENSHTEINDFA_H_
#define __LEVENSHTEINDFA_H_

#include <list>
#include <map>
#include "LevenshteinNFA.h"
#include "Trie.h"
namespace LevenshteinAutomata
{
	class LevenshteinDFA
	{
	public:
		LevenshteinDFA();
		~LevenshteinDFA();
		static LevenshteinDFA* SubsetConstruct(LevenshteinNFA *nfa);
		static std::list<int> EpsilonClosure(LevenshteinNFA *nfa, std::list<int> states);
		int start;
		std::list<int> *finalStates;
		std::map<std::pair<int, char>, int> *transTable;
		std::map<int, int> *defaultTrans;
		std::list<char> uniqueChars;
		void Search(Trie *trie, int start, TrieNode* node, std::list<string> &output);
	};
}
#endif