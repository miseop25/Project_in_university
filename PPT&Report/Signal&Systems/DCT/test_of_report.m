clear;
clc;
row = 256;
col = 256;
Bring_img = myfun_LoadImage('lena.raw', row, col);
Z1 =(fft2(Bring_img)/(256*256));

% lowest_Z1 = min(min(Z1))
% highest_Z1 = max(max(Z1))
% range = highest_Z1 - lowest_Z1;
% for i=1:col
%     for j=1:row
%     Z2(i,j) = ((Z1(i,j) - lowest_Z1)/range)*255;
%     end
% end

% for i=1:col
%     for j=1:row
%     Z3(i,j) = (Z2(i,j)*range)/255 + lowest_Z1;
%     end
% end
I_Z = uint8(ifft2(Z1)*256*256);


figure(1);
imshow((Z1));

figure(2);
imshow(I_Z);

figure(3);
imshow(Bring_img);






lowest_Z2 = min(min(Z3))
highest_Z2 = max(max(Z3))