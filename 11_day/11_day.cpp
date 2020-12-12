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

bool checkFree(const vector<vector<char>> & seats, ll i, ll j, ll limit) {
  ll height = seats.size(), width = seats[0].size();
  
  ll x = j, l = 0;
  while(++x < width && l++ < limit) {
    if (seats[i][x] == 'L') break;
    if (seats[i][x] == '#') return false;
  }
  
  x = j; l = 0;
  while(--x >= 0 && l++ < limit) {
    if (seats[i][x] == 'L') break;
    if (seats[i][x] == '#') return false;
  }

  x = i; l = 0;
  while(++x < height && l++ < limit) {
    if (seats[x][j] == '#') return false;
    if (seats[x][j] == 'L') break;
  }

  x = i; l = 0;
  while(--x >= 0 && l++ < limit) {
    if (seats[x][j] == '#') return false;
    if (seats[x][j] == 'L') break;
  }

  x = j; ll y = i; l = 0;
  while(--x >= 0 && --y >= 0 && l++ < limit) {
    if (seats[y][x] == '#') return false;
    if (seats[y][x] == 'L') break;
  }

  x = j; y = i; l = 0;
  while(--y >= 0 && ++x < width && l++ < limit) {
    if (seats[y][x] == '#') return false;
    if (seats[y][x] == 'L') break;
  }

  x = j; y = i; l = 0;
  while(--x >= 0 && ++y < height && l++ < limit)  {
    if (seats[y][x] == '#') return false;
    if (seats[y][x] == 'L') break;
  }

  x = j; y = i; l = 0;
  while(++x < width && ++y < height && l++ < limit)  {
    if (seats[y][x] == '#') return false;
    if (seats[y][x] == 'L') break;
  }

  return true;
}

bool checkOccupied(const vector<vector<char>> & seats, ll i, ll j, ll limit, ll tolerance) {
  ll height = seats.size(), width = seats[0].size();
  ll res = 0;

  ll x = j, l = 0;
  while(++x < width && l++ < limit) {
    if (seats[i][x] == 'L') break;
    if (seats[i][x] == '#') { res ++; break; }
  }  
  x = j; l = 0;
  while(--x >= 0 && l++ < limit) {
    if (seats[i][x] == 'L') break;
    if (seats[i][x] == '#') { res ++; break; }
  }
  x = i; l = 0;
  while(++x < height && l++ < limit) {
    if (seats[x][j] == 'L') break;
    if (seats[x][j] == '#') { res ++; break; }
  }
  x = i; l = 0;
  while(--x >= 0 && l++ < limit) {
    if (seats[x][j] == 'L') break;
    if (seats[x][j] == '#') { res ++; break; }
  }
  x = j; ll y = i; l = 0;
  while(--x >= 0 && --y >= 0 && l++ < limit) {
    if (seats[y][x] == 'L') break;
    if (seats[y][x] == '#') { res ++; break; }
  }  
  x = j; y = i; l = 0;
  while(--y >= 0 && ++x < width && l++ < limit) {
    if (seats[y][x] == 'L') break;
    if (seats[y][x] == '#') { res ++; break; }
  }
  x = j; y = i; l = 0;
  while(--x >= 0 && ++y < height && l++ < limit) {
    if (seats[y][x] == 'L') break;
    if (seats[y][x] == '#') { res ++; break; }
  }  
  x = j; y = i; l = 0;
  while(++x < width && ++y < height && l++ < limit) {
    if (seats[y][x] == 'L') break;
    if (seats[y][x] == '#') { res ++; break; }
  }

  return res >= tolerance;
}


void part_1(const string & file) {
  ifstream in(file);

  string str;
  vector<vector<char>> seats;
  
  while(getline(in, str)) {
    vector<char> tmp;
    for(const auto & i: str) tmp.PB(i);
    seats.PB(tmp);
  }

  while (true) {
    map<pair<ll, ll>, char> changes;

    F(seats.size()) {
      FF(seats[i].size()) {
        if(seats[i][j] == '.') continue;
        if(seats[i][j] == 'L' && checkFree(seats, i, j, 1)) changes[{i, j}] = '#';
        if(seats[i][j] == '#' && checkOccupied(seats, i, j, 1, 4)) changes[{i, j}] = 'L';
      }
    }

    if(changes.size() == 0) break;
    for(const auto [key, val]: changes) 
      seats[key.first][key.second] = val;
  }

  ll res = 0;
  F(seats.size()) 
    FF(seats[i].size()) 
      if(seats[i][j] == '#') ++ res;

  cout << "Part 1: " << res << endl;
}




void part_2(const string & file) {
  ifstream in (file);

  string str;
  vector<vector<char>> seats;

  while(getline(in, str)) {
    vector<char> tmp;
    for(const auto & i: str) tmp.PB(i);
    seats.PB(tmp);
  }

  while (true) {
    map<pair<ll, ll>, char> changes;

    F(seats.size()) {
      FF(seats[i].size()) {
        if(seats[i][j] == '.') continue;
        if(seats[i][j] == 'L' && checkFree(seats, i, j, INT_MAX)) changes[{i, j}] = '#';
        if(seats[i][j] == '#' && checkOccupied(seats, i, j, INT_MAX, 5)) changes[{i, j}] = 'L';
      }
    }

    if(changes.size() == 0) break;
    for(const auto [key, val]: changes) 
      seats[key.first][key.second] = val;
  }

  ll res = 0;
  F(seats.size()) 
    FF(seats[i].size()) 
      if(seats[i][j] == '#') ++ res;

  cout << "Part 2: " << res << endl;
}
