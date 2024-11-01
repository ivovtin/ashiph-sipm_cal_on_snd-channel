#!/bin/bash

###   root -l -b -q 'draw_hist.C("list_t15_u54.dat")'

indirs=()

count=0
while read str
do
        count=$[ count + 1 ]
        indirs+=($str)
        echo "Line contents are : $str "
#done < runs/list_t15_u53.dat
#done < runs/list_t15_u54.dat
#done < runs/list_t15_u55.dat
#done < runs/list_t15_u56.dat
#
#done < runs/list_t25_u54.dat
done < runs/list_t25_u55.dat
#done < runs/list_t25_u56.dat
#done < runs/list_t25_u57.dat
#
#done < runs/list_t45_u55.dat
#done < runs/list_t45_u56.dat
#done < runs/list_t45_u57.dat
#done < runs/list_t45_u58.dat
echo "count: $count "

for (( i = 0; i < $count; i++ ))
do
	root -l -b -q 'draw_hist.C("'${indirs[i]}'")'
done
