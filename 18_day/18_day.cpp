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

struct Token {
  char op;
  ll val;
};

bool isOp(char c) {
  return (c == '+' || c == '-' || c == '*');
}
bool isOp(Token c) { return isOp(c.op); }
map<char,int> opPrecedence = {{'+', 10}, {'-', 10}, {'*', 10}};
int opPrec(Token n) {
  return opPrecedence[n.op];
}

vector<Token> lexan(const string & in) {
  ll num = 0;
  vector<Token> res;
  F(in.size()) {
    if (in[i] == ' ') continue;
    if (isOp(in[i]) || in[i] == '(' || in[i] == ')') {
      res.push_back(Token({in[i], 0}));
    } else if (in[i] >= '0' && in[i] <= '9') {
      while (i < (ll)in.size() && in[i] >= '0' && in[i] <= '9') {
        num *= 10;
        num += in[i] - '0';
        i ++;
      }
      res.push_back({' ', num});
      if (i == (ll)in.size()) return res;
      i --;
      num = 0;
    }
  }
  return res;
}

vector<Token> postfix(const vector<Token> & in) {
  vector<Token> res;
  vector<Token> st;
  F(in.size()) {
    if (in[i].op == '(') st.push_back(in[i]);
    else if (in[i].op == ')') {
      while (st.back().op != '(') {
        res.push_back(st.back());
        st.pop_back();
      }
      st.pop_back();
    } else if (!isOp(in[i])) {
      res.push_back(in[i]);
    } else if (st.empty() || opPrec(st.back()) < opPrec(in[i])) {
      st.push_back(in[i]);
    } else {
      while (!st.empty() && opPrec(st.back()) >= opPrec(in[i])) {
        res.push_back(st.back());
        st.pop_back();
      }
      st.push_back(in[i]);
    }
  }
  while (!st.empty()) {
    res.push_back(st.back());
    st.pop_back();
  }
  return res;
}

Token doOp(Token a, Token b, char op) {
  ll res = 0;
  switch(op) {
    case '+': res = b.val + a.val; break;
    case '-': res = b.val - a.val; break;
    case '*': res = b.val * a.val; break;
    case '/': res = b.val / a.val; break;
  }
  return {' ', res};
}

ll eval(const vector<Token> & in) {
  Token op1, op2;
  vector<Token> st;
  F(in.size()) {
    
    if (isOp(in[i])) {
      op1 = st.back(); st.pop_back();
      op2 = st.back(); st.pop_back();
      Token result = doOp(op1, op2, in[i].op);
      st.push_back(result);
    } else {
      st.push_back(in[i]);
    }
  }
  return st.back().val;
}



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
  ll res = 0;
  while(getline(in, str)) {
    res += eval(postfix(lexan(str)));
  }
  cout << "Part 1: " << res << endl;
}


void part_2(const string & file) {
  ifstream in(file);
  string str;
  ll res = 0;
  opPrecedence['+'] = 20;
  while(getline(in, str)) {
    res += eval(postfix(lexan(str)));
  }
  cout << "Part 2: " << res << endl;
}
