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


ll applyMask(const vector<pair<ll,ll>> & mask, ll val, bool part1) {
  for(const auto & [bit, b]: mask) {
    if (((val >> bit) & 1) != b) {
      if (b == 1) val += pow(2, bit);
      if (b == 0 && part1) val -= pow(2, bit);
    }
  }
  return val;
}

void applyFloating(vector<ll> & res, const vector<ll> & fl, ll i, ll val) {
  if (i == (ll)fl.size()) {
    res.PB(val);
    return;
  }

  applyFloating(res, fl, i+1, ((val >> fl[i]) & 1) == 0 ? val : val - pow(2, fl[i]));
  applyFloating(res, fl, i+1, ((val >> fl[i]) & 1) == 1 ? val : val + pow(2, fl[i]));
}



void part_1(const string & file) {
  ifstream in(file);

  map<ll, ll> m;
  string str;

  vector<pair<ll,ll>> mask;
  while(getline(in, str)) {
    if (str.find("mask") != string::npos) {
      mask.clear();
      regex rgx("mask = (.*)");
      smatch matches;
      regex_search(str, matches, rgx);
      string parse =  matches[1].str();

      F(parse.size()) {
        if (parse[i] == 'X') continue;
        mask.PB({35-i, parse[i] - '0'});
      }
    } 
    else {
      regex rgx("mem\\[([0-9]+)] = ([0-9]+)");
      smatch matches;
      regex_search(str, matches, rgx);
      ll addr = stoi(matches[1].str()), val = stoi(matches[2].str());
      ll tmp = applyMask(mask, val, true);
      m[addr] = tmp;
    }
  }

  ll res = 0;
  for(const auto & i: m) {
    res += i.second;
  }


  cout << "Part 1: " << res << endl;
}


void part_2(const string & file) {
  ifstream in (file);

  map<ll, ll> m;
  string str;

  vector<pair<ll,ll>> mask;
  vector<ll> fl;

  while(getline(in, str)) {
    if (str.find("mask") != string::npos) {
      mask.clear();
      fl.clear();
      regex rgx("mask = (.*)");
      smatch matches;
      regex_search(str, matches, rgx);

      string parse =  matches[1].str();

      F(parse.size()) {
        if (parse[i] == 'X') { fl.PB(35-i); mask.PB({35-i, 0}); }
        else mask.PB({35-i, parse[i] - '0'}); 
      }
    } 
    else {
      regex rgx("mem\\[([0-9]+)] = ([0-9]+)");
      smatch matches;
      regex_search(str, matches, rgx);
      ll addr = stoi(matches[1].str()), val = stoi(matches[2].str());
      
      ll tmp = applyMask(mask, addr, false);
      vector<ll> addrs;
      applyFloating(addrs, fl, 0, tmp);
      for(const auto & i: addrs) {
        m[i] = val;
      }
    }
  }

  ll res = 0;
  for(const auto & i: m) {
    res += i.second;
  }

  cout << "Part 2: " << res << endl;
}
