function [After_img] = myfun_munTuck(Befor_img, col,row,mun_Tuck)
Z=Befor_img;
% for i=1:col
%     for j=1:row
%     if abs(Z(i,j)) < mun_Tuck
%         Z(i,j) = 0;
%     end
%     end
% end

k =find(abs(Z)< mun_Tuck);
Z(k) =0;
After_img=Z;
