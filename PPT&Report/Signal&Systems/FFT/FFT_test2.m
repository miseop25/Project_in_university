N1 = 16;
f1 = 0.1;
f2 = 0.3
x_n1 = 0 : 1 : N1-1;
x1 = 0.3*cos(2*pi*f1*x_n1) + 0.8*sin(2*pi*x_n1*f2);
[f_hat1 , Xk1, N_mult1] = myfun_N_Point_FFT2(x1);
[f_hat1_DFT , Xk1_DFT,N_mult1_DFT] = myfun_N_Point_DFT(x1)
N_mult1

N2 = 32;
x_n2 = 0 : 1 : N2-1;
x2 = 0.3*cos(2*pi*f1*x_n2) + 0.8*sin(2*pi*x_n2*f2);
[f_hat2 , Xk2, N_mult2] = myfun_N_Point_FFT2(x2);
[f_hat2_DFT , Xk2_DFT,N_mult2_DFT] = myfun_N_Point_DFT(x2)
N_mult2

N3 = 64;
x_n3 = 0 : 1 : N3-1;
x3 = 0.3*cos(2*pi*f1*x_n3) + 0.8*sin(2*pi*x_n3*f2);
[f_hat3 , Xk3, N_mult3] = myfun_N_Point_FFT2(x3);
[f_hat3_DFT , Xk3_DFT,N_mult3_DFT] = myfun_N_Point_DFT(x3)
N_mult3

N4 = 128;
x_n4 = 0 : 1 : N4-1;
x4 = 0.3*cos(2*pi*f1*x_n4) + 0.8*sin(2*pi*x_n4*f2);
[f_hat4 , Xk4, N_mult4] = myfun_N_Point_FFT2(x4);
[f_hat4_DFT , Xk4_DFT,N_mult4_DFT] = myfun_N_Point_DFT(x4)

N_mult4


figure(1)
subplot(2,1,1);
stem(x_n1,x1,'k','MarkerFaceColor','k')
ylabel('x[n]'); 
xlabel('n');
grid on
subplot(2,1,2);
plot(f_hat1,abs(Xk1),'ko')
hold on;
plot(f_hat1_DFT, abs(Xk1_DFT), 'rx:')
hold off;
ylabel('|Xl|'); 
xlabel('fhat');
legend('DFT','DTFT')
grid on

figure(2)
subplot(2,1,1);
stem(x_n2,x2,'k','MarkerFaceColor','k')
ylabel('x[n]'); 
xlabel('n');
grid on
axis([0 31 -2 2])


subplot(2,1,2);
plot(f_hat2,abs(Xk2),'ko')
hold on;
plot(f_hat2_DFT, abs(Xk2_DFT), 'rx:')
hold off;
legend('DFT','DTFT')
ylabel('|Xl|'); 
xlabel('fhat');
grid on

figure(3)
subplot(2,1,1);
stem(x_n3,x3,'k','MarkerFaceColor','k')
ylabel('x[n]'); 
xlabel('n');
grid on
axis([0 63 -2 2])

subplot(2,1,2);
plot(f_hat3,abs(Xk3),'ko')
hold on;
plot(f_hat3_DFT, abs(Xk3_DFT), 'rx:')
hold off;
legend('DFT','DTFT')
ylabel('|Xl|'); 
xlabel('fhat');
grid on

figure(4)
subplot(2,1,1);
stem(x_n4,x4,'k','MarkerFaceColor','k')
ylabel('x[n]'); 
xlabel('n');
axis([0 127 -2 2])

grid on
subplot(2,1,2);
plot(f_hat4,abs(Xk4),'ko')
hold on;
plot(f_hat4_DFT, abs(Xk4_DFT), 'rx:')
hold off;
legend('DFT','DTFT')
ylabel('|Xl|'); 
xlabel('fhat');
grid on

