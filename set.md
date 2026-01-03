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

__________________



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

![image-20260103153309260](C:\Users\蒋励\AppData\Roaming\Typora\typora-user-images\image-20260103153309260.png)

________________



# 27移除元素

> 给你一个数组 `nums` 和一个值 `val`，你需要 **[原地](https://baike.baidu.com/item/原地算法)** 移除所有数值等于 `val` 的元素。元素的顺序可能发生改变。然后返回 `nums` 中与 `val` 不同的元素的数量。

> 假设 `nums` 中不等于 `val` 的元素数量为 `k`，要通过此题，您需要执行以下操作：更改 `nums` 数组，使 `nums` 的前 `k` 个元素包含不等于 `val` 的元素。
>
> `nums` 的其余元素和 `nums` 的大小并不重要。
>
> 返回 `k`。

#### 第一版（暴力算法）：1.2

- 通过遍历每一个元素判断是否与val相等，来进行数组的移动
- 注意：<mark>不要使用额外的变量来记录k，只需要让数组的长度在每次遇到val时-1即可</mark>
- 内部循环从i+1和i开始都可以，不需要纠结
- 每次前移记得让i回到正确的位置上

``` c++
int removeElement(vector<int>& nums, int val) {
        int length=nums.size();
        for(int i=0;i<length;i++){
            if(nums[i]==val){
                //把和val的元素删除,即前移
                for(int j=i+1;j<length;j++){
                    nums[j-1]=nums[j];
                }
                length--;
                i--;//每次删除一个元素，集体前移1，因此要抵消掉循环的更新条件，再-1，才能保证下一次循环是本来的下一个元素
            }
        }
        return length;
    }
```

- 时间复杂度：O(n^2)

- 空间复杂度：O(1)

______________________



#### 第二版（快慢指针）（自写）：1.2

> 快慢指针：<mark>该方法本质就是在一个循环中完成两个循环才能干的事</mark>

- 在一次循环内，没碰到val两个指针就一起动，碰到了就判断fast是不是val，不是就交换slow，是就移动

```c++
 int removeElement(vector<int>& nums, int val) {
        //快慢指针：从0开始遍历，一开始一起移动
        int length=nums.size();
        int fast=0;
        int slow=0;//碰到val时停
        //快指针继续移动，当再次遇到非val元素交换slow和fast上的元素，接着继续移动，重复，只不过此时fast与slow中间有一段距离了
        //因此在慢指针遇到val那一刻就判断快指针脚底下是不是非val元素，如果是就交换，不是fast往前走知道遇见非val
        for(int i=0;i<length;i++){
            if(nums[slow]!=val){
                slow++;
                fast++;//一起移动
            }else{
                if(nums[fast]!=val){
                    nums[slow]=nums[slow]^nums[fast];
                    nums[fast]=nums[slow]^nums[fast];
                    nums[slow]=nums[slow]^nums[fast];//交换
                    slow++;
                    fast++;//交换完就往前走，不然少次数
                }else{
                    fast++;//让fast一直动直到fast是非val元素
                }
            }
        }
        return slow;//slow就是非val元素个数
    }
```

- 然而我这个代码其实很垃圾
- 1.i是一个垃圾变量，没有起到实际作用
- 2.快慢指针语义错误：我在判断slow上的值，理应通过fast扫描的值
- 3.交换函数写的有点装逼了，用swap就好了
- 4.试图维护数组的完整结构，但并不需要

_______________



#### 第三版（快慢指针）标准：

- 快指针理应是用来<mark>扫描数组</mark>

- 慢指针理应用来<mark>指向下一个可以写入的位置</mark>

- 直接把fast当做循环的变量

- `[0, slow)` 这一段，永远是“已经处理好的干净数据”

- 如果现在fast指的元素是非val元素，那就挪到前面去，然后让干净数据区域变大

  > 快慢指针的精髓不是“两个指针动来动去”，
  > 而是“前一段永远是正确答案”(from chatgpt)

```c++
int removeElement(vector<int>& nums, int val) {
        int slowIndex = 0;
        for (int fastIndex = 0; fastIndex < nums.size(); fastIndex++) {
            if (val != nums[fastIndex]) {
                nums[slowIndex++] = nums[fastIndex];
            }//在fast不为val时fast和slow一起跑，而且把slow指的元素变成fast指的元素；当fast指的就是val时，fast直接往后跑就好了
        }
        return slowIndex;
    }
```

- 时间复杂度：O(n)
- 空间复杂度：O(1)

________________________________________________



# 209 长度最小的子数组

题目：

> 给定一个含有 `n` 个正整数的数组和一个正整数 `target` **。**
>
> 找出该数组中满足其总和大于等于 `target` 的长度最小的 **子数组** `[numsl, numsl+1, ..., numsr-1, numsr]` ，并返回其长度**。**如果不存在符合条件的子数组，返回 `0` 。

其中：子数组是数组中<mark>连续的非空</mark>元素序列。

#### 思路：滑动窗口 1.3

本质：<mark>双指针</mark>,把每一个子数组看做一个区间[i,j]，左边为i指针，右边为j指针，并只用一个for循环完成暴力解法中的两个for循环的任务。

<mark>滑动窗口的左指针是不回溯的，只负责“收缩窗口“</mark>,右指针则是<mark>扩张窗口</mark>

暴力解法是把每一种区间可能列出来，而滑动窗口则是在成功一次，即sum>=target，以后利用该题都是正整数的特性:

> j++时sum只增不减，i++时sum只减不增

在增减区间时保证每一次都尽量仍然保持“成功”。

总体思路就是：

- for循环中只让右指针作为循环变量，不断<mark>扩张窗口</mark>，让nums[j]进入到sum中去
- 当sum>=target时，一直移动i，让nums[i]从sum中被删去，然后让i++

- 更新条件res=min(res,j-i+1)<mark>记得+1，不然只有一个元素的时候就会被记成0，所有长度都少1</mark>
- 最后返回没找到就返回0，不然就是res

``` c++
int minSubArrayLen(int target, vector<int>& nums) {
        //滑动窗口：本质双指针
        //用一次for完成两次for循环
        int i=0;//滑动滑动窗口左临界点
        int sum=0;
        int result=INT_MAX;//不能是0，不然取小值永远都是0啦
        for(int j=0;j<nums.size();j++)//j是所求区间的右临界点
        {
            sum+=nums[j];
            while(sum>=target){//第一次在起始i位置不变的情况下找到最小子数组长度
                result=min(j-i+1,result);//如果还能大于等于target，继续更新result//起始位置开始右移
                sum-=nums[i++];//先减去第i个元素再移动，不然忽略了第i个元素了！！！
            }
        }
        return result==INT_MAX?0:result;
    }
```

- 时间复杂度：O(n)

#### 易错点 ：

- result不能初始化为0
- i只能前进不能后退
- 只有sum>=target时才能更新答案



