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
ll inv(ll a, ll m);

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

  ll ts;
  string str;
  getline(in, str); ts = stoi(str);
  getline(in, str); vector<ll> buses = explode(str, ',');

  pair<ll, ll> res = {INT_MAX, -1};

  for(const auto & i : buses) {
    if (i == 1) continue;
    ll tmp = ((ts / i)+1) * i;
    if (tmp < res.first) res = {tmp, i};
  }

  cout << "Part 1: " << (res.first - ts) * res.second << endl;
}


void part_2(const string & file) {
  ifstream in (file);

  string str;
  getline(in, str);
  getline(in, str); vector<ll> buses = explode(str, ',');
  
  ll prod = 1;
  for(const auto & i: buses) {
    prod *= i;
  }

  ll res = 0;
  
  FOR(i, 1, buses.size()) {
    ll m = prod / buses[i];
    res += (buses[i] - i) * inv(m, buses[i]) * m;
  }

  
  cout << "Part 2: " << res % prod << endl;
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

ll inv(ll a, ll m) { 
    ll m0 = m, t, q, x0 = 0, x1 = 1; 
    if (m == 1) return 0; 
  
    while (a > 1) { 
      q = a / m; t = m; 
      m = a % m, a = t; t = x0; 
      x0 = x1 - q * x0; x1 = t; 
    } 

    if (x1 < 0) x1 += m0;
    return x1; 
} 
