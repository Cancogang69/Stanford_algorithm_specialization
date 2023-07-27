def DecToBin(num, binSize):
    bin = ["0" for _ in range(binSize)]
    pointer = len(bin) - 1
    while num != 0:
        if num % 2 != 0:
            bin[pointer] = "1"
        pointer -= 1
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

num = 16800000
size = 25
bin = DecToBin(num, size)
print(bin)
print(len(bin))
print(BinToDec("1111"))

