clc;
clear;
N = 4096;
f0 = 0.05;

x_n = 0 : 1 : N-1;
x = cos(2*pi*f0*x_n);


[f_hat , Xk, N_mult] = myfun_N_Point_FFT2(x);

N_mult
figure(1)

subplot(2,1,1);
plot(x_n,x,'k','MarkerFaceColor','k')
ylabel('x[n]'); 
xlabel('n');
 axis([0 64 -1 1])
grid on

subplot(2,1,2);
plot(f_hat,abs(Xk),'k','MarkerFaceColor','k')
ylabel('|Xl|'); 
xlabel('fhat');
grid on