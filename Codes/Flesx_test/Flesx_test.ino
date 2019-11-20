//#define DEBUG true
#define plotCSV

int flexiForcePin = A0; //analog pin 0
float flexiForceReading = 0;
float Voltage_Reading = 0.0;
float Weight_lbs = 0.0;
float final_Weight_lbs = 0.0;
float final_Weight_kgs = 0.0;
int16_t buf[10] = {0};
float avgValue = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(A0, INPUT);
}

void loop()
{
  avgValue = 0;
  for (int i = 0; i < 10; i++)
  {
    flexiForceReading = analogRead(flexiForcePin);
    Voltage_Reading = (flexiForceReading / 1024) * 4777;
    if (Voltage_Reading <= 3600)
    {
      Weight_lbs = mapfloat(Voltage_Reading, 3600, 0, 20, 0);
    }
    else
      Weight_lbs = mapfloat(Voltage_Reading, 4400, 3600, 100, 20);
    buf[i] = Voltage_Reading;
    buf[i] = Weight_lbs;
    avgValue += buf[i];
    //#ifdef DEBUG
    //    Serial.print(Voltage_Reading);
    //    Serial.print("\t");
    //    Serial.print(buf[i]);
    //    Serial.println("\t");
    //#endif
    delay(10);
  }
  final_Weight_lbs = (avgValue / 10);
  final_Weight_kgs = final_Weight_lbs * 0.45359237;

  //#ifdef DEBUG
  //  Serial.print("\n");
  //  Serial.print(final_Weight_lbs);
  //  Serial.print("\t");
  //  Serial.println(final_Weight_kgs);
  //  Serial.print("\n");
  //#endif

#ifdef plotCSV
  Serial.print(final_Weight_lbs);
  Serial.print(",");
  Serial.println(final_Weight_kgs);
#endif

  delay(0); //just here to slow down the output for easier reading
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
