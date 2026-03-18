import hashlib

def hash_data(data):
    return hashlib.sha256(data.encode()).hexdigest()


class MerkleTree:
    def __init__(self, data_list):
        self.leaves = [hash_data(d) for d in data_list]
        self.root = self.build_tree(self.leaves)

    def build_tree(self, nodes):
        if len(nodes) == 1:
            return nodes[0]

        new_level = []

        for i in range(0, len(nodes), 2):
            left = nodes[i]
            right = nodes[i + 1] if i + 1 < len(nodes) else left

            combined = hash_data(left + right)
            new_level.append(combined)

        return self.build_tree(new_level)


# Example
if __name__ == "__main__":
    data = ["a", "b", "c", "d"]
    tree = MerkleTree(data)
    print("Merkle Root:", tree.root)
