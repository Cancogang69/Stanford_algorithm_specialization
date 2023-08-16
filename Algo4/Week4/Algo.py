from collections import deque

def returnPos(value, graphSize):
    return int(graphSize/2) + value

def addGraph(graph, var):
    pos = [returnPos(v, len(graph)) for v in var]
    graph[pos[0]].append(var[1])
    graph[pos[1]].append(var[0])

def readFile(fileName):
    with open(fileName) as inputFile:
        size = int(inputFile.readline())
        graphSize = 2*size+1
        graph = [[] for _ in range(graphSize)]
        revGraph = [[] for _ in range(graphSize)]
        for line in inputFile:
            var = list(map(int, line.split(" ")))
            minusVar = [-v for v in var]
            addGraph(graph, var)
            addGraph(revGraph, minusVar)

        return size, graph, revGraph
    
def returnFileName(num):
    return "2sat" + str(num) + ".txt"


def DFS(graph, v, isExplored, isCaptured, fArray, leaderArray):
    stack = deque()
    stack.append(v)
    while(stack.count()!=0):
        top = stack.pop()
    

size, graph, revGraph = readFile("2sat1.txt")


                