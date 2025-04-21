#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
public:
    int minEatingSpeed(const vector<int>& piles, int h) {
        int total_bananas = accumulate(piles.begin(), piles.end(), 0);

        int k = floor(total_bananas / h);
        while (!can_all_piles_can_be_eaten_in_h_at_k(piles, h, k)) {
            k++;
        }

        return k;
    }
private:
    bool can_all_piles_can_be_eaten_in_h_at_k(const vector<int>& piles, int h, int k) {
        int hours_passed = 0;
        for (const int& bananas : piles) {
            // Increase hours by bananas at a rate of k
            hours_passed += floor(bananas - k / k);
            
            // Check if there are any bananas remaining
            if (bananas % k > 0) {
                hours_passed++;
            }
            
            // std::cout << hours_passed << ' ';
            if (hours_passed >= h) {
                // std::cout << '\n';
                return false;
            }
        }
        // std::cout << '\n';
        

        return true;
    }
};

int main() {
    cout << 534;
    Solution s;
    // std::cout << s.minEatingSpeed({3,6,7,11}, 8);
    cout << s.minEatingSpeed(vector{30,11,23,4,20}, 5);
    // std::cout << s.minEatingSpeed({30,11,23,4,20}, 6);
}