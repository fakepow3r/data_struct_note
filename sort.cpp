#include<iostream>
#include<vector>
#include<math.h>
void swap(std::vector<int>&arr, int i, int j) {
	//0^a=a,a^b=b^a,(a^b)^c=a^(b^c)
	arr[i] = arr[i] ^ arr[j];
	arr[j] = arr[i] ^ arr[j];
	arr[i] = arr[i] ^ arr[j];
}
void bubblesort(std::vector<int>&arr) {
	if ( arr.size() < 2) return; 
	int length = arr.size()-1;
	for (int j = length; j >= 0; j--) {
		for (int i = 0; i < j; i++) {
			if (arr[i] > arr[i + 1]) {
				swap(arr, i, i + 1);
			}
		}
	}
}
void selectionsot(std::vector<int>& arr) {
	if (arr.size() < 2)return;
	int length = arr.size() - 1;
	for (int i = 0; i <length;i++) {
		int minindex = i;
		for (int j = i + 1; j < length; j++) {//i到n-1上寻找最小值的坐标
			minindex = arr[j] < arr[minindex] ? j : minindex;
		}
		swap(arr, i, minindex);
	}
}

int find_appear_odd(std::vector<int>&num) {//一个数组中只有一个数字出现了奇数次，其他出现偶数次，找到出现奇数的数
	int ans = 0;
	for (int i = 0; i < num.size(); i++) {
		ans ^= num[i];
	}
	return ans;
}

void find_two_odd(std::vector<int>& num) {//找到数组中两个出现奇数次的数字，假设为a，b
	int ans1 = 0;
	int ans2 = 0;
	for (int i = 0; i < num.size(); i++) {
		ans1 ^= num[i];//结果是a^b
	}
	//ans1必然不等于0
	//ans1必然有一个位置上为1
	//取出ans1最右边的1
	int rightone = ans1 &(~ans1 + 1);
	for (int& n : num) {
		if (rightone & n == 0) {
			ans2 ^= n;
		}
	}
	std::cout << ans2 << (ans1 ^ ans2) << std::endl;
}

void insertsort(std::vector<int>nums) {
	if (nums.size() < 2)return;
	for (int i = 1; i < nums.size(); i++) {//0-i做到有序
		for (int j = i - 1; j >= 0 && nums[j] > nums[j +1]; j--) {
			swap(nums, j, j + 1);
		}
	}
}

void mergesort(std::vector<int>&nums) {
	//把数组分成两份，左边排好序，右边排好序，然后再把两边合并
	if (nums.size() < 2)return;
	help(nums, 0, nums.size());
}
void help(std::vector<int>&nums, int L, int R) {//排两边的函数
	if (L = R)return;
	int mid = L + (R - L) >> 1;
	help(nums, L, mid);
	help(nums, mid + 1, R);
	merge(nums, L, mid, R);
}
void merge(std::vector<int>&nums, int L, int mid, int R) {
	std::vector<int>nums_copy(R-L+1,0);
	int i = 0;
	//初始化两个指针
	int p = 0;
	int q = mid + 1;
	while (p <= mid && q <= R) {
		nums_copy[i++] = nums[p] <=nums[q] ? nums[p++] : nums[q++];
	}
	while (p <= mid) {
		nums_copy[i++] = nums[p++];
	}
	while (q <= R) {
		nums_copy[i++] = nums[q++];
	}
	for (int j = 0; j < nums_copy.size();j++) {
		nums[L+j] = nums_copy[j];
	}
	nums_copy.clear();
}
void quicksort(std::vector<int>&nums) {
	//
}
void partition(std::vector<int>& nums, int left, int right) {

}
int search(std::vector<int>& nums, int target) {
	int left = 0;
	int right = nums.size() - 1;
	while (left <= right) {
		int mid = left + ((right - left) >> 1);
		if (nums[mid] == target) {
			return mid;
		}
		else if (nums[mid] > target) {
			right = mid - 1;
		}
		else {
			left = mid + 1;
		}
	}
	return -1;
}
//给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。
// 如果目标值不存在于数组中，返回它将会被按顺序插入的位置。
int searchInsert(std::vector<int>& nums, int target) {
	//如果存在，直接二分查找
	//如果不存在，先放到最后然后排序
	int left = 0;
	int right = nums.size() - 1;
	while (left <= right) {
		int mid = left + ((right - left) >> 1);
		if (nums[mid] < target)left = mid + 1;
		else right = mid - 1;
	}
	return left;
}

//堆结构插入
void heapinsert(std::vector<int>& nums, int index) {
	while (nums[index] > nums[(index - 1) / 2]) {
		swap(nums, nums[index], nums[(index - 1) / 2]);
		index = (index - 1) / 2;
	}
}
//堆结构删除
void heapify(std::vector<int>& nums, int index,int heapsize){
	int left = 2 * index + 1;
	while (left < heapsize)//当index孩子存在时
	{
		//先比较左右孩子
		int largest = left+1<heapsize&&nums[left]>nums[left+1]?left: left+1;
		//再跟左右孩子的较大的比较
		largest = nums[largest]>nums[index] ? largest : index;
		//如果index更大就不换，largest更大就换
		if (largest == index)break;
		swap(nums, index, largest);
		index = largest;
		left = 2 * index + 1; 
	}
}
//heapinsert 负责“往上爬”，
//heapify 负责“往下滚”，

void heapsort(std::vector<int>&nums) {
	if (nums.size() < 2)return;
	for (int i = 0; i < nums.size(); i++) {
		heapinsert(nums, i);
	}
	int heapsize = nums.size();
	swap(nums, 0, --heapsize);
	while (heapsize > 0) {
		heapify(nums, 0, heapsize);
		swap(nums, 0,-- heapsize);
	}
}