N = 50;
f0 = 0.1;

x_n = 0 : 1 : N-1;
x = cos(2*pi*f0*x_n);


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