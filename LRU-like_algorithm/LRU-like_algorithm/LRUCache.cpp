#include "stdafx.h"
#include "LRUCache.h"


//构造函数
LRUCache::LRUCache(int cap)
{
	capacity = cap;
	count = 0;
	cachehead = NULL;
	cachetail = NULL;
}

//析构函数
LRUCache::~LRUCache()
{
	delete cachehead;
	delete cachetail;
	mp.clear();
}

//get方法
int LRUCache::set(int key, int data)
{
	if (cachehead == NULL)//如果初始化时列表为空
	{
		//	申请cacheHead
		cachehead = new Node(key, data);
		if (cachehead == NULL)
			return -1;
		//	前后节点置为空
		cachehead ->pre = NULL;
		cachehead ->next = NULL;
		//	将头结点复制给尾节点，方便后续一个元素的判断
		cachetail = cachehead;
		//	将cachehead加入map中
		mp[key] = cachehead;
		count++;
	}
	//如果cache不为空，则表示已经有值，先查找要set的key值是否已存在，如果存在
	else      
	{
		//生成迭代器，用于查找map中对应的key值
		map<int, Node*>::iterator it = mp.find(key);
		if (it == mp.end())//如果迭代器到了end,说明没有找到，也就是没有名中
		{
			//	没有命中，则要按照规则插入到Cache中
			if (count < capacity)//如果还有空位置
			{
				//申请一个位置
				Node * p = new Node(key, data);
				if (p == NULL)
					return -1;
				//新申请的节点放在Cache的头部，越近使用越靠前
				p->next = cachehead;
				p->pre = NULL;
				cachehead->pre = p;
				//将p的值赋给cachehead,已保证下次插入仍在最前
				cachehead = p;
				//将新的节点放入map中???????，方便查找
				mp[cachehead->key] = cachehead;
				//	计数+1
				count++;
			}
			//	如果没有命中，但是Cache里的值已经满了
			else 
			{
				//如果没有命中，Cache里的值已经满了，并且Cache里面只有一个节点
				if (cachehead == cachetail)// && cachehead !=NULL)//这里不能使用count==1来判断是否满了，因为capacity可能为1
				{
					//	将cachehead删除，替换成新节点的key和data值
					//Node * p = new Node(key, data);
					mp.erase(cachehead->key);
					//cachehead里保存的有前后指针，直接赋值而不是重新创建对象比较好
					cachehead->key = key;
					cachehead->data = data;
					mp[cachehead->key] = cachehead;
				}
				else //	Cache里的值已经满了，但是不止一个节点
				{
					//	删除尾节点的指针对应map中key的Node,但保留尾节点指针的指向
					Node *p = cachetail;

					cachetail->pre->next = cachetail->next;//NULL
					cachetail = cachetail->pre;//保证最后一个节点为尾指针

					mp.erase(p->key);

					p->key = key;
					p->data = data;
					p->pre = NULL;
					p->next = cachehead;
					cachehead->pre = p;
					cachehead = p;//保证第一个节点为头结点
					mp[cachehead->key] = cachehead; //??????					
				}
			}
		}
		else //如果命中
		{
			Node * p = it->second;//取出Node
			p->data = data;//用新值替换旧值
			pushfront(p);  //将p插入头结点位置
		}
	}
}

//	从map中将该值取出，并放置头结点位置。LRU算法
void LRUCache::pushfront(Node *p)
{
	if (count == 1)//如果只有一个节点就别来烦我
		return;
	if (p == cachehead)//如果你是头结点也别来烦我
		return;
	if (p == cachetail)//如果当前节点是尾节点标识位的话，不好意思，尾节点要换一个了
		cachetail = p->pre;

	/*准备工作全部做好之后，将该节点插入成第一个节点，并把原节点删除*/
	p->pre->next = p->next;//删除节点
	
	if (p->next != NULL)//如果p的下一个节点为空，还指望它指向前一个节前，指个毛啊
		p->next->pre = p->pre;

	p->next = cachehead;	
	p->pre = NULL;
	cachehead->pre = p; //bug在此，如果你不把cachehead往前指，那么cachehead所在节点指向前面的空指针，新的cachehead->pre将为非法。
	cachehead = p;		
}

void LRUCache::printCache()
{
	Node * phead = cachehead;
	while (phead != NULL)
	{
		cout << phead->key << ":"<<phead->data<<" "; //打印索引标志位
		phead = phead->next;
	}
	cout << endl;
}

int LRUCache::get(int key)
{
	if (cachehead == NULL)//如果头结点为空，表明该Cache为空
		return -1;
	map<int, Node *>::iterator it = mp.find(key);
	if (it == mp.end())//没有找到
		return -1;
	else
	{
		Node * p = it->second;//取出节点
		pushfront(p);		  //将它置为头结点，最后返回要用
	}
	return cachehead->data;
}