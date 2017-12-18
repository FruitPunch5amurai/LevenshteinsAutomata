
#include <string>
#include <stdio.h>
#include <list>
#include <iostream>
#include <fstream>
#include <ctime>

#include "Trie.h"
#include "LevenshteinNFA.h"
#include "LevenshteinDFA.h"
using namespace std;
int main(int argc, char **argv)
{
	ifstream file;
	Trie trie;
	clock_t timer;
	double duration = 0;
	double totalTime = 0;
	int maxDist = 2;
	LevenshteinAutomata::LevenshteinNFA *nfa;
	LevenshteinAutomata::LevenshteinDFA *dfa;
	char line[256];

	trie.rootNode = getNode(' ', "");
	file.open("wordList.txt");
	cout << "Constructing Trie..."<< endl;
	timer = clock();
	/*Load in all resources*/
	while (file.good())
	{
		file.getline(line,256);
		trie.Insert(line);
	}
	file.close();
	duration = (clock() - timer) / (double)CLOCKS_PER_SEC;
	cout << "Constructing Trie Complete! Time: " << duration << " Seconds" << endl;
	cout << "Levenshteins Distance: " << maxDist << endl;
	file.open("wordsToTest.txt");
	//Search
	while (file.good())
	{
		file.getline(line, 256);
		cout << "===================================================================" << endl;
		cout << "Constructing Levenshteins Automata for word: " << line << endl;
		timer = clock();
		nfa = LevenshteinAutomata::LevenshteinNFA::ConstructNFA(line, maxDist);
		dfa = LevenshteinAutomata::LevenshteinDFA::SubsetConstruct(nfa);
		list<string> output;
		cout << "Searching..." << endl;
		dfa->Search(&trie, dfa->start, trie.rootNode, output);
		duration = (clock() - timer) / (double)CLOCKS_PER_SEC;
		totalTime += duration;
		cout << "Construction and Search complete! Time: " << duration << " Seconds" << endl;
		cout << "Number of hits found: " << output.size() << endl;
	}
	cout << "Total time: " << totalTime << " Seconds.."<<endl;
	file.close();
	//Clean Up
	delete nfa;
	delete dfa;
	char c = getchar();
	return 0;
	
}