// LRU-like_algorithm.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "LRUCache.h"
#include <iostream>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	LRUCache cache(3);
	cache.set(1, 1);
	//cache.printCache();

	cache.set(2, 2);
	//cache.printCache();

	cache.set(3, 3);
	cache.printCache();

	cache.set(4, 4);
	cache.printCache();

	cout << cache.get(4) << endl;
	cache.printCache();

	cout << cache.get(3) << endl;
	cache.printCache();
	cout << cache.get(2) << endl;
	cache.printCache();
	cout << cache.get(1) << endl;
	cache.printCache();

	cache.set(5, 5);
	cache.printCache();

	cout << cache.get(1) << endl;
	cout << cache.get(2) << endl;
	cout << cache.get(3) << endl;
	cout << cache.get(4) << endl;
	cout << cache.get(5) << endl;

	system("pause");

	return 0;
}

