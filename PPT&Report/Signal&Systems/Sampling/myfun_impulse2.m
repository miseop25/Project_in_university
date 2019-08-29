function [t , p] = myfun_impulse2(t1,t2,N,fs)
Ts = 1/fs;
value_time = [t1 : Ts : t2-0.0001]
real_time = linspace(t1 ,t2 ,N);
real_time =round(real_time,4)

Ts = round(Ts,4);
%value_time = [t1 : Ts : t2]
value = [1,zeros(1,N)];


num= N/length(value_time)
num = ceil(num)

count =1;

for i = 2:N
    if count == num
        value(i) = 1;
        count =1;
    else
        value(i) =0;
        count = count +1;
    end
end




t = real_time(:,1:length(real_time));      
p = value(:,1:length(value)-1);
length(t)
length(p)
