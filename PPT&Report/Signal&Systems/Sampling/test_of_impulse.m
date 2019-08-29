N =4096;
t1 = -5;
t2 = 5;
fs =20;
tau = 20*pi;


[t , p] = myfun_impulse(t1,t2,N,fs); % ���޽���

[f0 , X] = myfun_SA(t,p); % ���޽���// �ð� -> ���ļ�
sinc_x = myfun_sinc(t,tau); 
[f1 , X1] = myfun_SA(t,sinc_x); %��ũ // �ð� -> ���ļ�
A = [sinc_x; p];
sample =prod(A);        %ǥ��ȭ ���� ��� �ΰ� �����ϼ� prod!!
[f2 , X2] = myfun_SA(t,sample);  %ǥ��ȭ �� ��ũ�Լ� // �ð� -> ���ļ�

sum(p)



figure(1)

subplot(3,1,1);
plot(t,p,'k','MarkerFaceColor','k')
axis([-1 1 0 1.2])
title('���޽���');
ylabel('p(t)'); 
xlabel('t[sec]');

subplot(3,1,2);
plot(t,sinc_x,'k')
axis([-1 1 -20 80])
title('Sinc �Լ�');
ylabel('x(t)'); 
xlabel('t[sec]');

subplot(3,1,3);
plot(t,sample,'k')
axis([-1 1 -20 80])
title('Sinc �Լ� ���ø�');
ylabel('y(t)'); 
xlabel('t[sec]');

grid

figure(2)

grid
subplot(3,1,1);
plot(f0,abs(X),'k')
axis([-30 30 0 1])
title('���ļ� �࿡���� ���޽���');
ylabel('|P(f)|'); 
xlabel('f[Hz]');
grid 

subplot(3,1,2);
plot(f1,abs(X1),'k')
axis([-30 30 0 8])
title('���ļ� �࿡���� Sinc �Լ�');
ylabel('|X(f)|'); 
xlabel('f[Hz]');
grid

subplot(3,1,3);
plot(f2,abs(X2),'k')
title('���ļ� �࿡���� Sinc �Լ� ���ø�');
ylabel('|Y(f)|'); 
xlabel('f[Hz]');
xlim([-30 30])

grid