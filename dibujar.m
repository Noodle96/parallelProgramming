x =[128,512,1024,2048,4096];
container01 = [0.000186, 0.000845, 0.002319, 0.010055, 0.039818  ]; 
container02 = [0.000176, 0.001364,0.006728, 0.056099, 0.247433  ];
plot( x, container01, "linewidth",5); 
hold on; 
plot( x, container02,"linewidth",5 ); 
hold off;
grid on;
title( 'tiempo de ejecución' );
xlabel ("x-axis tamaño array (n)");
ylabel ("y-axis tiempo (s)");
xlim ([0, 4200]);
set( gca, 'fontsize', 16 );
legend( 'container01', 'container02', "location", "northwest" );

