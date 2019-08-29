clear;
clc;
row = 256;
col = 256;
Bring_img = myfun_LoadImage('lena.raw', row, col);
Z =(dct2(Bring_img)/256);
figure(1);
imshow(abs(Z));

I_Z = uint8(idct2(Z)*256);
figure(4);
imshow(I_Z);

figure(3);
imshow(Bring_img);