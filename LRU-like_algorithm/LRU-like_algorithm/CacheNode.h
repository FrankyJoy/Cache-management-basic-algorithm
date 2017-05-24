
#ifndef CACHENODE_H
#define CACHENODE_H

#include <iostream>

typedef struct CacheNode
{
	int key;
	int data;
	CacheNode * pre;
	CacheNode * next;
	CacheNode(int k, int d) :key(k), data(d), pre(NULL), next(NULL){}
}Node;

#endif