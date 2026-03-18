import hashlib

class MerkleNode:
    def __init__(self, left, right, value, content, is_leaf=False):
        self.left = left
        self.right = right
        self.value = value
        self.content = content
        self.is_leaf = is_leaf

    @staticmethod
    def hash(val: str) -> str:
        return hashlib.sha256(val.encode('utf-8')).hexdigest()

class MerkleTree:
    def __init__(self, values):
        self.root = self.build_tree(values)

    def build_tree(self, values):
        if not values:
            return None
        
        leaves = [MerkleNode(None, None, MerkleNode.hash(val), val, True) for val in values]
        return self._build_tree(leaves)

    def _build_tree(self, nodes):
        if len(nodes) == 1:
            return nodes[0]
        
        # If odd number of nodes, duplicate the last one
        if len(nodes) % 2 != 0:
            nodes.append(nodes[-1])
            
        parents = []
        for i in range(0, len(nodes), 2):
            left = nodes[i]
            right = nodes[i + 1]
            parent_hash = MerkleNode.hash(left.value + right.value)
            content = f"{left.content}+{right.content}"
            parents.append(MerkleNode(left, right, parent_hash, content))
            
        return self._build_tree(parents)

    def print_tree(self, node, level=0):
        if node is not None:
            print("  " * level + f"Hash: {node.value[:8]}... | Content: {node.content}")
            self.print_tree(node.left, level + 1)
            self.print_tree(node.right, level + 1)

if __name__ == "__main__":
    blocks = ["Block1", "Block2", "Block3", "Block4"]
    print("Building Merkle Tree for:", blocks)
    tree = MerkleTree(blocks)
    tree.print_tree(tree.root)
