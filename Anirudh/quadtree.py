class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y


class Rectangle:
    def __init__(self, x, y, w, h):
        self.x = x
        self.y = y
        self.w = w
        self.h = h

    def contains(self, point):
        return (self.x - self.w <= point.x <= self.x + self.w and
                self.y - self.h <= point.y <= self.y + self.h)


class QuadTree:
    def __init__(self, boundary, capacity):
        self.boundary = boundary
        self.capacity = capacity
        self.points = []
        self.divided = False

    def subdivide(self):
        x, y, w, h = self.boundary.x, self.boundary.y, self.boundary.w, self.boundary.h

        self.ne = QuadTree(Rectangle(x + w/2, y - h/2, w/2, h/2), self.capacity)
        self.nw = QuadTree(Rectangle(x - w/2, y - h/2, w/2, h/2), self.capacity)
        self.se = QuadTree(Rectangle(x + w/2, y + h/2, w/2, h/2), self.capacity)
        self.sw = QuadTree(Rectangle(x - w/2, y + h/2, w/2, h/2), self.capacity)

        self.divided = True

    def insert(self, point):
        if not self.boundary.contains(point):
            return False

        if len(self.points) < self.capacity:
            self.points.append(point)
            return True

        if not self.divided:
            self.subdivide()

        return (self.ne.insert(point) or
                self.nw.insert(point) or
                self.se.insert(point) or
                self.sw.insert(point))

    def print_tree(self, level=0):
        print("  " * level + f"Level {level}: {[ (p.x, p.y) for p in self.points ]}")
        if self.divided:
            self.ne.print_tree(level + 1)
            self.nw.print_tree(level + 1)
            self.se.print_tree(level + 1)
            self.sw.print_tree(level + 1)


# Example usage
boundary = Rectangle(0, 0, 10, 10)
qt = QuadTree(boundary, 2)

points = [Point(1, 1), Point(-2, -3), Point(4, 5),
          Point(-6, 7), Point(8, -1), Point(0, 0)]

for p in points:
    qt.insert(p)

qt.print_tree()
