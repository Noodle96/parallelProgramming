graph_traversal01_tf = load("graph_traversal01_tf.txt");
graph_traversal01_tbb = load("graph_traversal01_tbb.txt");
graph_traversal01_omp = load("graph_traversal01_omp.txt");
% 10 15 21
% 2  3   4
[filas, columnas] = size(graph_traversal01_tf);
veces_tf_with_omp = 0;
veces_tf_with_tbb = 0;
for i = 1:filas
    elemento_omp = graph_traversal01_omp(i,2);
    elemento_tbb = graph_traversal01_tbb(i,2);
    elemento_tf = graph_traversal01_tf(i,2);
    %disp(elemento);  % Esto mostrará cada elemento de la lista en cada iteración del bucle
    veces_tf_with_omp =  veces_tf_with_omp + (elemento_omp/elemento_tf);
    veces_tf_with_tbb =  veces_tf_with_tbb + (elemento_tbb/elemento_tf); 
end
veces_tf_with_omp = veces_tf_with_omp/filas
veces_tf_with_tbb = veces_tf_with_tbb/filas 
