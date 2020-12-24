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


struct HEX_TILE{
  ll x,y,z;
  HEX_TILE(ll x, ll y, ll z): x(x), y(y), z(z) { }
  bool operator <(const HEX_TILE & other) const {
    return (x < other.x) 
          || (x == other.x && y < other.y)
          || (x == other.x && y == other.y && z < other.z);
  }
};

enum class direction {
  nw, w, sw, se, e, ne
};

map<string, direction> convert = {
  {"nw", direction::nw},
  {"w", direction::w},
  {"sw", direction::sw},
  {"se", direction::se},
  {"ne", direction::ne},
  {"e", direction::e},
  };

direction consume(const string & str, ll & i) {

  string res;
  res += str[i];
  if (str[i] == 'n' || str[i] == 's') res += str[++i];
  return convert[res];
}

void part_1(const string & file) {
  ifstream in(file);
  string str;

  set<HEX_TILE> tiles;
  while(getline(in, str)) {
    ll x = 0, y = 0, z = 0;
    F(str.size()) {
      direction dir = consume(str, i);
      switch(dir) {
        case direction::nw:     ++y; --z; break; // (0,+1,-1)
        case direction::ne: ++x;     --z; break; // (+1,0,-1)
        case direction::w: --x; ++y;      break; // (-1,+1,0)
        case direction::e: ++x; --y;      break; // (+1,-1,0)
        case direction::sw: --x;     ++z; break; // (-1,0,+1)
        case direction::se:     --y; ++z; break; // (0,-1,+1)
      }
    }
    auto tile = HEX_TILE(x,y,z);
    if(!tiles.insert(tile).second) tiles.erase(tile);
  }

  cout << "Part 1: " << tiles.size() << endl;
}

vector<tuple<ll,ll,ll>> adjacent = {
    {0,1,-1}, {1,0,-1}, {-1,1,0}, {1,-1,0},{-1,0,1},{0,-1,1}
};

ll count(ll x, ll y, ll z, const set<HEX_TILE> & tiles) {
  ll cnt = 0;
  for(const auto & n : adjacent) {
    ll x2,y2,z2, tmpx = x, tmpy = y, tmpz = z; tie(x2,y2,z2) = n; 
    tmpx = x+x2; tmpy = y+y2; tmpz = z+z2;

    if (tiles.count(HEX_TILE(tmpx,tmpy,tmpz))) ++cnt;
  }

  return cnt;
}

void part_2(const string & file) {
  ifstream in (file);
  string str;

  set<HEX_TILE> tiles;
  while(getline(in, str)) {
    ll x = 0, y = 0, z = 0;
    F(str.size()) {
      direction dir = consume(str, i);
      switch(dir) {
        case direction::nw:     ++y; --z; break; // (0,+1,-1)
        case direction::ne: ++x;     --z; break; // (+1,0,-1)
        case direction::w: --x; ++y;      break; // (-1,+1,0)
        case direction::e: ++x; --y;      break; // (+1,-1,0)
        case direction::sw: --x;     ++z; break; // (-1,0,+1)
        case direction::se:     --y; ++z; break; // (0,-1,+1)
      }
    }
    auto tile = HEX_TILE(x,y,z);
    if(!tiles.insert(tile).second) tiles.erase(tile);
  }


  FOR(day, 0, 100) { 
    set<HEX_TILE> tmp;
    for(const auto & tile: tiles) {
      for(const auto & n : adjacent) {
        ll x,y,z; tie(x,y,z) = n;
        x += tile.x; y += tile.y; z += tile.z;
        ll cnt = count(x,y,z, tiles);
        auto tile = HEX_TILE(x,y,z);
        if (!tiles.count(tile) && cnt == 2) tmp.insert(tile); 
        else if (tiles.count(tile) && cnt != 0 && cnt <= 2) tmp.insert(tile); 
      }
    }
    tiles = tmp;
  }


  cout << "Part 2: " << tiles.size() << endl;
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

