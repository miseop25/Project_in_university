clear;
clc;
se= linspace(-2*pi,2*pi,360);
f_w= linspace(0,2*pi,3000);
x=exp(1j*se);
N1= 5;

[buttap_z, buttap_p, buttap_k] = buttap(N1);
[cheb1ap_z, cheb1ap_p, cheb1ap_k]=cheb1ap(N1, 10);
[cheb2ap_z, cheb2ap_p, cheb2ap_k]=cheb2ap(N1, 30);
[ellipap_z, ellipap_p, ellipap_k]=ellipap(N1, 10, 30);


[buttap_zero_vector, buttap_pole_vector]=zp2tf(buttap_z,buttap_p,buttap_k);
buttap_freq_response=freqs(buttap_zero_vector, buttap_pole_vector, f_w);
buttap_freq_response = 10.*log10(abs(buttap_freq_response).^2);

[cheb1ap_zero_vector, cheb1ap_pole_vector]=zp2tf(cheb1ap_z,cheb1ap_p,cheb1ap_k);
cheb1ap_freq_response=freqs(cheb1ap_zero_vector, cheb1ap_pole_vector, f_w);
cheb1ap_freq_response = 10.*log10(abs(cheb1ap_freq_response).^2);

[cheb2ap_zero_vector, cheb2ap_pole_vector]=zp2tf(cheb2ap_z,cheb2ap_p,cheb2ap_k);
cheb2ap_freq_response=freqs(cheb2ap_zero_vector, cheb2ap_pole_vector, f_w);
cheb2ap_freq_response = 10.*log10(abs(cheb2ap_freq_response).^2);

[ellipap_zero_vector, ellipap_pole_vector]=zp2tf(ellipap_z,ellipap_p,ellipap_k);
ellipap_freq_response=freqs(ellipap_zero_vector, ellipap_pole_vector, f_w);
ellipap_freq_response = 10.*log10(abs(ellipap_freq_response).^2);


figure(1);
subplot(2,2,1);
plot(real(buttap_z),imag(buttap_z),'o','MarkerSize',20,'LineWidth',2)
hold on;
plot(x,'k:','MarkerSize',20,'LineWidth',4)
plot(real(buttap_p),imag(buttap_p),'xr','MarkerSize',20,'LineWidth',2)
hold off;
title("Butterworth")
grid on;

subplot(2,2,2);
plot(real(cheb1ap_z),imag(cheb1ap_z),'o','MarkerSize',20,'LineWidth',2)
hold on;
plot(x,'k:','MarkerSize',20,'LineWidth',4)
plot(real(cheb1ap_p),imag(cheb1ap_p),'xr','MarkerSize',20,'LineWidth',2)
hold off;
title("Chebyshev-1")

grid on;

subplot(2,2,3);
plot(real(cheb2ap_z),imag(cheb2ap_z),'o','MarkerSize',20,'LineWidth',2)
hold on;
plot(x,'k:','MarkerSize',20,'LineWidth',4)
plot(real(cheb2ap_p),imag(cheb2ap_p),'xr','MarkerSize',20,'LineWidth',2)
hold off;
title("Chebyshev-2")
grid on;

subplot(2,2,4);
plot(real(ellipap_z),imag(ellipap_z),'o','MarkerSize',20,'LineWidth',2)
hold on;
plot(x,'k:','MarkerSize',20,'LineWidth',4)
plot(real(ellipap_p),imag(ellipap_p),'xr','MarkerSize',20,'LineWidth',2)
hold off;
title("Eliptic")
grid on;


figure(2);
subplot(2,2,1);
plot(f_w,buttap_freq_response,'MarkerSize',20,'LineWidth',4);
axis([0 2 -40 10])
title("Butterworth")

grid on;
  
subplot(2,2,2);
plot(f_w,cheb1ap_freq_response,'MarkerSize',20,'LineWidth',4);
axis([0 2 -70 10])
title("Chebyshev-1")
grid on;

subplot(2,2,3);
plot(f_w,cheb2ap_freq_response,'MarkerSize',20,'LineWidth',4);
grid on;
axis([0 2 -70 10])
title("Chebyshev-2")

subplot(2,2,4);
plot(f_w,ellipap_freq_response,'MarkerSize',20,'LineWidth',4);
axis([0 2 -70 10])
grid on;
title("Eliptic")




