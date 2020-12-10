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



void part_1(const string & file) {
  ifstream in(file);

  set<ll> adapters;
  ll num;
  while(in >> num) {
    adapters.insert(num);
  }

  ll prev = 0;
  map<ll, ll> res;
  for(const auto & i: adapters) {
    ll diff = abs(i - prev);
    if (diff > 3) break; 
    res[diff] += 1;
    prev = i;
  }

  cout << "Part 1: " <<  res[1] * (res[3]+1) << endl;
}


ll rec(const set<ll> & adapters, ll curr, ll hi, map<ll, ll> & mem) {
  ll path = 0;

  FOR(i, 1, 4) {
    ll total = curr + i;
    auto it = adapters.find(total);

    if(it == adapters.end() || *it != total) continue;

    if(mem.count(total)) path += mem.at(total);
    else path += rec(adapters, total, hi, mem);
  }

  mem[curr] = path;
  return path;
}

void part_2(const string & file) {
  ifstream in (file);

  set<ll> adapters;
  map<ll, ll> mem;

  ll num, hi = 0;
  while(in >> num) {
    hi = max(num, hi);
    adapters.insert(num);
  }

  adapters.insert(hi+3);
  mem[hi+3] = 1;

  ll res = rec(adapters, 0, hi+3, mem);
  cout << "Part 2: " << res << endl;
}
