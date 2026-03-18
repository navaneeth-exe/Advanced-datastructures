import hashlib


class MerkleTree:
    def __init__(self, data_blocks):
        self.leaves = [self.hash_data(data) for data in data_blocks]
        self.root = self.build_tree(self.leaves)

    def hash_data(self, data):
        return hashlib.sha256(data.encode()).hexdigest()

    def build_tree(self, nodes):
        if not nodes:
            return None

        while len(nodes) > 1:
            temp = []

            for i in range(0, len(nodes), 2):
                left = nodes[i]
                right = nodes[i + 1] if i + 1 < len(nodes) else left
                combined = self.hash_data(left + right)
                temp.append(combined)

            nodes = temp

        return nodes[0]

    def get_root(self):
        return self.root


if __name__ == "__main__":
    data = ["a", "b", "c", "d"]
    tree = MerkleTree(data)
    print(tree.get_root())
