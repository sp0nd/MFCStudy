
#pragma once
#ifndef _TRIETREE_H
#define _TRIETREE_H
#include <vector>
using namespace std;
typedef struct _rowcolumn {
	int row;
	int column;
} ROWCOL;

class TrieTree {	// Trie Tree 클래스
	bool finish;
	TrieTree* nextNode[26];	// 26개 알파벳
	vector<ROWCOL> arr;
	int m_count;
public:
	TrieTree() {
		m_count = 26;
		finish = false;
		for (int i = 0; i < m_count; i++)
			nextNode[i] = NULL;
	}
	~TrieTree() { reset(); }
	void reset() {
		for (int i = 0; i < m_count; i++) {
			if (nextNode[i])
				delete nextNode[i];
		}
	}
	void insert(const char* key, int row, int col) {
		if (*key == '\0') {
			finish = true;
			insert(this, row, col);
		}
		else {
			int next = *key - 'A';
			if (nextNode[next] == NULL)
				nextNode[next] = new TrieTree;
			nextNode[next]->insert(key + 1, row, col);
		}
		return;
	}
	void insert(TrieTree* pTrie, int row, int col) {
		ROWCOL rw;
		rw.row = row;
		rw.column = col;
		pTrie->arr.push_back(rw);
	}
	TrieTree* find(const char* key) {
		if (*key == 0)
			return this;

		int next = *key - 'A';

		if (next < 0 || m_count <= next)
			return NULL;

		if (nextNode[next] == NULL)
			return NULL;
		return nextNode[next]->find(key + 1);
	}
	vector<ROWCOL> getVector() {
		return arr;
	}
};
#endif