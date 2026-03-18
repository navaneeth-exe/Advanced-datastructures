class Node:
 def __init__(self, value, color=1):
  self.value = value
  self.color = color
  self.left = self.right = self.parent = None

class RedBlackTree:
 def __init__(self):
  self.NIL = Node(0, 0)
  self.root = self.NIL

 def left_rotate(self, node):
  right_child = node.right
  node.right = right_child.left
  if right_child.left != self.NIL:
   right_child.left.parent = node
  right_child.parent = node.parent
  if node.parent is None:
   self.root = right_child
  elif node == node.parent.left:
   node.parent.left = right_child
  else:
   node.parent.right = right_child
  right_child.left = node
  node.parent = right_child

 def right_rotate(self, node):
  left_child = node.left
  node.left = left_child.right
  if left_child.right != self.NIL:
   left_child.right.parent = node
  left_child.parent = node.parent
  if node.parent is None:
   self.root = left_child
  elif node == node.parent.right:
   node.parent.right = left_child
  else:
   node.parent.left = left_child
  left_child.right = node
  node.parent = left_child

 def insert(self, value):
  new_node = Node(value)
  new_node.left = new_node.right = self.NIL
  parent = None
  current = self.root
  while current != self.NIL:
   parent = current
   if value < current.value:
    current = current.left
   else:
    current = current.right
  new_node.parent = parent
  if parent is None:
   self.root = new_node
  elif value < parent.value:
   parent.left = new_node
  else:
   parent.right = new_node
  if new_node.parent is None:
   new_node.color = 0
   return
  if new_node.parent.parent is None:
   return
  self.fix_insert(new_node)

 def fix_insert(self, node):
  while node.parent.color == 1:
   if node.parent == node.parent.parent.right:
    uncle = node.parent.parent.left
    if uncle.color == 1:
     uncle.color = 0
     node.parent.color = 0
     node.parent.parent.color = 1
     node = node.parent.parent
    else:
     if node == node.parent.left:
      node = node.parent
      self.right_rotate(node)
     node.parent.color = 0
     node.parent.parent.color = 1
     self.left_rotate(node.parent.parent)
   else:
    uncle = node.parent.parent.right
    if uncle.color == 1:
     uncle.color = 0
     node.parent.color = 0
     node.parent.parent.color = 1
     node = node.parent.parent
    else:
     if node == node.parent.right:
      node = node.parent
      self.left_rotate(node)
     node.parent.color = 0
     node.parent.parent.color = 1
     self.right_rotate(node.parent.parent)
   if node == self.root:
    break
  self.root.color = 0

 def transplant(self, u, v):
  if u.parent is None:
   self.root = v
  elif u == u.parent.left:
   u.parent.left = v
  else:
   u.parent.right = v
  v.parent = u.parent

 def find_min(self, node):
  while node.left != self.NIL:
   node = node.left
  return node

 def delete(self, value):
  node = self.root
  while node != self.NIL and node.value != value:
   node = node.left if value < node.value else node.right
  if node == self.NIL:
   print("Value not found in tree")
   return
  temp = node
  original_color = temp.color
  if node.left == self.NIL:
   fix_node = node.right
   self.transplant(node, node.right)
  elif node.right == self.NIL:
   fix_node = node.left
   self.transplant(node, node.left)
  else:
   temp = self.find_min(node.right)
   original_color = temp.color
   fix_node = temp.right
   if temp.parent != node:
    self.transplant(temp, temp.right)
    temp.right = node.right
    temp.right.parent = temp
   self.transplant(node, temp)
   temp.left = node.left
   temp.left.parent = temp
   temp.color = node.color
  if original_color == 0:
   self.fix_delete(fix_node)

 def fix_delete(self, node):
  while node != self.root and node.color == 0:
   if node == node.parent.left:
    sibling = node.parent.right
    if sibling.color == 1:
     sibling.color = 0
     node.parent.color = 1
     self.left_rotate(node.parent)
     sibling = node.parent.right
    if sibling.left.color == 0 and sibling.right.color == 0:
     sibling.color = 1
     node = node.parent
    else:
     if sibling.right.color == 0:
      sibling.left.color = 0
      sibling.color = 1
      self.right_rotate(sibling)
      sibling = node.parent.right
     sibling.color = node.parent.color
     node.parent.color = 0
     sibling.right.color = 0
     self.left_rotate(node.parent)
     node = self.root
   else:
    sibling = node.parent.left
    if sibling.color == 1:
     sibling.color = 0
     node.parent.color = 1
     self.right_rotate(node.parent)
     sibling = node.parent.left
    if sibling.left.color == 0 and sibling.right.color == 0:
     sibling.color = 1
     node = node.parent
    else:
     if sibling.left.color == 0:
      sibling.right.color = 0
      sibling.color = 1
      self.left_rotate(sibling)
      sibling = node.parent.left
     sibling.color = node.parent.color
     node.parent.color = 0
     sibling.left.color = 0
     self.right_rotate(node.parent)
     node = self.root
  node.color = 0

 def display(self, node=None, indent="", last=True):
  if node is None:
   node = self.root
  if node != self.NIL:
   print(indent + ("R----" if last else "L----") + f"{node.value} ({'RED' if node.color else 'BLACK'})")
   indent += "     " if last else "|    "
   self.display(node.left, indent, False)
   self.display(node.right, indent, True)

tree = RedBlackTree()
values = list(map(int, input("Enter values: ").split()))
for val in values:
 tree.insert(val)

print("\nTree before deletion:")
tree.display()

delete_val = int(input("\nEnter value to delete: "))
tree.delete(delete_val)

print("\nTree after deletion:")
tree.display()
