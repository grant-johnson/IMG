#ifndef __IMG_ERRORS_H
  #define __IMG_ERRORS_H
  #include <commandLib.h>
  
  //error sources for IMAGER
  enum{ERR_IMG=ERR_SRC_CMD+1};
  
  enum{ERR_IMG_SD_CARD_WRITE,ERR_IMG_SD_CARD_READ,ERR_IMG_SD_CARD_INIT,ERR_IMG_TX,ERR_IMG_TAKEPIC,ERR_IMG_READPIC,
       ERR_IMG_PICSIZE,ERR_IMG_BUFFER_BUSY,INFO_IMG_TAKE_PIC,ERR_IMG_LOADPIC_BUFFER,ERR_IMG_READ_START_BLOCK_ID,ERR_IMG_READ_BLOCK_ID,
       ERR_IMG_READ_INVALID_CRC};

  enum{IMG_RET_SUCCESS=0,IMG_RET_ERR_BUFFER_BUSY,IMG_RET_ERR_PICSIZE,IMG_RET_ERR_TAKEPIC,IMG_RET_ERR_READ_PIC_DAT,
       IMG_RET_ERR_SD_CARD_WRITE,IMG_RET_ERR_SD_READ,IMG_RET_BAD_CRC,IMG_RET_BAD_BLK_HEADER,IMG_RET_ERR_IMG_TX};

#endif
  