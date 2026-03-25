import hashlib
def hash_data(x):
    return hashlib.sha256(x.encode()).hexdigest()
def merkle_tree(data):
    level=[hash_data(x)for x in data]
    print("Leaf hashes:")
    for h in level:
        print(h)
    while len(level)>1:
        print("Next level:")
        new=[]
        for i in range(0,len(level),2):
            left=level[i]
            right=level[i+1] if i+1<len(level) else left
            h=hash_data(left+right)
            print(h)
            new.append(h)
        level=new
    return level[0]
n=int(input("Enter number of data blocks:"))
data=[]
for i in range(n):
    data.append(input())
root=merkle_tree(data)
print("Merkle Root:")
print(root)