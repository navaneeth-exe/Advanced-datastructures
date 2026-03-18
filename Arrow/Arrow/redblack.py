class Node:
    def __init__(self, data):
        self.data = data
        self.color = "RED"   # new nodes are always red
        self.left = None
        self.right = None
        self.parent = None


class RedBlackTree:
    def __init__(self):
        self.root = None

    # ----------- ROTATIONS -----------

    def left_rotate(self, x):
        y = x.right
        x.right = y.left

        if y.left:
            y.left.parent = x

        y.parent = x.parent

        if not x.parent:
            self.root = y
        elif x == x.parent.left:
            x.parent.left = y
        else:
            x.parent.right = y

        y.left = x
        x.parent = y

    def right_rotate(self, y):
        x = y.left
        y.left = x.right

        if x.right:
            x.right.parent = y

        x.parent = y.parent

        if not y.parent:
            self.root = x
        elif y == y.parent.left:
            y.parent.left = x
        else:
            y.parent.right = x

        x.right = y
        y.parent = x

    # ----------- INSERT -----------

    def insert(self, data):
        new_node = Node(data)

        parent = None
        current = self.root

        # Normal BST insertion
        while current:
            parent = current
            if data < current.data:
                current = current.left
            else:
                current = current.right

        new_node.parent = parent

        if not parent:
            self.root = new_node
        elif data < parent.data:
            parent.left = new_node
        else:
            parent.right = new_node

        # Fix violations
        self.fix_insert(new_node)

    # ----------- FIXING THE TREE -----------

    def fix_insert(self, node):
        while node != self.root and node.parent.color == "RED":
            parent = node.parent
            grandparent = parent.parent

            # Case: parent is left child
            if parent == grandparent.left:
                uncle = grandparent.right

                # Case 1: Uncle is red → recolor
                if uncle and uncle.color == "RED":
                    parent.color = "BLACK"
                    uncle.color = "BLACK"
                    grandparent.color = "RED"
                    node = grandparent

                else:
                    # Case 2: node is right child → rotate
                    if node == parent.right:
                        node = parent
                        self.left_rotate(node)

                    # Case 3: node is left child → rotate
                    parent.color = "BLACK"
                    grandparent.color = "RED"
                    self.right_rotate(grandparent)

            else:
                # Mirror case
                uncle = grandparent.left

                if uncle and uncle.color == "RED":
                    parent.color = "BLACK"
                    uncle.color = "BLACK"
                    grandparent.color = "RED"
                    node = grandparent
                else:
                    if node == parent.left:
                        node = parent
                        self.right_rotate(node)

                    parent.color = "BLACK"
                    grandparent.color = "RED"
                    self.left_rotate(grandparent)

        self.root.color = "BLACK"

    # ----------- TRAVERSAL -----------

    def inorder(self, node):
        if node:
            self.inorder(node.left)
            print(f"{node.data} ({node.color})", end=" ")
            self.inorder(node.right)


# ----------- USAGE -----------

tree = RedBlackTree()

values = [10, 20, 30, 15, 25, 5]

for v in values:
    tree.insert(v)

print("Inorder traversal:")
tree.inorder(tree.root)
