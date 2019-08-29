function [f_hat , Xk,N_mult] = myfun_N_Point_FFT2(x)

x_len = length(x);
bit_value= log2(x_len);     
N_to_order = 0 : 1:(x_len-1);
f_mid =  [zeros(1,x_len)];
X_mid=zeros(bit_value+1,x_len);
N_mult = 0;

W_turn = zeros(bit_value,(x_len/2));
for col = 1:bit_value
    for row = 1:2^(N_to_order(col))
    W_turn(col, row) = exp(-1i*((2*pi)/(2.^col))*N_to_order(row));
    end
end

new_num = rot90(bin2dec(fliplr(dec2bin(N_to_order,bit_value))));

for i = 1 : x_len
    In_To_x = new_num(i)+1; 
    X_mid(1,i) = x(In_To_x);
end

for stage=1 : bit_value
    w_value = 1 : 1 : 2.^(stage-1);
    In_To_W = 1;
    for k =1 : ( x_len - 2.^(N_to_order(stage)))
            if or((mod(k,2.^(stage)) > (2.^stage)/2),(mod(k,2.^(stage)) == 0))
            else
                same_W = W_turn(stage,w_value(In_To_W))*X_mid(stage,k+2.^N_to_order(stage));
                X_mid(stage+1,k) = X_mid(stage,k)+ same_W;
                X_mid(stage+1,k+2.^N_to_order(stage)) = X_mid(stage,k)- same_W;
                N_mult = N_mult +1;
            end
    In_To_W = In_To_W +1;
    if In_To_W >2.^(N_to_order(stage))   In_To_W = 1;   end
    end
end

for k =1 :  x_len
    if k < (x_len/2 +1)
        f_mid(k) = N_to_order(k)/x_len;
    else
        f_mid(k) = N_to_order(k)/x_len-1;
    end
end
Xk = [zeros(1,x_len)];
for a=1 :x_len
    Xk(a)= X_mid(bit_value+1,a);
end
f_hat =f_mid;
