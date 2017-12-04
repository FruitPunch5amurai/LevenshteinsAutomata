#ifndef __TRIE_H_
#define __TRIE_H_
#include <string>
using namespace std;

const int ALPHABET_SIZE = 26;
typedef struct TrieNode
{
	struct TrieNode* children[ALPHABET_SIZE];
	bool isEndWord;
}TrieNode;
TrieNode* getNode();

class Trie
{
public:
	Trie();
	TrieNode* rootNode;
	void Insert(string key);
	bool Search(string key);
};


#endif