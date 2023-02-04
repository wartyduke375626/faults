// digital pin 8 -- LED
#define ledReg(reg) reg ## B
static const uint8_t ledBit       = 0;
static const uint8_t ledPinIoAddr = _SFR_IO_ADDR(ledReg(PIN));

// digital pin 12 -- 1-wire
#define owReg(reg) reg ## B
static const uint8_t owBit       = 4;
static const uint8_t owPinIoAddr = _SFR_IO_ADDR(owReg(PIN));

static const uint8_t inv[256] = {
  0, 25, 50, 43, 100, 125, 86, 79, 200, 209, 250, 227, 172, 181, 158,
  135, 137, 144, 187, 162, 237, 244, 223, 198, 65, 88, 115, 106, 37,
  60, 23, 14, 11, 18, 57, 32, 111, 118, 93, 68, 195, 218, 241, 232,
  167, 190, 149, 140, 130, 155, 176, 169, 230, 255, 212, 205, 74, 83,
  120, 97, 46, 55, 28, 5, 22, 15, 36, 61, 114, 107, 64, 89, 222, 199,
  236, 245, 186, 163, 136, 145, 159, 134, 173, 180, 251, 226, 201, 208,
  87, 78, 101, 124, 51, 42, 1, 24, 29, 4, 47, 54, 121, 96, 75, 82, 213,
  204, 231, 254, 177, 168, 131, 154, 148, 141, 166, 191, 240, 233, 194,
  219, 92, 69, 110, 119, 56, 33, 10, 19, 44, 53, 30, 7, 72, 81, 122,
  99, 228, 253, 214, 207, 128, 153, 178, 171, 165, 188, 151, 142, 193,
  216, 243, 234, 109, 116, 95, 70, 9, 16, 59, 34, 39, 62, 21, 12, 67,
  90, 113, 104, 239, 246, 221, 196, 139, 146, 185, 160, 174, 183, 156,
  133, 202, 211, 248, 225, 102, 127, 84, 77, 2, 27, 48, 41, 58, 35, 8,
  17, 94, 71, 108, 117, 242, 235, 192, 217, 150, 143, 164, 189, 179,
  170, 129, 152, 215, 206, 229, 252, 123, 98, 73, 80, 31, 6, 45, 52,
  49, 40, 3, 26, 85, 76, 103, 126, 249, 224, 203, 210, 157, 132, 175,
  182, 184, 161, 138, 147, 220, 197, 238, 247, 112, 105, 66, 91, 20,
  13, 38, 63
};

// DELTA v mikrosekundach (cas potrebny na porovnanie jedneho bytu)
#define DELTA 1350

#define ledPinModeInput()     ledReg(DDR)  &= ~_BV(ledBit);
#define ledDigitalWriteLow()  ledReg(PORT) &= ~_BV(ledBit);
#define ledDigitalReadValue() (ledReg(PIN) &   _BV(ledBit))

#define pinModeOutput()    owReg(DDR)  |=  _BV(owBit);
#define pinModeInput()     owReg(DDR)  &= ~_BV(owBit);
#define digitalWriteHigh() owReg(PORT) |=  _BV(owBit);
#define digitalWriteLow()  owReg(PORT) &= ~_BV(owBit);
#define digitalReadValue() (owReg(PIN) &   _BV(owBit))

#define loop_until_bit_is_clear(port_IO_addr, bit_no) \
  asm volatile (                     \
                                     "start_%=:"             "\n\t" \
                                     "sbic %[addr], %[bitn]" "\n\t" \
                                     "rjmp start_%="         "\n\t" \
                                     : /* no outputs */             \
                                     : [addr] "I" (port_IO_addr),   \
                                     [bitn] "I" (bit_no)          \
               )

#define loop_until_bit_is_set(port_IO_addr, bit_no) \
  asm volatile (                     \
                                     "start_%=:"             "\n\t" \
                                     "sbis %[addr], %[bitn]" "\n\t" \
                                     "rjmp start_%="         "\n\t" \
                                     : /* no outputs */             \
                                     : [addr] "I" (port_IO_addr),   \
                                     [bitn] "I" (bit_no)          \
               )

#define count16_until_bit_is_set(port_IO_addr, bit_no, count) \
  asm volatile (                  \
                                  "cli"                   "\n\t" /* Cycles: 1 */ \
                                  "ldi  %A[count], 0x00"  "\n\t" /* Cycles: 1 */ \
                                  "ldi  %B[count], 0x00"  "\n\t" /* Cycles: 1 */ \
                                  "start_%=:"             "\n\t"                 \
                                  "subi %A[count], 0xFF"  "\n\t" /* Cycles: 1 */ \
                                  "sbci %B[count], 0xFF"  "\n\t" /* Cycles: 1 */ \
                                  "sbis %[addr], %[bitn]" "\n\t" /* Cycles: 1 (no skip) *//* Cycles: 2 (skip 1 word) */ \
                                  "rjmp start_%="         "\n\t" /* Cycles: 2 *//* Words: 1 (2 bytes) */ \
                                  "sei"                   "\n\t" /* Cycles: 1 */ \
                                  : [count] "=d" (count)       \
                                  : "0" (count),               \
                                  [addr] "I" (port_IO_addr), \
                                  [bitn] "I" (bit_no)        \
               )

#define count16_to_us(count) ( (3 + 5 * (count)) / (F_CPU / 1000000UL) )
#define us_to_count16(us)    ( ((F_CPU / 1000000UL) * (us) - 3) / 5 )

#define count32_until_bit_is_set(port_IO_addr, bit_no, count) \
  asm volatile (                  \
                                  "cli"                   "\n\t" /* Cycles: 1 */ \
                                  "ldi  %A[count], 0x00"  "\n\t" /* Cycles: 1 */ \
                                  "ldi  %B[count], 0x00"  "\n\t" /* Cycles: 1 */ \
                                  "ldi  %C[count], 0x00"  "\n\t" /* Cycles: 1 */ \
                                  "ldi  %D[count], 0x00"  "\n\t" /* Cycles: 1 */ \
                                  "start_%=:"             "\n\t"                 \
                                  "subi %A[count], 0xFF"  "\n\t" /* Cycles: 1 */ \
                                  "sbci %B[count], 0xFF"  "\n\t" /* Cycles: 1 */ \
                                  "sbci %C[count], 0xFF"  "\n\t" /* Cycles: 1 */ \
                                  "sbci %D[count], 0xFF"  "\n\t" /* Cycles: 1 */ \
                                  "sbis %[addr], %[bitn]" "\n\t" /* Cycles: 1 (no skip) *//* Cycles: 2 (skip 1 word) */ \
                                  "rjmp start_%="         "\n\t" /* Cycles: 2 *//* Words: 1 (2 bytes) */ \
                                  "sei"                   "\n\t" /* Cycles: 1 */ \
                                  : [count] "=d" (count)       \
                                  : "0" (count),               \
                                  [addr] "I" (port_IO_addr), \
                                  [bitn] "I" (bit_no)        \
               )

#define count32_to_us(count) ( (5 + 7 * (count)) / (F_CPU / 1000000UL) )
#define us_to_count32(us)    ( ((F_CPU / 1000000UL) * (us) - 5) / 7 )

void printHex(byte x)
{
  Serial.print( x / 16, HEX );
  Serial.print( x % 16, HEX );
  Serial.print(' ');
}

// Dallas Semiconductor 8 bit CRC
uint8_t crc8( const uint8_t *addr)
{
  uint8_t len = 8;
  addr = addr + 7;

  uint8_t crc = 0;
  while (len--)
  {
    uint8_t inbyte = *addr--;
    for (uint8_t i = 8; i; i--)
    {
      uint8_t mix = (crc ^ inbyte) & 0x01;
      crc >>= 1;
      if (mix) crc ^= 0x8C;
      inbyte >>= 1;
    }
  }
  return crc;
}

void setup() {
  Serial.begin(115200);

  Serial.print("running at ");
  Serial.print(F_CPU / 1000000.0);
  Serial.println(" MHz");

  if ( F_CPU % 1000000UL != 0 )
    Serial.println("Error: count_to_us and us_to_count assumes CPU freq. is multiply of 10^6");

  Serial.print("using bit ");
  Serial.print(owBit);
  Serial.print(" of IO pin ");
  Serial.println(owPinIoAddr);

  pinModeInput();
  digitalWriteLow();
  // disable pull-up and prepare for logical 0 output
  // we never write logical 1 to output, instead we use
  // Hi-Z state and external pull-up from master

  ledPinModeInput();
  ledDigitalWriteLow();  // disable pull-up
}

// http://www.maximintegrated.com/products/ibutton/ibuttons/standard.pdf

inline void wait_for_reset_pulse()
{ // page 38
  uint16_t count;
  do {
    // wait for falling edge
    loop_until_bit_is_clear(owPinIoAddr, owBit);
    // measure duration of pulse
    count16_until_bit_is_set(owPinIoAddr, owBit, count);
  }
  while ( count < us_to_count16(900) );
  // reset pulse tRSTL minimum 480 us maximum 960 us
  // brana dava cca 1100 us
}

inline void send_presence_pulse()
{ // page 38
  pinModeOutput();
  // transmits the Presence Pulse (tPDL, 60 us - 240 us)
  delayMicroseconds(150);
  pinModeInput();
  loop_until_bit_is_set(owPinIoAddr, owBit);
}

inline uint8_t receive_bit()
{ // page 36 - 37
  uint16_t count;

  cli();
  // wait for falling edge
  loop_until_bit_is_clear(owPinIoAddr, owBit);

  // measure duration of pulse
  count16_until_bit_is_set(owPinIoAddr, owBit, count);
  sei();

  // for 1 the line will be down for tLOW1 ( 1 us -  15 us)
  // for 0 the line will be down for tLOW0 (60 us - 120 us)
  // so test somewhere between 15 us - 60 us

  if ( count > us_to_count16(200) )
  { // too long, maybe this was reset pulse!
    return 2;
  }

  // whole cycle (from falling to raising edge) for any bit should take at most tSLOT (60 us - 120 us)
  // after raising edge there is at least tREC (1 us) recovery delay before anything else

  if ( count < us_to_count16(40) )
    return 1;
  else
    return 0;

  // if zero is received, do not forget to wait for line to raise
}

inline uint8_t receive_command()
{ // page 50 (command processing and bit sequence)
  // waiting for a command (represented as 8 bits sent down the one-wire)
  uint8_t cmd = 0;
  uint8_t bits_to_receive = 8;
  uint8_t val;
  do {
    cmd >>= 1; // prepare space for next bit

    loop_until_bit_is_set(owPinIoAddr, owBit);

    val = receive_bit();
    if ( val == 2 ) return 0xFF;
    if ( val == 1 )
      cmd |= 1 << 7; // read 1
    // else read 0 - no modification to cmd is required

    bits_to_receive--;
  } while ( bits_to_receive != 0 );

  return cmd;
}

// tRDV  (Read Data Valid) (max 15 us)
// tLOWR (Read Low Time)   (1 - 15 us)
// the master sampling windows is between tLOWR and tRDV
// for sending 0 pull the data line low for tRDV asap after falling edge
// the master should sample as close to tRDV as possible (to compensate for the cable capacitance)

inline void send_one()
{ // page 37
  cli();
  loop_until_bit_is_clear(owPinIoAddr, owBit);
  sei();

  // send one (nothing to do, just wait for pull-up to raise the line)

  // wait for the line to raise
  cli();
  loop_until_bit_is_set(owPinIoAddr, owBit);
  sei();
}

inline void send_zero()
{ // page 37
  cli();
  loop_until_bit_is_clear(owPinIoAddr, owBit);
  sei();

  pinModeOutput();
  delayMicroseconds(34); // wait for master to sample the line
  // we can pull-down the line for tRELEASE = 15 us (0 - 45 us) after tRDV
  pinModeInput();

  // wait for the line to raise
  cli();
  loop_until_bit_is_set(owPinIoAddr, owBit);
  sei();
}

uint32_t testSerial(const uint8_t serial[8])
{
  uint8_t buf;
  do {
    wait_for_reset_pulse();
    do {
      // after detecting the rising edge (the end of reset) wait (tPDH, 15 us - 60 us)
      delayMicroseconds(27); // page 38
      send_presence_pulse();
      buf = receive_command();
    } while (buf == 0xFF);
  } while ( buf != 0x33 ); // the read ROM  command is 33 hex

  // wait for the line to raise if MSB of command is zero
  loop_until_bit_is_set(owPinIoAddr, owBit);

  uint8_t mask;
  uint8_t iter = 8;
  do {
    iter--; // we are processing iter byte of serial
    buf = serial[iter];
    mask = 1;
    do { // we are processing mask bit of iter byte of serial number (now in buf)
      if ( (uint8_t)(buf & mask) )
        send_one();  // serial bit is one
      else
        send_zero(); // serial bit is zero
      mask <<= 1;
    } while ( mask != 0 );
  } while ( iter != 0 );

  uint32_t count;
  count32_until_bit_is_set(ledPinIoAddr, ledBit, count);
  return count;
}

// crc fix_this x5 x4 x3 x2 x1 x0
void fixCRC(uint8_t *addr)
{
  uint8_t tmp = inv[*addr];
  uint8_t len = 6;
  addr = addr + 7;

  uint8_t crc = 0;
  while (len--)
  {
    uint8_t inbyte = *addr--;
    for (uint8_t i = 8; i; i--)
    {
      uint8_t mix = (crc ^ inbyte) & 0x01;
      crc >>= 1;
      if (mix) crc ^= 0x8C;
      inbyte >>= 1;
    }
  }
  *addr = tmp ^ crc;
}

bool calibrate(uint8_t serial[8], const int x, uint32_t *base_count, uint32_t *blink_count, bool *blink_too_close)
{
  int i, k;
  uint32_t count;
  uint32_t data[11];

  Serial.print("Calibrating ");

  serial[7 - x] = 0x00;
  // 0x00 moze byt na tomto mieste sucastou kluca. V tom pripade nameriame cas pre spravnu odpoved.
  // Predpokladame vsak, ze nejaka hodnota bude aj nespravna (splnene ak napr. < 256 klucov).
  // Potom pri zisteny zmeny +-DELTA zistime, ci je 0x00 spravna alebo nespravna volba.
  // Toto ale nezafunguje, ak kluc 00 37 00 00 00 00 00 01 otvara branu (brana sa sice otvori ale zle sa nakalibrujeme).
  fixCRC(serial);

  for (i = 0; i < 11; i++)
  {
    data[i] = testSerial(serial);
    Serial.print('.');
  }

  // dve najvacsie hodnoty dame na koniec
  for (k = 0; k < 2; k++)
    for (i = 0; i < 10; i++)
      if (data[i] > data[i + 1])
      {
        count = data[i];
        data[i] = data[i + 1];
        data[i + 1] = count;
      }

  count = 0;
  for (i = 0; i < 9; i++) count += data[i];
  count /= 9;

  *base_count = count;
  *blink_count = (data[10] + count + us_to_count32(DELTA)) / 2;

  count += us_to_count32(DELTA / 2);
  k = 0;
  bool ok = true;
  for (i = 0; i < 10; i++)
  {
    if (data[i] <= *blink_count) // ak to nie je blink
      if (data[i] > count) k++; // tak to nesmie byt nad DELTA / 2
    ok = ok && (data[i] > 0);
  }

  // kalibracia je uspesna, ked ziadny cas nebol nulovy
  ok = ok && (k < 1); // a vsetky hodnoty okrem blinku <= base_count + DELTA / 2

  *blink_too_close = *blink_count <= *base_count + us_to_count32(DELTA);
  if (*blink_too_close)
  { // ak blink_count nie je dost daleko na to, aby sa spolahliho odlisil od potencialneho predlzenia odpovede
    // tak ho umelo zdvyhneme (aby sme mohli detegovat otvorenie brany) a pouzijeme alternativny pomalsi sposob prehladavania
    *blink_count = *base_count + 2 * us_to_count32(DELTA);
  }

  if (ok)
  {
    Serial.print(" done. ");
  }
  else
  {
    Serial.println(" failed.");
    for (i = 0; i < 11; i++)
      Serial.println(count32_to_us(data[i]));
  }

  Serial.print("Base: ");
  Serial.print(count32_to_us(*base_count));
  Serial.print(", blink: ");
  Serial.print(count32_to_us(*blink_count));
  Serial.print(", blink - base: ");
  Serial.print(count32_to_us(*blink_count - *base_count));
  Serial.print(", max: ");
  Serial.print(count32_to_us(data[10]));
  Serial.println(" us.");
  if (*blink_too_close)
    Serial.println("Blink too close. Fixed by using slower alternative search.");

  return ok;
}

#define NOT_FOUND 1
#define PARTIAL_FOUND 2
#define TOTAL_FOUND 3

uint8_t findval(uint8_t serial[8], const int x)
{
  int i;
  uint32_t count;
  uint32_t base_count;
  uint32_t blink_count;
  bool blink_too_close;
  bool blink_conflict = !calibrate(serial, x, &base_count, &blink_count, &blink_too_close);

  if (blink_conflict) die();

  char hex[] = "0123456789ABCDEF";
  Serial.print(' ');
  for (i = 0; i < 16; i++)
  {
    Serial.print(' ');
    Serial.print(hex[i]);
  }
  Serial.println();

  Serial.print("0 *"); // for skipped 0x00
  for (i = 1; i < 256; i++)
  {
    if (i % 16 == 0)
    {
      Serial.println();
      Serial.print(hex[i / 16]);
    }

    serial[7 - x] = i;
    fixCRC(serial);

    // speedup nezafunguje spravne ak x4 == 0
    bool x4speedup = (x == 4) && (serial[1] != 0);
    if (!x4speedup)
      if (blink_too_close)
      {
        uint32_t count1 = testSerial(serial); // at least one of them will be unaffected by blink
        uint32_t count2 = testSerial(serial);
        count = count1 < count2 ? count1 : count2; // the shorter one
      }
      else
      {
        uint8_t retries = 0;
        do {
          count = testSerial(serial);
          retries++;
        } while ((count > blink_count) && (retries < 2));
        // we hit the repeating blink, try again, unless gate is open
      }

    Serial.print(' ');
    if (!x4speedup && (count > base_count + us_to_count32(DELTA / 2)))
    {
      Serial.println('#');
      return count > blink_count ? TOTAL_FOUND : PARTIAL_FOUND;
    }
    else if (!x4speedup && (count < base_count - us_to_count32(DELTA / 2)))
    {
      Serial.println('<');
      serial[7 - x] = i - 1;
      fixCRC(serial);
      return PARTIAL_FOUND;
    }
    else if (!x4speedup && (count > blink_count))
    {
      Serial.println('@');
      return TOTAL_FOUND;
    }
    else if (x4speedup)
    {
      Serial.print('-');
    }
    else
    {
      Serial.print('*');
    }
  }

  Serial.println();
  return NOT_FOUND;
}

void die()
{
  Serial.println("No key found :-(");
  for (;;);
}

void test(uint8_t serial[8], const int x)
{
  int ret = findval(serial, x);
  if (ret == NOT_FOUND) die();

  Serial.println();
  for (int i = 0; i < 8; i++)
    if ((ret != TOTAL_FOUND) && (x == 7) && (i > 0 && i < 7))
      Serial.print("?? ");
    else if ((ret != TOTAL_FOUND) && (x < 5) && (i > 0 && i < 7 - x))
      Serial.print("?? ");
    else
      printHex(serial[i]);
  Serial.println();
  Serial.println();

  if (ret == TOTAL_FOUND)
  {
    Serial.println("Eureka :-D");
    for (;;);
  }
}

// the loop routine runs over and over again forever:
void loop()
{
  // in order as written on iButton
  // CC    SS    SS    SS    SS    SS    SS    FF
  // CC: CRC, SSSSSSSSSSSS: 12 digit hex serial num, FF: family code
  uint8_t serial[] = { 0x3d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 };

  test(serial, 7);
  for (int i = 1; i < 6; i++) test(serial, i);

  // sem by sme sa uz nemali dostat
}
