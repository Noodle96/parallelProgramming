%upload data
wavefront01_tf = load("wavefront01_tf.txt");
wavefront01_tbb = load("wavefront01_tbb.txt");
wavefront01_omp = load("wavefront01_omp.txt");

%plotting
plot(wavefront01_tf(:,1), wavefront01_tf(:,2), 'linewidth',3,'-xb',
    wavefront01_tbb(:,1), wavefront01_tbb(:,2), 'linewidth',3,'-xg',
    wavefront01_omp(:,1), wavefront01_omp(:,2), 'linewidth',3,'-xr');

xlabel('Block Count(tasks)','Color','black','FontWeight','bold');
ylabel('Runtime (ms)','Color','black','FontWeight','bold');

title('Wavefront','Color','black','FontWeight','bold');
%'north', 'south', 'east', 'west', 'northeast', 'southeast', 'northwest', 'southwest'
legend('Cpp-Taskflow','TBB','OpenMP','Location','northwest');