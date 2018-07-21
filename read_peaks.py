with open("res.txt", "r") as fr:
    with open("res.csv", "a") as fw:
        lines = []
        for line in fr:
            lines.append(line)
        i=0
        res = []
        while i < len(lines):
            fw.write(str(int(lines[i])+int(lines[i+2]))+"\n")
            i+=3
