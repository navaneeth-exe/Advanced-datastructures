class Node:
    def __init__(self, key):
        self.key = key
        self.degree = 0
        self.parent = None
        self.child = None
        self.sibling = None


class BinomialHeap:
    def __init__(self):
        self.head = None

    def merge_roots(self, h1, h2):
        if not h1:
            return h2
        if not h2:
            return h1

        if h1.degree <= h2.degree:
            head = h1
            h1 = h1.sibling
        else:
            head = h2
            h2 = h2.sibling

        tail = head

        while h1 and h2:
            if h1.degree <= h2.degree:
                tail.sibling = h1
                h1 = h1.sibling
            else:
                tail.sibling = h2
                h2 = h2.sibling
            tail = tail.sibling

        tail.sibling = h1 if h1 else h2
        return head

    def link(self, y, z):
        y.parent = z
        y.sibling = z.child
        z.child = y
        z.degree += 1

    def union(self, other):
        new_heap = BinomialHeap()
        new_heap.head = self.merge_roots(self.head, other.head)

        if not new_heap.head:
            return new_heap

        prev = None
        curr = new_heap.head
        next_node = curr.sibling

        while next_node:
            if (curr.degree != next_node.degree or
                (next_node.sibling and next_node.sibling.degree == curr.degree)):
                prev = curr
                curr = next_node
            else:
                if curr.key <= next_node.key:
                    curr.sibling = next_node.sibling
                    new_heap.link(next_node, curr)
                else:
                    if prev:
                        prev.sibling = next_node
                    else:
                        new_heap.head = next_node
                    new_heap.link(curr, next_node)
                    curr = next_node
            next_node = curr.sibling

        return new_heap

    def insert(self, key):
        temp = BinomialHeap()
        temp.head = Node(key)
        self.head = self.union(temp).head

    def get_min(self):
        if not self.head:
            return None

        y = None
        x = self.head
        min_key = float("inf")

        while x:
            if x.key < min_key:
                min_key = x.key
                y = x
            x = x.sibling

        return y

    def extract_min(self):
        if not self.head:
            return None

        prev_min = None
        min_node = self.head
        prev = None
        curr = self.head
        min_key = curr.key

        while curr:
            if curr.key < min_key:
                min_key = curr.key
                prev_min = prev
                min_node = curr
            prev = curr
            curr = curr.sibling

        if prev_min:
            prev_min.sibling = min_node.sibling
        else:
            self.head = min_node.sibling

        child = min_node.child
        prev = None

        while child:
            next_child = child.sibling
            child.sibling = prev
            child.parent = None
            prev = child
            child = next_child

        temp = BinomialHeap()
        temp.head = prev

        self.head = self.union(temp).head

        return min_node.key


if __name__ == "__main__":
    heap = BinomialHeap()
    values = [10, 3, 7, 1, 14, 8]

    for v in values:
        heap.insert(v)

    print(heap.extract_min())
    print(heap.extract_min())
