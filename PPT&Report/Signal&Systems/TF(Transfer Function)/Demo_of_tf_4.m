clear;
clc;
t = linspace(0,20,21);
se= linspace(-2*pi,2*pi,360);
x=exp(1j*se);

sys_1_zero = [-5];
sys_1_zero_real = real(sys_1_zero)
sys_1_zero_imag = imag(sys_1_zero)
sys_1_pole = [0.5*exp(1j*(pi/4)) , 0.5*exp(1j*(-pi/4))];
sys_1_pole_real = real(sys_1_pole)
sys_1_pole_imag = imag(sys_1_pole)


[sys_1_ja, sys_1_mo]=zp2tf(sys_1_zero,sys_1_pole,1)
[sys_1_r,sys_1_p,k] = residue(sys_1_ja,[sys_1_mo,0])
impulse_response_1 = myfun_impulse_response_Des(sys_1_r,sys_1_p,t);


sys_2_zero = [-5];
sys_2_zero_real = real(sys_2_zero)
sys_2_zero_imag = imag(sys_2_zero)
sys_2_pole = [exp(1j*(pi/4)) , exp(1j*(-pi/4))];
sys_2_pole_real = real(sys_2_pole)
sys_2_pole_imag = imag(sys_2_pole)

[sys_2_ja, sys_2_mo]=zp2tf(sys_2_zero,sys_2_pole,1)
[sys_2_r,sys_2_p,k] = residue(sys_2_ja,[sys_2_mo,0])
impulse_response_2 = myfun_impulse_response_Des(sys_2_r,sys_2_p,t);

sys_3_zero = [-5];
sys_3_zero_real = real(sys_3_zero)
sys_3_zero_imag = imag(sys_3_zero)
sys_3_pole = [1.5*exp(1j*(pi/4)) , 1.5*exp(1j*(-pi/4))];
sys_3_pole_real = real(sys_3_pole)
sys_3_pole_imag = imag(sys_3_pole)

[sys_3_ja, sys_3_mo]=zp2tf(sys_3_zero,sys_3_pole,1)
[sys_3_r,sys_3_p,k] = residue(sys_3_ja,[sys_3_mo,0])
impulse_response_3 = myfun_impulse_response_Des(sys_3_r,sys_3_p,t);



figure(1);
subplot(1,3,1);
plot(sys_1_zero_real,sys_1_zero_imag,'o','MarkerSize',20,'LineWidth',4)
hold on;
plot(x,'k:','MarkerSize',20,'LineWidth',4)

plot(sys_1_pole_real,sys_1_pole_imag,'x','MarkerSize',20,'LineWidth',4)
hold off;
grid on;
axis([-5.5 2 -2.5 2.5])

subplot(1,3,2);
plot(sys_2_zero_real,sys_2_zero_imag,'o','MarkerSize',20,'LineWidth',4)
hold on;
plot(x,'k:','MarkerSize',20,'LineWidth',4)

plot(sys_2_pole_real,sys_2_pole_imag,'x','MarkerSize',20,'LineWidth',4)
hold off;
grid on;
axis([-5.5 2 -2.5 2.5])

subplot(1,3,3);
plot(sys_3_zero_real,sys_3_zero_imag,'o','MarkerSize',20,'LineWidth',4)
hold on;
plot(x,'k:','MarkerSize',20,'LineWidth',4)

plot(sys_3_pole_real,sys_3_pole_imag,'x','MarkerSize',20,'LineWidth',4)
hold off;
grid on;
axis([-5.5 2 -2.5 2.5])


figure(2);
subplot(3,1,1);
stem(t,impulse_response_1,'MarkerSize',10,'LineWidth',2);
axis([0 20 -2 6])
title("System1")


subplot(3,1,2);
stem(t,impulse_response_2,'MarkerSize',10,'LineWidth',2);
axis([0 20 -10 10])
title("System2")
subplot(3,1,3);
stem(t,impulse_response_3,'MarkerSize',10,'LineWidth',2);
xlim([0 20])
title("System3")

