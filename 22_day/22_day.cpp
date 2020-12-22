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
  string str;

  queue<ll> p1, p2;
  in.ignore(INT_MAX, '\n');

  while(getline(in, str)) {
    if(str.empty()) break;
    p1.push(stoi(str));
  }

  in.ignore(INT_MAX, '\n');
  while(getline(in, str)) {
    if(str.empty()) break;
    p2.push(stoi(str));
  }
  
  while(!p1.empty() && !p2.empty()) {
    ll x = p1.front(), y = p2.front();
    p1.pop(); p2.pop();

    if(x > y) { p1.push(x); p1.push(y); }
    else { p2.push(y); p2.push(x); }
  }

  queue<ll> & ref = p1;
  if (p1.empty()) ref = p2;

  ll res = 0;
  while(!ref.empty()) {
    res += ref.size() * ref.front();
    ref.pop();
  }

  cout << "Part 1: " << res << endl;
}

void fight(vector<ll> & p1, vector<ll> & p2);


bool rec(vector<ll> p1, vector<ll> p2) {
  set<vector<ll>> deck, deck2;
  while(!p1.empty() && !p2.empty()) {
    if(deck.count(p1) != 0 || deck2.count(p2) != 0) { return true; }
    deck.insert(p1); deck2.insert(p2);
    fight(p1, p2);
  }

  return !p1.empty();
}

void fight(vector<ll> & p1, vector<ll> & p2) {
  ll x = p1.front(), y = p2.front();
  p1.erase(p1.begin()); p2.erase(p2.begin());

  bool winner;
  if(x <= (ll)p1.size() && y <= (ll)p2.size()) 
    winner = rec(vector<ll>(p1.begin(), p1.begin()+x), vector<ll>(p2.begin(), p2.begin()+y));
  else winner = x > y;
  
  if(winner) { p1.PB(x); p1.PB(y); }
  else { p2.PB(y); p2.PB(x); }
}

void combat(vector<ll> & p1, vector<ll> & p2) {
  set<vector<ll>> deck, deck2;

  while(!p1.empty() && !p2.empty()) {
    
    if(deck.count(p1) || deck2.count(p2) != 0) { p2.clear(); return; }
    deck.insert(p1); deck2.insert(p2);
    fight(p1, p2);
  }

  return;
}

void part_2(const string & file) {
  ifstream in (file);
  string str;

  vector<ll> p1, p2;
  in.ignore(INT_MAX, '\n');

  while(getline(in, str)) {
    if(str.empty()) break;
    p1.PB(stoi(str));
  }
  
  in.ignore(INT_MAX, '\n');
  while(getline(in, str)) {
    if(str.empty()) break;
    p2.PB(stoi(str));
  }
  
  combat(p1, p2);

  vector<ll> & ref = p1;
  if (p1.empty()) ref = p2;

  ll res = 0;
  F(ref.size()) res += (ref.size()-i) * ref[i];

  cout << "Part 2: " << res << endl;
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
