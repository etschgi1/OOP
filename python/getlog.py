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
        out.append(row[2] + row[3])
        for c in commands:
            out.append(c.replace("'", "").replace("[", "").replace(",", "").replace("]", ""))
    return out


if __name__ == "__main__":
    # lines = readfile("/mnt/s/VM/OOP-VM/OOP/oopA3/python/log.txt")
    lines = readfile("log.txt")
    formatted = (getformated(lines))

    f = 0
    file = open("input", "w")

    while f < len(formatted):
        if formatted[f] == "insert":
            file.write(formatted[f] + " " + formatted[f + 1] + " " + formatted[f + 2] + "\n")
            f += 3
        if formatted[f] == "go":
            file.write(formatted[f] + " " + formatted[f + 1] + " " + formatted[f + 2] + "\n")
            f += 3
        if formatted[f] == "finish":
            file.write(formatted[f] + "\n")
            f += 1
        else:
            f += 1
        # else:
        #     print(formated[f])
        #     f+=1
    file.close()
