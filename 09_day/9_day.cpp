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

bool find(const vector<ll> & nums, ll res) {
  FOR(i, nums.size()-25, nums.size()) {
    FOR(j, i+1, nums.size()) {
      if(nums[i] + nums[j] == res) return true;
    }
  }
  return false;
}


void part_1(const string & file) {
  ifstream in(file);

  vector<ll> nums;
  ll i;
  while(nums.size() < 25 && in >> i) nums.PB(i);
  
  while(in >> i) {
    if(!find(nums, i)) break;
    nums.PB(i);
  }
  
  cout << "Part 1: " << i << endl;
}


void part_2(const string & file) {
  ifstream in (file);

  ll res = 552655238;

  vector<ll> nums;
  ll i, it = 0, sum = 0, m = INT_MAX, m2 = 0;

  while(in >> i) {
    nums.PB(i);
    while (sum + i > res) sum -= nums[it++];
    sum += i;
    if (sum == res) break;
  }

  FOR(i, it, nums.size()) {
    m = min(nums[i], m);
    m2 = max(nums[i], m2);
  }
  cout << "Part 2: " << m + m2 << endl;
}
