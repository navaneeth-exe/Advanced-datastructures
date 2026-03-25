class Node:
    def __init__(self,key):
        self.key=key
        self.degree=0
        self.parent=None
        self.child=None
        self.sibling=None
def merge(h1,h2):
    if not h1:return h2
    if not h2:return h1
    if h1.degree<=h2.degree:
        head=h1
        h1=h1.sibling
    else:
        head=h2
        h2=h2.sibling
    tail=head
    while h1 and h2:
        if h1.degree<=h2.degree:
            tail.sibling=h1
            h1=h1.sibling
        else:
            tail.sibling=h2
            h2=h2.sibling
        tail=tail.sibling
    tail.sibling=h1 if h1 else h2
    return head
def link(y,x):
    y.parent=x
    y.sibling=x.child
    x.child=y
    x.degree+=1
def union(h1,h2):
    new=merge(h1,h2)
    if not new:return None
    prev=None
    curr=new
    next=curr.sibling
    while next:
        if curr.degree!=next.degree or(next.sibling and next.sibling.degree==curr.degree):
            prev=curr
            curr=next
        else:
            if curr.key<=next.key:
                curr.sibling=next.sibling
                link(next,curr)
            else:
                if not prev:
                    new=next
                else:
                    prev.sibling=next
                link(curr,next)
                curr=next
        next=curr.sibling
    return new
def insert(heap,key):
    node=Node(key)
    return union(heap,node)
def show(heap):
    print("Heap elements:")
    while heap:
        print(heap.key)
        heap=heap.sibling
heap=None

n=int(input("Enter number of elements:"))
for i in range(n):
    v=int(input())
    heap=insert(heap,v)
print("Final Binomial Heap:")
show(heap)