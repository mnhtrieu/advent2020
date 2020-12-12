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



void part_1(const string & file) {
  ifstream in(file);

  string str;
  ll direction = 0; // EAST = 0, SOUTH = 1, WEST = 2, NORTH = 3
  ll x = 0, y = 0;

  while(getline(in, str)) {
    char action = str[0];
    ll val = stoi(str.c_str()+1);
    
    if (action == 'F') {
      switch(direction) {
        case 0: x += val; break;
        case 1: y -= val; break;
        case 2: x -= val; break;
        case 3: y += val; break;
      }
    }
    else {
      switch(action) {
        case 'N': y += val; break;
        case 'S': y -= val; break;
        case 'E': x += val; break;
        case 'W': x -= val; break;
        case 'L': direction = (direction + 4 - (val / 90)) % 4; break;
        case 'R': direction = (direction + (val / 90)) % 4; break;
      }
    }

  }
  // cout << "(x=" << x << ", y=" << y << ")" << endl;
  cout << "Part 1: " << (abs(x) + abs(y)) << endl;
}

ll sgn(ll val) {
  return (0 < val) - (val < 0);
}


void part_2(const string & file) {
  ifstream in (file);

  string str;
  // EAST = 0, SOUTH = 1, WEST = 2, NORTH = 3
  ll wx = 10, wy = 1;
  ll x = 0, y = 0;

  while(getline(in, str)) {
    char action = str[0];
    ll val = stoi(str.c_str()+1);

    switch(action) {
      case 'N': wy += val; break;
      case 'S': wy -= val; break;
      case 'E': wx += val; break;
      case 'W': wx -= val; break;
      case 'F': x += val*wx; y += val*wy; break;
      case 'L':
      case 'R':
        ll direction = action == 'L' ? val : 360 - val;
        swap(wx, wy);
        switch (direction) {
          case 90: wx *= -1; break;
          case 180: swap(wx, wy); wx *= -1; wy *= -1; break;
          case 270: wy *= -1; break;
        }
        break;
    }
    // cout << "wx=" << wx << ", wy=" << wy << ", x=" << x << ", y=" << y << endl;

  }
  // cout << "(x=" << x << ", y=" << y << ")" << endl;

  cout << "Part 2: " << (abs(x) + abs(y)) << endl;
}
