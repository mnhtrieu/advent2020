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

bool overlap(ll x1, ll x2,ll y1,ll y2) {
  return max(x1,y1) <= min(x2,y2);
}

bool in_interval(ll x, ll lo, ll hi) {
  return lo <= x && x <= hi;
}

map<string, vector<pair<ll,ll>>> rules(ifstream & in, set<string> & fields, vector<pair<ll,ll>> & over) {
  string str;
  map<string, vector<pair<ll,ll>>> ints;

  while(getline(in, str)) {
    if (str.empty()) break;

    smatch m; 
    regex_search(str, m, regex("(.*): ([0-9]+)-([0-9]+) or ([0-9]+)-([0-9]+)"));

    fields.insert(m[1]);

    FF(2) {
      bool found = false;
      ll x = stoi(m[2*(j+1)]), y = stoi(m[2*(j+1)+1]);
      F(over.size()) {
        if(overlap(x, y, over[i].first, over[i].second)) {
          over[i].first = min(x, over[i].first);
          over[i].second = max(y, over[i].second);
          found = true;
          break;
        }
      }
      if (!found) over.PB({x,y});
      ints[m[1]].PB({x,y});
    }
  }
  return ints;
}


void part_1(const string & file) {
  ifstream in(file);

  string str;
  
  vector<pair<ll,ll>> over;
  set<string> fields;

  rules(in, fields, over);
  
  F(4) in.ignore(INT_MAX, '\n');// ignore your ticket

  ll sum = 0;
  while(getline(in, str)) {
    vector<ll> nums = explode(str, ',');
    for(const auto & n: nums) {
      bool found = false;
      F(over.size()) {
        if (in_interval(n, over[i].first, over[i].second)) {
          found = true;
          break;
        }
      }
      if (!found) sum += n;
    }
  }


  cout << "Part 1: " << sum << endl;
}

bool check(const vector<set<string>> & res) {
  F(res.size()) if (res[i].size() > 1) return false;
  return true;
}


void part_2(const string & file) {
  ifstream in (file);

  string str;
  vector<pair<ll,ll>> over;
  set<string> n;

  map<string, vector<pair<ll,ll>>> ints = rules(in, n, over);

  vector<set<string>> f;
  F(n.size()) f.PB(n);

  in.ignore(INT_MAX, '\n');
  getline(in, str);
  vector<ll> myTicket = explode(str, ',');

  F(2) in.ignore(INT_MAX, '\n');

  vector<vector<ll>> nearby;

  while(getline(in, str)) {
    vector<ll> nums = explode(str, ',');
    bool found = false;
    for(const auto & n: nums) {
      found = false;
      F(over.size()) {
        if (in_interval(n, over[i].first, over[i].second)) {
          found = true; break;
        }
      }
      if (!found) break;
    }
    if (!found) continue;
    nearby.PB(nums);
  }

  for(auto & ticket: nearby) {
    if(check(f)) break;

    for(ll i = 0; i < (ll)ticket.size(); ++ i) {
      ll field = ticket[i];

      for(auto r = f[i].begin(); r != f[i].end(); ) {
        bool found = false;
        for(auto & interval: ints[*r]) {
          if (in_interval(field, interval.first, interval.second)) {
            found = true; break;
          }
        }
        if(!found) f[i].erase(r++);
        else r++;
      }
      
      if (f[i].size() == 1) {
        ll it = i;
        ll found = true;
        set<ll> visited;
        while(found) {
          found = false;
          for(ll k = 0; k < (ll)f.size(); ++ k) {
            if (it == k) continue;
            f[k].erase(*f[it].begin());
          }

          for(ll k = 0; k < (ll)f.size(); ++ k) {
            if (k == it) continue;
            if(f[k].size() == 1 && !visited.count(k)) {
              found = true;
              visited.insert(it = k);
              break;
            }
          }
        }
      }
    }
  }

  ll res = 1;
  F(f.size()) {
    if((*f[i].begin()).find("departure") != string::npos) {
      res *= myTicket[i];
    }
  }

  cout << "Part 2: " << res << endl;
}



vector<ll> explode(string const & s, char delim)
{
    vector<ll> res;
    istringstream iss(s);

    for(string token; getline(iss, token, delim);){
      res.PB(stoi(token));
    }

    return res;
}
