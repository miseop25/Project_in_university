function [impulse_response] = myfun_impulse_response_Des(r,p,t)

impulse_mid= r.*(p.^t);
impulse_response = sum(impulse_mid);

% impulse_mid=zeros(length(p)+1,N);
% N=length(t);

% for k =1 : length(p)
%     for i = 1 :N
%     impulse_mid(k,i) = r(k)*(p(k)^t(i));
%     end
% 
% end
