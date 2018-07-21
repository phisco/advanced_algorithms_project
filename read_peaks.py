with open("res.txt", "r") as fr:
    with open("res.csv", "w") as fw:
        lines = []
        for line in fr:
            lines.append(line)
        i=0
        res = []
        while i < len(lines):
            fw.write(",".join(lines[i].split(".")[-1].strip().split("_"))+","+str(int(lines[i+1])+int(lines[i+3]))+"\n")
            i+=4
