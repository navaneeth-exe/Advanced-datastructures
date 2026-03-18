class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y


class Rectangle:
    def __init__(self, x, y, w, h):
        self.x = x  # center x
        self.y = y  # center y
        self.w = w  # half width
        self.h = h  # half height

    def contains(self, point):
        return (self.x - self.w <= point.x <= self.x + self.w and
                self.y - self.h <= point.y <= self.y + self.h)

    def intersects(self, range_rect):
        return not (range_rect.x - range_rect.w > self.x + self.w or
                    range_rect.x + range_rect.w < self.x - self.w or
                    range_rect.y - range_rect.h > self.y + self.h or
                    range_rect.y + range_rect.h < self.y - self.h)


class QuadTree:
    def __init__(self, boundary, capacity):
        self.boundary = boundary
        self.capacity = capacity
        self.points = []
        self.divided = False

    # ----------- SUBDIVIDE -----------

    def subdivide(self):
        x = self.boundary.x
        y = self.boundary.y
        w = self.boundary.w / 2
        h = self.boundary.h / 2

        self.northeast = QuadTree(Rectangle(x + w, y - h, w, h), self.capacity)
        self.northwest = QuadTree(Rectangle(x - w, y - h, w, h), self.capacity)
        self.southeast = QuadTree(Rectangle(x + w, y + h, w, h), self.capacity)
        self.southwest = QuadTree(Rectangle(x - w, y + h, w, h), self.capacity)

        self.divided = True

    # ----------- INSERT -----------

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

    # ----------- QUERY -----------

    def query(self, range_rect, found=None):
        if found is None:
            found = []

        if not self.boundary.intersects(range_rect):
            return found

        for p in self.points:
            if range_rect.contains(p):
                found.append(p)

        if self.divided:
            self.northeast.query(range_rect, found)
            self.northwest.query(range_rect, found)
            self.southeast.query(range_rect, found)
            self.southwest.query(range_rect, found)

        return found

    # ----------- PRINT -----------

    def print_tree(self, level=0):
        print(" " * level + f"Points: {[ (p.x, p.y) for p in self.points ]}")
        if self.divided:
            self.northeast.print_tree(level + 2)
            self.northwest.print_tree(level + 2)
            self.southeast.print_tree(level + 2)
            self.southwest.print_tree(level + 2)
            
            
            
boundary = Rectangle(0, 0, 10, 10)
qt = QuadTree(boundary, 2)

points = [Point(1, 1), Point(-2, 3), Point(4, -1), Point(3, 3), Point(-4, -2)]

for p in points:
    qt.insert(p)

print("QuadTree structure:")
qt.print_tree()

# Query a region
range_rect = Rectangle(0, 0, 5, 5)
found_points = qt.query(range_rect)

print("\nPoints in range:")
for p in found_points:
    print(p.x, p.y)
