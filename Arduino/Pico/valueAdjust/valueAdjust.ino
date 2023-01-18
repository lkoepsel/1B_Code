#include <LibPrintf.h>

const int numValues = 10;

double Lux2048[20] = {   5,  12,  30,  50,  60,  70,  74,  84,  92, 100, 92, 84, 74, 70, 60, 50, 30, 20, 12, 5};
double Lux360[6] ;
void setup()
{
  while (!Serial) { ; }
  Serial.begin(115200);

  for (int k=0; k< 5; k++)
  {
    int m = round (k * (20.0/6));
    Lux360[k] = Lux2048[m];
    printf("The kth value %d of Lux360 is %5.2lf\n", k, Lux360[k]);
  }
}

void loop()
{
}
