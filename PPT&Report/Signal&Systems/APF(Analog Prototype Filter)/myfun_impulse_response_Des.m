function [impulse_response] = myfun_impulse_response_Des(r,p,t)
N=length(t);
impulse_mid=zeros(length(p)+1,N);

% for k =1 : length(p)
%     for i = 1 :N
%     impulse_mid(k,i) = r(k)*(p(k)^t(i));
%     end
% 
% end

impulse_mid= r.*(p.^t);
impulse_response = sum(impulse_mid);
