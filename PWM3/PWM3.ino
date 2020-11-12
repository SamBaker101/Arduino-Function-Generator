
#define PWM_PIN 5            //PWM output at pin5
#define ANALOG_0 A0          //Input for sample_time
#define SWITCH_PIN 2         //Push button to switch waveform

#define PWM_FREQ  980        //Hz
#define N 100

int sine_table[100];
int rsaw_table[100];
int lsaw_table[100];
int triangle_table[100];

volatile int switch_state = LOW;

int table = 0;
/*
 * 0 - Sine
 * 1 - Right Saw
 * 2 - Left Saw
 * 3 - Triangle
 */


int sample_time;

void get_sine_table();
void get_rsaw_table();
void get_lsaw_table();
void get_triangle_table();

void setup() {
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(SWITCH_PIN), switch_pin_ISR, FALLING);
  
  get_sine_table();
  get_rsaw_table();
  get_lsaw_table();
  get_triangle_table();
}

void loop() {
  for (int i = 0; i < N; i++){
    sample_time = analogRead(ANALOG_0);
    sample_time = (sample_time/16)+2;

    switch (table) {
      case 0:
        analogWrite(PWM_PIN, sine_table[i]);
        break;

      case 1:
        analogWrite(PWM_PIN, rsaw_table[i]);
        break;

      case 2:
        analogWrite(PWM_PIN, lsaw_table[i]);
        break;

      case 3:
        analogWrite(PWM_PIN, triangle_table[i]);
        break;


      
      }
      
    delay(sample_time);
  }
}

void switch_pin_ISR(){
  table = (table + 1)%4;
  }

void get_sine_table(){
  for (int i = 0; i < N; i++){
    sine_table[i] = 127+127*sin(i*(2*3.14)/N);
  }
}

void get_rsaw_table(){
  for (int i = 0; i < N; i++){
    rsaw_table[i] = i*(255/N);
  }
}

void get_lsaw_table(){
  for (int i = 0; i < N; i++){
    lsaw_table[i] = 255 - i*(255/N);
  }
}

void get_triangle_table(){
  for (int i = 0; i < N; i++){
    if (i<(N/2)){
      triangle_table[i] = i*(255/(N/2));
      }
    else{
      triangle_table[i] = 255 - (i-N/2)*(255/(N/2));
      }
  }
}
