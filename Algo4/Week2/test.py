def DecToBin(num):
    bin = ""
    while num != 0:
        if num % 2 == 0:
            bin = "0" + bin
        else: 
            bin = "1" + bin
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


print(DecToBin(19))
print(BinToDec("10011"))

