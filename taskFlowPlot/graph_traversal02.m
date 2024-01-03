%upload data
graph_traversal02_tf = load("graph_traversal02_tf.txt");
graph_traversal02_tbb = load("graph_traversal02_tbb.txt");

%plotting
plot(graph_traversal02_tf(:,1), graph_traversal02_tf(:,2), 'linewidth',3,'-sb','MarkerSize',8,
    graph_traversal02_tbb(:,1), graph_traversal02_tbb(:,2), 'linewidth',3,'-sr','MarkerSize',8);

xlabel('Number of CPUs','Color','black','FontWeight','bold');
ylabel('Runtime (ms)','Color','black','FontWeight','bold');

title('Graph Traversal(0.7M tasks)','Color','black','FontWeight','bold');
%'north', 'south', 'east', 'west', 'northeast', 'southeast', 'northwest', 'southwest'
legend('Cpp-Taskflow','TBB','Location','northwest');