#include <math.h>
#include "serial.h"
#define PI		3.14159265358
#define DTR 	PI/180.0				   // Conversi degree to radian
#define RTD 	180.0/PI				   // Conversi degree to radian
#define L1	0.3   // link1
#define L2	0.2   // link2

float q1;
float q2;
float dq1 = 0;
float dq2 = 0;
float objx=0.3;
float objy=0.5;
float rv = 0;

float dshi=0;
float shi=0;
float shi_old=0;
float dx = 0;
float dy = 0;
float rx;
float ry;

void init_robot()
{
	q1=0.0 * DTR;
	q2=0.0 * DTR;
	shi = 0.0 * DTR;
	shi_old = shi;
	rx = 0;
	ry = 0;
}

void Retrieve_serial(void) {
  int retval=1, i,j,k,l;

  unsigned char sdata[3]; 
  unsigned char baca;
  
  
	i=1;

  while (i>0) {
    fcntl(fd, F_SETFL, FNDELAY); 
    i=read(fd, &baca, 1);
    if ((i==1) && (baca == 0xF5)) {
    	printf("masuk\n");
    	sdata[0]=baca;
    	while (i<3) {
    		  if (read(fd, &baca, 1)>0) {sdata[i]=baca; i++;}
    	}
   	  printf("terbaca %x  %x  %x \n",sdata[0],sdata[1],sdata[2]);
   	  q1=(sdata[1])*180.0/255.0*DTR;
   	  q2=(sdata[2])*180.0/255.0*DTR;
    }
  } 

}

void jacobian(float &dx, float &dy, float &dshi, float dq2, float dq1, float shi)
{
	dx = 0.025/2.0*cos(shi)*(dq2+dq1);
	dy = 0.025/2.0*sin(shi)*(dq2+dq1);
	dshi = 0.025/0.18*(dq2-dq1);
}

void animate(int k) 
{
  // write your program
  static int oldsensor = 0;
  //int sensor = ((ir1)?-4:0) + ((ir2)?-3:0) + ((ir3)?-2:0) + ((ir4)?-1:0) + ((ir5)?1:0) + ((ir6)?2:0) + ((ir7)?3:0) + ((ir8)?4:0);
  //int adasensor = ir1 + ir2 + ir3 + ir4 + ir5 + ir6 + ir7 + ir8;
  
  jacobian(dx, dy, dshi, dq2, dq1, shi);
  dq2 = 0;
  dq1 = 0;
  shi = 0.025/0.18*(q2-q1) + 0;
  rv = dx*cos(shi) + dy*sin(shi);
  rx = rx + rv*cos((shi+shi_old)/2.0);
  ry = ry + rv*sin((shi+shi_old)/2.0);
  shi_old = shi;
  usleep(10);
  
} 

