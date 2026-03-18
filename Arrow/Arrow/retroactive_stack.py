class RetroactiveStack:
    def __init__(self):
        self.operations = []  # (time, operation, value)

    # ----------- ADD OPERATIONS -----------

    def push(self, time, value):
        self.operations.append((time, "push", value))

    def pop(self, time):
        self.operations.append((time, "pop", None))

    # ----------- REMOVE OPERATION -----------

    def delete(self, time):
        self.operations = [op for op in self.operations if op[0] != time]

    # ----------- BUILD STACK STATE -----------

    def get_stack(self):
        stack = []

        # Sort by time
        ops = sorted(self.operations, key=lambda x: x[0])

        for time, op, value in ops:
            if op == "push":
                stack.append(value)
            elif op == "pop":
                if stack:
                    stack.pop()

        return stack

    # ----------- PRINT -----------

    def print_stack(self):
        print("Current stack:", self.get_stack())
        
        
        
rs = RetroactiveStack()

rs.push(1, 10)
rs.push(2, 20)
rs.pop(3)

print("Before retroactive change:")
rs.print_stack()

# Insert operation in the past
rs.push(2.5, 15)

print("After retroactive push at time 2.5:")
rs.print_stack()
