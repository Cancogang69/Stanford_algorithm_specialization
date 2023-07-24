def DecToBin(num):
    bin = ""
    while num != 0:
        if num % 2 == 0:
            bin = "0" + bin
        else: 
            bin = "1" + bin
        num = int(num / 2)
    return bin

bin = DecToBin(6)
print(bin)