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
void process(ll & acc, const vector<pair<string, ll>> & operations);
void process2(ll & acc, vector<pair<string, ll>> & operations, const vector<ll> & corrupted);

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

  string op;
  ll num;
  vector<pair<string, ll>> operations;

  while(in >> op >> num) {
    operations.PB({op, num});
  }
  
  ll acc = 0;

  process(acc, operations);

  cout << "Part 1: " << acc << endl;
}


void part_2(const string & file) {
  ifstream in (file);

  string op;
  ll num;
  vector<pair<string, ll>> operations;
  vector<ll> corrupted;

  while(in >> op >> num) {
    operations.PB({op, num});
    if(op == "nop" || op == "jmp") corrupted.PB(operations.size()-1);
  }
  
  ll acc = 0;
  process2(acc, operations, corrupted);
  cout << "Part 2: " << acc << endl;
}


void process(ll & acc, const vector<pair<string, ll>> & operations) {
  ll idx = 0;
  set<ll> visited;
  while(true) {
    while(idx < (ll)operations.size()) {
      string op; ll num;
      tie(op, num) = operations[idx];
      if(!visited.insert(idx).second) {
        cout << "infinity" << endl;
        break;
      }
      if (op == "jmp") idx = max((ll)0, idx + num - 1);
      else if(op == "acc") acc += num;
      ++ idx;
    }

    break;
  }
}


void process2(ll & acc, vector<pair<string, ll>> & operations, const vector<ll> & corrupted) {
  ll last = -1;
  
  while(true) {
    set<ll> visited;
    bool fail = false;
    acc = 0;
    ll idx = 0;
    while(idx < (ll)operations.size()) {
      string op; ll num;
      tie(op, num) = operations[idx];
      if(!visited.insert(idx).second) {
        fail = true;
        break;
      }
      if (op == "jmp") idx = max((ll)0, idx + num - 1);
      else if(op == "acc") acc += num;
      ++ idx;
    }
    if(!fail) break;

    if(last != -1) {
      ll i = corrupted[last];
      operations[i].first = operations[i].first == "nop" ? "jmp" : "nop";
    }

    ll i = corrupted[++last];
    operations[i].first = operations[i].first == "nop" ? "jmp" : "nop";
  }
}