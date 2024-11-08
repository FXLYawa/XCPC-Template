#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> g,e;
vector<int> deg;
void init(int n){
	g.clear();g.resize(n+1);
	e.clear();e.resize(n+1);
	deg.clear();deg.resize(n+1);
}
void create(int n){//建立新图
	for(int i=1;i<=n;i++)
		for(auto j:g[i])deg[j]++;
	for(int i=1;i<=n;i++)
		for(auto j:g[i])
			if(deg[i]==deg[j]?i<j:deg[i]<deg[j])
				e[i].push_back(j);
}
int Cal3Circle(int n){//三元环计数
	vector<int> vis(n+1);//i能到达的点
	int cnt=0;
	for(int i=1;i<=n;i++){
		for(auto j:e[i])vis[j]=i;
		for(auto j:e[i])
			for(auto k:e[j])
				if(vis[k]==i)cnt++;
	}
	return cnt;
}
int Cal4Circle(int n){//四元环计数
	vector<int> vis(n+1);//i能到达的点
	int cnt=0;
	for(int i=1;i<=n;i++){
		for(auto j:g[i])//枚举双向边
			for(auto k:e[j])//枚举单向边，
				if(deg[i]==deg[k]?i<k:deg[i]<deg[k])
					cnt+=vis[k]++;//保证k大于i(DAG上)
		for(auto j:g[i])//清空贡献
			for(auto k:e[j])
				vis[k]=0;
	}
	return cnt;
}