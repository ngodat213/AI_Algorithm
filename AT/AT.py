from queue import Queue

def read_graph(filename):
    with open(filename, 'r') as file:
        size, start, end = map(int, file.readline().split())
        graph = [list(map(int, file.readline().split())) for _ in range(size)]
    return graph, start, end

def at_algorithm(graph, start, end):
    visited = [False] * len(graph)
    prev = Queue()
    prev.put((start, [start]))
    visited[start] = True

    while not prev.empty():
        s, path = prev.get()
        
        # Check goal
        if s == end:
            print("Path:", path)
            return

        # Print succs
        print(f"{s} -> succs={{", end="")
        for node in range(len(graph)):
            if visited[node]:
                print(node, end="-")
        print("}")

        for i in range(len(graph)):
            if graph[s][i] and not visited[i]:
                visited[i] = True
                new_prev = path.copy()
                new_prev.append(i)
                prev.put((i, new_prev))

    print("FAIL")

filename = "D:\workspace\cpp\AI_Algorithm\AT\input.txt"
graph, start, end = read_graph(filename)
at_algorithm(graph, start, end)
