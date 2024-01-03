%upload data
graph_traversal02_tf = load("graph_traversal02_tf.txt");
graph_traversal02_tbb = load("graph_traversal02_tbb.txt");
% 10 15 21
% 2  3   4
[filas, columnas] = size(graph_traversal02_tf);
veces_tf_with_tbb = 0;
for i = 1:filas
    elemento_tbb = graph_traversal02_tbb(i,2);
    elemento_tf = graph_traversal02_tf(i,2);
    %disp(elemento);  % Esto mostrará cada elemento de la lista en cada iteración del bucle
    veces_tf_with_tbb =  veces_tf_with_tbb + (elemento_tbb/elemento_tf); 
end
veces_tf_with_tbb = veces_tf_with_tbb/filas 
