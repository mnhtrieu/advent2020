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

ll solve(const vector<ll> & input, unordered_map<ll, ll> & m, ll upper) {
  ll prev = input[input.size()-1];
  for(ll i = input.size(), next = 0; i < upper; ++i) {
    if(m.count(prev) == 1) next = (i - m[prev]);
    else next = 0;
    m[prev] = i;
    prev = next;
  }
  
  return prev;
}

void part_1(const string & file) {
  ifstream in(file);
  vector<ll> input;

  ll prev = 0;
  while(in >> prev) input.PB(prev);
  unordered_map<ll, ll> m;
  F(input.size()) m[input[i]] = i+1;
  
  cout << "Part 1: " << solve(input, m, 2020) << endl;
}


void part_2(const string & file) {
  ifstream in (file);
  vector<ll> input;

  ll prev = 0;
  while(in >> prev) input.PB(prev);
  unordered_map<ll, ll> m;
  F(input.size()) m[input[i]] = i+1;
 
  cout << "Part 2: " << solve(input, m, 30000000) << endl;
}
