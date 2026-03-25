import hashlib

def get_hash(data):
    return hashlib.sha256(data.encode()).hexdigest()

def build_tree(leaves):
    level=[get_hash(x)for x in leaves]

    print("Leaf hashes:")
    for h in level:
        print(h)

    while len(level)>1:
        new_level=[]
        print("Next level:")

        for i in range(0,len(level),2):
            left=level[i]
            if i+1<len(level):
                right=level[i+1]
            else:
                right=left 

            combined=get_hash(left+right)
            print(combined)
            new_level.append(combined)

        level=new_level

    return level[0]


n=int(input("Enter number of data blocks:"))

data=[]
for i in range(n):
    d=input()
    data.append(d)

root=build_tree(data)

print("Merkle Root:")
print(root)