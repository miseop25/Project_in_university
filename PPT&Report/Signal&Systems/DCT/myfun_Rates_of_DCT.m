function [Rate] = myfun_Rates_of_DCT(First_img, Second_img, col,row)

First_img_count = find(First_img ~= 0);
First_img_count = length(First_img_count);
Second_img_count =find(Second_img ~= 0);
Second_img_count = length(Second_img_count);

% First_img_count = 0;
% Second_img_count = 0;
% for i=1:col
%     for j=1:row
%          if First_img(i,j) ~= 0
%             First_img_count = First_img_count+1;
%          end
%          if Second_img(i,j) ~= 0
%             Second_img_count = Second_img_count+1;
%          end
%     end
% end

Rate = (Second_img_count/First_img_count);