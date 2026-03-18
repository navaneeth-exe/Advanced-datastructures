class RetroactiveStack:
    def __init__(self):
        self.operations = []  # (time, op, value)

    def add_operation(self, time, op, value=None):
        self.operations.append((time, op, value))
        self.operations.sort()  # keep timeline sorted

    def get_stack(self):
        stack = []
        for _, op, value in self.operations:
            if op == "push":
                stack.append(value)
            elif op == "pop" and stack:
                stack.pop()
        return stack


# Example
if __name__ == "__main__":
    rs = RetroactiveStack()

    rs.add_operation(1, "push", 10)
    rs.add_operation(2, "push", 20)
    rs.add_operation(3, "pop")

    print(rs.get_stack())  # [10]

    # Retroactively insert
    rs.add_operation(2.5, "push", 15)

    print(rs.get_stack())  # [10, 15]
