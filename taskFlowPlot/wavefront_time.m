wavefront01_tf = load("wavefront01_tf.txt");
wavefront01_tbb = load("wavefront01_tbb.txt");
wavefront01_omp = load("wavefront01_omp.txt");
% 10 15 21
% 2  3   4
[filas, columnas] = size(wavefront01_tf);
veces_tf_with_omp = 0;
veces_tf_with_tbb = 0;
for i = 1:filas
    elemento_omp = wavefront01_omp(i,2);
    elemento_tbb = wavefront01_tbb(i,2);
    elemento_tf = wavefront01_tf(i,2);
    %disp(elemento);  % Esto mostrará cada elemento de la lista en cada iteración del bucle
    veces_tf_with_omp =  veces_tf_with_omp + (elemento_omp/elemento_tf);
    veces_tf_with_tbb =  veces_tf_with_tbb + (elemento_tbb/elemento_tf); 
end
veces_tf_with_omp = veces_tf_with_omp/filas
veces_tf_with_tbb = veces_tf_with_tbb/filas 
