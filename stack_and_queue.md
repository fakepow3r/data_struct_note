# 232 用栈实现队列2026.1.15

> 请你仅使用两个栈实现先入先出队列。队列应当支持一般队列支持的所有操作（`push`、`pop`、`peek`、`empty`）：
>
> 实现 `MyQueue` 类：
>
> - `void push(int x)` 将元素 x 推到队列的末尾
> - `int pop()` 从队列的开头移除并返回元素
> - `int peek()` 返回队列开头的元素
> - `boolean empty()` 如果队列为空，返回 `true` ；否则，返回 `false`
>
> **说明：**
>
> - 你 **只能** 使用标准的栈操作 —— 也就是只有 `push to top`, `peek/pop from top`, `size`, 和 `is empty` 操作是合法的。
> - 你所使用的语言也许不支持栈。你可以使用 list 或者 deque（双端队列）来模拟一个栈，只要是标准的栈操作即可。

### 思路：

队列先进先出，但是栈只能先进后出，那用两个栈，一个栈用来保存整理好的顺序，一个栈用来颠倒顺序，具体步骤如下：

- push时，为了保证先进先出，把栈1的元素先挨个弹出并push到栈2中，然后再把xpush到栈2，再把栈2挨个push到栈1，这样，x就在栈1的最下面了，实现了后进后出
- 别的操作没什么花头

```c++
class MyQueue {
public:
    stack<int> s1;
    stack<int> s2;
    MyQueue() {

    }
    
    void push(int x) {
        while(!s1.empty()){
            s2.push(s1.top());
            s1.pop();
        }
        s2.push(x);
        while(!s2.empty()){
            s1.push(s2.top());
            s2.pop();
        }
    }
    
    int pop() {
        int x=s1.top();
        s1.pop();
        return s1.pop();
    }
    
    int peek() {
        return s1.top();
    }
    
    bool empty() {
        return s1.empty();
    }
};
```

然而，这样写的话，s2只起到了一个颠倒的中间的过程，另一种：

将s1设置为inStack，s2为outStack，顾名思义：

- instack是用来存push数据的
- outstack是用来pop和peek数据的

代码可以变成

```c++
class MyQueue {
public:
    stack<int> s1;
    stack<int> s2;
    MyQueue() {

    }
    
    void push(int x) {
        s1.push(x);
    }
    
    int pop() {
        if(s2.empty()){
            while(!s1.empty()){
                s2.push(s1.top());
                s1.pop();
            }
        }
        int x=s2.top();
        s2.pop();
        return x;
    }
    
    int peek() {
        if(s2.empty()){
            while(!s1.empty()){
                s2.push(s1.top());
                s1.pop();
            }
        }
        return s2.top();
    }
    
    bool empty() {
        return s1.empty()&&s2.empty();
    }
};
```

这样，in&out各司其职

___________

# 225 用队列实现栈2026.1.17

> 请你仅使用两个队列实现一个后入先出（LIFO）的栈，并支持普通栈的全部四种操作（`push`、`top`、`pop` 和 `empty`）。
>
> 实现 `MyStack` 类：
>
> - `void push(int x)` 将元素 x 压入栈顶。
> - `int pop()` 移除并返回栈顶元素。
> - `int top()` 返回栈顶元素。
> - `boolean empty()` 如果栈是空的，返回 `true` ；否则，返回 `false` 。

### 思路：

依然，用两个队列实现；有一个队列负责临时存放压入的元素，一个存放先进后出的顺序的元素

- 当要push元素时，先把元素存进q2，在把q1的元素依次弹出，push到q2，然后q2就已经被排好序了，但是为了代码的一致性，让两个队列职责明确，永远让q1负责存放排好的数据
- 别的也没啥花头

```c++
class MyStack {
public:
    queue<int> q1;
    queue<int> q2;
    MyStack() {
        int* data;
        int top;
        int end;
    }
    
    void push(int x) {
        q2.push(x);
        while(!q1.empty()){
            q2.push(q1.front());
            q1.pop();
        }
        swap(q1,q2);
    }
    
    int pop() {
        int r=q1.front();
        q1.pop();
        return r;
    }
    
    int top() {
        return q1.front();
    }
    
    bool empty() {
        return q1.empty();
    }
};

```

_______

# 20 有效的括号2026.1.17

> 给定一个只包括 `'('`，`')'`，`'{'`，`'}'`，`'['`，`']'` 的字符串 `s` ，判断字符串是否有效。
>
> 有效字符串需满足：
>
> 1. 左括号必须用相同类型的右括号闭合。
> 2. 左括号必须以正确的顺序闭合。
> 3. 每个右括号都有一个对应的相同类型的左括号。

**示例 1：**

**输入：**s = "()"

**输出：**true

**示例 2：**

**输入：**s = "()[]{}"

**输出：**true

**示例 3：**

**输入：**s = "(]"

**输出：**false

### 思路：

这道题在大二上数据结构的课堂上讲过，但是一直没有动手实践写过代码。

今天，从头学了一下：首先的首先，你既然要括号有效，那肯定成对出现，因此，字符数一定为偶数

接着，遍历所有左括号，然后把对应的右括号压入栈中，然后在遍历右括号的时候依次弹出，判断是否相等（利用栈的先进后出的特性），以及栈在没遍历完时是否为空

```c++
class Solution {
public:
    bool isValid(string s) {
        if(s.size()%2)return false;//为0则跳过，为1则为奇数返回false
        stack<char> str;
        for(char c:s){
            if(c=='('){
                str.push(')');
            }else if(c=='{'){
                str.push('}');
            }else if(c=='['){
                str.push(']');
            }//以上是遍历左括号的过程，压入的是右括号
            else{
                if(str.empty()||str.top()!=c)//判断时否为空以及是否相等
                {
                    return false;
                }
                str.pop();//判断完要记得弹出
            }
        }
        return str.empty();//执行到这一行就不可能有剩余，但是要防止全是右括号的情况
    }
};
```

当然，作为一道简单题，当然可以一个一个列出来，然而为了后续程序的健壮性，应该舍弃if-else的写法

可以利用哈希表map来体现括号左右的对应关系

```c++
class Solution {
    
public:
    unordered_map<char,char> mp={{'[',']'},{'(',')'},{'{','}'}};//哈希表
    bool isValid(string s) {
        if(s.size()%2)return false;
        stack<char> str;
        for(char c:s){
            if(mp.find(c)!=mp.end())//等价于mp.contains(c)
            {
                str.push(mp[c]);
            }
            else{
                if(str.empty()||str.top()!=c){
                    return false;
                }
                str.pop();
            }
        }
        return str.empty();
    }
};
```

用哈希表在后续要更改程序时只需要在哈希表中增加一个组合即可

_______

# 1047.删除字符串中的所有相邻重复项

> 给出由小写字母组成的字符串 `s`，**重复项删除操作**会选择两个相邻且相同的字母，并删除它们。
>
> 在 `s` 上反复执行重复项删除操作，直到无法继续删除。
>
> 在完成所有重复项删除操作后返回最终的字符串。答案保证唯一。

**示例：**

```
输入："abbaca"
输出："ca"
解释：
例如，在 "abbaca" 中，我们可以删除 "bb" 由于两字母相邻且相同，这是此时唯一可以执行删除操作的重复项。之后我们得到字符串 "aaca"，其中又只有 "aa" 可以执行重复项删除操作，所以最后的字符串为 "ca"。
```

 思路：

- 当前遍历的元素和栈顶元素相等就pop
- 不然就压栈

```c++
class Solution {
public:
    string removeDuplicates(string s) {
        stack<char> str;
        for(char x:s){
            if(str.empty()||x!=str.top())//一定要先判断是不是空，如果写反，str.top()是无意义的，会报错
            {
                str.push(x);
            }else{
                str.pop();
            }
        }
        string ans="";
        while(!str.empty()){
            ans+=str.top();
            str.pop();
        }
        reverse(ans.begin(),ans.end());
        return ans;
    }
};
```

然而，string可以直接用push_back和pop_back来实现栈的功能

```c++
class Solution {
public:
    string removeDuplicates(string s) {
        string ans;
        for(char x:s){
            if(ans.empty()||x!=ans.back())//取上一个元素用back（）
            {
                ans.push_back(x);
            }else{
                ans.pop_back();
            }
        }
        return ans;
    }
};
```

______

# 150.逆波兰表达式求值 2026.1.19

> 给你一个字符串数组 `tokens` ，表示一个根据 [逆波兰表示法](https://baike.baidu.com/item/逆波兰式/128437) 表示的算术表达式。
>
> 请你计算该表达式。返回一个表示表达式值的整数。
>
> **注意：**
>
> - 有效的算符为 `'+'`、`'-'`、`'*'` 和 `'/'` 。
> - 每个操作数（运算对象）都可以是一个整数或者另一个表达式。
> - 两个整数之间的除法总是 **向零截断** 。
> - 表达式中不含除零运算。
> - 输入是一个根据逆波兰表示法表示的算术表达式。
> - 答案及所有中间计算结果可以用 **32 位** 整数表示。

**示例 1：**

```
输入：tokens = ["2","1","+","3","*"]
输出：9
解释：该算式转化为常见的中缀算术表达式为：((2 + 1) * 3) = 9
```

### 思路：

对tokens里面每个元素，先判断是数字还是op

- 如果是数字直接压入栈
- 如果是op，就弹出栈中最上面两个元素进行运算，把结果再压回栈

```c++
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> nums;
        for(const string& s:tokens){
            if(s=="+"||s=="-"||s=="*"||s=="/"){
                int a=nums.top();
                nums.pop();
                int b=nums.top();
                nums.pop();
                if(s=="+") nums.push(b+a);
                else if(s=="-") nums.push(b-a);
                else if(s=="*") nums.push(b*a);
                else nums.push(b/a);
            }else nums.push(stoi(s));
        }
        return nums.top();
    }
};
```

### 代码细节：

- 由于遍历tokens时，得到的是一个字符串，而栈是储存int类型的，因此，在压入栈的时候要用stoi()把字符串转化为int类型

- 判断该字符串是不是数字是不太好判断的，而判断是不是op只有四种情况，因此直接枚举op即可
- 然后由于s是string，要用“  “
- 运算顺序是先弹出的在被运算位



_______

# 239.滑动窗口的最大值2026.1.19

> 给你一个整数数组 `nums`，有一个大小为 `k` 的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口内的 `k` 个数字。滑动窗口每次只向右移动一位。
>
> 返回 *滑动窗口中的最大值* 。
>
>  
>
> **示例 1：**
>
> ```
> 输入：nums = [1,3,-1,-3,5,3,6,7], k = 3
> 输出：[3,3,5,5,6,7]
> 解释：
> 滑动窗口的位置                最大值
> ---------------               -----
> [1  3  -1] -3  5  3  6  7       3
>  1 [3  -1  -3] 5  3  6  7       3
>  1  3 [-1  -3  5] 3  6  7       5
>  1  3  -1 [-3  5  3] 6  7       5
>  1  3  -1  -3 [5  3  6] 7       6
>  1  3  -1  -3  5 [3  6  7]      7
> ```

### 思路：

把滑动窗口具体变为一个<mark>存放下标</mark>的双端队列

- 每次移动有右入
- 每次移动有左出
- 最左边那个下标对应的元素一定是队列中最大的，并记录到答案集中

而且，这三件事顺序是不能变的

另外，右入是特殊的：因为为了做到第三点，那么这个队列一定是单调队列，那么进入队列的一定要是比最左边小的，不然就把左边第一个元素弹出，直到队列再加入新元素仍然是个单调递减队列

```c++
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n=nums.size();
        vector<int> ans(n-k+1);
        deque<int> wd;
        for(int i=0;i<n;i++){
            //1.右入
            while(!wd.empty()&&nums[i]>nums[wd.back()]){
                wd.pop_back();
            }
            wd.push_back(i);

            //2.左出
            int left=i-k+1;
            if(wd.front()<left){
                wd.pop_front();
            }
            
            //3.把wd最左边的数字记录到答案
            if(left>=0){
                ans[left]=nums[wd.front()];
            }
        }
        return ans;
    }
};
```



__________

# 347.前k个高频元素2026.1.20

> 给你一个整数数组 `nums` 和一个整数 `k` ，请你返回其中出现频率前 `k` 高的元素。你可以按 **任意顺序** 返回答案。
>
>  
>
> **示例 1：**
>
> **输入：**nums = [1,1,1,2,2,3], k = 2
>
> **输出：**[1,2]
>
> **示例 2：**
>
> **输入：**nums = [1], k = 1
>
> **输出：**[1]
>
> **示例 3：**
>
> **输入：**nums = [1,2,1,2,1,2,3,1,3,2], k = 2
>
> **输出：**[1,2]

### 思路：

- 首先，要记录每个数字出现的次数，那么就要用到哈希表unordered_map，key是nums中的元素，value是这个nums出现的次数
- 其次，需要给哈希表中的key以出现次数排序，可以用到数组，数组下标设置为数字出现的次数，元素设置为出现该次数的数字集合
- 最后，根据这个数组，从尾部开始遍历，直到答案数组个数为k时，停止遍历，返回答案数组

```c++
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int> count;//记录每个数字出现的次数
        int max_count=0;//记录最大出现次数,最后会被用作遍历数组的起始下标
        for(const int&x:nums){
            count[x]++;
            max_count=max(max_count,count[x]);
        }

        vector<vector<int>> sorted_nums(max_count+1);//防止下列添加元素是数组越界
        for(const auto&num:count){
            //sorted_nums[num.second]表示 频率为 num.second 的所有数字
            sorted_nums[num.second].push_back(num.first);//把每个数字都存到sorted_nums对于出现次数的集合中去
        }

        vector<int> ans;
        for(int i=max_count;i>0&&ans.size()<k;i--){
            ans.insert(ans.end(),//等价于从ans的尾部开始添加
                       sorted_nums[i].begin(),//从sorted_nums[i]的第一个元素开始添加
                       sorted_nums[i].end());//到最后一个元素
        }
        return ans;
    }
};
```

### 注：

- 最后一个for循环的body写法比较特殊，就是把 sorted_nums[i] 里所有元素，按顺序追加到 ans 的末尾

- ```c++ 
  vector<vector<int>> sorted_nums(max_count+1);
  ```

  是为了防止添加元素时数组越界







