file=open("./tc_results/result.txt","r");
lines=file.readlines();

indices = [i for i, x in enumerate(lines) if x == "Ours\n"]
indices2 = [i for i, x in enumerate(lines) if x == "BGL\n"]

ok=True

for j in range(0, len(indices)):
	for i in range(indices[j]+1,indices2[j]):
		splitted1=lines[i].strip().split(' -->')[1].split(" ");
		splitted2=lines[i+indices2[0]-indices[0]].strip().split(' -->')[1].split(" ");
		if(set(splitted1) - set(splitted2) != set() or set(splitted2) - set(splitted1) != set()):
			print("Errore al vertice "+str(i-indices[j]-1))
			ok=False;	

if(ok):
	print("RISULTATO CORRETTO")	
	

