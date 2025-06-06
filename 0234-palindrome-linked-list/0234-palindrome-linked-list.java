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
    public boolean isPalindrome(ListNode head) {
        while (head == null || head.next == null) {
            return true;
        }
        List <Integer> values = new ArrayList <> ();
        ListNode temp = head;
        while (temp != null) {
            values.add (temp.val);
            temp = temp.next;
        }
        int len = 0;
        int p1 = 0, p2 = values.size () - 1;
        while (p1 < p2) {
            if (values.get (p1) == values.get (p2)) {
                p1++; p2--;
            }
            else
                return false;
        }
        return true;
    }
}