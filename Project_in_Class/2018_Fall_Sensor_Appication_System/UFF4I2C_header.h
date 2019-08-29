#define SRF10_ERR_MAX_CNT 2000

unsigned char readByte_i2c(unsigned char address, unsigned char Reg)
{
    char read_data = 0;
    unsigned int srf10_ErrCnt = 0;
    
    TWCR = 0xA4;
    
    while(!(TWCR & 0x80))
    {
        if(srf10_ErrCnt++ > SRF10_ERR_MAX_CNT)
        {
            return 0;
        }
    };
    
    TWDR = address;
    TWCR = 0x84;
    
    while(!(TWCR & 0x80))
    {
        if(srf10_ErrCnt++ > SRF10_ERR_MAX_CNT)
        {
            return 0;
        }
    };
    
    TWDR = Reg;
    TWCR = (1<<TWINT) | (1<<TWEN);
    
    while(!(TWCR & 0x80))
    {
        if(srf10_ErrCnt++ > SRF10_ERR_MAX_CNT)
        {
            return 0;
        }
    };
    
    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
    
    while(!(TWCR & 0x80))
    {
        if(srf10_ErrCnt++ > SRF10_ERR_MAX_CNT)
        {
            return 0;
        }
    };
    
    TWDR = address + 1;
    TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
    
    while(!(TWCR & 0x80))
    {
        if(srf10_ErrCnt++ > SRF10_ERR_MAX_CNT)
        {
            return 0;
        }
    };
    
    TWCR = (1<<TWINT) | (1<<TWEN);
    
    while(!(TWCR & 0x80))
    {
        if(srf10_ErrCnt++ > SRF10_ERR_MAX_CNT)
        {
            return 0;
        }
    };
    
    read_data = TWDR;
    TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
    return read_data;
}

int writeByte_i2c(unsigned char address, unsigned char reg , unsigned char data)
{
    unsigned int srf10_ErrCnt = 0;
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    while(!(TWCR &(1<<TWINT)))
    {
        if(srf10_ErrCnt++>SRF10_ERR_MAX_CNT)
        {
            return 0;
        }
    };
    
    TWDR = address;
    TWCR = (1<<TWINT)|(1<<TWEN);
    
    while(!(TWCR & (1<<TWINT)))
    {
        if(srf10_ErrCnt++ > SRF10_ERR_MAX_CNT)
        {
            return 0;
        }
    };
    
    TWDR = reg;
    TWCR = (1<<TWINT) | (1<<TWEN);
    
    while(!(TWCR & (1<<TWINT)))
    {
        if(srf10_ErrCnt++ > SRF10_ERR_MAX_CNT)
        {
            return 0;
        }
    };
    
    TWDR = data;
    TWCR = (1<<TWINT) | (1<<TWEN);
    
    while(!(TWCR & (1<<TWINT)))
    {
        if(srf10_ErrCnt++ > SRF10_ERR_MAX_CNT)
        {
            return 0;
        }
    };
    
    TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
    return 1;
}

