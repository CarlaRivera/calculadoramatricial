/*         UTN-FICA-CIERCOM
             OPTATIVA II
            CARLA RIVERA

            
*Calculadora Matricial

 */
//incluir librerias
#include <Keypad.h>  
#include <LiquidCrystal.h>
//inicializar lcd
LiquidCrystal lcd(0, 1, 2, 3, 4, 5);  //RS,E,D4,D5,D6,D7 
const byte ROWS = 4; //defino tamaño de filas
const byte COLS = 4; //defino tamaño de columnas

char keys [ROWS] [COLS] = {
 
   {'7', '8', '9', '/'},
   {'4', '5', '6', '*'},
   {'1', '2', '3', '-'},
   {'C', '0', '=', '+'}
};
byte rowPins[ROWS] = {13,12,11,10}; //conexion de los pines de salida a las filas de la calculadora
byte colPins[COLS] = {9,8,7,6}; //conexion de los pines de salida a las clumnas del keypad

//inicializar keypad
Keypad myKeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

//variables a utilizar
boolean presentValue = false;
boolean next = false;
boolean final = false;
String num1, num2;
int answer;
char op;

void setup()
{

}

void loop(){
  char key = myKeypad.getKey();

  if (key != NO_KEY && (key=='1'||key=='2'||key=='3'||key=='4'||key=='5'||key=='6'||key=='7'||key=='8'||key=='9'||key=='0'))
  {
    if (presentValue != true)
    {
      num1 = num1 + key;
      int numLength = num1.length();
      lcd.setCursor(15 - numLength, 0); //to adjust one whitespace for operator
      lcd.print(num1);
    }
    else 
    {
      num2 = num2 + key;
      int numLength = num2.length();
      lcd.setCursor(15 - numLength, 1);
      lcd.print(num2);
      final = true;
    }
  }
//escoje la operacion
  else if (presentValue == false && key != NO_KEY && (key == '/' || key == '*' || key == '-' || key == '+'))
  {
    if (presentValue == false)
    {
      presentValue = true;
      op = key;
      lcd.setCursor(15,0);
      lcd.print(op);
    }
  }
//ejecuta la operacion 
  else if (final == true && key != NO_KEY && key == '='){
    if (op == '+'){
      answer = num1.toInt() + num2.toInt();
    }
    else if (op == '-'){
      answer = num1.toInt() - num2.toInt();
    }
    else if (op == '*'){
      answer = num1.toInt() * num2.toInt();
    }
    else if (op == '/'){
      answer = num1.toInt() / num2.toInt();
    }    
    //imprime el resultado de la operacion
      lcd.clear();
      lcd.setCursor(15,0);
      lcd.autoscroll();
      lcd.print(answer);
      lcd.noAutoscroll();
  }
  //en caso de digitar la letra C, regrese al valor inicial
  else if (key != NO_KEY && key == 'C'){
    lcd.clear();
    presentValue = false;
    final = false;
    num1 = "";
    num2 = "";
    answer = 0;
    op = ' ';
  }
}

