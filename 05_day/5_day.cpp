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

#define FILE "input.txt"

int main(){
  ios::sync_with_stdio(0);cin.tie(0);

  ifstream in (FILE);
  string str;

  vector<vector<bool>> v;
  F(128) v.PB(vector<bool>(8));
  ll res = 0;

  while(getline(in, str)) {
    ll l = 0, h = 127;
    F(str.size()-3) {
      double mid = (l+h)/2.0;
      if(str[i] == 'F') h = floor(mid);
      else if(str[i] == 'B') l = ceil(mid);
    }

    ll cl = 0, ch = 7;

    FOR(i, str.size()-3, str.size()) {
      double mid = (cl + ch) / 2.0;
      if(str[i] == 'L') ch = floor(mid);
      else if(str[i] == 'R') cl = ceil(mid);
    }
    res = max(res, l * 8 + cl);
    v[l][cl] = true;
  }

  cout << "Part 1: " << res << endl;

  bool begin = false;
  F(128) {
    FF(8) {
      if(!v[i][j] && begin) {
        cout << "Part 2: " << i * 8 + j << endl;
        return 0;
      }
      else if(v[i][j]) begin = true;
    }
  }
  return 0;
}


