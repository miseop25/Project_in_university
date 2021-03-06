n1 = linspace(0, 15, 16)
x1 = cos(2*pi*0.1*n1)

x2=[zeros(1,5),1,zeros(1,5)];


n2 = linspace(-5, 5, length(x2))

[y, n] = convo(x1,x2,n1,n2);

figure(1)
subplot(3,1,1);
stem(n1,x1,'k','MarkerFaceColor','k')
title('First Signals(x1[n])');
subplot(3,1,2);
stem(n2,x2,'k','MarkerFaceColor','k')
title('Second Signals(x2[n])');
subplot(3,1,3);
stem(n,y,'k','MarkerFaceColor','k')

ylabel('Y[n]'); 
xlabel('n');
title('Convolution of Two Signals(x1[n]*x2[n])');
grid 

