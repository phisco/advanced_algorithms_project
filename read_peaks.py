with open("res.txt", "r") as fr:
    with open("res.csv", "w") as fw:
        fw.write("algo,v,e,mem\n")
        lines = []
        for line in fr:
            lines.append(line)
        i=0
        res = []
        while i < len(lines):
            l = [d.strip() for d in lines[i:i+4]]
            heap = [x for x in l if x.startswith("mem_heap_B")][0].split("=")[-1]
            stack = [x for x in l if x.startswith("mem_stacks_B")][0].split("=")[-1]
            mem = int(heap)+int(stack)
            print(l, " = ", mem)

            fw.write(",".join(lines[i].split(".")[-1].strip().split("_"))+","+str(mem)+"\n")
            i+=4
