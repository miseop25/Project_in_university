clear;
clc;
t = linspace(0,10,1024);


sys_1_zero = [-5];
sys_1_zero_real = real(sys_1_zero)
sys_1_zero_imag = imag(sys_1_zero)
sys_1_pole = [-1+2i , -1-2i];
sys_1_pole_real = real(sys_1_pole)
sys_1_pole_imag = imag(sys_1_pole)

[sys_1_ja, sys_1_mo]=zp2tf(sys_1_zero,sys_1_pole,1)
[sys_1_r,sys_1_p,k] = residue(sys_1_ja,sys_1_mo)
impulse_response_1 = myfun_impulse_response(sys_1_r,sys_1_p,t);


sys_2_zero = [-5];
sys_2_zero_real = real(sys_2_zero)
sys_2_zero_imag = imag(sys_2_zero)
sys_2_pole = [2i , -2i];
sys_2_pole_real = real(sys_2_pole)
sys_2_pole_imag = imag(sys_2_pole)

[sys_2_ja, sys_2_mo]=zp2tf(sys_2_zero,sys_2_pole,1)
[sys_2_r,sys_2_p,k] = residue(sys_2_ja,sys_2_mo)
impulse_response_2 = myfun_impulse_response(sys_2_r,sys_2_p,t);

sys_3_zero = [-5];
sys_3_zero_real = real(sys_3_zero)
sys_3_zero_imag = imag(sys_3_zero)
sys_3_pole = [1+2i ,1-2i];
sys_3_pole_real = real(sys_3_pole)
sys_3_pole_imag = imag(sys_3_pole)

[sys_3_ja, sys_3_mo]=zp2tf(sys_3_zero,sys_3_pole,1)
[sys_3_r,sys_3_p,k] = residue(sys_3_ja,sys_3_mo)
impulse_response_3 = myfun_impulse_response(sys_3_r,sys_3_p,t);


figure(1);
subplot(1,3,1);
plot(sys_1_zero_real,sys_1_zero_imag,'o','MarkerSize',20,'LineWidth',4)
hold on;
plot(sys_1_pole_real,sys_1_pole_imag,'x','MarkerSize',20,'LineWidth',4)
hold off;
grid on;
axis([-5.5 2 -2.5 2.5])

subplot(1,3,2);
plot(sys_2_zero_real,sys_2_zero_imag,'o','MarkerSize',20,'LineWidth',4)
hold on;
plot(sys_2_pole_real,sys_2_pole_imag,'x','MarkerSize',20,'LineWidth',4)
hold off;
grid on;
axis([-5.5 2 -2.5 2.5])

subplot(1,3,3);
plot(sys_3_zero_real,sys_3_zero_imag,'o','MarkerSize',20,'LineWidth',4)
hold on;
plot(sys_3_pole_real,sys_3_pole_imag,'x','MarkerSize',20,'LineWidth',4)
hold off;
grid on;
axis([-5.5 2 -2.5 2.5])


figure(2);
subplot(3,1,1);
plot(t,impulse_response_1);
axis([0 10 -0.4 1.6])

subplot(3,1,2);
plot(t,impulse_response_2);
axis([0 10 -4 4])

subplot(3,1,3);
plot(t,impulse_response_3);
xlim([0 10])