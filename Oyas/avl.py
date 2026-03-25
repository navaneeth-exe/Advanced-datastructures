class Node:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None
        self.height = 1
def height(node):
    return node.height if node else 0
def balance(node):
    return height(node.left) - height(node.right) if node else 0
def rotate_right(y):
    x = y.left
    t2 = x.right
    x.right = y
    y.left = t2
    y.height = 1 + max(height(y.left), height(y.right))
    x.height = 1 + max(height(x.left), height(x.right))
    return x
def rotate_left(x):
    y = x.right
    t2 = y.left
    y.left = x
    x.right = t2
    x.height = 1 + max(height(x.left), height(x.right))
    y.height = 1 + max(height(y.left), height(y.right))
    return y
def insert(root, value):
    if not root:
        return Node(value)
    if value < root.value:
        root.left = insert(root.left, value)
    elif value > root.value:
        root.right = insert(root.right, value)
    else:
        return root  # no duplicates
    root.height = 1 + max(height(root.left), height(root.right))
    bf = balance(root)
    if bf > 1 and value < root.left.value:
        return rotate_right(root)
    if bf < -1 and value > root.right.value:
        return rotate_left(root)
    if bf > 1 and value > root.left.value:
        root.left = rotate_left(root.left)
        return rotate_right(root)
    if bf < -1 and value < root.right.value:
        root.right = rotate_right(root.right)
        return rotate_left(root)
    return root
def inorder(root):
    if root:
        inorder(root.left)
        print(root.value)   # no spaces before → fully left aligned
        inorder(root.right)
root = None
values = list(map(int, input("Enter numbers (space separated): ").split()))
for v in values:
    root = insert(root, v)
print("\nAVL Tree (Left-aligned output):")
inorder(root)