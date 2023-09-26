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
    for i, edge in enumerate(edgeList):
        reweightLength = edge[2] + weightList[edge[0]-1] - weightList[edge[1]-1]
        edgeList[i].append(reweightLength)
    #return rwEdgeList

def insertHeap(heap, value):
    heap.append(value)
    child = len(heap)-1
    parent = int((child-1)/2)
    while child!=parent:
        if heap[child][3] > heap[parent][3]:
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
        minPos = left if heap[left][3]<heap[right][3] else right
        if heap[parent][3] < heap[minPos][3]:
            return
        heap[parent], heap[minPos] = heap[minPos], heap[parent]
        parent = minPos
        left = parent*2+1


def Dijkstra(graph, sourceVertex, edgeList):
    nV = len(graph)
    flagList = [False] * nV
    heap = [[sourceVertex, sourceVertex, 0, 0], ]
    pathLengthList = [[0, 0]] * nV
    pathLengthList[sourceVertex-1] = [0, 0]
    min = float('inf')
    while(nV>0):
        edge = heap[0]
        popHeap(heap)
        head = edge[1]-1
        if flagList[head]:
            continue

        nV -= 1
        flagList[head]=True
        pathLengthList[head] = [edge[2], edge[3]]
        if min>edge[2] and edge[0]!=edge[1]:
            min = edge[2]
        for index in graph[head]:
            realLenght = edgeList[index][2] + pathLengthList[head][0]
            reweightLenght = edgeList[index][3] + pathLengthList[head][1]
            insertHeap(heap, [head+1, edgeList[index][1], realLenght, reweightLenght])
    return min

def findShortestShortestPath(edgeList, nV):
    graph = [[] for v in range(nV)]
    for i, item in enumerate(edgeList):
        graph[item[0]-1].append(i)
    min = float('inf')
    for i in range(1, nV+1):
        localMin = Dijkstra(graph, i, edgeList)
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

        #add reweighting lenght to edgeList
        reweight(edgeList, weightList)

        #find shortest shortest path in graph
        min = findShortestShortestPath(edgeList, nV)
        print(min)