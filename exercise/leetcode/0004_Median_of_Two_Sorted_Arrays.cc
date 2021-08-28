#include <vector>
#include <iostream>
#include <cassert>
using namespace std;
class Solution2 {
public:
    using ST = vector<int>::size_type; 

    // Filter k-1 smallest number
    // return kth smallest number
    // assert k <= total
    double FindKth(ST k, vector<int> &nums1, ST &low1, 
                         vector<int> &nums2, ST &low2) {
      for ( ; k > 1; --k) {
        if (low1 > nums1.size() - 1) {
          ++low2;
        }
        else if (low2 > nums2.size() - 1) {
          ++low1;
        }
        else if (nums1[low1] <= nums2[low2]) {
          ++low1;
        }
        else {
          ++low2;
        }
      }
      if (low1 > nums1.size() - 1) {
        return nums2[low2];
      }
      else if (low2 > nums2.size() - 1) {
        return nums1[low1];
      }
      else if (nums1[low1] <= nums2[low2]) {
        return nums1[low1];
      }
      else {
        return nums2[low2];
      }
    }

    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2) {
      if (nums1.size() > nums2.size()) {
        return findMedianSortedArrays(nums2, nums1);
      }
      if (nums1.empty()) {
        if (nums2.size() % 2) {
          return nums2[nums2.size() / 2];
        } else {
          return (nums2[nums2.size() / 2 - 1] + nums2[nums2.size() / 2]) 
                 * 1.0 / 2;
        }
      }

      ST total = nums1.size() + nums2.size();
      ST low1 = 0, low2 = 0;
      if (total % 2) {
        ST k = total / 2 + 1;
        return FindKth(k, nums1, low1, nums2, low2);
      } else {
        ST k = total / 2;
        auto n1 = FindKth(k, nums1, low1, nums2, low2);
        auto n2 = FindKth(2, nums1, low1, nums2, low2);
        return (n1 + n2) * 1.0 / 2;
      }
    }

};

class Solution {
public:
    using ST = vector<int>::size_type; 
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2) {
      if (nums1.size() > nums2.size()) {
        return findMedianSortedArrays(nums2, nums1);
      }
      if (nums1.empty()) {
        if (nums2.size() % 2) {
          return nums2[nums2.size() / 2];
        } else {
          return (nums2[nums2.size() / 2 - 1] + nums2[nums2.size() / 2]) 
                 * 1.0 / 2;
        }
      }
      ST total = nums1.size() + nums2.size();
      ST half_total = (total + 1) / 2; 
      ST min = 0; ST max = nums1.size();
      ST i, j; 
      while (min <= max){
        i = (min + max) / 2; 
        j = half_total - i;

        if (0 < i && nums1[i - 1] > nums2[j]){
          max = i - 1; 
        } 
        else if (i < nums1.size() && nums2[j - 1 ] > nums1[i]) {
          min = i + 1;
        } 
        else {
          int left_max = 0;
          if (i == 0) {
            left_max = nums2[j - 1]; 
          } 
          else if (j == 0) {
            left_max = nums1[i - 1];
          } 
          else {
            left_max = nums1[i -1] < nums2[j - 1] ? nums2[j - 1] : nums1[i - 1];
          }
          if (total % 2) {
            return left_max;
          }
          int right_max = 0;
          if (j == 0 || i == nums1.size()) {
            right_max = nums2[j];
          } 
          else if (j == nums2.size()) {
            right_max = nums1[i];
          }
          else {
            right_max = nums1[i] < nums2[j] ? nums1[i] : nums2[j];
          }
          return (left_max + right_max) * 1.0 / 2;
        }
      }
      assert(false);
      return 0;
    }
};

int main(){
  vector<int> nums1{1};
  vector<int> nums2{2, 3, 4} ;
  Solution sol;
  cout << sol.findMedianSortedArrays(nums1, nums2);
}