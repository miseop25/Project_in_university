function [impulse_response] = myfun_impulse_response(r,p,t)
impulse_mid = [;];
N=length(t);
% for k =1 : length(r)
%     for i = 1 :N
%     impulse_mid(k,i) = r(k)*exp(t(i)*p(k));
%     end
% end

impulse_mid = r.*exp(t.*p);
impulse_response = sum(impulse_mid);
