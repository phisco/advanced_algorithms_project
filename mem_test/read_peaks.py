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
            if not l[0].startswith("massif.out.pearce_nr"):
                fw.write(",".join(l[0].split(".")[-1].strip().split("_")))
            else:
                d= l[0][len("massif.out.pearce_nr_"):].split("_")
                fw.write(",".join(["pearce_nr",d[0],d[-1]]))
            fw.write(","+str(mem)+"\n")
            i+=4
