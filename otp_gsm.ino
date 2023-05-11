#include<Keypad.h>
#include <Password.h>
// include the library code:
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
  SoftwareSerial ser(11, 12);
char val;
int x = 0;
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
//initialize password to 1234
//you can change here for new password
long otp;
long otp1;
Password password = Password("0000");
int timesTosend = 1;

int count2 = 0;
byte maxPasswordLength = 4;
byte currentPasswordLength = 0;
const byte ROWS = 4;  // Four rows
const byte COLS = 4;  // Four columns
int s = 0;
//Define the keymap
char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};
char buf1[16];
String strotp;
//char otp[4];
/*char keys[ROWS][COLS] = {
{'D','#','0','*'},
{'C','9','8','7'},
{'B','6','5','4'},
{'A','3','2','1'}
};*/

//// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { 6, 7, 8, 9 };  //connect to row pinouts

// Connect keypad COL0, COL1, COL2 and COL3 to these Arduino pins.
byte colPins[COLS] = { 2, 3, 4, 5 };  //connect to column pinouts

// Create the Keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {

  Serial.begin(9600);
  ser.begin(9600);
  delay(500);
  ser.println("AT+CMGF=1");  //set GSM to text mode
  delay(500);
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Face Recog.");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("F: N");
}

void loop() {

  if (Serial.available() > 0) {
    val = Serial.read();
    if (val == 'A' && x == 0) {
      x = 1;
      lcd.setCursor(0, 0);
      lcd.print("F: Y");
    } else {
      lcd.setCursor(0, 0);
      lcd.print("F: N");
    }
  }
  //ser.println(otp1);
  char key = keypad.getKey();

  if (key != NO_KEY) {

    // Serial.println(key);
    delay(60);
    switch (key) {

        //    case '*':  break;


      default: processNumberKey(key);
    }
  }
  if (x == 1) {
    //  x=0;
    otp = random(1, 4);
    otp1 = otp;
    Serial.print(" generated opt is: ");
    Serial.println(otp);
    lcd.setCursor(0, 1);
    lcd.print("Sending OTP");
    switch (otp) {
      case 1:
        password = Password("2347");
        ser.println("AT+CMGF=1");  //set GSM to text mode
        delay(200);
        //  count2=0;
        while (count2 < timesTosend) {
          delay(1500);
          ser.print("AT+CMGS=\"");
          ser.print("9999999999");// enter users mobile number here
          ser.println("\"");
          while (ser.read() != '>')
            ;
          {
            ser.println("Otp is: 2347 ");

            //SMS body
            delay(500);
            //SMS body

            ser.write(0x1A);  // sends ctrl+z end of message
            ser.write(0x0D);  // Carriage Return in Hex
            ser.write(0x0A);  // Line feed in Hex

            //The 0D0A pair of characters is the signal for the end of a line and beginning of another.
            delay(5000);
          }
          count2++;
        }
        break;
      case 2:
        password = Password("9571");
        // count2=0;
        while (count2 < timesTosend) {
          delay(1500);
          ser.print("AT+CMGS=\"");
          ser.print("9999999999");
          ser.println("\"");
          while (ser.read() != '>')
            ;
          {
            ser.println("Otp is: 9571 ");

            //SMS body
            delay(500);
            //SMS body

            ser.write(0x1A);  // sends ctrl+z end of message
            ser.write(0x0D);  // Carriage Return in Hex
            ser.write(0x0A);  // Line feed in Hex

            //The 0D0A pair of characters is the signal for the end of a line and beginning of another.
            delay(5000);
          }
          count2++;
        }
        break;
      case 3:
        password = Password("6698");
        // count2=0;
        while (count2 < timesTosend) {
          delay(1500);
          ser.print("AT+CMGS=\"");
          ser.print("9999999999");
          ser.println("\"");
          while (ser.read() != '>')
            ;
          {
            ser.println("Otp is: 6698 ");

            //SMS body
            delay(500);
            //SMS body

            ser.write(0x1A);  // sends ctrl+z end of message
            ser.write(0x0D);  // Carriage Return in Hex
            ser.write(0x0A);  // Line feed in Hex

            //The 0D0A pair of characters is the signal for the end of a line and beginning of another.
            delay(5000);
          }
          count2++;
        }

        break;
      case 4:
        password = Password("9989");
        // count2=0;
        while (count2 < timesTosend) {
          delay(1500);
          ser.print("AT+CMGS=\"");
          ser.print("9999999999");
          ser.println("\"");
          while (ser.read() != '>')
            ;
          {
            ser.println("Otp is: 9989 ");

            //SMS body
            delay(500);
            //SMS body

            ser.write(0x1A);  // sends ctrl+z end of message
            ser.write(0x0D);  // Carriage Return in Hex
            ser.write(0x0A);  // Line feed in Hex

            //The 0D0A pair of characters is the signal for the end of a line and beginning of another.
            delay(5000);
          }
          count2++;
        }
        break;
    }
    Serial.println(" Sent");
    lcd.setCursor(0, 1);
    lcd.print("Sent         ");
    delay(3000);
    lcd.setCursor(0, 1);
    lcd.print("Enter OTP         ");
    delay(1000);
    x = 2;
  }
}

void processNumberKey(char key) {

  Serial.print(key);

  currentPasswordLength++;
  password.append(key);

  if (currentPasswordLength == maxPasswordLength) {

    checkPassword();
  }
}

void checkPassword() {
  if (password.evaluate()) {
    Serial.println("   OK.");
    lcd.setCursor(0, 1);
    lcd.print("Ok           ");
    s = 0;
    digitalWrite(10, LOW);
    delay(3000);
    digitalWrite(10, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("             ");



  } else {
    lcd.setCursor(0, 1);
    lcd.print("Wrong           ");
    Serial.println(" Wrong password!");



    delay(3000);

    lcd.setCursor(0, 1);
    lcd.print("                ");
  }
  resetPassword();
}

void resetPassword() {
  password.reset();
  currentPasswordLength = 0;
}
