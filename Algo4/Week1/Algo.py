def readGraph(inputFile):
    with open(inputFile, "r") as file:
        nV, nE = map(int, file.readline().split())
        edgeList = []
        for i in range(nE):
            edge = list(map(int, file.readline().split()))
            edgeList.append(edge)
    return edgeList, nV

def BellmanFord(edgeList, nV):
    weightList = [0] * nV
    for i in range(nV):
        endFlag = True
        negativeCircle = False
        for item in edgeList:
            headV, tailV, length = item
            if(weightList[tailV-1] > weightList[headV-1] + length):
                weightList[tailV-1] = weightList[headV-1] + length
                endFlag = False
                negativeCircle = True
        if endFlag:
            break
    return negativeCircle, weightList

def reweight(edgeList, weightList):
    rwEdgeList = []
    for edge in edgeList:
        reweightLength = edge[2] + weightList[edge[0]-1] - weightList[edge[1]-1]
        rwEdgeList.append([edge[0], edge[1], reweightLength])
    return rwEdgeList

def insertHeap(heap, value):
    heap.append(value)
    child = len(heap)-1
    parent = int((child-1)/2)
    while child!=parent:
        if heap[child] > heap[parent]:
            return
        heap[parent], heap[child] = heap[child], heap[parent]
        child = parent
        parent = int((child-1)/2)
        

def popHeap(heap):
    heap[0], heap[len(heap)-1] = heap[len(heap)-1], heap[0]
    heap.pop()
    
    parent = 0
    left = 1
    while left<len(heap):
        right = left+1 if left+1<len(heap) else left
        minPos = left if heap[left]<heap[right] else right
        if heap[parent] < heap[minPos]:
            return
        heap[parent], heap[minPos] = heap[minPos], heap[parent]
        parent = minPos
        left = parent*2+1


def Dijkstra(graph, sourceVertex, edgeList, rwEdgeList):
    nV = len(graph)
    flagList = [False] * nV
    pathLengthList = [[0, 0]] * nV
    heap = [[sourceVertex, sourceVertex, 0], ]

    #min is the minimum path
    #item pathLenghtList have 2 value:
    #first value is the lenth of the minimum path
    #second value is the reweight-length
    min = float('inf')
    temp = nV
    while(temp>0):
        edge = heap[0]
        popHeap(heap)
        if(flagList[edge[1]-1]==True):
            continue
        temp -= 1

    return min

def findShortestShortestPath(graph, edgeList, rwEdgeList):
    nV = len(graph)
    graph = [[] for v in range(nV)]
    for i, item in enumerate(edgeList):
        graph[item[0]-1].append(i)
    min = float('inf')
    for i in range(1, nV+1):
        localMin = Dijkstra(graph, i, edgeList, rwEdgeList)
        if(localMin<min):
            min = localMin
    return min

#Driver code
if __name__ =="__main__":
    inputList = ["g1.txt", "g2.txt", "g3.txt"]
    for inputFile in inputList:
        edgeList, nV = readGraph(inputFile)
        
        #find if graph has a negative circle
        negativeCircle, weightList = BellmanFord(edgeList, nV)
        if(negativeCircle==True):
            print("NULL")
            continue

        rwEdgeList = reweight(edgeList, weightList)

        #find shortest shortest path in graph
        min = findShortestShortestPath(edgeList, rwEdgeList)
        print(min)