// This part is processed every 128mS
void data125mSRun()
{
#ifdef DASHBRD_IS_THINGER
  thing.handle();
#endif

  // === ( Measures)  ===

#ifndef A0_IS_NONE  // Smothed A0 Measure
  pinMode(A0, INPUT);
  // Performing 3 reads to get a reliable reading.
  int A0Raw = analogRead(A0);  // 1st read  0...1V = 0 ..1023
  delay(3);
  A0Raw += analogRead(A0);  // 2nd read
  delay(3);
  A0Raw += analogRead(A0);  // 3rd read
  A0Raw = A0Raw / 3;
#endif

}
