# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def modifiedList (self, nums : List [int], head : Optional [ListNode]) -> Optional [ListNode]:
        mpp = set (nums)
        while head and head.val in mpp:
            head = head.next
        curr = head
        while curr and curr.next:
            while curr.next and curr.next.val in mpp:
                curr.next = curr.next.next
            curr = curr.next
        return head