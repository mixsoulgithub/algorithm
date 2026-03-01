/*
g++ --std=c++23 -o 1914D.out 1914D.cpp && cat 1914D.data|./1914D
*/
#include <bits/stdc++.h>
template <typename T> void dbg_out(T x) { std::cerr << x << ")" << std::endl; }
void dbg_out() { std::cerr << ")" << std::endl; }
template <typename Head, typename... Tail> void dbg_out(Head H, Tail... T) {
  std::cerr << H << ", ";
  dbg_out(T...);
}
#define debug(...)                                                             \
  std::cerr << "(" << #__VA_ARGS__ << ") = (", dbg_out(__VA_ARGS__)

typedef unsigned long long ll_t;
typedef std::vector<long long> vll_t;

using namespace std;
struct num {
  int value{};
  int index{};
  auto operator<=>(const num& b) const {
        // 先按value比较，如果value相等再按index比较
        if (auto cmp = value <=> b.value; cmp != 0) {
            return cmp;
        }
        return index <=> b.index;
    }
    
    // 需要定义相等运算符（如果自动生成的不满足需求）
    bool operator==(const num& b) const {
        return value == b.value && index == b.index;
    }
};

int main() {
  ll_t batch;
  cin >> batch;
  for (; batch > 0; batch--) {
    int days;
    cin >> days;
    priority_queue<num> n1;
    priority_queue<num> n2;
    priority_queue<num> n3;
    for (int i = 0; i < days; i++) {
      int a;
      cin >> a;
      n1.push({a, i});
    }
    for (int i = 0; i < days; i++) {
      int a;
      cin >> a;
      n2.push({a, i});
    }
    for (int i = 0; i < days; i++) {
      int a;
      cin >> a;
      n3.push({a, i});
    }
    num n1_top3[3];
    num n2_top3[3];
    num n3_top3[3];
    for (int i = 0; i < 3; i++) {
      n1_top3[i] = n1.top();
      n1.pop();
      n2_top3[i] = n2.top();
      n2.pop();
      n3_top3[i] = n3.top();
      n3.pop();
    }
    int ans = 0;
    for (int i1 = 0; i1 < 3; i1++) {
      for (int i2 = 0; i2 < 3; i2++) {
        for (int i3 = 0; i3 < 3; i3++) {
          if (n1_top3[i1].index == n2_top3[i2].index ||n3_top3[i3].index == n2_top3[i2].index|| n1_top3[i1].index == n3_top3[i3].index ){
            continue;
          }
          int sum = n1_top3[i1].value + n2_top3[i2].value + n3_top3[i3].value;
          if (sum > ans) {
            ans = sum;
          }
        }
      }
    }
    cout<<ans<<endl;
  }

  return 0;
}