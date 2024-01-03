%upload data
graph_traversal01_tf = load("graph_traversal01_tf.txt");
graph_traversal01_tbb = load("graph_traversal01_tbb.txt");
graph_traversal01_omp = load("graph_traversal01_omp.txt");

%plotting
plot(graph_traversal01_tf(:,1), graph_traversal01_tf(:,2), 'linewidth',3,'-xb',
    graph_traversal01_tbb(:,1), graph_traversal01_tbb(:,2), 'linewidth',3,'-xg',
    graph_traversal01_omp(:,1), graph_traversal01_omp(:,2), 'linewidth',3,'-xr');

xlabel('Graph Size(tasks)','Color','black','FontWeight','bold');
ylabel('Runtime (ms)','Color','black','FontWeight','bold');

title('Graph Traversal','Color','black','FontWeight','bold');
%'north', 'south', 'east', 'west', 'northeast', 'southeast', 'northwest', 'southwest'
legend('Cpp-Taskflow','TBB','OpenMP','Location','northwest');