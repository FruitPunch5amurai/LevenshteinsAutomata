#ifndef __LEVENSHTEINNFA_H_
#define __LEVENSHTEINNFA_H_

#include <list>

namespace LevenshteinAutomata
{

	class LevenshteinNFA
	{		
	public:
		LevenshteinNFA(int size, int state, std::list<int> finalStates);
		~LevenshteinNFA();

		enum Constants
		{
			Deletion = '1',   
			Dead = '\0',
			Insertion = '0'
		};
		static LevenshteinNFA* ConstructNFA(std::string str, int maxDist);
		void AddTransition(int from, int to, char input);
		std::list<int> Move(std::list<int> states, char inp);
		void Show();

		int initialState;
		std::list<int> finalStates;
		std::list<char> inputs;
		char** transTable;

	private:
		int size;
	};
}
#endif