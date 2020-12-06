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

void part_1() {
  ifstream file("input");

  ll low, high, res = 0;
  char delim, ch;
  string str;
  
  while(getline(file, str)) {
    istringstream ss(str);
    map<char, int> m;
    ss >> low >> delim >> high >> ch >> delim >> str;
    F(str.size()) m[str[i]] += 1;

    if (m[ch] >= low && m[ch] <= high) res++;
  }
  cout << "Part 1: " << res << endl;
}

void part_2() {
  ifstream file("input");

  ll p1, p2, res = 0;
  char delim, ch;
  string str;
  
  while(getline(file, str)) {
    istringstream ss(str);
    map<char, int> m;
    ss >> p1 >> delim >> p2 >> ch >> delim >> str;
    
    if((str[p1-1] == ch) + (str[p2-1] == ch) == 1) res ++;
  }
  cout << "Part 2: " << res << endl;
}


int main(){
  ios::sync_with_stdio(0);cin.tie(0);
  
  part_1();
  part_2();
  
  return 0;
}

