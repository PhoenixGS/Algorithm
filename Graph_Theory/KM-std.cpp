#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<set>
#include<map>
#include<vector>
#include<queue>
using namespace std;
#define ll long long
#define MAX 850
inline int read()
{
	int x=0;bool t=false;char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
    if(ch=='-')t=true,ch=getchar();
    while(ch<='9'&&ch>='0')x=x*10+ch-48,ch=getchar();
    return t?-x:x;
}
int n,nl,nr,m,a[MAX][MAX];
int slack[MAX],sl[MAX],sr[MAX],pre[MAX],match[MAX];
bool vis[MAX];
ll ans;
void bfs(int S)
{
	memset(slack,127,sizeof(slack));
	memset(vis,0,sizeof(vis));
	memset(pre,0,sizeof(pre));
	int u,nt,d,nw;
	match[u=0]=S;
	do
	{
		puts("^^");
		nw=match[u];d=slack[0];vis[u]=true;
		for(int v=1;v<=n;++v)
			if(!vis[v])
			{
				printf("=%d %d\n", u, v);
				if(sl[nw]+sr[v]-a[nw][v]<slack[v])
					slack[v]=sl[nw]+sr[v]-a[nw][v],pre[v]=u;
				if(d>slack[v])d=slack[v],nt=v;
			}
		for(int i=0;i<=n;++i)
			if(vis[i])sl[match[i]]-=d,sr[i]+=d;
			else slack[i]-=d;
		u=nt;
	}while(match[u]);
	while(u)match[u]=match[pre[u]],u=pre[u];
}
int main()
{
	nl=read();nr=read();m=read();n=max(nl,nr)<<1;
	for(int i=1;i<=m;++i)
	{
		int u=read(),v=read();
		a[u][v]=max(a[u][v],read());
		sl[u]=max(sl[u],a[u][v]);
	}
	for(int i=1;i<=nl;++i)bfs(i);
	for(int i=1;i<=n;++i)ans+=sl[i]+sr[i];
	printf("%lld\n",ans);memset(pre,0,sizeof(pre));
	for(int i=1;i<=n;++i)pre[match[i]]=i;
	for(int i=1;i<=nl;++i)printf("%d ",a[i][pre[i]]?pre[i]:0);
	return 0;
}	
