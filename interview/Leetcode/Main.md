# leetcode
## 零、Java刷题用到的接口
1. int num [];
num.length 
int[ ]  arr = new int[5];
2. String
String s = "";
s.length();
s.charAt(0); 
3. 栈
Stack<ListNode> stack = new Stack<ListNode>();
Stack<Integer> stack = new Stack<Integer>();
stack.push(new Integer(a));
stack.empty();
stack.pop();
stack.size();
![20201103233048](https://raw.githubusercontent.com/wlxklyh/imagebed/master/imageforvscode/20201103233048.png)
## 一、剑指offer
题库链接：
https://leetcode-cn.com/problemset/lcof/
参考链接：
https://github.com/aaronyan21/leetcode
https://blog.csdn.net/c406495762/article/details/79247243


1. [数组中重复的数字](https://leetcode-cn.com/problems/shu-zu-zhong-zhong-fu-de-shu-zi-lcof/)

题目：
找出数组中重复的数字。

在一个长度为 n 的数组 nums 里的所有数字都在 0～n-1 的范围内。数组中某些数字是重复的，但不知道有几个数字重复了，也不知道每个数字重复了几次。请找出数组中任意一个重复的数字。
示例 1：
输入：
[2, 3, 1, 0, 2, 5, 3]
输出：2 或 3 
限制：
2 <= n <= 100000

```Java
//解法1:拿个hashmap存储 出现两次则输出 这种方法内存占用高
class Solution {
    public int findRepeatNumber(int[] nums) {
        //注意边界
        if(nums.length == 0) {
            return -1;
        }
        boolean []hashMap = new boolean[nums.length];
        for(int i = 0;i < nums.length; i++) {
            hashMap[i] = false;
        }
        for(int i = 0;i < nums.length; i++) {
            //注意边界
            if(nums[i] < 0 || nums[i] >= nums.length) {
                return -1;
            }
            if(hashMap[nums[i]] == false) {
                hashMap[nums[i]] = true;
            }
            else{
                return nums[i];
            }
        }
        return -1;
    }
}

//解法2:从0开始将数据放到正确的位置上  正确的位置指的是 0放在坐标为0的曹位上 1放在坐标为1的上面 一旦发现放的位置已经有正确的数字 则输出。
class Solution {
    //写一个swap函数帮助很大
    public boolean swap(int[] nums,int index1,int index2){
        if(nums.length == 0) {
            return false;
        }
        if(index1 < 0 || index1 >= nums.length || index2 < 0 || index2 >= nums.length){
            return false;
        }
        int temp = nums[index1];
        nums[index1] = nums[index2];
        nums[index2] = temp;
        return true;
    }
    //
    public int findRepeatNumber(int[] nums) {
        if(nums.length == 0) {
            return -1;
        }
        //给每一个槽位找到正确的位置
        for(int i = 0;i < nums.length; i++)
        {
            if(i == nums[i])
            {
                continue;
            }
            int nowIndex = i;
            //当这个槽位不正确
            while(nowIndex != nums[nowIndex])
            {
                //放去正确的位置 交换回来
                //交换前判断下是不是交换一样的 如果是则输出
                if(nums[nowIndex] == nums[nums[nowIndex]]){
                    return nums[nowIndex];
                }
                //交换到正确位置
               swap(nums,nowIndex,nums[nowIndex]) ;
            }
        }
        return -1;
    }
}
```

2. [替换空格](https://leetcode-cn.com/problems/ti-huan-kong-ge-lcof/)

请实现一个函数，把字符串 s 中的每个空格替换成"%20"。
示例 1：
输入：s = "We are happy."
输出："We%20are%20happy."

```Java
//这个没什么好说的 但是字符串拼接会消耗这里要注意
class Solution {
    public String replaceSpace(String s) {
        String strRet = "";
        for(int i = 0;i < s.length();i++){
            if(s.charAt(i) == ' '){
                strRet = strRet + "%20";
            }else {
                strRet = strRet + s.charAt(i);
            }
        }
        return strRet;
    }
}
```

3. [从尾到头打印链表](https://leetcode-cn.com/problems/cong-wei-dao-tou-da-yin-lian-biao-lcof/)

输入一个链表的头节点，从尾到头反过来返回每个节点的值（用数组返回）。
示例 1：

输入：head = [1,3,2]
输出：[2,3,1]

```Java
/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) { val = x; }
 * }
 */
 import java.util.*;

class Solution {
    public int[] reversePrint(ListNode head) {
        Stack<ListNode> stack = new Stack<ListNode>();
        int listLen = 0 ;
        while(head != null)
        {
            listLen++;
            stack.push(head);
            head = head.next;
        }

        int []retArray = new int[listLen];
        int indexI = 0;
        while(stack.empty()==false)
        {
            retArray[indexI++] = stack.pop().val;
        }
        return retArray;
    }
}
//还可以使用递归来做
```

4. [重建二叉树](https://leetcode-cn.com/problems/zhong-jian-er-cha-shu-lcof/)

输入某二叉树的前序遍历和中序遍历的结果，请重建该二叉树。假设输入的前序遍历和中序遍历的结果中都不含重复的数字。
例如，给出
前序遍历 preorder = [3,9,20,15,7]
中序遍历 inorder = [9,3,15,20,7]
返回如下的二叉树：

```Java
/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }
 */
class Solution {
    public TreeNode buildTree(int[] preorder, int[] inorder) {
        return buildTree(preorder,0,preorder.length-1,inorder,0,inorder.length-1);
    }

    public TreeNode buildTree(int []preorder,int preStart,int preEnd,int[] inorder,int inStart,int inEnd){
        if(preStart > preEnd){
            return null;
        }
        if(inStart > inEnd){
            return null;
        }
        if(preStart == preEnd){
            TreeNode rootNode = new TreeNode();
            rootNode.val = preorder[preStart];
            rootNode.left = null;
            rootNode.right = null;
            return rootNode;
        }
        TreeNode rootNode = new TreeNode();
        rootNode.val = preorder[preStart];
        rootNode.left = null;
        rootNode.right = null;
        //下面这个for 可以提前遍历记录 快速索引 inorder[indexIn] == preorder[preStart] 加速点位 !!!
        for(int indexIn = inStart;indexIn <= inEnd;indexIn++){
            if(inorder[indexIn] == preorder[preStart]){
                TreeNode leftNode = buildTree(preorder,preStart + 1,preStart+indexIn-inStart,inorder,inStart,indexIn-1);
                TreeNode rightNode = buildTree(preorder,preStart+indexIn-inStart+1,preEnd,inorder,indexIn+1,inEnd);
                rootNode.left = leftNode;
                rootNode.right = rightNode;
                return rootNode;
            }
        }
        return rootNode;
    }
}
```


5. [用两个栈实现队列](https://leetcode-cn.com/problems/yong-liang-ge-zhan-shi-xian-dui-lie-lcof/)

用两个栈实现一个队列。队列的声明如下，请实现它的两个函数 appendTail 和 deleteHead ，分别完成在队列尾部插入整数和在队列头部删除整数的功能。(若队列中没有元素，deleteHead 操作返回 -1 )
示例 1：
输入：
["CQueue","appendTail","deleteHead","deleteHead"]
[[],[3],[],[]]
输出：[null,null,3,-1]
示例 2：
输入：
["CQueue","deleteHead","appendTail","appendTail","deleteHead","deleteHead"]
[[],[],[5],[2],[],[]]
输出：[null,-1,null,null,5,2]

```Java
class CQueue {
    Stack<Integer> stackAppend = new Stack<Integer>();
    Stack<Integer> stackDelete = new Stack<Integer>();
    public CQueue() {

    }
    
    public void appendTail(int value) {
        if(stackAppend.size() > 0){
            stackAppend.push(value);
        }else{
            while(stackDelete.size() > 0)
            {
                stackAppend.push(stackDelete.pop());
            }
            stackAppend.push(value);
        }
    }
    
    public int deleteHead() {
        if(stackDelete.size() > 0){
            return stackDelete.pop();
        }else{
            while(stackAppend.size() > 0)
            {
                stackDelete.push(stackAppend.pop());
            }
            if(stackDelete.empty() == false){
                return stackDelete.pop();
            }
        }
        return -1;
    }
}

/**
 * Your CQueue object will be instantiated and called as such:
 * CQueue obj = new CQueue();
 * obj.appendTail(value);
 * int param_2 = obj.deleteHead();
 */
```

6. [斐波那契数列](https://leetcode-cn.com/problems/fei-bo-na-qi-shu-lie-lcof/)

写一个函数，输入 n ，求斐波那契（Fibonacci）数列的第 n 项。斐波那契数列的定义如下：
F(0) = 0,   F(1) = 1
F(N) = F(N - 1) + F(N - 2), 其中 N > 1.
斐波那契数列由 0 和 1 开始，之后的斐波那契数就是由之前的两数相加而得出。
答案需要取模 1e9+7（1000000007），如计算初始结果为：1000000008，请返回 1。

```Java
//解法一：
class Solution {
    public int fib(int n) {
        if(n == 0){
            return 0;
        }
        if(n == 1){
            return 1;
        }

        int a = 0;
        int b = 1;
        int bBackup = 0;
        for(int i = 2;i <= n; i++){
            bBackup = b;
            b = (a + b)%1000000007;
            a = bBackup;
        }
        return b;
    }
}
//解法二：矩阵快速密
//解法三：公式法
```

7.  [青蛙跳台阶问题](https://leetcode-cn.com/problems/qing-wa-tiao-tai-jie-wen-ti-lcof/)

一只青蛙一次可以跳上1级台阶，也可以跳上2级台阶。求该青蛙跳上一个 n 级的台阶总共有多少种跳法。

答案需要取模 1e9+7（1000000007），如计算初始结果为：1000000008，请返回 1。
示例 1：
输入：n = 2
输出：2
示例 2：
输入：n = 7
输出：21
示例 3：
输入：n = 0
输出：1

```Java
//跟上面一题是一样的
class Solution {
    public int numWays(int n) {
        if(n == 0){
            return 1;
        }
        if(n == 1){
            return 1;
        }
        int a = 1;
        int b = 1;
        int bBackup = 1;
        for(int i = 2;i <= n;i++){
            bBackup = b;
            b = (a + b)%1000000007;
            a = bBackup;
        }
        return b;
    }
}
```
## 刷
https://leetcode-cn.com/problemset/lcof/
