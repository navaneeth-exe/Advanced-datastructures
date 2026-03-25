ops=[]

def build():
    s=[]
    for op in ops:
        if op[0]=="push":
            s.append(op[1])
        elif op[0]=="pop" and s:
            s.pop()
    return s
def show():
    s=build()
    print("Stack:")
    for x in s:
        print(x)
n=int(input("Enter number of operations:"))
for i in range(n):
    print("Enter operation:")
    print("push x / pop / insert t push x / insert t pop / delete t")    
    parts=input().split()
    if parts[0]=="push":
        ops.append(("push",int(parts[1])))
    elif parts[0]=="pop":
        ops.append(("pop",0))
    elif parts[0]=="insert":
        t=int(parts[1])
        if parts[2]=="push":
            ops.insert(t,("push",int(parts[3])))
        else:
            ops.insert(t,("pop",0))
    elif parts[0]=="delete":
        t=int(parts[1])
        if 0<=t<len(ops):
            ops.pop(t)
print("Final stack:")
show()