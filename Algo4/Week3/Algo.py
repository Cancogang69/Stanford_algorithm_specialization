def ReadGraph(inputFile):
    with open(inputFile) as graph:
        nV = int(graph.readline())
        coordList = []
        for v in range(nV):
            coord = list(map(float, graph.readline().split(" ")))
            coord[0] = int(coord[0])
            coordList.append(coord)
    return nV, coordList

def distance(p1, p2): 
    return ((p1[0]-p2[0])**2 + 
            (p1[1]-p2[1])**2) ** (1/2)

def func(nV, coordList):
    tourLenght = 0
    curV = 0
    for i in range(1, nV):
        coordList[curV][0] = -1
        minDis = INF
        for v in coordList:
            if v[0] == -1:
                continue
            dis = distance(coordList[curV][1:3], v[1:3])
            if dis < minDis:
                minDis = dis
                curV = v[0] - 1
        tourLenght += minDis
    return tourLenght

INF = float("inf")
files = ["data_file.txt"]
nV, coordList = ReadGraph(files[0])

print(func(nV, coordList))