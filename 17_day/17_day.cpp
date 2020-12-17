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

ll count(tuple<ll,ll,ll> coords, set<tuple<ll, ll, ll>> & m) {
  ll x,y,z,cnt=0; tie(y,x,z) = coords;

  FOR(i, -1, 2) {
    FOR(j, -1, 2) {
      FOR(k, -1, 2) {
        if(i == 0 && j == 0 && k == 0) continue;
        if(m.count({y+i,x+j,z+k})) cnt++;
        if(cnt > 3) return cnt;
      }
    }
  }
  return cnt;
}


ll count2(tuple<ll,ll,ll, ll> coords, set<tuple<ll, ll, ll, ll>> & m) {
  ll x,y,z,w,cnt=0; tie(y,x,z,w) = coords;

  FOR(i, -1, 2) {
    FOR(j, -1, 2) {
      FOR(k, -1, 2) {
        FOR(l, -1, 2) {
          if(i == 0 && j == 0 && k == 0 && l == 0) continue;
          if(m.count({y+i,x+j,z+k, w+l})) cnt++;
          if(cnt > 3) return cnt;
        }
      }
    }
  }
  return cnt;
}

void part_1(const string & file) {
  ifstream in(file);
  string str;

  set<tuple<ll, ll, ll>> m;

  ll y = 0, x = 0, z = 0;
  while(getline(in, str)) {
    for(const auto & ch: str) {
      if (ch == '#') m.insert({y,x,z});
      x ++;
    }
    x = 0; y ++;
  }

  FOR(cycle, 0, 6) {
    set<tuple<ll, ll, ll>> tmp;
    for(const auto & coords : m) {
      tie(y,x,z) = coords;
      FOR(i, -1, 2) {
        FOR(j, -1, 2) {
          FOR(k, -1, 2) {
            if(i == 0 && j == 0 && k == 0) continue;
            tuple<ll, ll, ll> n = {y+i, x+j, z+k};
            ll cnt = count(n, m);
            if(m.count(n)) {
              if (cnt == 2 || cnt == 3) tmp.insert(n);
            }
            else if (cnt == 3) tmp.insert(n);
          }
        }
      }
    }
    m = tmp;
  }


  cout << "Part 1: " << m.size() << endl;
}


void part_2(const string & file) {
  ifstream in (file);

  string str;

  set<tuple<ll, ll, ll, ll>> m;

  ll y = 0, x = 0, z = 0, w = 0;
  while(getline(in, str)) {
    for(const auto & ch: str) {
      if (ch == '#') m.insert({y,x,z,w});
      x ++;
    }
    x = 0; y ++;
  }

  FOR(cycle, 0, 6) {
    set<tuple<ll, ll, ll, ll>> tmp;
    for(const auto & coords : m) {
      tie(y,x,z,w) = coords;
      FOR(i, -1, 2) {
        FOR(j, -1, 2) {
          FOR(k, -1, 2) {
            FOR(l, -1, 2) {
              if(i == 0 && j == 0 && k == 0 && l == 0) continue;
              tuple<ll, ll, ll, ll> n = {y+i, x+j, z+k, w+l};
              ll cnt = count2(n, m);
              if(m.count(n)) {
                if (cnt == 2 || cnt == 3) tmp.insert(n);
              }
              else if (cnt == 3) tmp.insert(n);
            }
          }
        }
      }
    }
    m = tmp;
  }
  cout << "Part 2: " << m.size() << endl;
}
