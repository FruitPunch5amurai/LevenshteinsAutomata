#include <stack> 
#include <algorithm>
#include "LevenshteinDFA.h"


namespace LevenshteinAutomata
{
	LevenshteinDFA::LevenshteinDFA()
	{
		finalStates = new std::list<int>();
		defaultTrans = new std::map<int, int>();
		transTable = new std::map<std::pair<int, char>, int>();
	}


	LevenshteinDFA::~LevenshteinDFA()
	{
		free(defaultTrans);
		free(finalStates);
		free(transTable);
	}
	LevenshteinDFA * LevenshteinDFA::SubsetConstruct(LevenshteinNFA * nfa)
	{
		int num = 0;
		LevenshteinDFA* dfa = new LevenshteinDFA();

		std::list<std::list<int>> markedStates;
		std::list<std::list<int>> unmarkedStates;

		std::map<std::list<int>, int> dfaStateNum;

		std::list<int> nfaInitial;
		nfaInitial.emplace_back(nfa->initialState);

		std::list<int> first = EpsilonClosure(nfa, nfaInitial);
		unmarkedStates.emplace_back(first);

		//the initial dfa state
		int dfaInitial = num++;
		dfaStateNum[first] = dfaInitial;

		while (unmarkedStates.size() != 0)
		{
			std::list<int> aState = unmarkedStates.front();
			unmarkedStates.pop_front();

			markedStates.emplace_back(aState);

			//Kinda killer, should redo
			for (std::list<int>::iterator it = aState.begin(); it != aState.end();++it)
			{
				for (std::list<int>::iterator it2 = nfa->finalStates.begin(); it2 != nfa->finalStates.end();++it2)
				{
					if (*it == *it2)
					{
						dfa->finalStates->emplace_back(dfaStateNum[aState]);
					}
				}
			}
			for each (char c in nfa->inputs)
			{
				std::list<int> next = EpsilonClosure(nfa, nfa->Move(aState, c));
				if (next.empty()) continue;
				if (std::find(unmarkedStates.begin(), unmarkedStates.end(), next) == unmarkedStates.end() &&
					std::find(markedStates.begin(), markedStates.end(), next) == markedStates.end())
				{
					unmarkedStates.emplace_back(next);
					dfaStateNum.emplace(next, num++);
				}
				if (c != (char)LevenshteinNFA::Constants::Insertion && c != (char)LevenshteinNFA::Constants::Deletion)
				{
					dfa->uniqueChars.emplace_back(c);
					std::pair<int, char> transition = std::make_pair(dfaStateNum[aState],c);
					dfa->transTable->insert(std::pair<std::pair<int,char>,int>(transition,dfaStateNum[next]));
				}
				else
				{
					auto it = dfa->defaultTrans->find(dfaStateNum[aState]);
					if (it == dfa->defaultTrans->end())
					{
						dfa->defaultTrans->emplace(dfaStateNum[aState], dfaStateNum[next]);
					}
				}
			}
		}
		dfa->finalStates->sort();
		dfa->finalStates->unique();
		dfa->uniqueChars.sort();
		dfa->uniqueChars.unique();
		return dfa;
	}
	std::list<int> LevenshteinDFA::EpsilonClosure(LevenshteinNFA * nfa, std::list<int> states)
	{
		if (states.empty()) return states;

		std::stack<int> uncheckedStack;

		//Push all states onto stack
		for (std::list<int>::iterator it = states.begin(); it != states.end();++it)
		{
			uncheckedStack.push(*it);
		}

		std::list<int> epsilonClosure = states;

		while (!uncheckedStack.empty())
		{
			int t = uncheckedStack.top();
			uncheckedStack.pop();
			int startIndex = 0;
			
			for (int i = 0; i < nfa->size;i++)
			{
				char input = nfa->transTable->at((t* nfa->size) + i);
				if (input == (char)LevenshteinAutomata::LevenshteinNFA::Constants::Deletion)
				{
					if (std::find(epsilonClosure.begin(), epsilonClosure.end(), startIndex) == epsilonClosure.end())
					{
						epsilonClosure.emplace_back(startIndex);
						uncheckedStack.push(startIndex);
					}
				}
				startIndex++;
			}
		}
		return epsilonClosure;
	}
	void LevenshteinDFA::Search(Trie * trie, int start, TrieNode * node, std::list<string> &output)
	{
		/**/
		if (std::find(finalStates->begin(), finalStates->end(), start) != finalStates->end() &&node->isEndWord )
		{
			output.emplace_back(node->value);
		}
		std::list<char> inputs;
		for (std::list<char>::iterator it = uniqueChars.begin(); it != uniqueChars.end();++it)
		{
			std::pair<int, char> pair = std::make_pair(start, *it);
			auto it2 = transTable->find(pair);
			if (it2 != transTable->end())
			{
				inputs.emplace_back(*it);
				for (int i = 0; i < ALPHABET_SIZE;i++)
				{
					if (node->children[i] == NULL)
						continue;
					if (node->children[i]->key == *it)
					{
						Search(trie, transTable->at(pair), node->children[i], output);
					}
				}
			}
		}
		auto it = defaultTrans->find(start);
		if (it != defaultTrans->end())
		{
			for (int i = 0; i < ALPHABET_SIZE;i++)
			{
				bool found = false;;
				if (node->children[i] == NULL) continue;
				for (std::list<char>::iterator it = inputs.begin(); it != inputs.end();++it)
				{
					if (*it == node->children[i]->key)
					{
						found = true;
					}
				}
				if (!found)
				{
					Search(trie, defaultTrans->at(start), node->children[i], output);
				}
			}
		}
		
	}
}