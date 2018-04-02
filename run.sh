rm out 2> /dev/null
gcc -std=c11 pagerank.c arnoldi.c filereader.c matrix.c svd.c -o out -lm
./out > temp
python Datasets/dataset.py small_temp.txt ranking_small.txt

