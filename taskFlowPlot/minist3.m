%upload data
minist_tf = load("minist3_tf.txt");
minist_tbb = load("minist3_tbb.txt");
minist_omp = load("minist3_omp.txt");

%plotting
plot(minist_tf(:,1), minist_tf(:,2), 'linewidth',3,'-xb',
    minist_tbb(:,1), minist_tbb(:,2), 'linewidth',3,'-xg',
    minist_omp(:,1), minist_omp(:,2), 'linewidth',3,'-xr');

xlabel('Number of Epochs','Color','black','FontWeight','bold');
ylabel('Runtime (s)','Color','black','FontWeight','bold');

title('3-layer DNN (16 CPUs)','Color','black','FontWeight','bold');
%'north', 'south', 'east', 'west', 'northeast', 'southeast', 'northwest', 'southwest'
legend('Cpp-Taskflow','TBB','OpenMP','Location','northwest');