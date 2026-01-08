# 203 移除链表元素 2026.1.4

> 给你一个链表的头节点 `head` 和一个整数 `val` ，请你删除链表中所有满足 `Node.val == val` 的节点，并返回 **新的头节点** 。

#### 思路(哨兵节点）：

当没有哨兵节点的时候，即移除链表元素时是在链表上进行操作的，那么当要移除head时，需要不同于移除一般元素的逻辑（本身只需要将要删除前一个结点的指针指向要删除结点的指针即可），代码如下↓：

``` c++
  // 删除头结点
        while (head != NULL && head->val == val) { // 注意这里不是if
            ListNode* tmp = head;
            head = head->next;
            delete tmp;
        }
```

即把头结点变为原头结点的指针。

然而！！！当在头结点之前设置一个哨兵节点时，那么<mark>对链表操作的所有逻辑将统一</mark>

![image-20260104200958114](C:\Users\86173\AppData\Roaming\Typora\typora-user-images\image-20260104200958114.png)

原理就是用一个在head之前的结点，让删除head时也可以像一般节点一样，让当前节点的指针变为要删除节点的指针即可。

``` c++
    ListNode* removeElements(ListNode* head, int val) {
        if(head==nullptr)return nullptr;
        //哨兵节点
        ListNode* dummy=new ListNode(0);//设置一个哨兵节点
        dummy->next=head;//让哨兵节点指向head
        ListNode* cur=dummy;//用cur记录当前所在结点
        while(cur!=nullptr&&cur->next!=nullptr){
            if(cur->next->val==val){//要删除的结点是cur的下一个节点
                ListNode*temp=cur->next;//用一个临时节点储存要删除的结点
                cur->next=cur->next->next;//让cur指针指向要删除结点的指针即可
                delete temp;//不要忘了释放内存
            }
            else{
                cur=cur->next;//只有当没有删除的时候才移动，如果不加else每次都移动会忽略一些结点
            }
        }
        head=dummy->next;//删除操作结束后重新确定head，防止head被删除后返回head为空节点
        delete dummy;//记得释放内存
        return head;
    }
```

- 时间复杂度：O(n)
- 空间复杂度：O(1)

<mark>注意点</mark>:

- cur要在遍历开始前设置
- 注意要释放内存，每次声明一个新的Lisnode是最后都要delete掉
- cur只有不删除的时候才动，所以不要忘了else
- 最后一定要重新确定head=dummy->next

--------------------



# 206.反转链表2026.1.4

>给你单链表的头节点 `head` ，请你反转链表，并返回反转后的链表。

![img](https://assets.leetcode.com/uploads/2021/02/19/rev1ex1.jpg)

#### 思路：

首先我的想法再定义一个新的链表，实现链表元素的反转，其实这是对<mark>内存空间的浪费</mark>。

```c++
ListNode* reverseList(ListNode* head) {
        ListNode* new_chained_head=nullptr;//新链表头
        ListNode* cur=head;//当前旧链遍历到的结点
        while(cur){
            ListNode*nxt=cur->next;//保存cur—>next防止丢失
            //利用头结点插入
            cur->next=new_chained_head;
            new_chained_head=cur;
            //将cur后移
            cur=nxt;
        }
        return new_chained_head;
    }
```

双指针：

设置一个cur指针初始指向head，以及一个pre，初始指向null；

每次移动的时候，cur的结点指向pre，然后再同时移动cur和pre；

```c++
ListNode* reverseList(ListNode* head) {
        ListNode* temp;
        ListNode*cur=head;
        ListNode*pre=nullptr;
        while(cur){
            temp=cur->next;//保存下一个节点，防止断链后找不到
            cur->next=pre;//颠倒指针
            pre=cur;//pre前移
            cur=temp;//cur前移
        }
        return pre;
    }	
```

![img](https://file1.kamacoder.com/i/algo/206.%E7%BF%BB%E8%BD%AC%E9%93%BE%E8%A1%A8.gif)

# 707.设计链表 2026.1.6

> 单链表中的节点应该具备两个属性：`val` 和 `next` 。`val` 是当前节点的值，`next` 是指向下一个节点的指针/引用。
>
> 实现 `MyLinkedList` 类：
>
> - `MyLinkedList()` 初始化 `MyLinkedList` 对象。
> - `int get(int index)` 获取链表中下标为 `index` 的节点的值。如果下标无效，则返回 `-1` 。
> - `void addAtHead(int val)` 将一个值为 `val` 的节点插入到链表中第一个元素之前。在插入完成后，新节点会成为链表的第一个节点。
> - `void addAtTail(int val)` 将一个值为 `val` 的节点追加到链表中作为链表的最后一个元素。
> - `void addAtIndex(int index, int val)` 将一个值为 `val` 的节点插入到链表中下标为 `index` 的节点之前。如果 `index` 等于链表的长度，那么该节点会被追加到链表的末尾。如果 `index` 比长度更大，该节点将 **不会插入** 到链表中。
> - `void deleteAtIndex(int index)` 如果下标有效，则删除链表中下标为 `index` 的节点。

_______

思路：这道题写起来挺顺的，但是实际遇到了很多小错误，这一次我只写了单向链表

1. 首先node的结构要写在整个链表大类里面，同时还要是public
2. 利用虚拟节点！！！这很重要，本质还是为了让对头结点的操作逻辑一般化
3. 初始化，即初始化虚拟节点，和链表长度让后面的操作简单
4. get()要首先判断index是否合法，这很重要！！！因为我经常忘记。
5. 找index个结点的时候一定要额外设定一个记录当前节点的结点cur，初始化具体是dummy还是dummy->next根据功能具体分析，总的来说<mark>要对cur停下来的那个节点操作的时候那就初始化为dummy，不然就是->next</mark>
6. 移动指针时要用while，用for我感觉逻辑会很怪，边界会处理的很模糊，但是while（）里面如果是0就不执行了，就完美解决了边界问题！！！
7. 每次增减结点的时候记得增减size！！！

``` c++
class MyLinkedList {

public:
    struct node{
        int val;
        node* next;
        node(int x):val(x),next(nullptr){}
    };
private:
    int size;
    node* dummy;
public:
    MyLinkedList() {
        dummy=new node(0);
        size=0;
    }

    int get(int index) {
        if(index<0||index>=size){
            return -1;
        }
        node*cur=dummy->next;
        while(index--){
            cur=cur->next;
        }
        return cur->val;
    }
    
    void addAtHead(int val) {
        node* cur=new node(val);
        cur->next=dummy->next;
        dummy->next=cur;
        size++;
    }
    
    void addAtTail(int val) {
        node* cur=new node(val);
        node* tail=dummy;
        while(tail->next){
            tail=tail->next;
        }
        tail->next=cur;
        size++;
    }
    
    void addAtIndex(int index, int val) {
        if(index > size) return;
        if(index < 0) index = 0; 
        node* newnode=new node(val);
        node* cur=dummy;
        while(index--){
            cur=cur->next;
        }
        newnode->next=cur->next;//逻辑搞搞清楚
        cur->next=newnode;
        size++;
    }
    
    void deleteAtIndex(int index) {
        if(index<0||index>=size)return;
        node*cur=dummy;
        while(index--){
            cur=cur->next;
        }
        node*temp=cur->next;
        cur->next=temp->next;//既然已经用temp访问了next那就直接用temp
        size--;
        delete temp;
        temp=nullptr;//防止temp变成野指针
    }
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */
```

小声哔哔：我一定会写双向链表的，某一天

______

# 面试题02.07 链表相交2026.1.7

> 给你两个单链表的头节点 `headA` 和 `headB` ，请你找出并返回两个单链表相交的起始节点。如果两个链表没有交点，返回 `null` 。

**示例 1：**

[![img](https://assets.leetcode.cn/aliyun-lc-upload/uploads/2018/12/14/160_example_1.png)](https://assets.leetcode.com/uploads/2018/12/13/160_example_1.png)

```
输入：intersectVal = 8, listA = [4,1,8,4,5], listB = [5,0,1,8,4,5], skipA = 2, skipB = 3
输出：Intersected at '8'
解释：相交节点的值为 8 （注意，如果两个链表相交则不能为 0）。
从各自的表头开始算起，链表 A 为 [4,1,8,4,5]，链表 B 为 [5,0,1,8,4,5]。
在 A 中，相交节点前有 2 个节点；在 B 中，相交节点前有 3 个节点。
```

_______

思路：我还以为有什么比较深奥的技巧,但其实就是把两条链的长度求出来，搞出来他俩的长度差值，让长的那条链把他们的差值先走完，然后再一起走，判断第一个一样的结点一样的是哪个就好了。。。

```c++
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        int alen=0;
        int blen=0;
        ListNode* cur1=headA;
        ListNode* cur2=headB;
        while(cur1){
            cur1=cur1->next;
            alen++;
        }
        while(cur2){
            cur2=cur2->next;
            blen++;
        }
        int gap=0;
        if(alen>blen){
            gap=alen-blen;
            while(gap--){
                headA=headA->next;
            }
        }else{
            gap=blen-alen;
            while(gap--){
                headB=headB->next;
            }
        }
        while(headA->next&&headB->next){
            if(headA==headB)return headA;
            else{
                headA=headA->next;
                headB=headB->next;
            }
        }
        return nullptr;
    }

//来自一个月前更优美的写法
node* link_list::findFirstCommonNode(node* head1,node* head2) {
	//遍历计算长度
	if (head1 == nullptr || head2 == nullptr || head1)return nullptr;
	int n = 0;//存放长度差值
	node* cur1 = head1;
	node* cur2 = head2;
	while (cur1->next!=nullptr) {
		n++;
		cur1 = cur1->next;
	}
	while (cur2->next != nullptr) {
		n--;
		cur2 = cur2->next;
	}
	if (cur1 != cur2) return nullptr; 
	//如果通过这个if，则就一定有公共节点
	cur1 = n > 0 ? head1 : head2;//那个链表长，把cur1设置为该链表
	cur2 = n <= 0 ? head1 : head2;
	n = abs(n);
	while (n != 0) //长的链表先走n步
	{
		n--;
		cur1 = cur1->next;
	}
	while (cur1 != cur2) {
		cur1 = cur1->next;
		cur2 = cur2->next;
	}
	return cur1;
}
//特点：利用n直接计算出gap
```

O(m+n),O(1)

注意：

- 两条链长度的差值要用变量存下来，不然在while里面做加减会编译错误
- 我这个代码后半段没有把cur1和cur2复位，其实应该复位的，我这样不是很优美

______

# 24 两两交换链表中的结点

> 给你一个链表，两两交换其中相邻的节点，并返回交换后链表的头节点。你必须在不修改节点内部的值的情况下完成本题（即，只能进行节点交换）。

**示例 1：**

![img](https://assets.leetcode.com/uploads/2020/10/03/swap_ex1.jpg)

```
输入：head = [1,2,3,4]
输出：[2,1,4,3]
```

#### 思路：

设置一个虚拟节点，在虚拟节点next和next的next不为空的时候可以进行交换，就是一定要是一对一对两个两个的换，然后把第一个next和第二个next进行交换，即可

```c++
ListNode* swapPairs(ListNode* head) {
        ListNode*dummy=new ListNode(0);
        dummy->next=head;
        ListNode*pre=dummy;
       
        while(pre->next!=NULL&&pre->next->next!=NULL){
        ListNode* first=pre->next;
        ListNode* second=pre->next->next;
        
        //先动first指针再动second指针，最后确保pre指针指向second
        //一定要保证交换完链表结构（包括pre）完整连续
        first->next=second->next;
        second->next=first;
        pre->next=second;
        //移动pre
        pre=first;
        }
        //交换完了
        ListNode* result=dummy->next;
        delete dummy;
        return result;
    }
```

#### 注意：

- 一定要先动first指针，再动second，最后保证pre在链中指向next正确，为second
- 如果先动second的话要创建额外的变量来储存second的next，麻烦！！！！

__________

# 19 删除链表的倒数第n个结点

> 给你一个链表，删除链表的倒数第 `n` 个结点，并且返回链表的头结点。

**示例 1：**

![img](https://assets.leetcode.com/uploads/2020/10/03/remove_ex1.jpg)

```
输入：head = [1,2,3,4,5], n = 2
输出：[1,2,3,5]
```

#### 思路：

这题做了很多遍了，就是用<mark>快慢指针</mark>,快指针先走n步，然后在一起走，慢指针停的那个结点的next指针就是那个要删除的结点 ezmoney

```c++
ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode*dummy=new ListNode(0);
        dummy->next=head;
        ListNode*fast=dummy,*slow=dummy;

        for(int i=0;i<n;i++){
            fast=fast->next;
        }
        while(fast->next!=NULL){
            fast=fast->next;
            slow=slow->next;
        }
        ListNode* temp=slow->next;
        slow->next=slow->next->next;
        delete temp;
        ListNode* result=dummy->next;
        delete dummy;
        return result;
    }


```

ezez

___________

# 142 环形链表ll

> 给定一个链表的头节点  `head` ，返回链表开始入环的第一个节点。 *如果链表无环，则返回 `null`。*
>
> 如果链表中有某个节点，可以通过连续跟踪 `next` 指针再次到达，则链表中存在环。 为了表示给定链表中的环，评测系统内部使用整数 `pos` 来表示链表尾连接到链表中的位置（**索引从 0 开始**）。如果 `pos` 是 `-1`，则在该链表中没有环。**注意：`pos` 不作为参数进行传递**，仅仅是为了标识链表的实际情况。
>
> **不允许修改** 链表。

**示例 1：**

![img](https://assets.leetcode.com/uploads/2018/12/07/circularlinkedlist.png)

```
输入：head = [3,2,0,-4], pos = 1
输出：返回索引为 1 的链表节点
解释：链表中有一个环，其尾部连接到第二个节点。
```

#### 思路：

通过快慢指针，先判断是否有环，然后把fast放回head，再和slow一步一步走，再次相遇时即为环入口

```c++
node* link_list::detectCycle(node* head) {
	//快慢指针第一次相遇证明有环，把快指针放回head，知道再次与慢指针相遇前一直走一步，相遇的地方就是环入口
	if (!head||!head->next) return nullptr;
	node* slow = head;
	node* fast = head;
	while (fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast) {
			fast = head;
			while (fast != slow) {
				fast = fast->next;
				slow = slow->next;
			}
			return fast;
		}
	}
	return nullptr;
}
```

设head到环入口为m，快慢指针第一次相遇离入口n个结点，m=n
