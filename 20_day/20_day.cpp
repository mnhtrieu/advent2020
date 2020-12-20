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
vector<string> rot(const vector<string> & m, ll k);
vector<string> flip(const vector<string> & m);

struct RESULT {
  bool flag;
  vector<ll> order;
  unordered_map<ll, vector<string>> tiles;

  RESULT(bool flag): flag(flag) { }
  RESULT(bool flag, vector<ll> && order): flag(flag), order(order) { }
  RESULT(bool flag, vector<ll> && order, unordered_map<ll, vector<string>> && tiles): flag(flag), order(order), tiles(tiles) { }
};


RESULT rec(ll id, vector<string> && data, set<ll> used, ll idx, vector<ll> order, unordered_map<ll, vector<string>> tiles) {
  if (!data.empty()) {

    ll len = data.size();
    tiles[id] = move(data);

    ll size = (ll)sqrt(tiles.size()), col = idx % size, row = idx / size;

    if (row != 0) {
      ll id2 = order[(row-1)*size + col];
      F(len) if(tiles[id2][len-1][i] != tiles[id][0][i]) return {false};
    }

    if (col != 0) {
      ll id2 = order[(row)*size + (col - 1)];
      F(len) if(tiles[id2][i][len-1] != tiles[id][i][0]) return {false};
    }

    order.PB(id);
    used.insert(id);
  }

  if (order.size() == tiles.size()) return {true, std::move(order), std::move(tiles)};

  for(const auto & [id, data]: tiles) {
    if(used.count(id)) continue;
    F(4) {
      auto tmp = std::move(rec(id, std::move(rot(data, i)), used, idx+1, order, tiles));
      if (tmp.flag) return tmp;
      tmp = std::move(rec(id, std::move(flip(rot(data, i))), used, idx+1, order, tiles));
      if (tmp.flag) return tmp;
    }
  }

  return {false};
}


void part_1(const string & file) {
  ifstream in(file);

  string str;
  unordered_map<ll, vector<string>> tiles;

  while(!in.eof()) {
    getline(in, str);
    ll id = stoi(str.substr(str.find(' ')+1));

    vector<string> tmp;
    while(getline(in, str) && !str.empty()) tmp.emplace_back(str);
    tiles[id] = std::move(tmp);
  }

  RESULT arr = rec(0, {}, {}, -1, {}, tiles);
  ll size = sqrt(tiles.size());
  cout << "Part 1: " << arr.order[0] * arr.order[size-1] * arr.order[(size-1)*size] * arr.order[(size*size)-1] << endl;
}


bool isMonster(const vector<string> & image, ll i, ll j) {
  vector<pair<ll,ll>> relative = {
    {-1, 18},
    {0,0}, {0,5}, {0,6}, {0,11}, {0,12}, {0,17}, {0,18}, {0,19},
    {1,1}, {1,4}, {1,7}, {1,10}, {1,13}, {1,16}};

  for(auto & pos: relative) {
    ll y = i + pos.first, x = j + pos.second;
    if (y < 0 || y >= (ll)image.size() || x < 0 || x >= (ll)image.size()) return false;
    if (image[y][x] != '#') return false;
  }
    
  return true;
}

bool hasMonster(const vector<string> & image) {
  F(image.size()) {
    FF(image[i].size()) {
      if (image[i][j] == '.') continue;
      if (isMonster(image, i, j)) return true;
    }
  }
  return false;
}


void part_2(const string & file) {
  ifstream in (file);

  string str;
  unordered_map<ll, vector<string>> tiles;

  while(!in.eof()) {

    getline(in, str);
    ll id = stoi(str.substr(str.find(' ')+1));

    vector<string> tmp;
    while(getline(in, str) && !str.empty()) tmp.PB(str);
    tiles[id] = std::move(tmp);
  }

  RESULT arr = rec(0, {}, {}, -1, {}, tiles);
  ll chars = (*arr.tiles.begin()).second.size();
  ll size = sqrt(arr.tiles.size());
  vector<string> image;

  for(ll row = 0; row < size; ++ row) {
    for (ll line = 1; line < chars-1; ++ line) {
      string l;
      for(ll column = 0; column < size; ++column) {
        ll tile = arr.order[row*size+column];
        l +=arr.tiles[tile][line].substr(1, chars-2);
      }
      image.emplace_back(std::move(l));
    }
  }

  ll dragons = 0, cnt = 0;
  F(4) {
    vector<string> rotated = std::move(rot(image, i));
    if (hasMonster(rotated)) { image = std::move(rotated); break; }
    rotated = std::move(flip(rotated));
    if (hasMonster(rotated)) { image = std::move(rotated); break; }
  }

  F(image.size()) {
    FF(image[i].size()) {
      if (image[i][j] == '.') continue;
      cnt ++;
      if (isMonster(image, i, j)) dragons ++;
    }
  }

  cout << "Part 2: " << cnt - (dragons*15) << endl;
}


vector<string> rot(const vector<string> & m, ll k) { 
  if (k == 0) return m;
  vector<string> res = m;
  ll dim = m.size();

  FOR(rot, 0, k) {
    for (ll i = 0; i <= (dim-1)/2; ++i) {
      for (ll j  =i; j < dim-i-1; ++j) {
        ll p1 = res[i][j];
        ll p2 = res[j][dim-i-1];
        ll p3 = res[dim-i-1][dim-j-1];
        ll p4 = res[dim-j-1][i];

        res[j][dim-i-1] = p1;
        res[dim-i-1][dim-j-1] = p2;
        res[dim-j-1][i] = p3;
        res[i][j] = p4;
      }
    }
  }

  return res;
} 

vector<string> flip(const vector<string> & m) {
  vector<string> res = m;
  F(m.size()) FF(m.size() / 2) swap(res[i][j], res[i][m.size()-1-j]);
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