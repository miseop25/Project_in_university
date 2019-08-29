
function [t, x] = myfun_impulse_train( t1, t2, N, f)
d = t2 - t1;
ones = d*f;                             %1�� ���� 
Ts = 1/f;                               %�ֱ�
d_ones = (d-Ts)/(ones-1);               %1������ �Ÿ�
b_zeros = fix((N-ones)/(ones-1));       %1�� 1������ 0�� ����
r_zeros = N-((b_zeros+1)*(ones-1))-1;   %���� 0�� ����
d_zeros = d_ones/(b_zeros+1);           %0�� 0������ �Ÿ�


t = linspace(t1,t2-Ts+(d_zeros*r_zeros),N);
blk = 1:b_zeros+1:N;
blk;

x = zeros(1,N);
x(blk) = 1;

