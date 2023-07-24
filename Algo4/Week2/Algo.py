def readGraph(inputFile):
    graph = open(inputFile, "r")
    nV = int(graph.readline())
    coordinateList = []
    for i in range(nV):
        coordinate = list(map(float, graph.readline().split()))
        coordinateList.append(coordinate)
    graph.close()
    return nV, coordinateList

def DecToBin(num):
    bin = ""
    while num != 0:
        if num % 2 == 0:
            bin = "0" + bin
        else: 
            bin = "1" + bin
        num = int(num / 2)
    return bin

input = "data_file.txt"
nV, coordinateList = readGraph(input)

table = [[]]

# for size in range (2, nV):
#     for S in range (1, pow(2, nV-1), 2):
        

