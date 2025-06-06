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
    public void reorderList(ListNode head) {
        if (head == null || head.next == null)
            return;
        ListNode mid = findMid (head);
        ListNode h2 = mid.next;
        mid.next = null;
        ListNode h1 = head;
        h2 = reverse (h2);
        merge (h1, h2);
    }
    public ListNode reverse (ListNode head) {
        ListNode prev = null;
        ListNode curr = head;
        while (curr != null) {
            ListNode next = curr.next;
            curr.next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }
    public ListNode findMid (ListNode head) {
        ListNode slow = head, fast = head;
        while (fast.next != null && fast.next.next != null) {
            slow = slow.next;
            fast = fast.next.next;
        }
        return slow;
    }
    public void merge (ListNode h1, ListNode h2) {
        ListNode curr = h1;
        while (h1 != null && h2 != null) {
            ListNode next1 = h1.next;
            ListNode next2 = h2.next;
            h1.next = h2;
            h2.next = next1;
            h1 = next1;
            h2 = next2;
        }
    }
}