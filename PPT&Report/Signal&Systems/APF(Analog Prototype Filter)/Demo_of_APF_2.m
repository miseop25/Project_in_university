clear;
clc;
se= linspace(-2*pi,2*pi,360);
f_w= linspace(0,2.5,100);
f_w_High= linspace(0,5000,10000);

x=exp(1j*se);

N = ceil(log10((1/10^(-4))-1)/(2*log10(2)));
[buttap_z, buttap_p, buttap_k] = buttap(N);

[buttap_zero_vector, buttap_pole_vector]=zp2tf(buttap_z,buttap_p,buttap_k);
buttap_freq_response=freqs(buttap_zero_vector, buttap_pole_vector, f_w);
buttap_freq_response = 10.*log10(abs(buttap_freq_response).^2);

[numt, dent]=lp2lp(buttap_zero_vector, buttap_pole_vector, 300);
lpf_freq_response300=freqs(numt, dent, f_w_High);
lpf_freq_response300 = 10.*log10(abs(lpf_freq_response300).^2);

[numt_bpf, dent_bpf]=lp2bp(buttap_zero_vector, buttap_pole_vector, 650,700);
bpf_freq_response300=freqs(numt_bpf, dent_bpf, f_w_High);
bpf_freq_response300 = 10.*log10(abs(bpf_freq_response300).^2);

[numt_bpf1000, dent_bpf1000]=lp2bp(buttap_zero_vector, buttap_pole_vector, 1500,1000);
bpf_freq_response1000=freqs(numt_bpf1000, dent_bpf1000, f_w_High);
bpf_freq_response1000 = 10.*log10(abs(bpf_freq_response1000).^2);

[numt_bpf2000, dent_bpf2000]=lp2bp(buttap_zero_vector, buttap_pole_vector, 3000,2000);
bpf_freq_response2000=freqs(numt_bpf2000, dent_bpf2000, f_w_High);
bpf_freq_response2000 = 10.*log10(abs(bpf_freq_response2000).^2);

[numt_h, dent_h]=lp2hp(buttap_zero_vector, buttap_pole_vector, 4000);
hpf_freq_response4000=freqs(numt_h, dent_h, f_w_High);
hpf_freq_response4000 = 10.*log10(abs(hpf_freq_response4000).^2);

figure(1);
plot(real(buttap_z),imag(buttap_z),'o','MarkerSize',20,'LineWidth',4)
hold on;
plot(x,'k:','MarkerSize',20,'LineWidth',4)
plot(real(buttap_p),imag(buttap_p),'xr','MarkerSize',20,'LineWidth',4)
hold off;
grid on;


figure(2);
plot(f_w,buttap_freq_response,'LineWidth',4);
axis([0 2.5 -50 5])
grid on;

figure(3);
plot(f_w_High,lpf_freq_response300,'LineWidth',4);
hold on;
plot(f_w_High,bpf_freq_response300,'LineWidth',4);
plot(f_w_High,bpf_freq_response1000,'LineWidth',4);
plot(f_w_High,bpf_freq_response2000,'LineWidth',4);
plot(f_w_High,hpf_freq_response4000,'LineWidth',4);
hold off;
grid on;
ylim([-30 10])