clear;
clc;
row = 256;
col = 256;
Bring_img = myfun_LoadImage('lena.raw', row, col);
Z =fft2(Bring_img);

lowest = min(min(Z))
highest = max(max(Z))
range = highest - lowest;
for i=1:col
    for j=1:row
    Z(i,j) = ((Z(i,j) - lowest)/range)*256;
    end
end

figure(1);
imshow(abs(Z));
for i=1:col
    for j=1:row
    Z(i,j) = (Z(i,j)*range)/256 + lowest;
    end
end
I_Z = uint8(ifft2(Z));



figure(2);
imshow(I_Z);

figure(3);
imshow(Bring_img);