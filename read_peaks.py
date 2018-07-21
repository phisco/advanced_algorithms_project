with open("res.txt", "r") as fr:
    with open("res.csv", "w") as fw:
        lines = []
        for line in fr:
            lines.append(line)
        i=0
        res = []
        while i < len(lines):
            l = lines[i:i+4]
            l = [d.strip() for d in l]
            print(l)
            heap = [x for x in l if x.startswith("mem_heap_B")][0].split("=")[-1]
            stack = [x for x in l if x.startswith("mem_stacks_B")][0].split("=")[-1]

            fw.write(",".join(lines[i].split(".")[-1].strip().split("_"))+","+str(int(heap)+int(stack))+"\n")
            i+=4
