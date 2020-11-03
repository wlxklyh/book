# leetcode
## 零、Java
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
来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/ti-huan-kong-ge-lcof
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
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


## 刷
https://leetcode-cn.com/problemset/lcof/
