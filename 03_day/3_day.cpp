#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using ld=double;
#define FOR(i,a,b) for(ll i=a;i<(ll)b;++i)
#define F(n) FOR(i,0,n)
#define FF(n) FOR(j,0,n)
#define aa first
#define bb second
#define PB push_back
#define EQ(a,b) (fabs(a-b)<=(fabs(a+b)*EPS))
#define MOD ((ll)(1e9+7))

#define FILE "input.in"

void part_1();
void part_2();

int main(){
  ios::sync_with_stdio(0);cin.tie(0);

  ifstream in (FILE);

  vector<vector<char>> v;
  ll pos[5][2] = {{1,1}, {3,1}, {5,1}, {7,1}, {1, 2}};


  string str;
  while(getline(in, str)) {
    vector<char> tmp;
    F(str.size()) tmp.PB(str[i]);
    v.PB(tmp);
  }

  ll res = 1;

  F(5) {
    ll x = 0, y = 0, trees = 0, width = v[0].size();
    while(true) {
      x = (x + pos[i][0]) % width;
      y += pos[i][1];
      if(y >= (int)v.size()-1) break;
      if(v[y][x] == '#') trees ++;
    }

    if(i == 1) cout << "Part 1: " << trees << endl;
    res *= trees;
  }

  cout << "Part 2: " << res << endl;

  return 0;
}



