/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode() {}
 *     TreeNode(int val) { this.val = val; }
 *     TreeNode(int val, TreeNode left, TreeNode right) {
 *         this.val = val;
 *         this.left = left;
 *         this.right = right;
 *     }
 * }
 */
class Solution {
    public TreeNode subtreeWithAllDeepest (TreeNode root) {
        return node_helper (root).node;
    }
    private class NodeHelper {  
        TreeNode node;
        int depth;

        NodeHelper (TreeNode node, int depth) {
            this.node = node;
            this.depth = depth;
        }
    }
    public NodeHelper node_helper (TreeNode node) {
        if (node == null) return new NodeHelper (null, 0);

        NodeHelper left = node_helper (node.left);
        NodeHelper right = node_helper (node.right);

        if (left.depth > right.depth)
            return new NodeHelper (left.node, left.depth + 1);

        if (right.depth > left.depth)
            return new NodeHelper (right.node, right.depth + 1);

        return new NodeHelper (node, left.depth + 1);
    }
}