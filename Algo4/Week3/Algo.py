def ReadGraph(inputFile):
    with open(inputFile) as graph:
        nV = int(graph.readline())
        coordList = []
        for v in range(nV):
            coord = tuple(map(float, graph.readline().split(" ")))
            coordList.append(coord)
    return nV, coordList

files = ["data_file.txt"]
nV, coordList = ReadGraph(files[0])

    