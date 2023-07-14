import math
infinite = math.inf

def readGraph(edgeList, inputFile):
    graph = open(inputFile, "r")
    nV, nE = map(int, graph.readline().split())
    for i in range(nE):
        edge = list(map(int, graph.readline().split()))
        edgeList.append([edge[0], edge[1], edge[2]])
    graph.close()
    return nV

def BellmanFord(edgeList, nV):
    verticesWeightList = [0] * nV
    for i in range(nV):
        endFlag = True
        negativeFlag = False
        for item in edgeList:
            headV, tailV, length = item
            if(verticesWeightList[tailV-1] > verticesWeightList[headV-1] + length):
                verticesWeightList[tailV-1] = verticesWeightList[headV-1] + length
                endFlag = False
                negativeFlag = True
        if(endFlag==True):
            break
    return negativeFlag, verticesWeightList

def reweight(edgeList, verticesWeightList):
    newEdgeList = []
    for edge in edgeList:
        newEdge = edge
        reweightLength = edge[2] + verticesWeightList[edge[0]-1] - verticesWeightList[edge[1]-1]
        newEdge.append(reweightLength)
        newEdgeList.append(newEdge)
    return newEdgeList

def swap(list, pos1, pos2):
    list[pos1], list[pos2] = list[pos2], list[pos1]
    return list   

def insertHeap(heap, value):
    heap.append(value)
    while True:
        child = int(len(heap)-1)
        parent = int((child-1)/2)
        if(heap[child][3]<heap[parent][3] or 
           (heap[child][3]==heap[parent][3] and heap[child][2]<heap[parent][2])):
            swap(heap, child, parent)
        else:
            break

def deleteLastHeap(heap):
    heap = swap(heap, 0, len(heap)-1)
    heap.pop()
    
    parent = 0
    while True:
        lChild = parent*2+1
        if(lChild>=len(heap)):
            break

        rChild = parent*2+2
        if(rChild>=len(heap)):
            rChild=-1
        min = parent
        if(heap[lChild][3]<heap[parent][3] or 
           (heap[lChild][3]==heap[parent][3] and heap[lChild][2]<heap[parent][3])):
            min = lChild
        elif(rChild != -1 and (heap[rChild][3]<heap[parent][3] or
                               (heap[rChild][3]==heap[parent][3] and heap[rChild][2]<heap[parent][3]))):
            min = rChild
        else:
            break

        swap(heap, parent, min)
        parent = min


def Dijkstra(vertexList, sourceVertex, nV):
    flagList = [False] * nV
    pathList = [[0] for x in range(nV)]
    heap = []
    for item in vertexList[sourceVertex-1]:
        insertHeap(heap, item)
    if(len(heap)==0):
        return infinite
    nV-=1
    flagList[sourceVertex-1] = True
    pathList[sourceVertex-1] = ([sourceVertex, 0, 0])

    #minPath is the minimum path
    #first value is the lenth of the minimum path
    #second value is the reweight-length
    minPath = infinite
    while(nV>0):
        edge = heap[0]
        while flagList[edge[1]-1]!=False:
            deleteLastHeap(heap)
            if(len(heap) == 0):
                return minPath
            edge = heap[0]

        headE = edge[0]
        tailE = edge[1]
        flagList[tailE-1] = True
        pathLength = pathList[headE-1][1] + edge[2]
        reweightPathLength = pathList[headE-1][2] + edge[3]
        pathList[tailE-1] = [headE, pathLength, reweightPathLength]
        nV-=1
        if(minPath>pathLength):
            minPath= pathLength
        for item in vertexList[tailE-1]:
            insertHeap(heap, item)
    return minPath

def findShortestShortestPath(edgeList, nV):
    vertexList = [[] for x in range(nV)]
    for item in edgeList:
        vertexList[item[0]-1].append(item)
    min = math.inf
    for i in range(1, nV+1):
        localMin = Dijkstra(vertexList, i, nV)
        if(localMin<min):
            min = localMin

    return min

def Algo(inputFile):
    edgeList = []
    input = inputFile
    nV = readGraph(edgeList, input)
    #reweight
    negativeCircle, verticesWeightList = BellmanFord(edgeList, nV)

    if(negativeCircle==True):
        print("NULL")
        return

    edgeList = reweight(edgeList, verticesWeightList)
    #find shortest shortest path in graph
    shortestPath = findShortestShortestPath(edgeList, nV)

    print(shortestPath)

#Driver code
inputList = ("test.txt", )
for inputFile in inputList:
    Algo(inputFile)




