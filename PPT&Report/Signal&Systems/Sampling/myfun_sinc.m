function  sinc_x = myfun_sinc(t,tau)
sinc_x = tau*sinc((tau*t)/(2*pi));
