def readGraph(inputFile):
    graph = open(inputFile, "r")
    nV = int(graph.readline())
    coordList = []
    for i in range(nV):
        coordinate = list(map(float, graph.readline().split()))
        coordList.append(coordinate)
    graph.close()
    return nV, coordList

def DecToBin(num):
    bin = []
    while num != 0:
        if num % 2 == 0:
            bin.append('0')
        else: 
            bin.append('1')
        num = int(num / 2)
    return bin

def BinToDec(bin):
    num = 0
    expTwo = 1
    for i in range (len(bin)-1, -1, -1):
        if bin[i] == "1":
            num += expTwo
        expTwo *= 2
    return num

def SubSize(sub):
    size = 0
    for vertex in sub:
        if vertex == "1":
            size +=1
    return size

def distance(v1, v2):
    coord1 = coordList[v1]
    coord2 = coordList[v2]
    return ((coord1[0]-coord2[0])**2 +
            (coord1[1]-coord2[1])**2)**(1/2)

def func(table, S, sub, des):
    sub[des]="0"
    newS = BinToDec(sub)
    min = INF
    for x in table[newS]:   
        if x[1] == des:
            continue
        newDis = x[0] + distance(x[1], des)
        if newDis<min:
            min = newDis
    return (min, des)
            

#Driver code
INF = float("inf")

input = "data_file.txt"
nV, coordList = readGraph(input)



# table[S] : a list of dict {distance, end_vertex}

table = [[] for _ in range (1, 2**(nV-1))]
table[1].append((0,1))

# size mean size of subset
# S is subset which is displayed with a integer number
# then S is tranfered into integer number
# S start from 3 because the subset size start from 2

for size in range (2, nV):
    for S in range (3, pow(2, nV-1), 2):
        sub = DecToBin(S)
        if SubSize(sub) != size:
            continue
        for i in range(0, len(sub)-1):
            if sub[i] == "0":
                continue
            table[S].append(func(table, S, sub, i))

