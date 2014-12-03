#ifndef __IMG_H
#define __IMG_H
    #include <Error.h>
    #include <ctl.h>

    //flags for events handled by the imager
    enum{IMG_EV_TAKEPIC=(1<<0),IMG_EV_LOADPIC=(1<<1)};

    
    #define IMG_EV_ALL (IMG_EV_TAKEPIC|IMG_EV_LOADPIC)
    
    //define number of image slots
    #define NUM_IMG_SLOTS           (5)
    //define the size of a image slot
    #define IMG_SLOT_SIZE           (100)
    //define address ranges for image data
    enum{IMG_ADDR_START=ERR_ADDR_END+1,IMG_ADDR_END=IMG_ADDR_START+NUM_IMG_SLOTS*IMG_SLOT_SIZE};

    //read and write slots for picture
    extern int readPic,writePic;
    
    //Event set for imager events
    extern CTL_EVENT_SET_t IMG_events;

    void cmd_parse(void *p);
    void sub_events(void *p);
    void img_events(void *p0);  

#endif
    