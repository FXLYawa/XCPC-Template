#include <bits/stdc++.h>
using namespace std;

//odd[i]表示第i位的奇回文串长度为2*odd[i]-1
//even[i]表示第i位的偶回文串长度为2*even[i]且i为中间靠后一位
vector<int> odd,even;
void manacher(string &s){
	int n=s.size();
	//odd
	int l=0,r=-1;odd.resize(n);
	for(int i=0;i<n;i++) {
		int k=(i>r)?1:min(odd[l+r-i],r-i+1);
		//k是回文串半径长度 2*k-1是回文串全长
		while (0<=i-k&&i+k<n&&s[i-k]==s[i+k]){
			k++;//朴素处理
		}
		odd[i]=k--;//--简化后续运算
		if (i+k>r){
			l=i-k; r=i+k;
		}
	}
	//even
	l=0,r=-1;even.resize(n);
	for (int i=0;i<n;i++) {
		int k=(i>r)?0:min(even[l+r-i+1],r-i+1);
		while (0<=i-k-1&&i+k<n&&s[i-k-1]==s[i+k]){
			k++;
			
		}
		even[i]=k--;
		if (i+k>r){
			l=i-k-1; r=i+k;
		}
	}
}