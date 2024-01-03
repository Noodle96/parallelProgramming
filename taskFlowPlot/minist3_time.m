minist3_tf = load("minist3_tf.txt");
minist3_tbb = load("minist3_tbb.txt");
minist3_omp = load("minist3_omp.txt");
% 10 15 21
% 2  3   4
[filas, columnas] = size(minist3_tf);
veces_tf_with_omp = 0;
veces_tf_with_tbb = 0;
for i = 1:filas
    elemento_omp = minist3_omp(i,2);
    elemento_tbb = minist3_tbb(i,2);
    elemento_tf = minist3_tf(i,2);
    %disp(elemento);  % Esto mostrará cada elemento de la lista en cada iteración del bucle
    veces_tf_with_omp =  veces_tf_with_omp + (elemento_omp/elemento_tf);
    veces_tf_with_tbb =  veces_tf_with_tbb + (elemento_tbb/elemento_tf); 
end
veces_tf_with_omp = veces_tf_with_omp/filas
veces_tf_with_tbb = veces_tf_with_tbb/filas 
