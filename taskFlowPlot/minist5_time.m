minist5_tf = load("minist5_tf.txt");
minist5_tbb = load("minist5_tbb.txt");
minist5_omp = load("minist5_omp.txt");
% 10 15 21
% 2  3   4
[filas, columnas] = size(minist5_tf);
veces_tf_with_omp = 0;
veces_tf_with_tbb = 0;
for i = 1:filas
    elemento_omp = minist5_omp(i,2);
    elemento_tbb = minist5_tbb(i,2);
    elemento_tf = minist5_tf(i,2);
    %disp(elemento);  % Esto mostrará cada elemento de la lista en cada iteración del bucle
    veces_tf_with_omp =  veces_tf_with_omp + (elemento_omp/elemento_tf);
    veces_tf_with_tbb =  veces_tf_with_tbb + (elemento_tbb/elemento_tf); 
end
veces_tf_with_omp = veces_tf_with_omp/filas
veces_tf_with_tbb = veces_tf_with_tbb/filas 
