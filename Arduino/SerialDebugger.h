/**
      Version 0.3
      Works only with Arduino Mega at the Moment
      
      TBD: Add support for other Arduino, ESP and other MCU boards
*/      

/*  Arduino Digital I/O Pins to PIN PEGISTER Mappings
 *   'BX' refers to Bit postion in the Register. (MSB)B7-(LSB)B0
 *   
 *   Pin22 PINA B0
 *   Pin23 PINA B1
 *   Pin24 PINA B2
 *   Pin25 PINA B3
 *   Pin26 PINA B4
 *   Pin27 PINA B5
 *   Pin28 PINA B6
 *   Pin29 PINA B7
 *   Pin30 PINC B7
 *   Pin31 PINC B6
 *   Pin32 PINC B5

 *   Pin33 PINC B4
 *   Pin34 PINC B3
 *   Pin35 PINC B2
 *   Pin36 PINC B1
 *   Pin37 PINC B0
 *   Pin38 PIND B7
 *   Pin39 PING B2
 *   Pin40 PING B1
 *   Pin41 PING B0
 *   Pin42 PINL B7
 *   Pin43 PINL B6
 *   Pin44 PINL B5
 *   Pin45 PINL B4
 *   Pin46 PINL B3
 *   Pin47 PINL B2
 *   Pin48 PINL B1
 *   Pin49 PINL B0
 *   Pin50 PINB B3
 *   Pin51 PINB B2
 *   Pin52 PINB B1

 */
#define SZ_DATA_BUFFER 192 /* Debug Message Max Length */
#define DEBUG_TIMER 10000  /* Debug Msg Print Interval */

unsigned long debuggerclock = 0UL ;
char debug_buffer[SZ_DATA_BUFFER];

// const char* msgFmt = "=P%d,%d,%d,%d,%d,%d,%d=I%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d=O%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d=A%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d]" ;
const char* msgFmt = "[,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d" ;

void serialDebugger(Stream* COMX=&Serial, int debug_interval=DEBUG_TIMER)
{
  if( millis() - debuggerclock > debug_interval ) 
  {
     // PWM Output pins D3-D9
     int p[7];
     int j=0;
     for (int i=3; i<=9; i++) {
        p[j]=analogRead(i);
        j++;
     }
  
    // Digital Input pins D22-D32
    int di[11];
    
    di[0]=bitRead(PINA, 0);
    di[1]=bitRead(PINA, 1);
    di[2]=bitRead(PINA, 2);
    di[3]=bitRead(PINA, 3);
    di[4]=bitRead(PINA, 4);
    di[5]=bitRead(PINA, 5);
    di[6]=bitRead(PINA, 6);
    di[7]=bitRead(PINA, 7);
    di[8]=bitRead(PINC, 7);
    di[9]=bitRead(PINC, 6);
   di[10]=bitRead(PINC, 5);

    /*
    j=0;
    for (int i=22; i<=32; i++){
      di[j]=digitalRead(i);
      j++;
    }
    */
    
    // Digital Output pins D33-D52
    int d[20];

    d[0]=bitRead(PINC, 4);
    d[1]=bitRead(PINC, 3);
    d[2]=bitRead(PINC, 2);
    d[3]=bitRead(PINC, 1);
    d[4]=bitRead(PINC, 0);
    d[5]=bitRead(PIND, 7);
    d[6]=bitRead(PING, 2);
    d[7]=bitRead(PING, 1);
    d[8]=bitRead(PING, 0);
    d[9]=bitRead(PINL, 7);
   d[10]=bitRead(PINL, 6);
   d[11]=bitRead(PINL, 5);
   d[12]=bitRead(PINL, 4);
   d[13]=bitRead(PINL, 3);
   d[14]=bitRead(PINL, 2);
   d[15]=bitRead(PINL, 1);
   d[16]=bitRead(PINL, 0);
   d[17]=bitRead(PINB, 3);
   d[18]=bitRead(PINB, 2);
   d[19]=bitRead(PINB, 1);
    
    /*
    j=0;
    for (int i=33; i<=52; i++){
      d[j]=digitalRead(i);
      j++;
    }
    */
      
    // Analog Pins
    int a[16];
    j=0;
    for (int i=0; i<=15; i++){
      a[j]=analogRead(i);
      j++;
    }
    
    memset(debug_buffer, '\0', sizeof(debug_buffer));
    sprintf(debug_buffer, msgFmt, p[0],p[1],p[2],p[3],p[4],p[5],p[6],
                           di[0],di[1],di[2],di[3],di[4],di[5],di[6],di[7],di[8],di[9],di[10],
                           d[0],d[1],d[2],d[3],d[4],d[5],d[6],d[7],d[8],d[9],d[10],d[11],d[12],d[13],d[14],d[15],d[16],d[17],d[18],d[19],
                           a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8],a[9],a[10],a[11],a[12],a[13],a[14],a[15]
    );  
          
    COMX->println(debug_buffer); // serial debug
    debuggerclock = millis() ; // update sysclock
  }
}

