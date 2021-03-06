#include <bits/stdc++.h>
#define st first
#define nd second
#define mp make_pair
#define pb push_back
#define mod 1000000007
#define N 2100005

using namespace std;

typedef long long ll;
typedef pair < int , int > ii;

int n, m, a[N], b[1000005], say[N], fen[1000005];
ll ans;
ii git[N];
vector < int > g;

void up(int x, int y){
	b[x] += y;
	for(; x <= n; x += x&-x)
		fen[x] += y;
}

int qu(int x){
	int ans = 0;
	for(; x > 0; x -= x&-x)
		ans += fen[x];
	return ans;
}

void oku(int k){
	int x;
	scanf("%d",&x);
	if(x == 0){
		git[k].st = ++m;
		oku(m);
		git[k].nd = ++m;
		oku(m);
	} else
		a[k] = x;
}

void hazirla(int node){
	if(a[node]){
		// cout << node << " = " << a[node] << endl;
		say[node] = 1;
		return;
	}
	// cout << node << " -> " << git[node].st << endl;
	// cout << node << " -> " << git[node].nd << endl;
	hazirla(git[node].st);
	hazirla(git[node].nd);
	say[node] += say[git[node].st] + say[git[node].nd];
}

void ekle(int node){
	if(a[node]){
		g.pb(a[node]);
		up(a[node], -b[a[node]]);
		return;
	}
	ekle(git[node].st);
	ekle(git[node].nd);
}

void dfs(int node){
	if(a[node]){
		up(a[node], 1);
		return;
	}
	if(say[git[node].st] > say[git[node].nd])
		swap(git[node].st, git[node].nd);
	// cout << node << " -> " << git[node].st << " " << git[node].nd << endl;
	dfs(git[node].st);

	g.clear();
	ekle(git[node].st);
	vector < int > gg;
	swap(gg, g);
	g.clear();

	dfs(git[node].nd);
	ll x = 0, y = 0;
	// cout << node << " -> " << endl;
	for(int i = 0; i < gg.size(); i++){
		// cout << gg[i] << " ";
		int kac = qu(gg[i]);
		x += kac;
		y += say[git[node].nd] - kac;
	}
	// cout << " = " << x << " " << y << endl;
	ans += min(x, y);
	for(int i = 0; i < gg.size(); i++)
		up(gg[i], 1);
}

int main() {
	// freopen("in.txt", "r", stdin);
	// freopen("out.txt", "w", stdout);
	scanf("%d",&n);
	a[++m] = 0;
	oku(1);
	hazirla(1);
	dfs(1);
	printf("%lld\n",ans);
	return 0;
}
