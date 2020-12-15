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

map<string, bool> req = {
    {"byr", false}, 
    {"iyr", false},
    {"eyr", false},
    {"hgt", false},
    {"hcl", false},
    {"ecl", false},
    {"pid", false},
    {"cid", true}
  };

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
  ll res = 0;

  map<string, bool> check = req;
  while(getline(in, str)) {
    if(str.empty()) {
      ll n = 0;
      for(auto r: req) {
        if(check[r.first] == false) break;
        n++;
      }
      if(n == 8) res ++;
      check = req;
    }

    istringstream is(str);
    string seq;
    while(getline(is, seq, ' ')) {
      ll p = seq.find(':');
      string key = seq.substr(0, p);
      check[key] = true;
    }
  }

  cout << "Part 1: " << res << endl;
}


bool validate(string key, string val) {
  // cout << "key: " << key << ", val: " << val;
  if(key == "byr") {
    ll num = stoi(val);
    return num >= 1920 && num <= 2002;
  }
  else if(key == "iyr") {
    ll num = stoi(val);
    return num >= 2010 && num <= 2020;
  }
  else if(key == "eyr") {
    ll num = stoi(val);
    return num >= 2020 && num <= 2030;
  }
  else if(key == "hgt") {
    string unit = val.substr(val.size()-2);
    if(unit != "cm" && unit != "in") return false;

    val[val.size()-2] = 0;
    ll num = stoi(val);
    return (unit == "cm" && num >= 150 && num <= 193) ||
            (unit == "in" && num >= 59 && num <= 76);

  }
  else if(key == "hcl") {
    if(val.size() > 7 || val[0] != '#') return false;
    FOR(i, 1, val.size()) {
      if ((val[i] < '0' || val[i] > '9') && (val[i] < 'a' || val[i] > 'f'))
        return false;
    }
    return true;
  }
  else if(key == "ecl") {
    set<string> available = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
    return available.count(val);
  }
  else if(key == "pid") {
    if(val.size() != 9) return false;
    F(val.size()) {
      if(val[i] < '0' || val[i] > '9') return false;
    }
    return true;
  }

  return true;
}


void part_2() {
  ifstream in (FILE);
  string str;
  ll res = 0;

  map<string, bool> check = req;
  while(getline(in, str)) {
    if(str.empty()) {
      ll n = 0;
      for(auto r: req) {
        if(check[r.first] == false) break;
        n++;
      }
      if(n == 8) res ++;
      check = req;
    }

    istringstream is(str);
    string seq;
    while(getline(is, seq, ' ')) {
      ll p = seq.find(':');
      string key = seq.substr(0, p), val = seq.substr(p+1);
      check[key] = validate(key, val);
    }
  }
  cout << "Part 2: " << res << endl;
}
