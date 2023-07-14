def readGraph(inputFile):
    graph = open(inputFile, "r")
    nV = int(graph.readline())
    coordinateList = ()
    for i in range(nV):
        coordinate = list(map(int, graph.readline().split()))
        coordinateList.append(coordinate)
    graph.close()
    return nV, coordinateList

input = "data_file.txt"
nV, coordinateList = readGraph(input)
print(coordinateList)