/*
 * This software program is licensed subject to the GNU General Public License
 * (GPL).Version 2,June 1991, available at http://www.fsf.org/copyleft/gpl.html

 * (C) Copyright 2011 Bosch Sensortec GmbH
 * All Rights Reserved
 */
/***********************************************************************/
/* Modified by                                                         */
/* (C) NEC CASIO Mobile Communications, Ltd. 2011                      */
/***********************************************************************/













#include <linux/i2c/smb380.h>



smb380_t *p_smb380;             







int smb380_init(smb380_t *smb380)
{
    int comres=0;
    unsigned char data;

    p_smb380 = smb380;                                                                          
    p_smb380->dev_addr = SMB380_I2C_ADDR;                                       
    comres += p_smb380->SMB380_BUS_READ_FUNC(p_smb380->dev_addr, SMB380_CHIP_ID__REG, &data, 1);    

    p_smb380->chip_id = SMB380_GET_BITSLICE(data, SMB380_CHIP_ID);                      

    comres += p_smb380->SMB380_BUS_READ_FUNC(p_smb380->dev_addr, SMB380_ML_VERSION__REG, &data, 1); 
    p_smb380->ml_version = SMB380_GET_BITSLICE(data, SMB380_ML_VERSION);                
    p_smb380->al_version = SMB380_GET_BITSLICE(data, SMB380_AL_VERSION);                

    return comres;

}



int smb380_soft_reset()
{
    int comres;
    unsigned char data=0;
    if (p_smb380==0)
        return E_SMB_NULL_PTR;
    data = SMB380_SET_BITSLICE(data, SMB380_SOFT_RESET, 1);
  comres = p_smb380->SMB380_BUS_WRITE_FUNC(p_smb380->dev_addr, SMB380_SOFT_RESET__REG, &data,1);
    return comres;
}





int smb380_update_image()
{
    int comres;
    unsigned char data=0;
    if (p_smb380==0)
        return E_SMB_NULL_PTR;
    data = SMB380_SET_BITSLICE(data, SMB380_UPDATE_IMAGE, 1);
    comres = p_smb380->SMB380_BUS_WRITE_FUNC(p_smb380->dev_addr, SMB380_UPDATE_IMAGE__REG, &data,1);
    return comres;
}






int smb380_set_image (smb380regs_t *smb380Image)
{
    int comres;
    unsigned char data;
    if (p_smb380==0)
        return E_SMB_NULL_PTR;









    comres = p_smb380->SMB380_BUS_READ_FUNC(p_smb380->dev_addr, SMB380_EE_W__REG,&data, 1);
    data = SMB380_SET_BITSLICE(data, SMB380_EE_W, SMB380_EE_W_ON);
    comres += p_smb380->SMB380_BUS_WRITE_FUNC(p_smb380->dev_addr, SMB380_EE_W__REG, &data, 1);
    comres += p_smb380->SMB380_BUS_WRITE_FUNC(p_smb380->dev_addr, SMB380_IMAGE_BASE, (unsigned char*)smb380Image, SMB380_IMAGE_LEN);
    comres += p_smb380->SMB380_BUS_READ_FUNC(p_smb380->dev_addr, SMB380_EE_W__REG,&data, 1);
    data = SMB380_SET_BITSLICE(data, SMB380_EE_W, SMB380_EE_W_OFF);
    comres += p_smb380->SMB380_BUS_WRITE_FUNC(p_smb380->dev_addr, SMB380_EE_W__REG, &data, 1);

    return comres;
}








int smb380_get_image(smb380regs_t *smb380Image)
{

    int comres;
    unsigned char data;
    if (p_smb380==0)
        return E_SMB_NULL_PTR;








        comres = p_smb380->SMB380_BUS_READ_FUNC(p_smb380->dev_addr, SMB380_EE_W__REG,&data, 1);
    data = SMB380_SET_BITSLICE(data, SMB380_EE_W, SMB380_EE_W_ON);
    comres += p_smb380->SMB380_BUS_WRITE_FUNC(p_smb380->dev_addr, SMB380_EE_W__REG, &data, 1);
    comres += p_smb380->SMB380_BUS_READ_FUNC(p_smb380->dev_addr, SMB380_IMAGE_BASE, (unsigned char *)smb380Image, SMB380_IMAGE_LEN);
    data = SMB380_SET_BITSLICE(data, SMB380_EE_W, SMB380_EE_W_OFF);
    comres += p_smb380->SMB380_BUS_WRITE_FUNC(p_smb380->dev_addr, SMB380_EE_W__REG, &data, 1);

    return comres;
}







int smb380_get_offset(unsigned char xyz, unsigned short *offset)
{

   int comres;
   unsigned char data;
   if (p_smb380==0)
        return E_SMB_NULL_PTR;
   comres = p_smb380->SMB380_BUS_READ_FUNC(p_smb380->dev_addr, (SMB380_OFFSET_X_LSB__REG+xyz), &data, 1);
   data = SMB380_GET_BITSLICE(data, SMB380_OFFSET_X_LSB);
   *offset = data;
   comres += p_smb380->SMB380_BUS_READ_FUNC(p_smb380->dev_addr, (SMB380_OFFSET_X_MSB__REG+xyz), &data, 1);
   *offset |= (data<<2);
   return comres;
}








int smb380_set_offset(unsigned char xyz, unsigned short offset)
{

   int comres;
   unsigned char data;
   if (p_smb380==0)
        return E_SMB_NULL_PTR;
   comres = p_smb380->SMB380_BUS_READ_FUNC(p_smb380->dev_addr, (SMB380_OFFSET_X_LSB__REG+xyz), &data, 1);
   data = SMB380_SET_BITSLICE(data, SMB380_OFFSET_X_LSB, offset);
   comres += p_smb380->SMB380_BUS_WRITE_FUNC(p_smb380->dev_addr, (SMB380_OFFSET_X_LSB__REG+xyz), &data, 1);
   data = (offset&0x3ff)>>2;
   comres += p_smb380->SMB380_BUS_WRITE_FUNC(p_smb380->dev_addr, (SMB380_OFFSET_X_MSB__REG+xyz), &data, 1);
   return comres;
}








int smb380_set_offset_eeprom(unsigned char xyz, unsigned short offset)
{

   int comres;
   unsigned char data;
   if (p_smb380==0)
        return E_SMB_NULL_PTR;
   comres = p_smb380->SMB380_BUS_READ_FUNC(p_smb380->dev_addr, (SMB380_OFFSET_X_LSB__REG+xyz), &data, 1);
   data = SMB380_SET_BITSLICE(data, SMB380_OFFSET_X_LSB, offset);
   comres += p_smb380->SMB380_BUS_WRITE_FUNC(p_smb380->dev_addr, (SMB380_EEP_OFFSET+SMB380_OFFSET_X_LSB__REG + xyz), &data, 1);
   p_smb380->delay_msec(34);
   data = (offset&0x3ff)>>2;
   comres += p_smb380->SMB380_BUS_WRITE_FUNC(p_smb380->dev_addr, (SMB380_EEP_OFFSET+ SMB380_OFFSET_X_MSB__REG+xyz), &data, 1);
   p_smb380->delay_msec(34);
   return comres;
}








int smb380_set_ee_w(unsigned char eew)
{
  unsigned char data;
    int comres;
    if (p_smb380==0)
        return E_SMB_NULL_PTR;
  comres = p_smb380->SMB380_BUS_READ_FUNC(p_smb380->dev_addr, SMB380_EE_W__REG,&data, 1);
    data = SMB380_SET_BITSLICE(data, SMB380_EE_W, eew);



    comres += p_smb380->SMB380_BUS_WRITE_FUNC(p_smb380->dev_addr, SMB380_EE_W__REG, &data, 1);

    return comres;
}





int smb380_get_ee_w(unsigned char *eew)
{
    int comres;
    if (p_smb380==0)
        return E_SMB_NULL_PTR;
  comres = p_smb380->SMB380_BUS_READ_FUNC(p_smb380->dev_addr, SMB380_EE_W__REG,eew, 1);
    *eew = SMB380_GET_BITSLICE(*eew, SMB380_EE_W);
    return comres;
}








int smb380_write_ee(unsigned char addr, unsigned char data)
{
    int comres;
    if (p_smb380==0)            
        return E_SMB_NULL_PTR;
    if (p_smb380->delay_msec == 0)
        return E_SMB_NULL_PTR;
    comres = smb380_set_ee_w( SMB380_EE_W_ON );
    addr|=0x20;   
    comres += smb380_write_reg(addr, &data, 1 );
    p_smb380->delay_msec( SMB380_EE_W_DELAY );
    comres += smb380_set_ee_w( SMB380_EE_W_OFF);
    return comres;
}









int smb380_selftest(unsigned char st)
{
    int comres;
    unsigned char data;
    comres = p_smb380->SMB380_BUS_READ_FUNC(p_smb380->dev_addr, SMB380_SELF_TEST__REG, &data, 1);
    data = SMB380_SET_BITSLICE(data, SMB380_SELF_TEST, st);
    comres += p_smb380->SMB380_BUS_WRITE_FUNC(p_smb380->dev_addr, SMB380_SELF_TEST__REG, &data, 1);
    return comres;

}











int smb380_set_range(char range)
{
   int comres = 0;
   unsigned char data;

   if (p_smb380==0)
        return E_SMB_NULL_PTR;

   if (range<3) {
        comres = p_smb380->SMB380_BUS_READ_FUNC(p_smb380->dev_addr, SMB380_RANGE__REG, &data, 1 );
        data = SMB380_SET_BITSLICE(data, SMB380_RANGE, range);
         comres += p_smb380->SMB380_BUS_WRITE_FUNC(p_smb380->dev_addr, SMB380_RANGE__REG, &data, 1);
   }
   return comres;

}








int smb380_get_range(unsigned char *range)
{

    int comres = 0;


    if (p_smb380==0)
        return E_SMB_NULL_PTR;
    comres = p_smb380->SMB380_BUS_READ_FUNC(p_smb380->dev_addr, SMB380_RANGE__REG, range, 1 );

    *range = SMB380_GET_BITSLICE(*range, SMB380_RANGE);

    return comres;

}










int smb380_set_mode(unsigned char mode) {

    int comres=0;
    unsigned char data1, data2;

    if (p_smb380==0)
        return E_SMB_NULL_PTR;

    if (mode<4 && mode!=1) {
        comres = p_smb380->SMB380_BUS_READ_FUNC(p_smb380->dev_addr, SMB380_WAKE_UP__REG, &data1, 1 );
        data1  = SMB380_SET_BITSLICE(data1, SMB380_WAKE_UP, mode);
        comres += p_smb380->SMB380_BUS_READ_FUNC(p_smb380->dev_addr, SMB380_SLEEP__REG, &data2, 1 );
        data2  = SMB380_SET_BITSLICE(data2, SMB380_SLEEP, (mode>>1));
        comres += p_smb380->SMB380_BUS_WRITE_FUNC(p_smb380->dev_addr, SMB380_WAKE_UP__REG, &data1, 1);
        comres += p_smb380->SMB380_BUS_WRITE_FUNC(p_smb380->dev_addr, SMB380_SLEEP__REG, &data2, 1);
        p_smb380->mode = mode;
    }
    return comres;

}

























int smb380_set_bandwidth(char bw)
{
    int comres = 0;
    unsigned char data;


    if (p_smb380==0)
        return E_SMB_NULL_PTR;

    if (bw<8) {

      comres = p_smb380->SMB380_BUS_READ_FUNC(p_smb380->dev_addr, SMB380_BANDWIDTH__REG, &data, 1 );
      data = SMB380_SET_BITSLICE(data, SMB380_BANDWIDTH, bw);
      comres += p_smb380->SMB380_BUS_WRITE_FUNC(p_smb380->dev_addr, SMB380_BANDWIDTH__REG, &data, 1 );

    }
    return comres;


}







int smb380_get_bandwidth(unsigned char *bw) {
    int comres = 1;
    if (p_smb380==0)
        return E_SMB_NULL_PTR;

    comres = p_smb380->SMB380_BUS_READ_FUNC(p_smb380->dev_addr, SMB380_BANDWIDTH__REG, bw, 1 );

    *bw = SMB380_GET_BITSLICE(*bw, SMB380_BANDWIDTH);

    return comres;

}














































































































































































































































































































































































































































































































































































int smb380_read_temperature(unsigned char * temp)
{
    int comres;

    if (p_smb380==0)
        return E_SMB_NULL_PTR;

    comres = p_smb380->SMB380_BUS_READ_FUNC(p_smb380->dev_addr, SMB380_TEMPERATURE__REG, temp, 1);
    return comres;

}






int smb380_read_accel_xyz(smb380acc_t * acc)
{
    int comres;
    unsigned char data[6];


    if (p_smb380==0)
        return E_SMB_NULL_PTR;

    comres = p_smb380->SMB380_BUS_READ_FUNC(p_smb380->dev_addr, SMB380_ACC_X_LSB__REG, &data[0],6);

    acc->x = SMB380_GET_BITSLICE(data[0],SMB380_ACC_X_LSB) | (SMB380_GET_BITSLICE(data[1],SMB380_ACC_X_MSB)<<SMB380_ACC_X_LSB__LEN);
    acc->x = acc->x << (sizeof(short)*8-(SMB380_ACC_X_LSB__LEN+SMB380_ACC_X_MSB__LEN));
    acc->x = acc->x >> (sizeof(short)*8-(SMB380_ACC_X_LSB__LEN+SMB380_ACC_X_MSB__LEN));

    acc->y = SMB380_GET_BITSLICE(data[2],SMB380_ACC_Y_LSB) | (SMB380_GET_BITSLICE(data[3],SMB380_ACC_Y_MSB)<<SMB380_ACC_Y_LSB__LEN);
    acc->y = acc->y << (sizeof(short)*8-(SMB380_ACC_Y_LSB__LEN + SMB380_ACC_Y_MSB__LEN));
    acc->y = acc->y >> (sizeof(short)*8-(SMB380_ACC_Y_LSB__LEN + SMB380_ACC_Y_MSB__LEN));


    acc->z = SMB380_GET_BITSLICE(data[4],SMB380_ACC_Z_LSB);
    acc->z |= (SMB380_GET_BITSLICE(data[5],SMB380_ACC_Z_MSB)<<SMB380_ACC_Z_LSB__LEN);
    acc->z = acc->z << (sizeof(short)*8-(SMB380_ACC_Z_LSB__LEN+SMB380_ACC_Z_MSB__LEN));
    acc->z = acc->z >> (sizeof(short)*8-(SMB380_ACC_Z_LSB__LEN+SMB380_ACC_Z_MSB__LEN));

    return comres;

}







int smb380_get_interrupt_status(unsigned char * ist)
{

    int comres=0;
    if (p_smb380==0)
        return E_SMB_NULL_PTR;
    comres = p_smb380->SMB380_BUS_READ_FUNC(p_smb380->dev_addr, SMB380_STATUS_REG, ist, 1);
    return comres;
}



















































































































































int smb380_pause(int msec)
{
    if (p_smb380==0)
        return E_SMB_NULL_PTR;
    else
      p_smb380->delay_msec(msec);
    return msec;

}










int smb380_read_reg(unsigned char addr, unsigned char *data, unsigned char len)
{

    int comres;
    if (p_smb380==0)
        return E_SMB_NULL_PTR;

    comres = p_smb380->SMB380_BUS_READ_FUNC(p_smb380->dev_addr, addr, data, len);
    return comres;

}







int smb380_write_reg(unsigned char addr, unsigned char *data, unsigned char len)
{

    int comres;

    if (p_smb380==0)
        return E_SMB_NULL_PTR;

    comres = p_smb380->SMB380_BUS_WRITE_FUNC(p_smb380->dev_addr, addr, data, len);

    return comres;

}

