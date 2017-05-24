
#ifndef LRUCACHE_H
#define LRUCACHE_H

#include "CacheNode.h"
#include <map>
//#include <iostream>
using namespace std;

class LRUCache
{
private:
	int capacity;
	int count;
	map<int, Node *>mp;
	Node * cachehead;
	Node * cachetail;	

public:
	LRUCache(int capacity);//¹¹Ôìº¯Êý
	~LRUCache();
	int set(int key, int data);
	int get(int key);
	void pushfront(Node * p);
	void printCache();
};


#endif