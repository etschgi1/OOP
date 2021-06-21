def readfile(file):
    with open(file) as f:
        lines = f.readlines()
    f.close()
    return lines

def getformated(lines):
    out = []
    for line in lines:
        row = (line.split())
        # print(row)
        # print(row[1])
        if row[1] != "round":
            continue
        commands = row[4:]
        out.append(row[2]+row[3])
        for c in commands:
            out.append(c.replace("'","").replace("[","").replace(",","").replace("]",""))
    return out

lines = readfile("/mnt/s/VM/OOP-VM/OOP/oopA3/python/log.txt")
formated = (getformated(lines))

f=0
file=open("input","w")

while(f<len(formated)):
    if formated[f] == "insert":
        file.write(formated[f]+" "+formated[f+1]+" "+formated[f+2]+"\n")
        f+=3
    if formated[f] == "go":
        file.write(formated[f]+" "+formated[f+1]+" "+formated[f+2]+"\n")
        f+=3
    if formated[f] == "finish":
        file.write(formated[f]+"\n")
        f+=1
    else:
        f+=1
    # else:
    #     print(formated[f])
    #     f+=1
file.close()