function [RMSE_Value] = myfun_RMSE(First_img, Second_img, col,row)
RMSE_mid =[];
RMSE_mid =abs(First_img - Second_img).^2;
RMSE_MAX = sum(sum(RMSE_mid));
RMSE_Value =sqrt((1/(row*col))*RMSE_MAX);

% for i=1 :col
%     for j = 1: row   
%     RMSE_mid(i,j) =abs(First_img(i,j) - Second_img(i,j))^2;
%     end
% end


