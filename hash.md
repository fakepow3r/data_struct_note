# 242 有效的字母异位词2026.1.8

> 给定两个字符串 `s` 和 `t` ，编写一个函数来判断 `t` 是否是 `s` 的 字母异位词。
>
> 字母异位词是通过重新排列不同单词或短语的字母而形成的单词或短语，并使用所有原字母一次。

**示例 1:**

```
输入: s = "anagram", t = "nagaram"
输出: true
```

**示例 2:**

```
输入: s = "rat", t = "car"
输出: false
```

### 思路：

用一个哈希表，key值为s中的字符，value存放该字符在s中出现的次数

最后通过t对value减少，如果都是0说明每个字母出现的次数一样，那么就是字母异位词

```c++
bool isAnagram(string s, string t) {
        if(s.length()!=t.length())return false;
        //selected_letter存放每个字母出现的次数
        unordered_map<char,int> selected_letter;
        //计算s每个字母出现的次数
        for(const char &word:s){
            if(selected_letter.find(word)==selected_letter.end()){
                selected_letter[word]=1;
            }else{
                selected_letter[word]++;
            }
        }
        //计算t中每个字母出现的次数
        for(const char &w:t){
            if(selected_letter.find(w)==selected_letter.end()){
                return false;
            }else{
                selected_letter[w]--;
            }
        }
        //如果selected_letter有不是0的值，那s和t就不是字母异位词
        for(const auto&n:selected_letter){
            if(n.second!=0)return false;
        }
        return true;
    }
```

然而！！！我这写的其实是屎,优化后：

```c++
bool isAnagram(string s, string t) {
        if(s.length()!=t.length())return false;
        //selected_letter存放每个字母出现的次数
        unordered_map<char,int> selected_letter;
        //计算s每个字母出现的次数
        for(const char &word:s){
            //不需要初始化unordered_map 的 operator[] 本身就会自动初始化为 0
            selected_letter[word]++;
        }
        //计算t中每个字母出现的次数
        for(const char &w:t){
            if(selected_letter[w]==0){
                return false;
            }else{
                selected_letter[w]--;
            }
        }
        return true;
    }
```

### ASCII码思路（普通数组）：

由于 a 到 z 的 ASCII 值是连续的，我们可以将字符减去 a，转换成 0 到 25 中的数字，即数组下标。

```c++
bool isAnagram(string s, string t) {
        array<int, 26> cnt{};
        for (char c : s) {
            cnt[c - 'a']++;
        }
        for (char c : t) {
            cnt[c - 'a']--;
        }
        return cnt == array<int, 26>();
    }

```

______________

# 349 两个数组的交集 2026.1.10

> 给定两个数组 `nums1` 和 `nums2` ，返回 *它们的 交集* 。输出结果中的每个元素一定是 **唯一** 的。我们可以 **不考虑输出结果的顺序** 。

**示例 1：**

```
输入：nums1 = [1,2,2,1], nums2 = [2,2]
输出：[2]
```

### 思路：

用一个unordered_set来存放第一个数组中已经出现过的数组，然后检测第二个数组里面出现在set里面的数字

``` c++
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> selected_num;
        vector<int> ans;
        for(const int&x:nums1){
            if(selected_num.find(x)==selected_num.end()){//如果x不在selectedset中
                selected_num.insert(x);//就把x放入
            }
        }
        for(const int&y:nums2){
            if(selected_num.find(y)!=selected_num.end()){//如果y在集合中
                ans.push_back(y);//那y就是交集元素之一
                selected_num.erase(y);//为了防止重复录入ans，把集合中的y删掉
            }
        }
        return ans;
    }
};
```



。。。然而我没有利用到unordered_set的特性

- 如果元素已经在set中时，对该元素进行insert操作不会有别的操作
- 如果要删除的元素不在set中，那么erase就不会执行任何操作，同时会有返回值0，因此可以把erase放在if的条件判断语句；反之，则会删除这元素，返回1

同时，对于建立一个unordered_set

- 利用begin和end来框定该集合的左右区间。即[begin，end）

```c++
vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
    	unordered_set<int> selected_num(nums1.begin(),nums1.end());//建立nums1出现过的数字的set，不包括重复元素
        vector<int> ans;
        for(const int&y:nums2){
            if(selected_num.erase(y))//如果y在集合中，就删除y，返回1，执行if语句
            {
                ans.push_back(y);
            }
        }
        return ans;
    }
```

### 另外：

至于为什么erase没有变量接受返回值，由chatgpt：

因为在 C++ 的设计哲学里：

- 返回值 ≠ 必须使用
- 函数的主要意义可能是 **副作用**
- 是否使用返回值，由程序员自己负责

____________

# 202 快乐数2026.1.10

> 编写一个算法来判断一个数 `n` 是不是快乐数。
>
> **「快乐数」** 定义为：
>
> - 对于一个正整数，每一次将该数替换为它每个位置上的数字的平方和。
> - 然后重复这个过程直到这个数变为 1，也可能是 **无限循环** 但始终变不到 1。
> - 如果这个过程 **结果为** 1，那么这个数就是快乐数。
>
> 如果 `n` 是 *快乐数* 就返回 `true` ；不是，则返回 `false` 。
>
>  
>
> **示例 1：**
>
> ```
> 输入：n = 19
> 输出：true
> 解释：
> 12 + 92 = 82
> 82 + 22 = 68
> 62 + 82 = 100
> 12 + 02 + 02 = 1
> ```
>
> **示例 2：**
>
> ```
> 输入：n = 2
> 输出：false
> ```

### 思路:

用哈希数组来存放已经出现过的n的变化形式，如果n变化后，又变回了之前存在集合的数字，那么说明这个数字会变回来，那说明他就不是快乐数，因为他永远在一个循环内那几个数字变来变去，变不到一

```c++
class Solution {
public:
    int getSum(int n){
        int sum=0;
        while(n>0){
            int x=n%10;//从个位开始算平方和
            sum+=x*x;
            n=n/10;
        }
        return sum;
    }
    bool isHappy(int n) {
        unordered_set<int> seen;
        while(n!=1&&seen.find(n)==seen.end())//如果这个数字不等于且没在集合中
        {
            seen.insert(n);
            n=getSum(n);
        }
        return n==1;
    }
};
```

### 思路二：快慢指针

由于要判断n不是快乐数就是判断它的衍生数会不会形成循环，这类似于一个链表，只不过没有指针，但是又getnext来获得下一个元素，因此可以用快慢指针判断它的衍生数是不是有环来判断是不是快乐数

```c++
class Solution {
public:
    int getSum(int n){
        int sum=0;
        while(n>0){
            int x=n%10;//从个位开始算平方和
            sum+=x*x;
            n=n/10;
        }
        return sum;
    }
    bool isHappy(int n) {
        int slow=getSum(n);
        int fast=getSum(getSum(n));
        while(fast!=1&&slow!=fast){
            slow=getSum(slow);
            fast=getSum(getSum(fast));
            //如果slow==fast，说明有环，说明不是快乐数
        }
        return fast==1;;
    }
};
```

注意！！！：初始化快慢指针的时候就要搞定这个前后顺序了，然后用while的话，由于要先判断slow和fast相不相等才能进循环，就进不了循环了，导致只能返回false；或者用do while也可以

__________

# 1.两数之和2026.1.10

>  给定一个整数数组 `nums` 和一个整数目标值 `target`，请你在该数组中找出 **和为目标值** *`target`* 的那 **两个** 整数，并返回它们的数组下标。你
>
> 可以假设每种输入只会对应一个答案，并且你不能使用两次相同的元素。
>
> 你可以按任意顺序返回答案。

 

**示例 1：**

```
输入：nums = [2,7,11,15], target = 9
输出：[0,1]
解释：因为 nums[0] + nums[1] == 9 ，返回 [0, 1] 。
```

**示例 2：**

```
输入：nums = [3,2,4], target = 6
输出：[1,2]
```

### 思路：

利用一个哈希表来存放出现过的数字和坐标，key为数字，value为坐标，然后遍历的时候检查遍历到的这个数与target相减后的答案是否存在于哈希表中

- 如果在就直接返回这个数的坐标，和哈希表中对应数字的坐标
- 如果不在，把这个数存入哈希表中

```c++
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int>hash;
        for (int j=0;j<nums.size();j++){
            auto it=hash.find(target-nums[j]);
            if(=hash.find(target-nums[j])!=hash.end()){
                return{it->second,j};
            }
            hash[nums[j]]=j;
        }
        return{};
    }
};
```

_______

# 454 四数相加 2026.1.11

​	给你四个整数数组 `nums1`、`nums2`、`nums3` 和 `nums4` ，数组长度都是 `n` ，请你计算有多少个元组 `(i, j, k, l)` 能满足：

- `0 <= i, j, k, l < n`
- `nums1[i] + nums2[j] + nums3[k] + nums4[l] == 0`

 

**示例 1：**

```
输入：nums1 = [1,2], nums2 = [-2,-1], nums3 = [-1,2], nums4 = [0,2]
输出：2
解释：
两个元组如下：
1. (0, 0, 0, 1) -> nums1[0] + nums2[0] + nums3[0] + nums4[1] = 1 + (-2) + (-1) + 2 = 0
2. (1, 1, 0, 0) -> nums1[1] + nums2[1] + nums3[0] + nums4[0] = 2 + (-1) + (-1) + 0 = 0
```

**示例 2：**

```
输入：nums1 = [0], nums2 = [0], nums3 = [0], nums4 = [0]
输出：1
```

### 思路（暴力解法）：

用两个哈希表，key存放两个数组相加得到的值，value用来存放这个值出现的次数

```c++
class Solution {
public:
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
        unordered_map<int,int> res1,res2;
        int ans=0;
        for(int i=0;i<nums1.size();i++){
            for(int j=0;j<nums2.size();j++){
                res1[nums1[i]+nums2[j]]++;
            }
        }
        for(int x=0;x<nums3.size();x++){
            for(int y=0;y<nums4.size();y++){
                res2[nums3[x]+nums4[y]]++;
            }
        }
        for(auto pair1:res1){
            for(auto pair2:res2){
                if((pair1.first+pair2.first)==0){
                    ans+=pair1.second*pair2.second;//ans应该用两个出现次数的乘积表示，不能直接去较大值，万一另外一个也不是1，那就少算了
                }
            }
        }
        return ans;
    }
};
```

![image-20260111233254430](C:\Users\蒋励\AppData\Roaming\Typora\typora-user-images\image-20260111233254430.png)

#### 警钟长鸣。。。

### 思路（正常）：

既然要求i+j+k+l=0，即求i+j=-k-l

那么只需要一个哈希表来存放两个数组相加得到的值的次数

然后遍历另外两个数组来求他们得到值的相反数在哈希表出现的次数累加即可。。。

```c++
class Solution {
public:
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
        unordered_map<int,int> res1;
        int ans=0;
        for(int i=0;i<nums1.size();i++){
            for(int j=0;j<nums2.size();j++){
                res1[nums1[i]+nums2[j]]++;
            }
        }
        
        for(auto x:nums3){
            for(auto y:nums4){
                ans+=res1[-x-y];//会有多余的数字插入哈希表，但其value都是0，所以对结果不影响
                /*
                auto it=res1.find(-x-y);
                if(it!=res1.end()){
                	ans+=it->second;
                }
                */
            }
        }
        return ans;
    }
};
```

#### 复杂度分析

- 时间复杂度：O(*n*2)，其中 *n* 是 *nums**i* 的长度。
- 空间复杂度：O(*n*2)。



![image-20260111233741298](C:\Users\蒋励\AppData\Roaming\Typora\typora-user-images\image-20260111233741298.png)

进步了！

_______

# 383 赎金信 2026.1.12

> 给你两个字符串：`ransomNote` 和 `magazine` ，判断 `ransomNote` 能不能由 `magazine` 里面的字符构成。
>
> 如果可以，返回 `true` ；否则返回 `false` 。
>
> `magazine` 中的每个字符只能在 `ransomNote` 中使用一次。

**示例 1：**

```
输入：ransomNote = "a", magazine = "b"
输出：false
```

**示例 2：**

```
输入：ransomNote = "aa", magazine = "ab"
输出：false
```

### 思路：

这题很ez啊，用unordered_map来保存magazine每个字母出现的次数，然后遍历ransomNote，如果遍历到的字母出现次数≤0，那不就说明，不在magazine中嘛，那就是false；当然每次如果是的话就减一

```c++
class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        unordered_map<char,int> words;
        for(char x:magazine){
            words[x]++;
        }
        for(char y:ransomNote){
            if(words[y]<=0)return false;
            else{words[y]--;}
        }
        return true;
    }
};
```

### 思路二：

当然不一定要用哈希表，都说哈希表是费时的，因此直接用数组，还是利用到子母间的ASCII码是连续的，因此在数组中用当前字母减去‘a'就可以当他下标了，然后这个数组有26个，然后代码逻辑其实大差不差

```c++
class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        if (ransomNote.size() > magazine.size()) {
            return false;
        }
        int cnt[26]={0};
        for (char c : magazine) {
            cnt[c - 'a']++;
        }
        for (char c : ransomNote) {
            if (--cnt[c - 'a'] < 0) {
                return false;
            }
        }
        return true;
    }
};
```

_______

# 15 三数之和2025.9.24

> 给你一个整数数组 `nums` ，判断是否存在三元组 `[nums[i], nums[j], nums[k]]` 满足 `i != j`、`i != k` 且 `j != k` ，同时还满足 `nums[i] + nums[j] + nums[k] == 0` 。请你返回所有和为 `0` 且不重复的三元组。
>
> **注意：**答案中不可以包含重复的三元组。

**示例 1：**

```
输入：nums = [-1,0,1,2,-1,-4]
输出：[[-1,-1,2],[-1,0,1]]
解释：
nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0 。
nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0 。
nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0 。
不同的三元组是 [-1,0,1] 和 [-1,-1,2] 。
注意，输出的顺序和三元组的顺序并不重要。
```

**示例 2：**

```
输入：nums = [0,1,1]
输出：[]
解释：唯一可能的三元组和不为 0 。
```

### 思路：

大二上学期开学写到的这个题目，当时感觉就挺复杂的，也是看了题解才做出来。

核心思想其实就是将nums数组排序好，然后利用下标越大，数组越大，以及nums[j]+nums[k]=-nums[i]，这样循环变量的时候只要一个动i的变量就可以了，然后j等于i+1，k等于size-1

```c++
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        vector<vector<int>> ans_all;
        //枚举nums[i],将问题转换为nums[j]+nums[k]=-nums[i]
        for(int i=0;i<nums.size()-2;i++){
            //如果相领两个数相等，跳过
            if(i>0&&nums[i]==nums[i-1])continue;
            //如果nums[i]与紧接着后两个数字相加就大于0了，那越往后越大就不可能减小了，直接退出循环
            if(nums[i]+nums[i+1]+nums[i+2]>0)break;
            //如果nums[i]与最后两个最大的数相加还小于零，则之前不可能再出现增大的情况了，只有在增加nums【i】的情况下才有可能，所以循还最外层循环
            if(nums[i]+nums[nums.size()-2]+nums[nums.size()-1]<0)continue;
            int j=i+1,k=nums.size()-1;
            while(j<k){
                if(nums[j]+nums[k]==-nums[i]){
                    ans_all.push_back({nums[i],nums[j],nums[k]});
                    while(j<k&&nums[j]==nums[j+1])j++;
                    while(j<k&&nums[k]==nums[k-1])k--;
                    j++;
                    k--;
                }else if(nums[j]+nums[k]>-nums[i]){
                    //如果不等于且大于，移动指向更大值的指针，试着减小总体
                    k--;
                    }
                else if(nums[j]+nums[k]<-nums[i]){
                    j++;
                }
            }
        }
        return ans_all;
    }
};
```

_____

# 18四数之和2026.1.12

> 给你一个由 `n` 个整数组成的数组 `nums` ，和一个目标值 `target` 。请你找出并返回满足下述全部条件且**不重复**的四元组 `[nums[a], nums[b], nums[c], nums[d]]` （若两个四元组元素一一对应，则认为两个四元组重复）：
>
> - `0 <= a, b, c, d < n`
> - `a`、`b`、`c` 和 `d` **互不相同**
> - `nums[a] + nums[b] + nums[c] + nums[d] == target`
>
> 你可以按 **任意顺序** 返回答案 。

**示例 1：**

```
输入：nums = [1,0,-1,0,-2,2], target = 0
输出：[[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
```

**示例 2：**

```
输入：nums = [2,2,2,2,2], target = 8
输出：[[2,2,2,2]]
```

### 思路：

与15同样，只不过这一题先固定一个数字，要再固定后面一个数字，然后用双指针来求解

```c++
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(nums.begin(),nums.end());
        vector<vector<int>> ans;
        int n=nums.size();
        for(int a=0;a<n-3;a++)//对nums[a]进行枚举，即固定a看后面3个数改变
        {
            long long x=nums[a];//使用long long防止溢出
            if(a>0&&x==nums[a-1]) continue;//跳过重复数字
            if(x+nums[a+1]+nums[a+2]+nums[a+3]>target)break;//如果a连着的4个数都大于target了，那就没必要往后看了，因为后面只会越来越大，不可能再小于target了，a变成什么样都不行了，因此停止外循环
            if(x+nums[n-1]+nums[n-2]+nums[n-3]<target)continue;//如果最后3个大数加起来都小于target了，那就在这个a是没办法大于target了，移动a即可
            for(int b=a+1;b<n-2;b++)//枚举第二个数
            {
                long long y=nums[b];
                if(b>a+1&&y==nums[b-1])continue;//同上
                if (x + y + nums[b + 1] + nums[b + 2] > target) break; // 优化一
                if (x + y + nums[n - 2] + nums[n - 1] < target) continue; // 优化二
                int c = b + 1, d = n - 1;
                while(c<d)//枚举第三四个数
                {
                    long long s=x+y+nums[c]+nums[d];
                    if(s>target)d--;
                    else if(s<target)c++;
                    else{
                        ans.push_back({(int) x, (int) y, nums[c], nums[d]});
                        for (c++; c < d && nums[c] == nums[c - 1]; c++); // 跳过重复数字
                        for (d--; d > c && nums[d] == nums[d + 1]; d--); // 跳过重复数字
                    }
                }
            }
        }
        return ans;
    }
};
```

