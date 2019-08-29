function [se,freq] = myfun_freq_response_Des(r,p)
se= linspace(-pi,pi,360);
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

freq = (bun_ja_mult./bun_mo_mult);