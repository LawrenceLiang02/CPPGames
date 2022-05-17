// C++ code
//
const int switch1 = A0;
const int switch2 = A1;
const int switch3 = A2;
const int switch4 = A3;

const int start_switch = A4;

const int light1 = 5;
const int light2 = 4;
const int light3 = 3;
const int light4 = 2;

const int sequence_size = 4;
int sequence[sequence_size];
int input_sequence[sequence_size];

bool started = false;
const int chances = 3;
int errors = 0;

int error_repetition = 3;

void setup() {
  Serial.begin(9600);
  pinMode(switch1, INPUT);
  pinMode(switch2, INPUT);
  pinMode(switch3, INPUT);
  pinMode(switch4, INPUT);

  pinMode(light1, OUTPUT);
  pinMode(light2, OUTPUT);
  pinMode(light3, OUTPUT);
  pinMode(light4, OUTPUT);

  digitalWrite(light1, LOW);
  digitalWrite(light2, LOW);
  digitalWrite(light3, LOW);
  digitalWrite(light4, LOW);
}

void loop()
{
  if (errors == chances)
  {
     errors = 0;
    error_repetition = 3;
    started = false;
  }
  if (digitalRead(start_switch) == LOW && started == false)
  {
    started = true;    
    Serial.println("my message");
  }
  if (started == true && errors < chances)
  {
    set_sequence();
    get_sequence();
  }
  
  
}

void set_sequence()
{
  randomSeed(millis()); //in this way is really random!!!

  for (int i = 0; i < sequence_size; i++)
  {
    sequence[i] = random(2,6);
  }

  digitalWrite(light1, LOW);
  digitalWrite(light2, LOW);
  digitalWrite(light3, LOW);
  digitalWrite(light4, LOW);

  for (int i = 0; i < sequence_size; i++)
  {
    digitalWrite(sequence[i], HIGH);
    delay(1000);
    digitalWrite(sequence[i], LOW);
    delay(200);
  }
  
}

void get_sequence()
{
  int flag = 0; //this flag indicates if the sequence is correct

  for (int i = 0; i < sequence_size; i++)
  {
    flag = 0;
    while(flag == 0)
    {
      if (digitalRead(switch1) == LOW)
      {
        digitalWrite(light1, HIGH);
        input_sequence[i] = 5;
        flag = 1;
        delay(200);
        if (input_sequence[i] != sequence[i])
        {
          wrong_sequence();
          errors++;
          return;
        }
        digitalWrite(light1, LOW);
       }

      if (digitalRead(switch2) == LOW)
      {
        digitalWrite(light2, HIGH);
        input_sequence[i] = 4;
        flag = 1;
        delay(200);
        if (input_sequence[i] != sequence[i])
        {
          wrong_sequence();
          errors++;
          return;
        }
        digitalWrite(light2, LOW);
       }

      if (digitalRead(switch3) == LOW)
      {
        digitalWrite(light3, HIGH);
        input_sequence[i] = 3;
        flag = 1;
        delay(200);
        if (input_sequence[i] != sequence[i])
        {
          wrong_sequence();
          errors++;
          return;
        }
        digitalWrite(light3, LOW);
      }

      if (digitalRead(switch4) == LOW)
      {
        digitalWrite(light4, HIGH);
        input_sequence[i] = 2;
        flag = 1;
        delay(200);
        if (input_sequence[i] != sequence[i])
        {
          wrong_sequence();
          errors++;
          return;
        }
        digitalWrite(light4, LOW);
      }
   }
    }
  right_sequence();
}

void right_sequence()
{

    digitalWrite(light1, LOW);
    digitalWrite(light2, LOW);
    digitalWrite(light3, LOW);
    digitalWrite(light4, LOW);
    delay(500);

    digitalWrite(light1, HIGH);
    digitalWrite(light2, HIGH);
    digitalWrite(light3, HIGH);
    digitalWrite(light4, HIGH);
  
  delay(500);
    digitalWrite(light1, LOW);
    digitalWrite(light2, LOW);
    digitalWrite(light3, LOW);
    digitalWrite(light4, LOW);
    delay(1000);
}

void wrong_sequence()
{
  for (int i = 0; i < error_repetition; i++)
  {
      digitalWrite(light1, LOW);
      digitalWrite(light2, LOW);
      digitalWrite(light3, LOW);
      digitalWrite(light4, LOW);
      delay(200);
      digitalWrite(light1, HIGH);
      digitalWrite(light2, HIGH);
      digitalWrite(light3, HIGH);
      digitalWrite(light4, HIGH);
      delay(200);
      digitalWrite(light1, LOW);
      digitalWrite(light2, LOW);
      digitalWrite(light3, LOW);
      digitalWrite(light4, LOW);

  }
  error_repetition = error_repetition + 3 ;
  delay(1000);
}
