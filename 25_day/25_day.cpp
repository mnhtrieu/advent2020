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

ll pow2(ll base, ll exp) {
  ll result = 1;
  while (exp)
  {
    if (exp & 1) {
      result *= base;
      result %= 20201227;
    }
    exp >>= 1;
    base *= base;
    base %= 20201227;
  }

  return result;
}

ll discrete(ll a, ll b) { 
    ll n = (ll) sqrt(20201227)+1; 
    unordered_map<ll, ll> value; 
    for (ll i = n; i >= 1; --i) value[pow2 (a, i * n)] = i; 
    for (ll j = 0; j < n; ++j) { 
      ll cur = (pow2(a, j)*b) % 20201227; 
      if (value[cur]) { 
        ll ans = value[cur]*n-j; 
        if (ans < 20201227) return value[cur]*n-j; 
      } 
    }
    return -1; 
} 


void part_1(const string & file) {
  ifstream in(file);
  string str;
  ll pb, pb2;
  in >> pb >> pb2;
  ll res1 = discrete(7, pb);
  cout << "Part 1: " << pow2(pb2, res1) << endl;
}


void part_2(const string & file) {
  ifstream in (file);
  string str;

  cout << "Part 2: " << endl;
}

vector<ll> explode(string const & s, char delim) {
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

