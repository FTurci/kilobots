
#ifndef M_PI
#define M_PI 3.141592653589793238462643383279502884197169399375105820974944
#endif


// declare motion variable type
typedef enum {
    STOP,
    FORWARD,
    LEFT,
    RIGHT
} motion_t;

// declare variables

typedef struct 
{
  uint16_t gradient_value;
  uint16_t light;


  uint32_t last_state_update;

  uint16_t turn;
   uint16_t turned;
  uint16_t recvd_gradient;
  uint8_t new_message;

  message_t msg;
 
} USERDATA;

extern USERDATA *mydata;

