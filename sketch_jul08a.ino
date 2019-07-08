long int i;

char condition =0;

int main()
{
    // Init Arduino board

    cli();//stop interrupts

    // Timer1 initialization
    // Assign first registers TCCR1A, -B and counter val. to 0
    TCCR1A = 0; TCCR1B = 0; TCNT1 = 0;
    // set compare match register for 0,5hz increments
    OCR1A = 30637;
    // turn on CTC mode    
    TCCR1B |= (1 << WGM12);
    // Set CS10 and CS12 bits for 1024 prescaler
    TCCR1B |= (1 << CS12) | (1 << CS10);  
    // enable timer compare interrupt
    TIMSK1 |= (1 << OCIE1A);

    
    // Set the pin datadirection in register: 0 is input, 1 is output
    DDRB |= B00000000;
    // Setting port B's pin 5 to output.
    DDRB |= 1<<PB5;

    // Setting the led pin to high state
    // Port pin state control: 0 is LOW, 1 is HIGH
    //PORTB |= 1<<PB5;

    sei();//allow interrupts

    // Main loop
    while(1)
    {
      // If true do this
      if(condition){
        // Set pin to HIGH
        PORTB |= 1<<PB5;
   delay(1000); 
      }
      else{
        // Set pin to LOW
        PORTB &= ~(1<<PB5);
 
      }
    }

    return 0;
}

// Interupt handler for timer1 CTC reg. interrupt vector
ISR(TIMER1_COMPA_vect){
  // Assign condition to be it's negation. True to False, False to True
  condition = !condition;
  TCNT1 = 0;  // Zero the timer
}
