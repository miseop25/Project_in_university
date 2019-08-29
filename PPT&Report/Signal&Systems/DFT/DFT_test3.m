
N = 50;
x_n = 0 : 1 : N-1;
L1 =1;
L2 =10;
L3 =30;
L4 =50;


L_DFT =[ones(1,L1),zeros(1,(N-L1))];
L_DTFT =[ones(1,L1),zeros(1,(1024-L1))];

[f_hat , Xk, N_mult] = myfun_N_Point_DFT(L_DFT);
[f_hat_DTFT , Xk_DTFT, N_mult_DTFT] = myfun_N_Point_DFT(L_DTFT);

L_DFT2 =[ones(1,L2),zeros(1,(N-L2))];
L_DTFT2 =[ones(1,L2),zeros(1,(1024-L2))];

[f_hat2 , Xk2, N_mult2] = myfun_N_Point_DFT(L_DFT2);
[f_hat_DTFT2 , Xk_DTFT2, N_mult_DTFT2] = myfun_N_Point_DFT(L_DTFT2);

L_DFT3 =[ones(1,L3),zeros(1,(N-L3))];
L_DTFT3 =[ones(1,L3),zeros(1,(1024-L3))];

[f_hat3 , Xk3, N_mult3] = myfun_N_Point_DFT(L_DFT3);
[f_hat_DTFT3 , Xk_DTFT3, N_mult_DTFT3] = myfun_N_Point_DFT(L_DTFT3);

L_DFT4 =[ones(1,L4),zeros(1,(N-L4))];
L_DTFT4 =[ones(1,L4),zeros(1,(1024-L4))];

[f_hat4 , Xk4, N_mult4] = myfun_N_Point_DFT(L_DFT4);
[f_hat_DTFT4 , Xk_DTFT4, N_mult_DTFT4] = myfun_N_Point_DFT(L_DTFT4);






figure(1)
subplot(4,2,1);
stem(x_n,L_DFT,'k','MarkerFaceColor','k')
ylabel('x[n]'); 
xlabel('n');
grid

subplot(4,2,2);
plot(f_hat_DTFT,abs(Xk_DTFT),'k','MarkerFaceColor','k')
hold on
plot(f_hat,abs(Xk),'ro')
hold off
ylabel('|Xl|'); 
xlabel('fhat');
axis([-0.5 0.5 0 2])
legend('DTFT', 'DFT')
grid

subplot(4,2,3);
stem(x_n,L_DFT2,'k','MarkerFaceColor','k')
ylabel('x[n]'); 
xlabel('n');
grid

subplot(4,2,4);
plot(f_hat_DTFT2,abs(Xk_DTFT2),'k','MarkerFaceColor','k')
hold on
stem(f_hat2,abs(Xk2),'ro')
hold off
ylabel('|Xl|'); 
xlabel('fhat');
legend('DTFT', 'DFT')
grid

subplot(4,2,5);
stem(x_n,L_DFT3,'k','MarkerFaceColor','k')
ylabel('x[n]'); 
xlabel('n');
grid

subplot(4,2,6);
plot(f_hat_DTFT3,abs(Xk_DTFT3),'k','MarkerFaceColor','k')
hold on
stem(f_hat3,abs(Xk3),'ro')
hold off
ylabel('|Xl|'); 
xlabel('fhat');
legend('DTFT', 'DFT')
grid

subplot(4,2,7);
stem(x_n,L_DFT4,'k','MarkerFaceColor','k')
ylabel('x[n]'); 
xlabel('n');
grid

subplot(4,2,8);
plot(f_hat_DTFT4,abs(Xk_DTFT4),'k','MarkerFaceColor','k')
hold on
stem(f_hat4,abs(Xk4),'ro')
hold off
ylabel('|Xl|'); 
xlabel('fhat');
legend('DTFT', 'DFT')
grid