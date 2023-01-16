#define F_CPU 9600000

int servo = PB0;  //connect servo to PB0

int led = PB1;

int b;

long angle;

int pwm;

#include <avr/io.h>

void adc_setup (void)

{

  // Set the ADC input to PB2/ADC1

  ADMUX |= (1 << MUX0);

  ADMUX |= (1 << ADLAR);

  // Set the prescaler to clock/128 & enable ADC

  // At 9.6 MHz this is 75 kHz.

  ADCSRA |= (1 << ADPS1) | (1 << ADPS0) | (1 << ADEN);

}

int adc_read (void)

{

  // Start the conversion

  ADCSRA |= (1 << ADSC);

  // Wait for it to finish

  while (ADCSRA & (1 << ADSC));

  return ADCH; // return the value

}

void setup()

{

  pinMode(servo, OUTPUT);  // set servo as output pin

  pinMode(led, OUTPUT);

}

void loop ()

{

    long a;

    adc_setup();

    a = adc_read();  // read the potentiometer value

    angle = (a * 3) / 2; // convert the reading to angle between 0 and 180.

    servoPulse(servo, angle);  // call the servoPulse function.

    b = map(a, 0, 255, 0, 1023);

    analogWrite(led, b);

}

void servoPulse (int servo, int angle)

{

  pwm = (angle * 11) + 500;    // Convert angle to microseconds

  digitalWrite(servo, HIGH);

  digitalWrite(servo, HIGH);

  delayMicroseconds(pwm);

  digitalWrite(servo, LOW);

  delay(50);                   // Refresh cycle of servo

}
