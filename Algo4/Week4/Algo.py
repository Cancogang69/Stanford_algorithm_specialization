from collections import deque

def returnPos(value, graphSize):
    return int(graphSize/2) + value

def addGraph(graph, var):
    pos = [returnPos(-v, len(graph)) for v in var]
    minusPos = [returnPos(v, len(graph)) for v in var]
    graph[pos[0]].append(minusPos[1])
    graph[pos[1]].append(minusPos[0])

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

        return graphSize, graph, revGraph
    
def returnFileName(num):
    return "2sat" + str(num) + ".txt"


def DFS(graph, v, isTouched, fArray, leaderArray):
    stack = deque()
    stack.append(v)
    while(len(stack)!=0):
        top = stack.pop()
        if isTouched[top] == 2:
            continue
        if isTouched[top] == 1:
            isTouched[top] = 2
            if leaderArray:
                leaderArray[top] = v
            if fArray:
                fArray.append(top)
            continue
        
        stack.append(top)
        isTouched[top] = 1
        for var in graph[top]:
            if isTouched[var] == 0:
                stack.append(var)

def computeSCC(graph, revGraph, graphSize):
    isTouched = [0 for _ in range(graphSize)]
    fArray = [graphSize, ]
    for i in range(graphSize-1, -1, -1):
        if i == int(graphSize/2):
            continue
        if not isTouched[i]:
            DFS(revGraph, i, isTouched, fArray, None)
    del isTouched
    isTouched = [0 for _ in range(graphSize)]
    leaderArray = [-1 for _ in range(graphSize)]
    for i in range(graphSize-1, -1, -1):
        var = fArray[i]
        if var == graphSize:
            continue
        if not isTouched[var]:
            DFS(graph, var, isTouched, None, leaderArray)
    return leaderArray

#Driver code
for i in range(1, 7):
    inputFile = returnFileName(i)
    graphSize, graph, revGraph = readFile(inputFile)
    leaderArray = computeSCC(graph, revGraph, graphSize)
    flag = True
    for i in range(1, int(graphSize/2)+1):
        posVar = returnPos(i, graphSize)
        posMinusVar = returnPos(-i, graphSize)
        if(leaderArray[posVar]==leaderArray[posMinusVar]):
            flag = False
            print("0")
            break
    if flag:
        print("1")

                