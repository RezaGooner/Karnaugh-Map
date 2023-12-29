file = open("minterms.txt","r");
mt = []

if(file.mode == 'r'):
    line = file.readline();
    mt = line.strip().split(" ")

for i in range(len(mt)) :
    mt[i] = int(mt[i])
    
file = open("dontcares.txt","r");
dc = []

if(file.mode == 'r'):
    line = file.readline();
    if (line.strip() != ""):
        dc = line.strip().split(" ")

if len(dc) != 0 :
    for i in range(len(dc)) :
        if (dc[i].isdigit()):
            dc[i] = int(dc[i])
    
mt.sort()
minterms = mt + dc
minterms.sort()
size = len(bin(minterms[-1])) - 2
groups, all_pi = {}, set()

for minterm in minterms:
    try:
        groups[bin(minterm).count('1')].append(bin(minterm)[2:].zfill(size))
    except KeyError:
        groups[bin(minterm).count('1')] = [bin(minterm)[2:].zfill(size)]

while True:
    tmp = groups.copy()
    groups, m, marked, should_stop = {}, 0, set(), True
    l = sorted(list(tmp.keys()))
    for i in range(len(l) - 1):
        for j in tmp[l[i]]:
            for k in tmp[l[i + 1]]:
                c = 0
                mismatch_index = -1
                for z in range(len(j)):
                    if j[z] != k[z]:
                        mismatch_index = z
                        c += 1
                        if c > 1:
                            break
                if c == 1:
                    try:
                        groups[m].append(j[:mismatch_index] + '-' + j[mismatch_index + 1:]) if j[:mismatch_index] + '-' + j[mismatch_index + 1:] not in groups[m] else None
                    except KeyError:
                        groups[m] = [j[:mismatch_index] + '-' + j[mismatch_index + 1:]]
                    should_stop = False
                    marked.add(j)
                    marked.add(k)
        m += 1
    local_unmarked = set()
    for i in tmp:
        local_unmarked.update(tmp[i])
    local_unmarked = local_unmarked.difference(marked)
    all_pi = all_pi.union(local_unmarked)
    if should_stop:
        break

sz = len(str(mt[-1]))
chart = {}

minterms_Merged = []
for i in all_pi:
    gaps = i.count('-')
    if gaps == 0:
        merged_minterms = [str(int(i, 2))]
    else:
        x = [bin(I)[2:].zfill(gaps) for I in range(pow(2, gaps))]
        merged_minterms = []
        for I in range(pow(2, gaps)):
            temp2, ind = i[:], -1
            for J in x[0]:
                if ind != -1:
                    ind = ind + temp2[ind + 1:].find('-') + 1
                else:
                    ind = temp2[ind + 1:].find('-')
                temp2 = temp2[:ind] + J + temp2[ind + 1:]
            merged_minterms.append(str(int(temp2, 2)))
            x.pop(0)

    minterms_Merged.append(merged_minterms)
    for j in merged_minterms:
        if int(j) not in dc:
            x = mt.index(int(j)) * (sz + 1)
            y = x + sz
            try:
                chart[j].append(i) if i not in chart[j] else None
            except KeyError:
                chart[j] = [i]

for i in minterms_Merged:
    print(i, end=' ')


with open('minterms_merged.txt', 'w') as file:
    for item in minterms_Merged:
        file.write(' '.join(item) + '\n')
