clear;
clc;

row = 256;
col = 256;
mun_Tuck = [0.001,0.01,0.05,0.1,0.25,0.5];
Bring_img = myfun_LoadImage('lena.raw', row, col);
Z_orginal =(dct2(Bring_img)/256);


Z1 =myfun_munTuck(Z_orginal, col,row,mun_Tuck(1));
I_Z1 = uint8(idct2(Z1)*256);
RMSE1 = myfun_RMSE(Bring_img, I_Z1, col,row)
Rate1 = myfun_Rates_of_DCT(Z1, Z1, col,row)

Z2 =myfun_munTuck(Z_orginal, col,row,mun_Tuck(2));
I_Z2 = uint8(idct2(Z2)*256);
RMSE2 = myfun_RMSE(Bring_img, I_Z2, col,row)
Rate2 = myfun_Rates_of_DCT(Z1, Z2, col,row)

Z3 =myfun_munTuck(Z_orginal, col,row,mun_Tuck(3));
I_Z3 = uint8(idct2(Z3)*256);
RMSE3 = myfun_RMSE(Bring_img, I_Z3, col,row)
Rate3 = myfun_Rates_of_DCT(Z1, Z3, col,row)

Z4 =myfun_munTuck(Z_orginal, col,row,mun_Tuck(4));
I_Z4 = uint8(idct2(Z4)*256);
RMSE4 = myfun_RMSE(Bring_img, I_Z4, col,row)
Rate4 = myfun_Rates_of_DCT(Z1, Z4, col,row)

Z5 =myfun_munTuck(Z_orginal, col,row,mun_Tuck(5));
I_Z5 = uint8(idct2(Z5)*256);
RMSE5 = myfun_RMSE(Bring_img, I_Z5, col,row)
Rate5 = myfun_Rates_of_DCT(Z1, Z5, col,row)

Z6 =myfun_munTuck(Z_orginal, col,row,mun_Tuck(6));
I_Z6 = uint8(idct2(Z6)*256);
RMSE6 = myfun_RMSE(Bring_img, I_Z6, col,row)
Rate6 = myfun_Rates_of_DCT(Z1, Z6, col,row)

RMSE = [RMSE1,RMSE2,RMSE3,RMSE4,RMSE5,RMSE6];
Rate = [Rate1,Rate2,Rate3,Rate4,Rate5,Rate6];

figure(1);
subplot(2,2,1);
imshow(abs(Z2));
title('문턱값 = 0.01')
subplot(2,2,2);
imshow(abs(Z4));
title('문턱값 = 0.1')
subplot(2,2,3);
imshow(abs(Z5));
title('문턱값 = 0.25')
subplot(2,2,4);
imshow(abs(Z6));
title('문턱값 = 0.5')


figure(2);
subplot(2,2,1);
imshow((I_Z2));
title('문턱값 = 0.01')
subplot(2,2,2);
imshow((I_Z4));
title('문턱값 = 0.1')
subplot(2,2,3);
imshow((I_Z5));
title('문턱값 = 0.25')
subplot(2,2,4);
imshow((I_Z6));
title('문턱값 = 0.5')


figure(3);
imshow(Bring_img);
title('Orignal_img')


figure(3);
subplot(2,1,1);
semilogy(mun_Tuck,Rate,'ro-')
title('압축률')

subplot(2,1,2);
plot(mun_Tuck,RMSE,'bo-')
grid on;
title('RMSE')



