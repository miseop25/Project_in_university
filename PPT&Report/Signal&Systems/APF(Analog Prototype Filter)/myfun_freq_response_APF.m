function [se,freq] = myfun_freq_response_APF(r,p)
se= linspace(0,2,1000);
x=(1j*se);

    bun_mo = abs(x-p);
    bun_ja = abs(x-r);

if size(bun_mo) >1
    bun_mo_mult = prod(bun_mo);
else
    bun_mo_mult = bun_mo;
end

if size(bun_ja) >1
    bun_ja_mult = prod(bun_ja);
else
    bun_ja_mult = bun_ja;
end



freq = (1./bun_mo_mult);

%freq = 1./sqrt(1+bun_mo_mult.^10);