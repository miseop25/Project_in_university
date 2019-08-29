n1 = linspace(-5, 5, 11)
x1= cos(2*pi*0.05*n1)

x2 = [1,2,3,4,5,6];
n2 = linspace(0, 5, length(x2))


[y, n] = convo(x1,x2,n1,n2);
[y_gyo, n_gyo] =  convo(x2,x1,n2,n1);

figure(1)
subplot(3,1,1);
stem(n1,x1,'k','MarkerFaceColor','k')
title('First Signals(x1[n])');
subplot(3,1,2);
stem(n2,x2,'k','MarkerFaceColor','k')
title('Second Signals(x2[n])');

subplot(3,1,3);
stem(n,y,'k','MarkerFaceColor','k')
hold on;
stem(n_gyo,y_gyo,'rx','MarkerFaceColor','k')
legend('x1[n]*x2[n]', 'x2[n]*x1[n]')
ylabel('Y[n]'); 
xlabel('n');
title('Convolution of Two Signals(x1[n]*x2[n])');
grid 

