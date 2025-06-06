/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode() {}
 *     ListNode(int val) { this.val = val; }
 *     ListNode(int val, ListNode next) { this.val = val; this.next = next; }
 * }
 */
class Solution {
    public ListNode partition(ListNode head, int x) {
        if (head == null || head.next == null)
            return head;
        ListNode lessHead = new ListNode (-1), greatHead = new ListNode (-1);
        ListNode less = lessHead, great = greatHead, curr = head;
        while (curr != null) {
            if (curr.val < x) {
                less.next = curr;
                less = less.next;
            } else {
                great.next = curr;
                great = great.next;
            }
            curr = curr.next;
        }    
        great.next = null;
        less.next = greatHead.next;
        return lessHead.next;
    }
}