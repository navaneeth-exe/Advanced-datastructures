class BinomialNode:
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
        next = curr.sibling

        while next:
            if (curr.degree != next.degree or
               (next.sibling and next.sibling.degree == curr.degree)):
                prev = curr
                curr = next
            else:
                if curr.key <= next.key:
                    curr.sibling = next.sibling
                    self.link(next, curr)
                else:
                    if prev:
                        prev.sibling = next
                    else:
                        new_heap.head = next
                    self.link(curr, next)
                    curr = next
            next = curr.sibling

        return new_heap

    def insert(self, key):
        new_heap = BinomialHeap()
        new_heap.head = BinomialNode(key)
        self.head = self.union(new_heap).head

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

    def extract_min(self):
        if not self.head:
            return None

        prev_min = None
        min_node = self.head
        prev = None
        curr = self.head
        min_val = curr.key

        while curr:
            if curr.key < min_val:
                min_val = curr.key
                prev_min = prev
                min_node = curr
            prev = curr
            curr = curr.sibling

        # Remove min_node from root list
        if prev_min:
            prev_min.sibling = min_node.sibling
        else:
            self.head = min_node.sibling

        # Reverse children
        child = min_node.child
        rev = None
        while child:
            next = child.sibling
            child.sibling = rev
            child.parent = None
            rev = child
            child = next

        new_heap = BinomialHeap()
        new_heap.head = rev

        self.head = self.union(new_heap).head
        return min_node.key
