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
const std::string WHITESPACE = " \n\r\t\f\v";

void part_1(const string & fileName);
void part_2(const string & fileName);
string ltrim(const string& s); 
string rtrim(const string& s);
vector<string> explode(string const & s, char delim);
ll dfs(const map<string, set<string>> & m);
ll dfs2(const map<string, set<pair<ll, string>>> & m, const string & current);

int main(int argc, const char ** argv){
  ios::sync_with_stdio(0);cin.tie(0);
  part_1(argv[1]);
  part_2(argv[1]);
  return 0;
}


string name(const string & str) {
  ll pos = str.find("bags");
  return str.substr(0, pos-1);
}


pair<int, string> parse(string str) {
  str = rtrim(ltrim(str.substr(0, str.find("bag")-1)));
  ll pos = str.find(" ");
  ll num = stoi(str.substr(0, pos));
  string name = str.substr(pos+1);
  return pair<int, string>(num, name);
}


void part_1(const string & fileName) {
  ifstream in(fileName);

  string str;
  map<string, set<string>> m;

  while(getline(in, str)) {
    ll pos = str.find("contain");
    string key = name(str.substr(0, pos-1));

    vector<string> content = explode(str.substr(pos+8), ',');
    for(const auto & i: content) {
      if (i == "no other bags.") continue;
      m[parse(i).second].insert(key);
    }
  }
  cout << "Part 1: " << dfs(m) << endl;
}

void part_2(const string & fileName) {
  ifstream in (fileName);

  string str;
  map<string, set<pair<ll, string>>> m;


  while(getline(in, str)) {
    ll pos = str.find("contain");
    string key = name(str.substr(0, pos-1));

    vector<string> content = explode(str.substr(pos+8), ',');
    for(const auto & i: content) {
      if (i == "no other bags.") continue;
      m[key].insert(parse(i));
    }
  }

  cout << "Part 2: " << dfs2(m, "shiny gold") << endl;
}

//-------------------------------------------------------------------------------------------------

ll dfs(const map<string, set<string>> & m) {
  stack<string> s;
  set<string> res;

  s.push("shiny gold");

  while(!s.empty()) {
    string top = s.top(); s.pop();

    if(!m.count(top)) continue;
    
    for(auto & i: m.at(top)) {
      res.insert(i);
      s.push(i);
    }
  }
  
  return res.size();
}


ll dfs2(const map<string, set<pair<ll, string>>> & m, const string & current) {
  if (!m.count(current)) return 0;
  ll curr = 0; 

  for(const auto & i: m.at(current)) 
    curr += i.first + i.first * dfs2(m, i.second);
  
  return curr;
}

//-------------------------------------------------------------------------------------------------

vector<string> explode(string const & s, char delim)
{
    vector<string> res;
    istringstream iss(s);

    for(string token; getline(iss, token, delim);){
      res.PB(move(rtrim(ltrim(token))));
    }

    return res;
}

string ltrim(const string& s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == string::npos) ? "" : s.substr(start);
}


string rtrim(const string& s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == string::npos) ? "" : s.substr(0, end + 1);
}