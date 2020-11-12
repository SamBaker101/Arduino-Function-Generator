
#define PWM_PIN 5            //PWM output at pin5
#define ANALOG_0 A0          //Input for sample_time
#define PWM_FREQ  980        //Hz
#define N 50

int sine_table[50];
int sample_time;
void get_sine_table();

void setup() {
  get_sine_table();
}

void loop() {
  for (int i = 0; i < N; i++){
    sample_time = analogRead(ANALOG_0);
    sample_time = (sample_time/16)+2;
    analogWrite(PWM_PIN, sine_table[i]);
    delay(sample_time);
  }
}

void get_sine_table(){
  for (int i = 0; i < N; i++){
    sine_table[i] = 127+127*sin(i*(2*3.14)/N);
  }
}
