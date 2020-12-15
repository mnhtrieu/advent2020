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

void part_1(vector<ll> & nums) {
  ll l = 0, r = nums.size() - 1;

  while (l < r) {
    if(nums[l] + nums[r] == 2020) {
      cout << "Part 1: " << nums[l] * nums[r] << endl;
      break;
    }
    else if (nums[l] + nums[r] < 2020) l ++;
    else r --;
  }
}

void part_2(vector<ll> & nums) {
  F(nums.size()-2) {
    ll l = i+1, r = nums.size() - 1;

    while (l < r) {
      if(nums[l] + nums[i] + nums[r] == 2020) {
        cout << "Part 2: " << nums[l] * nums[i] * nums[r] << endl;
        break;
      }
      else if (nums[l] + nums[i] + nums[r] < 2020) l ++;
      else r --;
    }
  }
}



int main(){
  ios::sync_with_stdio(0);cin.tie(0);

  vector<ll> nums;
  ll num;

  while (cin >> num) {
    nums.PB(num);
  }

  sort(nums.begin(), nums.end());


  part_1(nums);
  part_2(nums);
    
  return 0;
}



