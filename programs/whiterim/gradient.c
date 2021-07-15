/* The gradient demonstration from the kilobotics-labs
 * https://www.kilobotics.com/labs#lab6-gradient
 *
 * The robot with ID 0 is initialized ith the gradient_value 0
 * Every other bot gets the smallest-value-ever-received + 1 as its own value
 * Note that the gradient_value never increases, even if the bots are moved around. 
 * In the simulator one can force a reset by pressing F6, which calls setup() 
 * using the callback mechanism.
 *
 * Lightly modified to work in the simulator, in particular:
 *  - mydata->variable for global variables
 *  - callback function botinfo() to report bot state back to the simulator for display
 *  - callback function json_state() to save bot state as json
 *  - setup() is used as reset callback function 
 *  - we use a table of 10 rainbow colors instead of just 3 colors. 
 *
 *   When a message arrives, it is processed immediately, instead of
 *   storing it as in the original code. In the simulator, storing the message
 *   led to lost messages if two neighbors transmit at once.   
 *
 * Modifications by Fredrik Jansson 2015
 */

#include <kilombo.h>
#include <math.h>
#include "gradient.h" // defines the USERDATA structure

#define STOP 0
#define FORWARD 1
#define LEFT 2
#define RIGHT 3
#define THRESH_LO 300
#define THRESH_HI 600


REGISTER_USERDATA(USERDATA)

// rainbow colors
uint8_t colors[] = {
  RGB(0,0,0),  //0 - off
  RGB(2,0,0),  //1 - red
  RGB(2,1,0),  //2 - orange
  RGB(2,2,0),  //3 - yellow
  RGB(1,2,0),  //4 - yellowish green
  RGB(0,2,0),  //5 - green
  RGB(0,1,1),  //6 - cyan
  RGB(0,0,1),  //7 - blue
  RGB(1,0,1),  //8 - purple
  RGB(3,3,3)   //9  - bright white
};

/*
//  these global variables are defined in the user data structure USERDATA, in gradient.h
uint16_t gradient_value = UINT16_MAX;
uint16_t recvd_gradient = 0;
uint8_t new_message = 0;
message_t msg;
*/
void update_message() {
    // pack one 16-bit integer into two 8-bit integers
    mydata->msg.data[0] = mydata->gradient_value&0xFF;
    mydata->msg.data[1] = (mydata->gradient_value>>8)&0xFF;
    mydata->msg.crc = message_crc(&mydata->msg);
}


void message_rx(message_t *m, distance_measurement_t *d) {
  // mydata->new_message = 1;
  // unpack two 8-bit integers into one 16-bit integer
  // mydata->recvd_gradient = m->data[0]  | (m->data[1]<<8);

  // process the received value immediately, to avoid message collisions.
  // at least in the simulator it is possible that two neighbors transmits in the same time slot
  // and then one message may be lost.
  uint16_t recvd_gradient = m->data[0]  | (m->data[1]<<8);
  if (mydata->gradient_value > recvd_gradient+1)
    {
      mydata->gradient_value = recvd_gradient+1;
      update_message();
    }   
   
}

message_t *message_tx() {
    if (mydata->gradient_value != UINT16_MAX)
        return &mydata->msg;
    else
        return '\0';
}

// Function to sample light
int sample_light() {

  int numsamples = 0;
  int sum = 0;

  while (numsamples < 300) {
        int sample = get_ambientlight();
        // printf("sample %d\n", sample);
        if (sample != -1) {
            sum = sum + sample;
            numsamples = numsamples+1;
        }
  }
  return (sum / 300);
}


void setup() {

  spinup_motors();
  mydata->last_state_update = kilo_ticks;
   mydata->turned = 0;
}

void loop1()
{
  mydata->light = sample_light();
  set_color(RGB(1, 0, 0));
  

  if (mydata->light < THRESH_LO) {

    set_motors(kilo_turn_left, kilo_turn_right);
    if (mydata->turn ==0) mydata->turn=1;
    else mydata->turn=0;
  }

  else{
      // set_motion(RIGHT);
    // int r = rand()%2;
    // if (r==0)
      if (mydata->turn==0)
      set_motors(kilo_turn_left, 10);
    else 
      set_motors(10, kilo_turn_right);
  
  }

}

void loop()
{
  mydata->light = sample_light();
  set_color(RGB(0, 1, 1));
  if (mydata->light < THRESH_LO)
     {

    set_motors(kilo_turn_left, kilo_turn_right);

    if (mydata->turn ==0) mydata->turn=1;
    else mydata->turn=0;

    mydata->turned=0;
  }
   else if (kilo_ticks > (mydata->last_state_update + 128))
    {
      mydata->last_state_update = kilo_ticks;

      if (mydata->turned>2){
        set_motors(kilo_turn_left, kilo_turn_right);
        mydata->turned=0;
      }
      else{
        
        mydata->turned+=1;

      if (mydata->turn==0 && mydata->turned<3 )
        set_motors(kilo_turn_left, 0);
      else 
        set_motors(00, kilo_turn_right);

  }
  }


}

#ifdef SIMULATOR
/* provide a text string for the simulator status bar about this bot */
static char botinfo_buffer[10000];
char *botinfo(void)
{
  char *p = botinfo_buffer;
  p += sprintf (p, "ID: %d \n", kilo_uid);
  p += sprintf (p, "Light: %d\n", mydata->light);
  // p += sprintf (p, "last_state_update: %d\n", mydata->last_state_update);
  p += sprintf (p, "turned: %d\n ", mydata->turned);
  
  return botinfo_buffer;
}

int16_t  callback_lighting(double x, double y){

  double r = sqrt(x*x + y*y);
  int value;
  if (r<150) value = 0;
  else value = 500;

  // int value = (int)(0.001*(x*x+y*y));
  // printf ("value %d %g %g %g - ", value,x,y, r);
  return value;
}

#include <jansson.h>
json_t *json_state();

#endif

int main() {
    // initialize hardware
    kilo_init();
    // register message callbacks
    kilo_message_rx = message_rx;
    kilo_message_tx = message_tx;
    // register your program
    kilo_start(setup, loop);

    SET_CALLBACK(botinfo, botinfo);
    SET_CALLBACK(reset, setup);
    SET_CALLBACK(lighting, callback_lighting);
    // SET_CALLBACK(json_state, json_state);
    
    
    return 0;
}
