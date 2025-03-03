class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


def buildTreeFromPreIn(preorder, inorder):
    if not preorder or not inorder:
        return None

    root_val = preorder[0]
    root = TreeNode(root_val)

    root_index_inorder = inorder.index(root_val)

    left_inorder = inorder[:root_index_inorder]
    right_inorder = inorder[root_index_inorder + 1:]

    left_preorder = preorder[1:1 + len(left_inorder)]
    right_preorder = preorder[1 + len(left_inorder):]

    root.left = buildTreeFromPreIn(left_preorder, left_inorder)
    root.right = buildTreeFromPreIn(right_preorder, right_inorder)

    return root


def buildTreeFromPostIn(postorder, inorder):
    if not postorder or not inorder:
        return None

    root_val = postorder[-1]
    root = TreeNode(root_val)

    root_index_inorder = inorder.index(root_val)

    left_inorder = inorder[:root_index_inorder]
    right_inorder = inorder[root_index_inorder + 1:]

    left_postorder = postorder[:len(left_inorder)]
    right_postorder = postorder[len(left_inorder):-1]

    root.left = buildTreeFromPostIn(left_postorder, left_inorder)
    root.right = buildTreeFromPostIn(right_postorder, right_inorder)

    return root


def buildTreeFromPrePost(preorder, postorder):
    if not preorder or not postorder:
        return None

    root_val = preorder[0]
    root = TreeNode(root_val)

    if len(preorder) == 1:
        return root

    left_root_val = preorder[1]
    left_root_index_post = postorder.index(left_root_val)

    left_postorder = postorder[:left_root_index_post + 1]
    right_postorder = postorder[left_root_index_post + 1:-1]

    left_preorder = preorder[1:len(left_postorder) + 1]
    right_preorder = preorder[len(left_postorder) + 1:]

    root.left = buildTreeFromPrePost(left_preorder, left_postorder)
    root.right = buildTreeFromPrePost(right_preorder, right_postorder)

    return root


def inOrderTraversal(root):
    result = []
    if root:
        result = inOrderTraversal(root.left)
        result.append(root.val)
        result = result + inOrderTraversal(root.right)
    return result


def example_1():
    preorder = [3, 9, 20, 15, 7]
    inorder = [9, 3, 15, 20, 7]
    postorder = [9, 15, 7, 20, 3]

    # Build from Pre-order and In-order
    root_pre_in = buildTreeFromPreIn(preorder, inorder)
    print("In-order traversal from tree built using Pre-order and In-order:")
    print(inOrderTraversal(root_pre_in))

    # Build from Post-order and In-order
    root_post_in = buildTreeFromPostIn(postorder, inorder)
    print("In-order traversal from tree built using Post-order and In-order:")
    print(inOrderTraversal(root_post_in))

    # If the tree is guaranteed to be full, build from Pre-order and Post-order
    if len(preorder) == len(postorder):
        root_pre_post = buildTreeFromPrePost(preorder, postorder)
        print("In-order traversal from tree built using Pre-order and Post-order:")
        print(inOrderTraversal(root_pre_post))


def main():
    examples = [
        {
            "preorder": [3, 9, 20, 15, 7],
            "inorder": [9, 3, 15, 20, 7],
            "postorder": [9, 15, 7, 20, 3],
            "description": "Example 0"
        },
        {
            "preorder": [1, 2, 4, 5, 3],
            "inorder": [4, 2, 5, 1, 3],
            "postorder": [4, 5, 2, 3, 1],
            "description": "Example 1"
        },
        {
            "preorder": [4, 2, 1, 3, 6, 5, 7],
            "inorder": [1, 2, 3, 4, 5, 6, 7],
            "postorder": [1, 3, 2, 5, 7, 6, 4],
            "description": "Example 2"
        },
        {
            "preorder": [10, 5, 15, 12, 20],
            "inorder": [5, 10, 12, 15, 20],
            "postorder": [5, 12, 20, 15, 10],
            "description": "Example 3"
        }
    ]

    for example in examples:
        print(f"\n{example['description']}:")
        preorder = example["preorder"]
        inorder = example["inorder"]
        postorder = example["postorder"]

        root_pre_in = buildTreeFromPreIn(preorder, inorder)
        print("In-order traversal from tree built using Pre-order and In-order:")
        print(inOrderTraversal(root_pre_in))

        root_post_in = buildTreeFromPostIn(postorder, inorder)
        print("In-order traversal from tree built using Post-order and In-order:")
        print(inOrderTraversal(root_post_in))

        if len(preorder) == len(postorder):
            root_pre_post = buildTreeFromPrePost(preorder, postorder)
            print("In-order traversal from tree built using Pre-order and Post-order:")
            print(inOrderTraversal(root_pre_post))


if __name__ == "__main__":
    main()
