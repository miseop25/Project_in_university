N = 50;
f0 = 0.1;
f1 = 0.2;
f2 = 0.3;

x_n = 0 : 1 : N-1;
x0 = cos(2*pi*f0*x_n);
x1 = 0.5*cos(2*pi*f1*x_n);
x2 = 0.1*cos(2*pi*f2*x_n);

x= x0+x1+x2;

[f_hat , Xk, N_mult] = myfun_N_Point_DFT(x);


figure(1)

subplot(2,1,1);
stem(x_n,x,'k','MarkerFaceColor','k')
ylabel('x[n]'); 
xlabel('n');

subplot(2,1,2);
stem(f_hat,abs(Xk),'k','MarkerFaceColor','k')
ylabel('|Xl|'); 
xlabel('fhat');