class Node:
    def __init__(self, key):
        self.key = key
        self.degree = 0
        self.parent = None
        self.child = None
        self.sibling = None


class BinomialHeap:
    def __init__(self):
        self.head = None  # start of root list

    # ----------- MERGE ROOT LISTS -----------

    def merge(self, h1, h2):
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

    # ----------- LINK TREES -----------

    def link(self, y, z):
        # Make y a child of z
        y.parent = z
        y.sibling = z.child
        z.child = y
        z.degree += 1

    # ----------- UNION -----------

    def union(self, other_heap):
        new_heap = BinomialHeap()
        new_heap.head = self.merge(self.head, other_heap.head)

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
                    self.link(next_node, curr)
                else:
                    if prev:
                        prev.sibling = next_node
                    else:
                        new_heap.head = next_node
                    self.link(curr, next_node)
                    curr = next_node
            next_node = curr.sibling

        return new_heap

    # ----------- INSERT -----------

    def insert(self, key):
        new_heap = BinomialHeap()
        new_heap.head = Node(key)
        self.head = self.union(new_heap).head

    # ----------- FIND MIN -----------

    def get_min(self):
        if not self.head:
            return None

        y = None
        x = self.head
        min_val = float('inf')

        while x:
            if x.key < min_val:
                min_val = x.key
                y = x
            x = x.sibling

        return y

    # ----------- EXTRACT MIN -----------

    def extract_min(self):
        if not self.head:
            return None

        prev_min = None
        min_node = self.head
        prev = None
        curr = self.head
        min_val = curr.key

        # Find minimum root
        while curr:
            if curr.key < min_val:
                min_val = curr.key
                prev_min = prev
                min_node = curr
            prev = curr
            curr = curr.sibling

        # Remove min node from root list
        if prev_min:
            prev_min.sibling = min_node.sibling
        else:
            self.head = min_node.sibling

        # Reverse children
        child = min_node.child
        prev = None

        while child:
            next_child = child.sibling
            child.sibling = prev
            child.parent = None
            prev = child
            child = next_child

        new_heap = BinomialHeap()
        new_heap.head = prev

        self.head = self.union(new_heap).head

        return min_node.key

    # ----------- PRINT -----------

    def print_heap(self):
        def print_tree(node, indent=0):
            while node:
                print(" " * indent + str(node.key))
                if node.child:
                    print_tree(node.child, indent + 4)
                node = node.sibling

        print_tree(self.head)
        

bh = BinomialHeap()

bh.insert(10)
bh.insert(20)
bh.insert(5)
bh.insert(30)
bh.insert(2)

print("Minimum:", bh.get_min().key)

print("Extract Min:", bh.extract_min())

print("Heap structure:")
bh.print_heap()
