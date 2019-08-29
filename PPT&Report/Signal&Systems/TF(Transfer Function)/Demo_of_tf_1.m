clear;
clc;

bun_ja = roots([1,5])
bun_ja_real = real(bun_ja)
bun_ja_imag = imag(bun_ja)

bun_mo = roots([1,2,5])
bun_mo_real = real(bun_mo)
bun_mo_imag = imag(bun_mo)

figure(1);
plot(bun_ja_real,bun_ja_imag,'o','MarkerSize',20,'LineWidth',4)
hold on;
plot(bun_mo_real,bun_mo_imag,'x','MarkerSize',20,'LineWidth',4)
hold off;
grid on;
axis([-5.5 0 -2.5 2.5])


t = linspace(0,10,1024);
[sys_1_r,sys_1_p,k] = residue([1,5],[1,2,5])
impulse_response = myfun_impulse_response(sys_1_r,sys_1_p,t);

figure(2);
plot(t,impulse_response);
axis([0 10 -0.4 1.6])


[f_w,freq] = myfun_freq_response(bun_ja,bun_mo);
figure(3);
plot(f_w,freq);
grid on;
axis([-4 4 0.4 1.4])



