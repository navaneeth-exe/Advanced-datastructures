class Point:
    def __init__(self,x,y):
        self.x=x
        self.y=y
class Box:
    def __init__(self,x,y,w,h):
        self.x=x
        self.y=y
        self.w=w
        self.h=h
    def contains(self,p):
        return(self.x-self.w<=p.x<=self.x+self.w and self.y-self.h<=p.y<=self.y+self.h)
class Quadtree:
    def __init__(self,box,cap):
        self.box=box
        self.cap=cap
        self.points=[]
        self.divided=False
    def split(self):
        x,y,w,h=self.box.x,self.box.y,self.box.w//2,self.box.h//2
        self.ne=Quadtree(Box(x+w,y-h,w,h),self.cap)
        self.nw=Quadtree(Box(x-w,y-h,w,h),self.cap)
        self.se=Quadtree(Box(x+w,y+h,w,h),self.cap)
        self.sw=Quadtree(Box(x-w,y+h,w,h),self.cap)
        self.divided=True
    def insert(self,p):
        if not self.box.contains(p):
            return False
        if len(self.points)<self.cap:
            self.points.append(p)
            return True
        if not self.divided:
            self.split()
        return(self.ne.insert(p)or self.nw.insert(p)or self.se.insert(p)or self.sw.insert(p))
    def show(self):
        for p in self.points:
            print(f"({p.x},{p.y})")
        if self.divided:
            self.ne.show()
            self.nw.show()
            self.se.show()
            self.sw.show()
root=Quadtree(Box(50,50,50,50),2)
n=int(input("Enter number of points:"))
for i in range(n):
    x,y=map(int,input().split())
    root.insert(Point(x,y))
print("Points in Quadtree:")
root.show()