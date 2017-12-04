#include "Trie.h"

TrieNode *getNode()
{
	TrieNode *pNode = new TrieNode;

	pNode->isEndWord = false;

	for (int i = 0; i < ALPHABET_SIZE; i++)
		pNode->children[i] = NULL;

	return pNode;
}

Trie::Trie()
{
}

void Trie::Insert(string key)
{
	struct TrieNode *pCrawl = rootNode;

	for (int i = 0; i < key.length(); i++)
	{
		int index = key[i] - 'a';
		if (!pCrawl->children[index])
			pCrawl->children[index] = getNode();

		pCrawl = pCrawl->children[index];
	}

	// mark last node as leaf
	pCrawl->isEndWord = true;
}

bool Trie::Search(string key)
{
	struct TrieNode *pCrawl = rootNode;

	for (int i = 0; i < key.length(); i++)
	{
		int index = key[i] - 'a';
		if (!pCrawl->children[index])
			return false;

		pCrawl = pCrawl->children[index];
	}

	return (pCrawl != NULL && pCrawl->isEndWord);
}
