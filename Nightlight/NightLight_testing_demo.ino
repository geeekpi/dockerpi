#include <Wire.h>

#define RED 0X00
#define GREEN 0X01
#define BLUE 0X02

#define OFF 0X00
#define TEST 0X15

uint8_t RED_LED[8] = {0X01, 0X04, 0X07, 0X0A, 0X0D, 0X10, 0X13, 0X16};
uint8_t GREEN_LED[8] = {0X02, 0X05, 0X08, 0X0B, 0X0E, 0X11, 0X14, 0X17};
uint8_t BLUE_LED[8] = {0X03, 0X06, 0X09, 0X0C, 0X0F, 0X12, 0X15, 0X18};

uint8_t flag = 0;
uint8_t KEY = 0;

void Write_Byte(uint8_t Adress = 0x15, uint8_t REG_Adress = 0x00, uint8_t Usr_Byte = 0x00) //器件地址(默认0x15)，寄存器地址，用户数据
{
	Wire.beginTransmission(Adress); 
	Wire.write(REG_Adress);
	Wire.write(Usr_Byte);
	Wire.endTransmission(); // stop transmitting
}

void Turn_Led(uint8_t Color, uint8_t Brightness = 0x25)
{
	switch (Color)
	{
	case 0x00:
		for (int i = 0; i < 8; i++)
			Write_Byte(0X15, RED_LED[i], Brightness);
		break; //Turn_On_Led RED;
	case 0x01:
		for (int i = 0; i < 8; i++)
			Write_Byte(0X15, GREEN_LED[i], Brightness);
		break; //Turn_On
		break; //Turn_On_Led GREEN;
	case 0x02:
		for (int i = 0; i < 8; i++)
			Write_Byte(0X15, BLUE_LED[i], Brightness);
		break; //Turn_On
		break; //Turn_On_Led BLUE;
	}
}

uint8_t Read_Key(void)
{
	Wire.beginTransmission(0x15);
	Wire.write(0x19);
	Wire.endTransmission(); // stop transmitting
	Wire.requestFrom(0x15, 1, false);
	if (Wire.available())
	{
		while (Wire.available())
		{
			uint8_t c = Wire.read(); // receive a byte as character

			Wire.beginTransmission(0x15); //将按键寄存器置零
			Wire.write(0x19);
			Wire.write(0x00);
			Wire.endTransmission(); // stop transmitting

			Serial.print("c=0x");   // print the character
			Serial.println(c, HEX); // print the character

			if (c == 0x01)
				return 1;
			else
				return 0;
		}
	}
	else
	{
		return 0;
	}
}

void setup()
{
	Wire.begin();
	Serial.begin(9600);
	Turn_Led(RED,OFF);
	Turn_Led(GREEN,OFF);
	Turn_Led(BLUE,OFF);
  Turn_Led(RED,TEST);
  pinMode(11, INPUT); 
}
void loop()
{ 
  if(digitalRead(11)==HIGH){    //李刚说：如果有个5v没插好就一直亮红灯。
	KEY = Read_Key();
	if (KEY == 1)
		switch (flag)
		{
		case 0x00:
			Turn_Led(RED,OFF);
			Turn_Led(GREEN,TEST);
			flag++;
			break;
		case 0X01:
			Turn_Led(GREEN,OFF);
			Turn_Led(BLUE,TEST);
			flag++;
			break;
		case 0x02:
			Turn_Led(BLUE,OFF);
      Turn_Led(RED,TEST);
			flag++;
			break;
      case 0x03:
      Turn_Led(RED,OFF);
      flag=0;
      break;
		}
	delay(50);
  }
  else {
    Turn_Led(RED, TEST);
    Turn_Led(GREEN, OFF);
    Turn_Led(BLUE, OFF);
  }
}
