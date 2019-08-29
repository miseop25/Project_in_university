function [t , p] = myfun_impulse(t1,t2,N,fs)
Ts = 1/fs;
value_time = [t1 : Ts : t2];
between_time = N/(length(value_time))
between_time = ceil(between_time)
D=[];

for k=2:length(value_time)
    mid = linspace(value_time(k-1),value_time(k),between_time+1);
    D=[D , mid];
    D = unique(D);
end

total_time = D(:,1:length(D)-1);
value = [zeros(1,length(total_time))]; 

for i = 1:length(total_time)
    for j=1:length(value_time)
        if total_time(i) == value_time(j) 
            value(i) =1;
        end
    end
end

t = total_time(:,1:N);
p = value(:,1:N);
