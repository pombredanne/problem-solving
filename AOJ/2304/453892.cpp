
/*
Test program for rejudge.

Thanks for vjudge

 */

#include<iostream>
#include<cstdio>
#include<cstring>
#include<stack>
#include<cstdlib>
#include<queue>
using namespace std;
const int MAXN=505;
int map[MAXN][MAXN],n,p[MAXN];
int yuan[MAXN][MAXN];
int pp[MAXN][3];
int bian[MAXN];
bool EK_Bfs(int start,int end)
{
    queue<int> que;
    bool flag[MAXN];
    memset(flag,false,sizeof(flag));
    memset(p,-1,sizeof(p));
    que.push(start);
    flag[start]=true;
    while(!que.empty())
    {
        int e=que.front();
        if(e==end) return true;
        que.pop();
        for(int i=1;i<=n;++i)
        {
            if(map[e][i]&&!flag[i])
            {
                flag[i]=true;
                p[i]=e;
                que.push(i);
            }
        }
    }
    return false;
}
int EK_MAX(int start,int end)
{
    int u,flow_ans=0; int mn;
    while(EK_Bfs(start,end))
    {
        mn=99999999;
        u=end;
        while(p[u]!=-1)
        {
            mn=min(mn,map[p[u]][u]);
            u=p[u];
        }
        flow_ans+=mn;
        u=end;
        while(p[u]!=-1)
        {
            map[p[u]][u]-=mn;
            map[u][p[u]]+=mn;
            u=p[u];
        }
    }
    return flow_ans;
}
int main()
{
    int i,j,k,m;
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        memset(map,0,sizeof(map));
        memset(yuan,0,sizeof(yuan));
        for(i=1;i<=m;++i)
        {
            int oo,mm;
            scanf("%d%d",&oo,&mm);
            map[oo][mm]=1;
            yuan[oo][mm]=1;
            pp[i][1]=oo;
            pp[i][2]=mm;
        }
        int ss,ee; int num1=0;
        scanf("%d%d",&ss,&ee);
        int ans=EK_MAX(ss,ee);
        j=1;
        int ans1=-1;
        for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
        map[i][j]=1;
        ans1=EK_MAX(ss,ee);
        j=1;
        if(ans1==ans)
        {
            cout<<ans<<endl;
            cout<<"0"<<endl;
            continue;
        }
        j=1;
        for(i=1;i<=m;i++)
        {
            int oo,mm;
            oo=pp[i][1];
            mm=pp[i][2];
            if(map[oo][mm]>yuan[oo][mm]&&(yuan[oo][mm]==1))
            {
               bian[j++]=i;
            }
        }
        cout<<ans1<<endl;
        cout<<j-1<<endl;
        for(i=1;i<=j-1;i++)
        cout<<bian[i]<<endl;
      /*  for(i=1;i<=m;++i)
        {
            for(int qq=1;qq<=n;qq++)
            {
                for(int ww=1;ww<=n;ww++)
                map[qq][ww]=yuan[qq][ww];
            }  */
         /*   map[pp[i][1]][pp[i][2]]=0;
            map[pp[i][2]][pp[i][1]]=1;
            yuan[pp[i][1]][pp[i][2]]=0;
            yuan[pp[i][2]][pp[i][1]]=1;
            k=EK_MAX(ss,ee);
            if(k>ans)
            {
                num1++;
                ans=k;
                bian[j++]=i;
            }
            else if(k==ans) { }
            else
            {
                yuan[pp[i][1]][pp[i][2]]=1;
                yuan[pp[i][2]][pp[i][1]]=0;
            }  */
       // }
     /*   j--;
        cout<<ans<<endl;
        cout<<j<<endl;
        for(i=1;i<=j;++i)
        cout<<bian[i]<<endl;  */
    }
    return 0;
}

