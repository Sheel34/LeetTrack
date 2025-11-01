/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* modifiedList (int* nums, int numsSize, struct ListNode* head) {
    bool map [100001] = {false};
    for (int i = 0; i < numsSize; i++)
        if (nums [i] >= 0 && nums [i] <= 100000) map [nums [i]] = true;
    while (head && map [head -> val]) head = head -> next;
    struct ListNode* curr = head;
    while (curr && curr -> next) {
        if (map [curr -> next -> val])
            curr -> next = curr -> next -> next;
        else
            curr = curr -> next;
    }
    return head;
}