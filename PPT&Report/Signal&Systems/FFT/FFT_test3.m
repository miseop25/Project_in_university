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
N_mult2;

N3 = 64;
x_n3 = 0 : 1 : N3-1;
x3 = 0.3*cos(2*pi*f1*x_n3) + 0.8*sin(2*pi*x_n3*f2);
[f_hat3 , Xk3, N_mult3] = myfun_N_Point_FFT2(x3);
[f_hat3_DFT , Xk3_DFT,N_mult3_DFT] = myfun_N_Point_DFT(x3)
N_mult3;

N4 = 128;
x_n4 = 0 : 1 : N4-1;
x4 = 0.3*cos(2*pi*f1*x_n4) + 0.8*sin(2*pi*x_n4*f2);
[f_hat4 , Xk4, N_mult4] = myfun_N_Point_FFT2(x4);
[f_hat4_DFT , Xk4_DFT,N_mult4_DFT] = myfun_N_Point_DFT(x4)
N_mult4;

semilog_N = [N1,N2,N3,N4];
N_mult_FFT = [N_mult1,N_mult2,N_mult3,N_mult4];
N_mult_DFT = [N_mult1_DFT,N_mult2_DFT,N_mult3_DFT,N_mult4_DFT];
ratio_FFT = (N_mult_FFT./N_mult_DFT);

figure(1)
subplot(2,1,1);
semilogy(semilog_N,N_mult_FFT,'g^-')
hold on;
semilogy(semilog_N,N_mult_DFT,'bo-')
hold off;
ylabel('°ö¼À¿¬»ê È½¼ö'); 
xlabel('N');
legend('FFT','DFT')
grid on

subplot(2,1,2);
semilogy(semilog_N,ratio_FFT,'ko-')
ylabel('FFT : DFT °ö¼À¿¬»ê ºñÀ²'); 
xlabel('N');
axis([0 140 0.02 0.14])
grid on