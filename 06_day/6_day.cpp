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

void part_1();
void part_2();

int main(){
  ios::sync_with_stdio(0);cin.tie(0);

  part_1();
  part_2();
  return 0;
}



void part_1() {
  ifstream in(FILE);

  string str;
  set<char> q;
  ll res = 0;
  while(getline(in, str)) {
    if(str.empty()) {
      res += q.size();
      q.clear();
    }

    F(str.size()) {
      q.insert(str[i]);
    }
  }
  cout << "Part 1: " << res << endl;
}


void part_2() {
  ifstream in (FILE);

  string str;
  map<char, ll> q;
  ll res = 0, ppl = 0;
  while(getline(in, str)) {
    if(str.empty()) {
      ll tmp = 0;
      for(auto & i: q) {
        if(i.second == ppl) tmp ++;
      }
      res += tmp;
      q.clear();
      ppl = 0;
    }
    else ppl++;

    F(str.size()) {
      q[str[i]] ++;
    }

  }
  cout << "Part 2: " << res << endl;
}
