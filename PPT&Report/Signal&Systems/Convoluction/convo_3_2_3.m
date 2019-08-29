n1 = linspace(0, 15, 16);
x1 = cos(2*pi*0.1*n1);
n2 = linspace(0, 5, 6);
x2= 0.5.^n2;

d=5;
n3 = linspace(0, 15, 16);
x3 = [cos(2*pi*0.1*n3)];


[y, n] = convo(x1,x2,n1,n2);
[y_2, n_2] = convo(x3,x2,n3-d,n2)


n3 = [linspace(-5, 10, 16),11,12,13,14,15];
x3 = [x3,zeros(1,d)];


y_2=[y_2,zeros(1,d)]
n_2=[n_2,16,17,18,19,20]






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


figure(2)
subplot(3,1,1);
stem(n3,x3,'r','MarkerFaceColor','r')
axis([0 15 -1 1])
title('First Signals(x1[n-5])');

subplot(3,1,2);
stem(n2,x2,'k','MarkerFaceColor','k')
title('Second Signals(x2[n])');


subplot(3,1,3);
stem(n_2,y_2,'r','MarkerFaceColor','r')
axis([0 20 -2 2])

ylabel('Y[n-5]'); 
xlabel('n');
title('Convolution of Two Signals(x1[n-5]*x2[n])');
grid 

