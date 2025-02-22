def BFS(start: str, adjacency_list: dict) -> list:
    print(f"Added {start} to queue")
    queue: list = [start]
    visited: list = []
    while queue:
        if queue[0] not in visited:
            visited.append(queue[0])
            print(f"Visited {queue[0]}")
        for neighbour in adjacency_list[queue[0]]:
            if neighbour not in visited and neighbour not in queue:
                queue.append(neighbour)
                print(f"Added {neighbour} to queue")
        print(f"Deleted {queue.pop(0)} from queue")
    return visited


def DFS(start: str, adjacency_list: dict) -> list:
    stack: list = [start]
    print(f"Added {start} to stack")
    visited: list = []
    while stack:
        vertex = stack.pop()
        print(f"Deleted {vertex} from stack")
        if vertex not in visited:
            visited.append(vertex)
            print(f"Visited {vertex}")
            for neighbour in adjacency_list[vertex][::-1]:
                if neighbour not in visited:
                    stack.append(neighbour)
                    print(f"Added {neighbour} to stack")
    return visited


if __name__ == '__main__':
    print("*" * 20 + "-BFS-" + "*" * 20)
    print(BFS("1", {"1": ["2", "3"],
                    "2": ["1", "3", "5"],
                    "3": ["1", "2", "4", "5"],
                    "4": ["3"],
                    "5": ["2", "3"]}))
    print("\n" + "*" * 20 + "-DFS-" + "*" * 20)
    print(DFS("1", {"1": ["2", "5"],
                    "2": ["1", "3"],
                    "3": ["2", "4", "5"],
                    "4": ["3", "8"],
                    "5": ["1", "3", "6", "8"],
                    "6": ["5", "7"],
                    "7": ["6"],
                    "8": ["4", "5", "9"],
                    "9": ["8"]}))

