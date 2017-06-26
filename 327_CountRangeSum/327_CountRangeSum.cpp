#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	int countRangeSum(vector<int>& nums, int lower, int upper) {
		const int n = nums.size();
		if (n <= 0){
			return 0;
		}
		vector<long long> sums(n+1, 0);
		for (int i = 0; i < n; ++i){
			sums[i + 1] = sums[i] + nums[i];
		}
		return merge(sums, 0, n, lower, upper);
	}
private:
	int merge(vector<long long>& sums, int start, int end, int lower, int upper){
		if (start >= end){
			return 0;
		}
		int mid = start + (end - start) / 2;
		int count = merge(sums, start, mid, lower, upper) 
			+ merge(sums, mid+1, end, lower, upper); // 分治 

		vector<long long> tmp(end - start + 1, 0);  // 合并 
		int j = mid + 1, k = mid + 1, t = mid + 1, r = 0; // i 遍历左数组， j，k双指针遍历右数组，i增加，jk不用从头开始
		for (int i = start; i <= mid; ++i, ++r){
			while (j <= end && sums[j] - sums[i] <= upper) {
				++j;
			}
			while (k <= end && sums[k] - sums[i] < lower) {
				++k;
			}
			count += j - k;
			while (t <= end && sums[t] <= sums[i]) { // t从mid+1开始, i从start开始，如果sum[t] < sum[i]，则说明
				tmp[r++] = sums[t++];
			}
			tmp[r] = sums[i]; // tmp存储后半段sum
		}

		for (int i = 0; i < r; ++i){  // tmp : sum[mid+1] sum[mid+2] sum[mid+3] ... sum[mid]
			sums[start + i] = tmp[i];
		}
		return count;
	}
};

int main(int argc, char *argv[]){
	Solution s;
	cout << s.countRangeSum(vector<int>{-2, 5, -1}, -2, 2) << endl;
	system("pause");
	return 0;
}