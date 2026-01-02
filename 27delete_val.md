# 27移除元素

> 给你一个数组 `nums` 和一个值 `val`，你需要 **[原地](https://baike.baidu.com/item/原地算法)** 移除所有数值等于 `val` 的元素。元素的顺序可能发生改变。然后返回 `nums` 中与 `val` 不同的元素的数量。

> 假设 `nums` 中不等于 `val` 的元素数量为 `k`，要通过此题，您需要执行以下操作：

- 更改 `nums` 数组，使 `nums` 的前 `k` 个元素包含不等于 `val` 的元素。`nums` 的其余元素和 `nums` 的大小并不重要。
- 返回 `k`。

#### 第一版（暴力算法）：

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



#### 第二版（快慢指针）（自写）：

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
  >  而是“前一段永远是正确答案”(from chatgpt)

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

