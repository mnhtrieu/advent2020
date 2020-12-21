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
set<string> explode(string const & s, char delim);

int main(int argc, const char ** argv){
  ios::sync_with_stdio(0);cin.tie(0);
  
  string file = FILE;
  if (argc > 1) {
    file = argv[1];
  }

  part_1(file);
  // part_2(file); part_2 can be solved with part_1
  return 0;
}

// 1647 to low

void part_1(const string & file) {
  ifstream in(file);
  string str;

  unordered_map<string, ll> appeared;
  map<string, set<string>> aler_ingr;

  while(getline(in, str)) {
    ll pos = str.find("(contains");
    string ss = str.substr(0, pos-1);
    string sss = str.substr(pos+10, str.find_last_of(')')-pos-10);
    
    set<string> ingrs = explode(ss, ' ');
    set<string> alergs = explode(sss, ',');

    for(auto & ingr: ingrs) appeared[ingr] ++;
    
    for(auto & alerg : alergs) {
      if(aler_ingr.count(alerg)) {
        auto & it = aler_ingr.at(alerg);
        set<string> inter; 
        set_intersection(it.begin(), it.end(), ingrs.begin(), ingrs.end(), inserter(inter, inter.begin()));
        it = std::move(inter);
      }
      else aler_ingr[alerg] = ingrs;
    }   
  }

  ll found = true;
  while(found) {
    found = false;
    for(auto & [alergen, ingredients]: aler_ingr) {
      if (ingredients.size() == 1) {
        for(auto & [alergen2, ingredients2]: aler_ingr) {
          if(alergen == alergen2) continue;
          ingredients2.erase(*ingredients.begin());
        }
      } else found = true;
    }
  }

  set<string> hasAlergens;
  for(auto & i: aler_ingr) hasAlergens.insert(*i.second.begin());

  ll res = 0;
  for(auto & [key, val]: appeared) {
    if (hasAlergens.count(key)) continue;
    res += val;
  }

  cout << "Part 1: " << res << endl;


  str.clear();
  for(const auto & i : aler_ingr) {
    str += *i.second.begin() + ",";
  }
  str[str.size()-1] = 0;
  cout << "Part 2: " << str << endl;

}

set<string> explode(string const & s, char delim)
{
    set<string> res;
    istringstream iss(s);

    for(string token; getline(iss, token, delim);){
      if (token[0] == ' ') token.erase(token.begin());
      res.insert(token);
    }

    return res;
}