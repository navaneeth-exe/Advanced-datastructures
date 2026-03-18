class BinomialTree:
    def __init__(self, key):
        self.key = key
        self.children = []
        self.order = 0

    def attach_tree(self, other):
        # Attach other tree as a child of this tree
        self.children.append(other)
        self.order += 1

class BinomialHeap:
    def __init__(self):
        self.trees = []

    def insert(self, key):
        new_heap = BinomialHeap()
        new_heap.trees.append(BinomialTree(key))
        self.merge(new_heap)

    def merge(self, other_heap):
        self.trees = self._merge_roots(self.trees, other_heap.trees)
        
        if not self.trees:
            return
            
        i = 0
        while i < len(self.trees) - 1:
            curr = self.trees[i]
            next_tree = self.trees[i + 1]
            
            # Cases for linking
            if curr.order != next_tree.order or \
               (i + 2 < len(self.trees) and self.trees[i + 2].order == curr.order):
                i += 1
            elif curr.key <= next_tree.key:
                curr.attach_tree(next_tree)
                del self.trees[i + 1]
            else:
                next_tree.attach_tree(curr)
                del self.trees[i]

    def _merge_roots(self, trees1, trees2):
        merged = []
        i = j = 0
        while i < len(trees1) and j < len(trees2):
            if trees1[i].order <= trees2[j].order:
                merged.append(trees1[i])
                i += 1
            else:
                merged.append(trees2[j])
                j += 1
        merged.extend(trees1[i:])
        merged.extend(trees2[j:])
        return merged

    def get_min(self):
        if not self.trees:
            return None
        min_val = self.trees[0].key
        for tree in self.trees:
            if tree.key < min_val:
                min_val = tree.key
        return min_val

if __name__ == "__main__":
    heap = BinomialHeap()
    for val in [10, 20, 30, 5, 2]:
        heap.insert(val)
        
    print("Minimum value in Binomial Heap:", heap.get_min())
