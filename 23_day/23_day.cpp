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

#define FILE "demo.txt"
//#define FILE "input.txt"

void part_1(const string & file);
void part_2(const string & file);
vector<ll> explode(string const & s, char delim);

void part_1(const string & file) {
  ifstream in(file);
  string str; getline(in, str);

  vector<ll> v(10);
  ll j = 0;
  FOR(i, 0, str.size()) {
    v[j] = str[i] - '0';
    j = v[j];
  }

  F(v.size()) if (v[i] == 0) v[i] = v[0];

  ll curr = v[0];
  FOR(round, 0, 100) {
    ll last = curr;
    F(3) last = v[last];

    ll dest = curr;
    while(true) {
      dest = dest-1 <= 0 ? 9 : dest-1;
      ll i = 0;
      for(ll tmp = curr; i < 3; ++ i, tmp = v[tmp]) if (v[tmp] == dest) break;
      if (i == 3) break;
    }

    ll first = v[curr];
    v[curr] = v[last];
    v[last] = v[dest];
    v[dest] = first;
    curr = v[curr];
  }

  cout << "Part 1: ";

  for(ll i = 1; v[i] != 1; i = v[i]) {
      cout << v[i];
  }
  cout << endl;
}


void part_2(const string & file) {
  ifstream in (file);
  string str; getline(in, str);

  vector<ll> v(1000001, 10);
  ll j = 0;
  FOR(i, 0, str.size()) {
    v[j] = str[i] - '0';
    j = v[j];
  }

  FOR(i, 10, 1000000) v[i] = i+1;
  v[1000000] = v[0];

  ll curr = v[0];
  FOR(round, 0, 10000000) {
    
    ll last = curr;
    F(3) last = v[last];
    
    ll dest = curr;
    while(true) {
      dest = dest-1 <= 0 ? 1000000 : dest-1;
      ll i = 0;
      for(ll tmp = curr; i < 3; ++ i, tmp = v[tmp]) if (v[tmp] == dest) break;
      if (i == 3) break;
    }

    ll first = v[curr];
    v[curr] = v[last];
    v[last] = v[dest];
    v[dest] = first;

    curr = v[curr];
  }

  cout << "Part 2: " << v[1] * v[v[1]] << endl;
}

vector<ll> explode(string const & s, char delim)
{
    vector<ll> res;
    istringstream iss(s);

    for(string token; getline(iss, token, delim);){
      if (token == "x") res.PB(1);
      else res.PB(stoi(token));
    }

    return res;
}

int main(int argc, const char ** argv){
  ios::sync_with_stdio(0);cin.tie(0);
  
  string file = FILE;
  if (argc > 1) {
    file = argv[1];
  }

  part_1(file);
  part_2(file);
  return 0;
}

