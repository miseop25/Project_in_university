clear;
clc;
t = linspace(0,20,21);
se= linspace(-2*pi,2*pi,360);
x=exp(1j*se);


bun_ja = roots([1,-0.3])
bun_ja_real = real(bun_ja);
bun_ja_imag = imag(bun_ja);

bun_mo = roots([1,0.3,0.36,0.108])
bun_mo_real = real(bun_mo);
bun_mo_imag = imag(bun_mo);

figure(1);
plot(bun_ja_real,bun_ja_imag,'o','MarkerSize',20,'LineWidth',4)
hold on;
plot(x,'k:','MarkerSize',20,'LineWidth',4)
plot(bun_mo_real,bun_mo_imag,'x','MarkerSize',20,'LineWidth',4)
hold off;
grid on;


[r,p,k] = residue([1,-0.3],[1,0.3,0.36,0.108,0]);
impulse_response = myfun_impulse_response_Des(r,p,t);
figure(2);
stem(t,impulse_response,'MarkerSize',10,'LineWidth',2);


[f_w,freq] = myfun_freq_response_Des(bun_ja,bun_mo);
figure(3);
plot(f_w,freq);
grid on;
axis([-3 3 0.2 1.8])