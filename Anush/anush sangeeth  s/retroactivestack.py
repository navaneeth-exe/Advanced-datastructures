class RetroactiveStack:
    def __init__(self):
        self.operations = []

    def push(self, time, value):
        self.operations.append((time, "push", value))
        self.operations.sort()

    def pop(self, time):
        self.operations.append((time, "pop", None))
        self.operations.sort()

    def get_stack(self, time):
        stack = []

        for t, op, val in sorted(self.operations):
            if t > time:
                break
            if op == "push":
                stack.append(val)
            elif op == "pop" and stack:
                stack.pop()

        return stack

    def top(self, time):
        stack = self.get_stack(time)
        return stack[-1] if stack else None


if __name__ == "__main__":
    rs = RetroactiveStack()

    rs.push(1, 10)
    rs.push(2, 20)
    rs.pop(3)
    rs.push(4, 30)

    print(rs.get_stack(4))
    print(rs.top(4))
