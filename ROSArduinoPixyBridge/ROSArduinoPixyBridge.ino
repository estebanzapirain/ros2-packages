/*********************************************************************
 *  ROSArduinoPixyBridge

    A simple serial interface to communicate to Pixy-CMUCam5, which 
    provides embedded object recognition through color signature.   
    https://pixycam.com/pixy-cmucam5/

    Author: Esteban Zapirain 

    Inspired and modeled after ROS Arduino Bridge by Patrick Goebel
    and James Nugen.

    Software License Agreement (BSD License)

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions
    are met:

     * Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.
     * Redistributions in binary form must reproduce the above
       copyright notice, this list of conditions and the following
       disclaimer in the documentation and/or other materials provided
       with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
    FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
    COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
    INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
    BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
    LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
    ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/

/* Serial port baud rate */
#define BAUDRATE     115200

/* Maximum number of block scans per command */
#define MAX_SCANS    5

/*Libraries needed*/
#include <SPI.h>  
#include <Pixy.h>
/* Include definition of serial commands */
#include "commands.h"

/* Variable initialization */

// A pair of varibles to help parse serial commands (thanks Fergs)
int arg = 0;
int index = 0;

// Variable to hold an input character
char chr;

// Variable to hold the current single-character command
char cmd;

// Character arrays to hold the first and second arguments
char argv1[16];
char argv2[16];

// The arguments converted to integers
long arg1;
long arg2;

/* Clear the current command parameters */
void resetCommand() {
  cmd = NULL;
  memset(argv1, 0, sizeof(argv1));
  memset(argv2, 0, sizeof(argv2));
  arg1 = 0;
  arg2 = 0;
  arg = 0;
  index = 0;
}

Pixy pixy; //main PixyCam object

/* Run a command.  Commands are defined in commands.h */
int runCommand() {

  switch(cmd) {
  
  case GET_MAP:  //m
  
    uint16_t blocks = 0;                          // number of blocks detected
    int scan = 0;                                 //scan, up to MAX_SCANS
    while (blocks == 0 && scan < MAX_SCANS){      //if no blocks detected and MAX_SCANS not reached
      blocks = pixy.getBlocks();                  //get blocks
      scan++;                                     //update scan
      if (blocks) //if there are blocks
      {
          for (int j=0; j<blocks; j++)   //print each of them
          {
            pixy.blocks[j].print();
          }
        }
    }  
    break;
  default:
    Serial.println("Invalid Command");
    break;
  }
}

void setup()
{
  Serial.begin(BAUDRATE);
  pixy.init();
}

void loop()
{ 
    while (Serial.available() > 0) {
    
    // Read the next character
    chr = Serial.read();
    
    // Terminate a command with a CR
    if (chr == 13) {
      if (arg == 1) argv1[index] = NULL;
      else if (arg == 2) argv2[index] = NULL;
      runCommand();
      resetCommand();
    }
    // Use spaces to delimit parts of the command
    else if (chr == ' ') {
      // Step through the arguments
      if (arg == 0) arg = 1;
      else if (arg == 1)  {
        argv1[index] = NULL;
        arg = 2;
        index = 0;
      }
      continue;
    }
    else {
      if (arg == 0) {
        // The first arg is the single-letter command
        cmd = chr;
      }
      else if (arg == 1) {
        // Subsequent arguments can be more than one character
        argv1[index] = chr;
        index++;
      }
      else if (arg == 2) {
        argv2[index] = chr;
        index++;
      }
    }
  }
}