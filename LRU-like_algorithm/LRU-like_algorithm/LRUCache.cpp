#include "stdafx.h"
#include "LRUCache.h"


//���캯��
LRUCache::LRUCache(int cap)
{
	capacity = cap;
	count = 0;
	cachehead = NULL;
	cachetail = NULL;
}

//��������
LRUCache::~LRUCache()
{
	delete cachehead;
	delete cachetail;
	mp.clear();
}

//get����
int LRUCache::set(int key, int data)
{
	if (cachehead == NULL)//�����ʼ��ʱ�б�Ϊ��
	{
		//	����cacheHead
		cachehead = new Node(key, data);
		if (cachehead == NULL)
			return -1;
		//	ǰ��ڵ���Ϊ��
		cachehead ->pre = NULL;
		cachehead ->next = NULL;
		//	��ͷ��㸴�Ƹ�β�ڵ㣬�������һ��Ԫ�ص��ж�
		cachetail = cachehead;
		//	��cachehead����map��
		mp[key] = cachehead;
		count++;
	}
	//���cache��Ϊ�գ����ʾ�Ѿ���ֵ���Ȳ���Ҫset��keyֵ�Ƿ��Ѵ��ڣ��������
	else      
	{
		//���ɵ����������ڲ���map�ж�Ӧ��keyֵ
		map<int, Node*>::iterator it = mp.find(key);
		if (it == mp.end())//�������������end,˵��û���ҵ���Ҳ����û������
		{
			//	û�����У���Ҫ���չ�����뵽Cache��
			if (count < capacity)//������п�λ��
			{
				//����һ��λ��
				Node * p = new Node(key, data);
				if (p == NULL)
					return -1;
				//������Ľڵ����Cache��ͷ����Խ��ʹ��Խ��ǰ
				p->next = cachehead;
				p->pre = NULL;
				cachehead->pre = p;
				//��p��ֵ����cachehead,�ѱ�֤�´β���������ǰ
				cachehead = p;
				//���µĽڵ����map��???????���������
				mp[cachehead->key] = cachehead;
				//	����+1
				count++;
			}
			//	���û�����У�����Cache���ֵ�Ѿ�����
			else 
			{
				//���û�����У�Cache���ֵ�Ѿ����ˣ�����Cache����ֻ��һ���ڵ�
				if (cachehead == cachetail)// && cachehead !=NULL)//���ﲻ��ʹ��count==1���ж��Ƿ����ˣ���Ϊcapacity����Ϊ1
				{
					//	��cacheheadɾ�����滻���½ڵ��key��dataֵ
					//Node * p = new Node(key, data);
					mp.erase(cachehead->key);
					//cachehead�ﱣ�����ǰ��ָ�룬ֱ�Ӹ�ֵ���������´�������ȽϺ�
					cachehead->key = key;
					cachehead->data = data;
					mp[cachehead->key] = cachehead;
				}
				else //	Cache���ֵ�Ѿ����ˣ����ǲ�ֹһ���ڵ�
				{
					//	ɾ��β�ڵ��ָ���Ӧmap��key��Node,������β�ڵ�ָ���ָ��
					Node *p = cachetail;

					cachetail->pre->next = cachetail->next;//NULL
					cachetail = cachetail->pre;//��֤���һ���ڵ�Ϊβָ��

					mp.erase(p->key);

					p->key = key;
					p->data = data;
					p->pre = NULL;
					p->next = cachehead;
					cachehead->pre = p;
					cachehead = p;//��֤��һ���ڵ�Ϊͷ���
					mp[cachehead->key] = cachehead; //??????					
				}
			}
		}
		else //�������
		{
			Node * p = it->second;//ȡ��Node
			p->data = data;//����ֵ�滻��ֵ
			pushfront(p);  //��p����ͷ���λ��
		}
	}
}

//	��map�н���ֵȡ����������ͷ���λ�á�LRU�㷨
void LRUCache::pushfront(Node *p)
{
	if (count == 1)//���ֻ��һ���ڵ�ͱ�������
		return;
	if (p == cachehead)//�������ͷ���Ҳ��������
		return;
	if (p == cachetail)//�����ǰ�ڵ���β�ڵ��ʶλ�Ļ���������˼��β�ڵ�Ҫ��һ����
		cachetail = p->pre;

	/*׼������ȫ������֮�󣬽��ýڵ����ɵ�һ���ڵ㣬����ԭ�ڵ�ɾ��*/
	p->pre->next = p->next;//ɾ���ڵ�
	
	if (p->next != NULL)//���p����һ���ڵ�Ϊ�գ���ָ����ָ��ǰһ����ǰ��ָ��ë��
		p->next->pre = p->pre;

	p->next = cachehead;	
	p->pre = NULL;
	cachehead->pre = p; //bug�ڴˣ�����㲻��cachehead��ǰָ����ôcachehead���ڽڵ�ָ��ǰ��Ŀ�ָ�룬�µ�cachehead->pre��Ϊ�Ƿ���
	cachehead = p;		
}

void LRUCache::printCache()
{
	Node * phead = cachehead;
	while (phead != NULL)
	{
		cout << phead->key << ":"<<phead->data<<" "; //��ӡ������־λ
		phead = phead->next;
	}
	cout << endl;
}

int LRUCache::get(int key)
{
	if (cachehead == NULL)//���ͷ���Ϊ�գ�������CacheΪ��
		return -1;
	map<int, Node *>::iterator it = mp.find(key);
	if (it == mp.end())//û���ҵ�
		return -1;
	else
	{
		Node * p = it->second;//ȡ���ڵ�
		pushfront(p);		  //������Ϊͷ��㣬��󷵻�Ҫ��
	}
	return cachehead->data;
}