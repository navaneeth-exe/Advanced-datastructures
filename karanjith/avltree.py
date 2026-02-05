class avltree:
    class Node:
        def __init__(self, key):
            self.key = key
            self.left = None
            self.right = None
            self.height = 1

    def __init__(self):
        self.root = None
    
    def get_height(self, node):
        if node is None:
            return 0
        return node.height
    
    def get_balance(self, node):
        if node is None:
            return 0
        return self.get_height(node.left) - self.get_height(node.right)
    
    def update_height(self, node):
        if node:
            node.height = 1 + max(self.get_height(node.left), self.get_height(node.right))
    
    def rotate_right(self, z):
        y = z.left
        T2 = y.right
        
        y.right = z
        z.left = T2
        
        self.update_height(z)
        self.update_height(y)
        
        return y
    
    def rotate_left(self, z):
        y = z.right
        T2 = y.left
        
        y.left = z
        z.right = T2
        
        self.update_height(z)
        self.update_height(y)
        
        return y
    
    def insert(self, key):
        self.root = self._insert_helper(self.root, key)
    
    def _insert_helper(self, node, key):
        if node is None:
            return self.Node(key)
        
        if key < node.key:
            node.left = self._insert_helper(node.left, key)
        elif key > node.key:
            node.right = self._insert_helper(node.right, key)
        else:
            return node
        
        self.update_height(node)
        
        balance = self.get_balance(node)
        
        if balance > 1:
            if key < node.left.key:
                return self.rotate_right(node)
            else:
                node.left = self.rotate_left(node.left)
                return self.rotate_right(node)
        
        if balance < -1:
            if key > node.right.key:
                return self.rotate_left(node)
            else:
                node.right = self.rotate_right(node.right)
                return self.rotate_left(node)
        
        return node
    
    def search(self, key, node=None):
        if node is None:
            node = self.root
        
        if node is None:
            return False
        if key == node.key:
            return True
        elif key < node.key:
            return self.search(key, node.left)
        else:
            return self.search(key, node.right)

