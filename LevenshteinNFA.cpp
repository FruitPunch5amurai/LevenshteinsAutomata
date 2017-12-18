#include "LevenshteinNFA.h"


namespace LevenshteinAutomata
{
	LevenshteinNFA::LevenshteinNFA(int _size, int _initialstate, std::list<int> _finalStates)
	{
		initialState = _initialstate;
		size = _size;
		finalStates = _finalStates;
		transTable = new std::vector<char>();
		for (int i = 0; i < size*size;i++)
		{
			transTable->emplace_back('\0');
		}

		//transTable = new char*[size];
		/*
		for (int i = 0; i < size;++i)
		{
			transTable[i] = new char[size];
			memset(transTable[i], '\0', sizeof(char)*size);
		}*/
	}
	LevenshteinNFA::~LevenshteinNFA()
	{
		free(transTable);
	}
	LevenshteinNFA* LevenshteinNFA::ConstructNFA(std::string str, int maxDist)
	{
		int width = str.length() + 1;
		int height = maxDist + 1;
		int size = width * height;
		std::list<int> finalStates;
		for (int i = 1; i <= height;++i)
		{
			finalStates.push_back(i* width - 1);
		}
		LevenshteinNFA *nfa = new LevenshteinNFA(size, 0, finalStates);
		for (int e = 0; e < height;++e)
		{
			for (int i = 0; i < width - 1;++i)
			{
				nfa->AddTransition(e*width + i, e*width + i + 1, str[i]);
				if (e < height - 1)
				{
					nfa->AddTransition(e*width + i, (e + 1)*width + i, (char)Constants::Insertion);
					nfa->AddTransition(e*width + i, (e + 1)*width + i + 1, (char)Constants::Deletion);
				}
			}
		}
		for (int j = 1;j < height;++j)
		{
			nfa->AddTransition(j*width - 1, (j + 1)* width - 1, (char)Constants::Insertion);
		}
		return nfa;
	}
	void LevenshteinNFA::AddTransition(int from, int to, char input)
	{
		transTable->at((from * size) + to) = input;
		inputs.emplace_front(input);
		inputs.sort();
		inputs.unique();
	}
	std::list<int> LevenshteinNFA::Move(std::list<int> states, char inp)
	{
		std::list<int> result;
		bool needNormalLetter = false;
		bool findNormalLetter = false;
		if (inp != (char)LevenshteinNFA::Constants::Insertion &&
			inp != (char)LevenshteinNFA::Constants::Deletion)
		{
			needNormalLetter = true;
		}
		for (std::list<int>::iterator it = states.begin(); it != states.end();++it)
		{
			for (int j = 0; j < size;j++)
			{
				char c = transTable->at((*it * size) + j);
				if (c== inp || c== (char)LevenshteinNFA::Constants::Insertion || c == (char)LevenshteinNFA::Constants::Deletion)
				{
					if (needNormalLetter && c == inp) findNormalLetter = true;
					result.push_back(j);
				}
			}
		}
		if (needNormalLetter && !findNormalLetter) result.clear();
		result.sort();
		result.unique();
		return result;
	}

	void LevenshteinNFA::Show()
	{
		printf("This NFA has %d states: 0 - %d\n", size, size - 1);
		printf("The initial state is %d\n", initialState);
		printf("The final state is %d\n", finalStates);
		for (int from = 0; from < size; ++from)
		{
			for (int to = 0; to < size; ++to)
			{
				char in = transTable->at((from * size) + to);

				if (in != (char)LevenshteinNFA::Constants::Dead)
				{
					printf("Transition from %d to %d on input ", from, to);

					if (in == (char)LevenshteinNFA::Constants::Deletion)
						printf("Deletion\n");
					else if (in == (char)LevenshteinNFA::Constants::Insertion)
						printf("Insertion\n");
					else
						printf("%c \n", in);
				}
			}
		}
		printf("\n\n");
	}
}
