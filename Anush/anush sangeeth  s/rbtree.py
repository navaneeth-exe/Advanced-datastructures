class Node:
    def __init__(self, value, color="RED"):
        self.value = value
        self.color = color  # RED or BLACK
        self.left = None
        self.right = None
        self.parent = None


class RedBlackTree:
    def __init__(self):
        self.NIL = Node(value=None, color="BLACK")  # Sentinel node
        self.root = self.NIL

    # 🔄 Left rotation
    def rotate_left(self, node):
        right_child = node.right
        node.right = right_child.left

        if right_child.left != self.NIL:
            right_child.left.parent = node

        right_child.parent = node.parent

        if node.parent is None:
            self.root = right_child
        elif node == node.parent.left:
            node.parent.left = right_child
        else:
            node.parent.right = right_child

        right_child.left = node
        node.parent = right_child

    # 🔄 Right rotation
    def rotate_right(self, node):
        left_child = node.left
        node.left = left_child.right

        if left_child.right != self.NIL:
            left_child.right.parent = node

        left_child.parent = node.parent

        if node.parent is None:
            self.root = left_child
        elif node == node.parent.right:
            node.parent.right = left_child
        else:
            node.parent.left = left_child

        left_child.right = node
        node.parent = left_child

    # 🌱 Insert a new value
    def insert(self, value):
        new_node = Node(value)
        new_node.left = self.NIL
        new_node.right = self.NIL

        parent = None
        current = self.root

        # Find correct position
        while current != self.NIL:
            parent = current
            if new_node.value < current.value:
                current = current.left
            else:
                current = current.right

        new_node.parent = parent

        if parent is None:
            self.root = new_node
        elif new_node.value < parent.value:
            parent.left = new_node
        else:
            parent.right = new_node

        # Fix tree balance
        self.fix_insert(new_node)

    # 🛠 Fix violations after insert
    def fix_insert(self, node):
        while node.parent and node.parent.color == "RED":
            grandparent = node.parent.parent

            if node.parent == grandparent.left:
                uncle = grandparent.right

                # Case 1: Uncle is RED
                if uncle.color == "RED":
                    node.parent.color = "BLACK"
                    uncle.color = "BLACK"
                    grandparent.color = "RED"
                    node = grandparent
                else:
                    # Case 2: Triangle
                    if node == node.parent.right:
                        node = node.parent
                        self.rotate_left(node)

                    # Case 3: Line
                    node.parent.color = "BLACK"
                    grandparent.color = "RED"
                    self.rotate_right(grandparent)
            else:
                uncle = grandparent.left

                if uncle.color == "RED":
                    node.parent.color = "BLACK"
                    uncle.color = "BLACK"
                    grandparent.color = "RED"
                    node = grandparent
                else:
                    if node == node.parent.left:
                        node = node.parent
                        self.rotate_right(node)

                    node.parent.color = "BLACK"
                    grandparent.color = "RED"
                    self.rotate_left(grandparent)

        self.root.color = "BLACK"

    # 🔍 Inorder traversal (for checking)
    def inorder(self, node):
        if node != self.NIL:
            self.inorder(node.left)
            print(f"{node.value} ({node.color})", end=" ")
            self.inorder(node.right)


# 🚀 Example usage
if __name__ == "__main__":
    tree = RedBlackTree()

    values = [10, 20, 30, 15, 25, 5]
    for v in values:
        tree.insert(v)

    print("Inorder traversal:")
    tree.inorder(tree.root)
