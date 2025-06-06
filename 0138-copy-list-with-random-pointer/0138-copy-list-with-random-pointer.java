/*
// Definition for a Node.
class Node {
    int val;
    Node next;
    Node random;

    public Node(int val) {
        this.val = val;
        this.next = null;
        this.random = null;
    }
}
*/

class Solution {
    public Node copyRandomList(Node head) {
        if (head == null)
            return null;
        Node curr = head;
        while (curr != null) {
            Node newNode = new Node (curr.val);
            newNode.next = curr.next;
            curr.next = newNode;
            curr = curr.next.next;
        }
        curr = head;
        while (curr != null) {
            if (curr.random != null) {
                curr.next.random = curr.random.next;
            }
            curr = curr.next.next;
        }
        Node dummy = new Node (-1);
        Node p2 = dummy;
        Node p1 = head;
        while (p1 != null) {
            p2.next = p1.next;
            p1.next = p1.next.next;
            p2 = p2.next;
            p1 = p1.next;
        }
        return dummy.next;
    }
}