#include<bits/stdc++.h>
using namespace std;
/*
ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
*/
#define int long long
#define ld long double
//#define INT __int128
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<long long, long long> PLL;
typedef pair<int, int> PII;
typedef pair<double, double> PDD;
const LL INF = 0x3f3f3f3f3f3f3f3f;
const int inf = 0x3f3f3f3f;
const LL mod = 1e9 + 7;
const ld eps = 1e-12;
const int N = 2e5 + 10, M = N + 10;
int n,k,p,q;
int a[N],b[N],c[N],mn[N];

void solve(){
	cin>>n>>k>>p>>q;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		b[i]=a[i]%p;
		c[i]=(a[i]%q)%p;
		mn[i]=min(b[i],c[i]);
		mn[i]+=mn[i-1];
		b[i]+=b[i-1];
		c[i]+=c[i-1];
	}
	int ans=INF;
	for(int i=k;i<=n;i++){
		int t=mn[n]-mn[i]+mn[i-k]+min(b[i]-b[i-k],c[i]-c[i-k]);
		ans=min(ans,t);
	}
	cout<<ans<<endl;
}

signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
    int T=1,cas=1;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}