#include<bits/stdc++.h>
typedef long long int ll;
#define MOD 998244353
#define read(v)for(auto &i:v)cin>>i
#define pv(v)for(auto i:v)cout<<i<<" ";cout<<endl
using namespace std;

// const ll m = 1e9 + 7;
int **vis;
vector<pair<pair<int,int>,char>>dirs = {{{0,-1},'L'},{{0,+1},'R'},{{-1,0},'U'},{{+1,0},'D'}};


void solve() {
	using pii = pair<int,pair<int,int>>;
	ll n,m;
	cin>>n>>m;
	vector<vector<char>>grid(n,vector<char>(m));
	priority_queue<pii,vector<pii>,greater<pii>>pq;
	vis = new int*[n];
	for(int i=0;i<n;i++){
		vis[i] = new int[m];
		for(int j=0;j<m;j++)vis[i][j] = 1e9;
	}
	ll rr,cc;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			cin>>grid[i][j];
			if(grid[i][j]=='M'){
				vis[i][j] = 0;
				pq.push({0,{i,j}});
			}
			if(grid[i][j]=='A'){
				grid[i][j] = '.';
				rr = i,cc = j;
			}
		}
	}
	while(!pq.empty()){
		auto it = pq.top();
		pq.pop();
		ll r = it.second.first,c = it.second.second;
		for(ll k=0;k<4;k++){
			ll row = r+dirs[k].first.first;
			ll col = c+dirs[k].first.second;
			if(row>=0 && col>=0 && row<n && col<m && grid[row][col]=='.'){
				if(vis[r][c]+1<vis[row][col]){
					vis[row][col] = vis[r][c]+1;
					pq.push({vis[row][col],{row,col}});
				}
			}
		}
	}
	bool **pvis;
	pvis = new bool*[n];
	for(ll i=0;i<n;i++){
		pvis[i] = new bool[m];
		for(ll j=0;j<m;j++)pvis[i][j] = false;
	}
	pq.push({0,{rr,cc}});
	pvis[rr][cc] = true;
	bool f = false;
	vector<vector<pair<int,int>>>parent(n,vector<pair<int,int>>(m));
	int endi,endj;
	while(!pq.empty()){
		auto it = pq.top();
		pq.pop();
		ll r = it.second.first,c = it.second.second;
		if(r==0 || r==n-1 || c==0 || c==m-1){
			f = true;
			endi = r,endj = c;
		}
		for(ll k=0;k<4;k++){
			ll row = r+dirs[k].first.first;
			ll col = c+dirs[k].first.second;
			if(row>=0 && col>=0 && row<n && col<m && !pvis[row][col] && it.first+1<vis[row][col] && grid[row][col]=='.'){
				pvis[row][col] = true;
				parent[row][col] = {r,c};
				pq.push({it.first+1,{row,col}});
			}
		}
	}
	if(!f){
		cout<<"NO"<<endl;
		return;
	}
	parent[rr][cc] = {-1,-1};
	string ans;
	while(parent[endi][endj].first!=-1){
		pair<ll,ll> curr = parent[endi][endj];
		pair<ll,ll> diff = {endi-curr.first,endj-curr.second};
		for(ll k=0;k<4;k++){
			if(diff.first==dirs[k].first.first && diff.second==dirs[k].first.second){
				ans+=dirs[k].second;
				break;
			}
		}
		endi = curr.first;
		endj = curr.second;
	}
	reverse(ans.begin(),ans.end());
	cout<<"YES"<<endl;
	cout<<ans.size()<<endl;
	cout<<ans<<endl;
}
int main() {
    #ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
	freopen("Error.txt","w",stderr);
	freopen("output.txt","w",stdout);
	#endif  
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	t = 1;
	while(t--)
	{
		solve();
	}
	return 0; 
}
