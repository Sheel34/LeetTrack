/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) {
 *         val = x;
 *         next = null;
 *     }
 * }
 */
public class Solution {
    public ListNode getIntersectionNode(ListNode headA, ListNode headB) {
        if (headA == null || headB == null)  
            return null;
        int n = 0, m = 0;
        ListNode tempA = headA, tempB = headB;
        while (tempA != null) {
            n++;
            tempA = tempA.next;
        }
        while (tempB != null) {
            m++;
            tempB = tempB.next;
        }
        int diff = Math.abs (n - m);
        ListNode p1 = headA, p2 = headB;
        if (n > m) {
            for (int i = 0; i < diff; i++)
                p1 = p1.next;
        }
        else {
            for (int i = 0; i < diff; i++)
                p2 = p2.next;
        }
        while (p1 != null && p2 != null && p1 != p2) {
            p1 = p1.next;
            p2 = p2.next;
        }
        return p1;
    }
}