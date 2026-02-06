#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int batch;
    cin >> batch;
    for (int batch_iter = 0; batch_iter < batch; batch_iter++) {
        int element_num;
        cin >> element_num;
        vector<int> elements(element_num);
        for(int i = 0; i < element_num; i++) {
            cin >> elements[i];
        }
        
        int max_e = elements[element_num-1];
        long long ans = 0;
        
        for(int big = element_num-1; big >= 2; big--) {
            for(int mid = big-1; mid >= 1; mid--) {
                // 条件1: a[small] + a[mid] > a[big]
                int target1 = elements[big] - elements[mid];
                int l1 = 0, r1 = mid-1;
                while(l1 <= r1) {
                    int m = (l1 + r1) / 2;
                    if(elements[m] > target1) {
                        r1 = m - 1;
                    } else {
                        l1 = m + 1;
                    }
                }
                
                int target2 = max_e - elements[big] - elements[mid];
                int l2 = 0, r2 = mid-1;
                while(l2 <= r2) {
                    int m = (l2 + r2) / 2;
                    if(elements[m] > target2) {
                        r2 = m - 1;
                    } else {
                        l2 = m + 1;
                    }
                }
                
                // 取两个条件的交集
                ans+= mid-max(l1, l2);
            }
        } 
        cout << ans << endl;
    }
    return 0;
}