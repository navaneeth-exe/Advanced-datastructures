import bisect

class RetroactiveStack:
    """
    A simple partially retroactive stack implementation.
    It simulates retroactivity by maintaining a timeline of operations
    and answering queries for any specific point in time history.
    """
    def __init__(self):
        # Timeline stores tuples: (timestamp, operation_type, value)
        self.operations = []
        
    def add_push(self, time, val):
        """Insert a push operation retroactively at the given time"""
        bisect.insort(self.operations, (time, 'push', val))
        
    def add_pop(self, time):
        """Insert a pop operation retroactively at the given time"""
        bisect.insort(self.operations, (time, 'pop', None))
        
    def query(self, current_time):
        """Reconstruct and return the stack's state exactly at `current_time`"""
        stack = []
        for t, op, val in self.operations:
            if t > current_time:
                break
            if op == 'push':
                stack.append(val)
            elif op == 'pop' and stack:
                stack.pop()
        return stack

if __name__ == "__main__":
    rs = RetroactiveStack()
    
    # Timeline of operations:
    rs.add_push(1, 'A')
    rs.add_push(3, 'C')
    rs.add_pop(4)
    rs.add_push(5, 'D')
    
    # Output stack history
    print("Stack at t=2:", rs.query(2))  # Expected: ['A']
    print("Stack at t=3:", rs.query(3))  # Expected: ['A', 'C']
    print("Stack at t=4:", rs.query(4))  # Expected: ['A']
    
    # Retroactively add a push at t=2
    print("\nAdding push('B') retroactively at t=2")
    rs.add_push(2, 'B')
    
    # Changes ripple naturally:
    print("New Stack at t=3:", rs.query(3))  # Expected: ['A', 'B', 'C']
    print("New Stack at t=4:", rs.query(4))  # Expected: ['A', 'B'] (Since C is popped instead of B or just normally popped due to order)
    print("New Stack at t=5:", rs.query(5))  # Expected: ['A', 'B', 'D']
