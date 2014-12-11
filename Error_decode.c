#include <Error.h>
#include "IMG_errors.h"
#include <stdio.h>
#include <string.h>
#include <ARCbus.h>
#include <SDlib.h>

//decode errors from ACDS system
char *err_decode(char buf[150], unsigned short source,int err, unsigned short argument){
  switch(source){
    case ERR_SRC_CMD:
      switch(err){
        case CMD_ERR_RESET:
          return "Command Line : Reset Command reset";  
      }
    break;

    case ERR_IMG:
      switch(err){
        case ERR_IMG_SD_CARD_WRITE:
          sprintf(buf, "IMG : Error writing to SD card, %s (%i)",SD_error_str(argument),argument);
          return buf;
        case ERR_IMG_SD_CARD_READ:
          sprintf(buf, "IMG : Error reading from SD card, %s (%i)",SD_error_str(argument),argument);
          return buf;
        case ERR_IMG_SD_CARD_INIT:
          sprintf(buf, "IMG : SD card not initialized, %s (%i)",SD_error_str(argument),argument);
          return buf;
        case ERR_IMG_TX:
          sprintf(buf, "IMG : Error transmitting packet, %s (%i)",BUS_error_str(argument),argument);
          return buf;
        case ERR_IMG_TAKEPIC:
          return "IMG : Error taking picture";
        case ERR_IMG_READPIC:
          return "IMG : Error reading picture data from camera";
        case ERR_IMG_PICSIZE:
          return "IMG : Adafruit_VC0706_frameLength returned zero";
      }
    break; 
  }
  sprintf(buf,"source = %i, error = %i, argument = %i",source,err,argument);
  return buf;
}
