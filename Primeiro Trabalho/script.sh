
gcc matrix.c -o c_matrix
gfortran matrix.f95 -o fortran_matrix

PATH1=time_files/C/j_externo.csv
PATH2=time_files/C/i_externo.csv
PATH3=time_files/Fortran/j_externo.csv
PATH4=time_files/Fortran/i_externo.csv

for value in 1 2 5 10 21 43 86 173 346 693 1387 2775 5550 11100 22200 44400
do
    echo $(./c_matrix $value 1) >> $PATH1
    echo $(./c_matrix $value 0) >> $PATH2
    echo $(./fortran_matrix $value 1) >> $PATH3
    echo $(./fortran_matrix $value 0) >> $PATH4
done
