class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y


class Rectangle:
    def __init__(self, x, y, w, h):
        self.x = x  # center x
        self.y = y  # center y
        self.w = w  # width
        self.h = h  # height

    def contains(self, point):
        return (self.x - self.w <= point.x <= self.x + self.w and
                self.y - self.h <= point.y <= self.y + self.h)


class Quadtree:
    def __init__(self, boundary, capacity):
        self.boundary = boundary
        self.capacity = capacity
        self.points = []
        self.divided = False

    def subdivide(self):
        x, y = self.boundary.x, self.boundary.y
        w, h = self.boundary.w // 2, self.boundary.h // 2

        self.northeast = Quadtree(Rectangle(x + w, y - h, w, h), self.capacity)
        self.northwest = Quadtree(Rectangle(x - w, y - h, w, h), self.capacity)
        self.southeast = Quadtree(Rectangle(x + w, y + h, w, h), self.capacity)
        self.southwest = Quadtree(Rectangle(x - w, y + h, w, h), self.capacity)

        self.divided = True

    def insert(self, point):
        if not self.boundary.contains(point):
            return False

        if len(self.points) < self.capacity:
            self.points.append(point)
            return True
        else:
            if not self.divided:
                self.subdivide()

            return (self.northeast.insert(point) or
                    self.northwest.insert(point) or
                    self.southeast.insert(point) or
                    self.southwest.insert(point))

    def display(self):
        for p in self.points:
            print(f"({p.x}, {p.y})")  # left aligned

        if self.divided:
            self.northeast.display()
            self.northwest.display()
            self.southeast.display()
            self.southwest.display()


boundary = Rectangle(50, 50, 50, 50)

qt = Quadtree(boundary, 2)

n = int(input("Enter number of points: "))

for i in range(n):
    x, y = map(int, input(f"Enter point {i+1} (x y): ").split())
    qt.insert(Point(x, y))

print("\nPoints stored in Quadtree (Left-aligned):")
qt.display()