# 704二分查找

> 给定一个 n 个元素有序的（升序）整型数组 nums 和一个目标值 target  ，写一个函数搜索 nums 中的 target，如果目标值存在返回下标，否则返回 -1。

### 思路：2025.12.31

#### 闭区间写法：

- 把target框定在区间[left，right]中，每次循环结束对区间长度进行调整
- 注意循环条件一定要是<=，当只有<时，会省略掉单元素集合的情况，因此=时也是有意义的，也要进行一次判断
- 由于target在闭区间中，当mid位不是target时，就应该把mid移除在区间外，因此right和left要+-1
- 计算mid时，位运算>>优先级小于+，因此记得加括号（12月中旬跟左程云学的），还有一点就是防止和溢出

``` c++
int search(vector<int>& nums, int target) {
        if(nums.size()==0)return -1;
        int right=0;
        int left=nums.size()-1;//初始区间为[0,nums.size()-1]
        while(right<=left){
            int mid=right+((left-right)>>1);
            if(nums[mid]==target)return mid;
            if(nums[mid]<target){
                right=mid+1;//区间更新为[left,mid+1]
            }else if(nums[mid]>target){
                left=mid-1;//区间更新为[mid-1,right]
            }
        }
        return -1;
    }
```

- 时间复杂度：O(n)
- 空间复杂度：O(1)

#### 左闭右开写法：

- 把target框定在区间[left，right）
- 这时候left=right就没意义了

``` c++
int search(vector<int>& nums, int target) {
        int left=0;
        int right=nums.size();
        while(left<right){
            int mid=left+((right-left)>>1);
            if(nums[mid]>target){
                right=mid;//更新区间为[left,mid)
            }else if(nums[mid]<target){
                left=mid+1;
            }else{
                return mid;
            }
        }   
        return -1;
    }
```

- 时间复杂度：O(n)
- 空间复杂度：O(1)

<mark>一定一定要注意left是左区间头，right是右区间头，这是一个很弱智的错误，但是我因为这个错了好几次了，left在左，right在右</mark>

