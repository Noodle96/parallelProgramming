%upload data
wavefront02_tf = load("wavefront02_tf.txt");
wavefront02_tbb = load("wavefront02_tbb.txt");

%plotting
plot(wavefront02_tf(:,1), wavefront02_tf(:,2), 'linewidth',3,'-sb','MarkerSize',8,
    wavefront02_tbb(:,1), wavefront02_tbb(:,2), 'linewidth',3,'-sr','MarkerSize',8);

xlabel('Number of CPUs','Color','black','FontWeight','bold');
ylabel('Runtime (ms)','Color','black','FontWeight','bold');

title('Wavefront(0.2M tasks)','Color','black','FontWeight','bold');
%'north', 'south', 'east', 'west', 'northeast', 'southeast', 'northwest', 'southwest'
legend('Cpp-Taskflow','TBB','Location','northwest');