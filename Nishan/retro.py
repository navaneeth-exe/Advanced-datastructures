ops=[]

def rebuild():
    s=[]
    for op in ops:
        if op[0]=="push":
            s.append(op[1])
        elif op[0]=="pop" and s:
            s.pop()
    return s

def show():
    s=rebuild()
    print("Stack:")
    for x in s:
        print(x)

while True:
    print("1 push")
    print("2 pop")
    print("3 insert past")
    print("4 delete past")
    print("5 show")
    print("0 exit")

    ch=int(input())

    if ch==1:
        v=int(input())
        ops.append(("push",v))

    elif ch==2:
        ops.append(("pop",0))

    elif ch==3:
        t=int(input())
        typ=input()
        if typ=="push":
            v=int(input())
            ops.insert(t,("push",v))
        else:
            ops.insert(t,("pop",0))

    elif ch==4:
        t=int(input())
        if 0<=t<len(ops):
            ops.pop(t)

    elif ch==5:
        show()

    elif ch==0:
        break