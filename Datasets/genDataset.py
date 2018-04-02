import pandas as pd
import os
import sys
import numpy as np

if __name__ == '__main__':
    count = 1
    file = open(sys.argv[1], 'r')
    list_index = []
    with open(sys.argv[1], 'r') as f:
        for line in f:
            a = line.split(' ')
            list_index.append(int(a[0].strip()))
    mat = pd.DataFrame(0, index=list_index, columns=list_index)
    with open(sys.argv[1], 'r') as f:
        for line in f:
            a = line.split(' ')
            row_index = int(a[0].strip())
            # print "\nnext row =", count
            # count = count + 1
            for i in range(1, len(a)):
                mat[row_index][int(a[i].strip())] = 1
    print len(list_index)
    for i in list_index:
        for j in list_index:
            print mat[i][j], "  ",
        print ""
