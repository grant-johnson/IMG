#include <msp430.h>
#include <string.h>
#include "sensor.h"
#include "Adafruit_VC0706.h"
#include <UCA1_uart.h>
#include "LED.h"
#include "IMG.h"
#include "IMG_errors.h"
#include <Error.h>
#include <SDlib.h>


void sensor_init(void){

    //setup UCA1 uart for image communication
    UCA1_init_UART();

    //setup system specific peripherals
    Adafruit_VC0706_init();

    //setup P7.0 for imager on/off
    // Set imager to off to start with (this will save power)
    P7OUT&=BIT0;
    //set pin direction to output
    P7DIR|=BIT0;
    //turn off pull resistor
    P7REN&=BIT0;
    //set pin as GPIO
    P7SEL&=BIT0;
}

void sensor_on(void){
    //power on sensor
    P7OUT|=BIT0;
    //turn power LED on
    LED_on(IMG_PWR_LED);
}

void sensor_off(void){
    //power off sensor
    P7OUT&=~BIT0;
    //turn power LED off
    LED_off(IMG_PWR_LED);
}

int savepic(void){
    uint32_t jpglen;
    int writeCount = 0;
    unsigned char *block;
    int count = 0;
    int nextBlock = IMG_ADDR_START;
    unsigned char* buffer=NULL;
    int resp;
    int bytesToRead;
    
    //get frame length
    jpglen = Adafruit_VC0706_frameLength();
    //check if there is an image available
    if(jpglen == 0){
        printf("Error: No image in buffer\r\n\n");
        return 1;
    }
    
    //get buffer
    block = BUS_get_buffer(CTL_TIMEOUT_DELAY,1000);
    //check if timeout expired
    if(block==NULL){
        printf("Error : buffer busy\r\n");
        return 2;
    }
    
    while(jpglen > 0){
        //check if there is less than 64 bytes
        if (jpglen < 64){
            //if yes read all bytes
            bytesToRead = jpglen;
        }else{
            //otherwise read 64 bytes
            bytesToRead = 64;
        }
        //get data from sensor
        buffer = Adafruit_VC0706_readPicture(bytesToRead);
        //check for errors
        if(buffer==NULL){
            printf("Error Reading image data. aborting image transfer\r\n");
            report_error(ERR_LEV_ERROR,ERR_IMG,ERR_IMG_READPIC,0);
            BUS_free_buffer();
            return 3;
        }
        //copy into buffer
        memcpy(block + count*64, buffer, 64); count++;
        
        //check if block if full
        if (count >= 8){
            //reset count
            count = 0;
            //write block to SD card
            resp = mmcWriteBlock(nextBlock++, block);
            //check for errors
            if(resp != MMC_SUCCESS){
                report_error(ERR_LEV_ERROR,ERR_IMG,ERR_IMG_SD_CARD_WRITE,resp);
                //free buffer
                BUS_free_buffer();
                //error encountered, abort image store
                return 4;
            }
        }
        //print progress dots
        if(++writeCount >= 64){
            printf(".");
            writeCount = 0;
        }
        //subtract bytes read from total
        jpglen -= bytesToRead;
    }
    //check if there is data in the block
    if (count != 0){
        //write block
        mmcWriteBlock(nextBlock++, block);
        //check for error
        if(resp != MMC_SUCCESS){
            report_error(ERR_LEV_ERROR,ERR_IMG,ERR_IMG_SD_CARD_WRITE,resp);
            //free buffer
            BUS_free_buffer();
            return 5;
        }
    }
    BUS_free_buffer();
    printf("\r\nDone writing image to SD card.\r\n""Memory blocks used: %i\r\n",(nextBlock-1));
    return 0;
}

