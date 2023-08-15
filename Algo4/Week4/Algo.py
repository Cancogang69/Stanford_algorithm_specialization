def addGraph(graph, revGraph, var, midPos):
    #minusVar contain vertices for revGraph
    minusVar = [-v for v in var]
    var.extend(minusVar)
    pos = [(midPos + v) for v in var]
    graph[pos[0]].append(var[1])
    graph[pos[1]].append(var[0])
    revGraph[pos[2]].append(minusVar[1])
    revGraph[pos[3]].append(minusVar[0])

def readFile(fileName):
    with open(fileName) as inputFile:
        size = int(inputFile.readline())
        graphSize = 2*size+1
        graph = [[] for _ in range(graphSize)]
        revGraph = [[] for _ in range(graphSize)]
        for line in inputFile:
            var = list(map(int, line.split(" ")))
            addGraph(graph, revGraph, var, size)

        return size, graph, revGraph
    
def returnFileName(num):
    return "2sat" + str(num) + ".txt"

size, graph, revGraph = readFile("2sat1.txt")

print("done")
                