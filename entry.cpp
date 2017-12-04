
#include <string>
#include <stdio.h>
#include "Trie.h"
#include "LevenshteinNFA.h"
using namespace std;
int main(int argc, char **argv)
{
	/* Testing Trie*/
	string keys[] = { "the", "a", "there",
		"answer", "any", "by",
		"bye", "their" };
	int n = sizeof(keys) / sizeof(keys[0]);
	Trie trie;
	trie.rootNode = getNode();
	// Construct trie
	for (int i = 0; i < n; i++)
		trie.Insert(keys[i]);

	// Search for different keys
	trie.Search("the") ? printf("Yes\n") :
		printf("No\n");
	trie.Search("these") ? printf("Yes\n") :
		printf("No\n");
	LevenshteinAutomata::LevenshteinNFA *nfa = LevenshteinAutomata::LevenshteinNFA::ConstructNFA("to",1);
	nfa->Show();

	char c = getchar();
	return 0;
	
}