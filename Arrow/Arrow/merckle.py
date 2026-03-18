import hashlib

class MerkleTree:
    def __init__(self, data_list):
        self.leaves = [self.hash_data(data) for data in data_list]
        self.root = self.build_tree(self.leaves)

    # ----------- HASH FUNCTION -----------

    def hash_data(self, data):
        return hashlib.sha256(data.encode()).hexdigest()

    # ----------- BUILD TREE -----------

    def build_tree(self, nodes):
        # If only one node, that's the root
        if len(nodes) == 1:
            return nodes[0]

        new_level = []

        # Process pairs
        for i in range(0, len(nodes), 2):
            left = nodes[i]

            # If odd number, duplicate last node
            if i + 1 < len(nodes):
                right = nodes[i + 1]
            else:
                right = left

            combined = left + right
            new_hash = self.hash_data(combined)
            new_level.append(new_hash)

        # Recursive build
        return self.build_tree(new_level)

    # ----------- GET ROOT -----------

    def get_root(self):
        return self.root
        


data = ["A", "B", "C", "D"]

tree = MerkleTree(data)

print("Merkle Root:", tree.get_root())
