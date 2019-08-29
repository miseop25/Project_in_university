n1 = linspace(0, 15, 16)
x1 = cos(2*pi*0.1*n1)

n2 = linspace(-5, 5, 11)
x2= cos(2*pi*0.05*n2)

n3 = linspace(0, 10, 11)
x3= (-1).^n3


[x_min, n_mid] = convo(x1,x2,n1,n2);
[y_1, n_1] = convo(x_min,x3,n_mid,n3);

[x_mid2, n_mid2] = convo(x2,x3,n2,n3);
[y_2, n_2] = convo(x1,x_mid2,n1,n_mid2);


figure(1)
subplot(4,1,1);
stem(n1,x1,'k','MarkerFaceColor','k')
title('First Signals(x1[n])');

subplot(4,1,2);
stem(n2,x2,'k','MarkerFaceColor','k')
title('Second Signals(x2[n])');

subplot(4,1,3);
stem(n3,x3,'k','MarkerFaceColor','k')
title('Third Signals(x3[n])');

subplot(4,1,4);
stem(n_1,y_1,'k','MarkerFaceColor','k')
hold on;
stem(n_2,y_2,'rx','MarkerFaceColor','k')
legend('(x1[n]*x2[n])*x3[n]', 'x1[n]*(x2[n]*x3[n])')
ylabel('Y[n]'); 
xlabel('n');
title('Convolution of Two Signals(x1[n]*x2[n])');
grid 

