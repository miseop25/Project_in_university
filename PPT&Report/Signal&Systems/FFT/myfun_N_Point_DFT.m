function [f_hat , Xk,N_mult] = myfun_N_Point_DFT(x)

x_len = length(x);          
N_to_Sum = 0 : 1:(x_len-1); 
Xk_mid = [zeros(1,x_len)];
f_mid =  [zeros(1,x_len)];


for k=1 : x_len
    for n=1:x_len
    Xk_mid(k) =Xk_mid(k) + x(n)*exp(-1i*2*pi*(N_to_Sum(k)/ x_len)*N_to_Sum(n));
    end
    
    if k < (x_len/2 +1)
    f_mid(k) = N_to_Sum(k)/x_len;
    else
    f_mid(k) = N_to_Sum(k)/x_len-1;
    end      
end


f_hat = f_mid;
Xk = Xk_mid;
N_mult =(x_len).^2;





