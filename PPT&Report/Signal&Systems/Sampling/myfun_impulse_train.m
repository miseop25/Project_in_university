
function [t, x] = myfun_impulse_train( t1, t2, N, f)
d = t2 - t1;
ones = d*f;                             %1의 개수 
Ts = 1/f;                               %주기
d_ones = (d-Ts)/(ones-1);               %1사이의 거리
b_zeros = fix((N-ones)/(ones-1));       %1과 1사이의 0의 개수
r_zeros = N-((b_zeros+1)*(ones-1))-1;   %남은 0의 개수
d_zeros = d_ones/(b_zeros+1);           %0과 0사이의 거리


t = linspace(t1,t2-Ts+(d_zeros*r_zeros),N);
blk = 1:b_zeros+1:N;
blk;

x = zeros(1,N);
x(blk) = 1;

