# 977有序数组的平方

> 给你一个按 **非递减顺序** 排序的整数数组 `nums`，返回 **每个数字的平方** 组成的新数组，要求也按 **非递减顺序** 排序。

#### 直接双指针：

- 因为有可能有负数，因此平方后，最大的有可能是原来的最小的负数，即最大的数只可能在数组的两边
- 因此设置头尾各两个指针，谁大，就往答案数组的尾部挨个放

```c++
vector<int> sortedSquares(vector<int>& nums) {
        int length=nums.size()-1;
        for(int i=0;i<length+1;i++){
            nums[i]=nums[i]*nums[i];
        }
        vector<int> ans(length+1);//初始化长度为length+1的数组
        for(int left=0,right=length;left<=right;){//left=right时是有意义的，也要算进去的
            if(nums[left]<nums[right]){
                ans[length--]=nums[right--];//ans的坐标指针要额外设置，这里直接用length即可，不然会和左右指针重复
            }else{
                ans[length--]=nums[left++];
            }
        }
        return ans;
    }
```

