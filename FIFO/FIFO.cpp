/*
 * 先进先出队列实现FIFO算法 
 */
 #include <iostream>
 #include <deque>
 #include <algorithm>

 using namespace std;

 deque<int> cache;
 void printcache(deque<int> cache);
 void push_front(deque<int> & cache,deque<int>::iterator it);

 int main()
 {
     int n,input;
     cout<<"输入队列长度n:"<<endl;
     cin >> n;
     cout<<"输入存入的cache,每次输入一个数:"<<endl;
     while(cin>>input)
     {
         if(cache.size()<n)
        {
            cache.push_back(input);
            printcache(cache);
        }
         else
         {
             deque<int>::iterator it = find(cache.begin(),cache.end(),input);
             if(it == cache.end())  //没有找到
             {
                 // 将队头的元素删除
                 cache.pop_front();
                 cache.push_back(input);
                 printcache(cache);
             }
             else// 找到了
             {
                 //将该元素从队列置到队头
                 push_front(cache,it);
                 printcache(cache);
             }
         }
         cout<<"输入存入的cache,每次输入一个数:"<<endl;
     }
     
     return 0;
 }

 void printcache(deque<int> cache)
 {
     deque<int>::iterator it;
     cout<<"当前Cache队列为:"<<endl;
     for(it=cache.begin();it!=cache.end();it++)
     {
         cout<<*it<<" ";
     }
     cout<<endl<<endl;
 }

 void push_front(deque<int> & cache,deque<int>::iterator it)
 {
     int tmp = *it;
     cache.erase(it);
     cache.push_back(tmp);
 }