#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "MPU6050.h"
#include "Encoder.h"
#include "AD.h"
#include <math.h>

#define BUZZER_GPIO_PORT        GPIOB
#define BUZZER_GPIO_PIN         GPIO_Pin_12
#define LED_GPIO_PORT           GPIOB
#define LED_GPIO_PIN            GPIO_Pin_13
#define KEY_GPIO_PORT           GPIOA
#define KEY_GPIO_PIN            GPIO_Pin_3

#define LIGHT_ALARM_THRESHOLD   1200
#define SAMPLE_PERIOD_MS        100
#define ALARM_ANGLE_MIN         0
#define ALARM_ANGLE_MAX         90
#define ALARM_DELAY_MIN         1
#define ALARM_DELAY_MAX         10

typedef enum
{
	STATE_MONITOR = 0,
	STATE_SET_ANGLE,
	STATE_SET_DELAY
} AppState_t;

static AppState_t State = STATE_MONITOR;
static uint8_t Alarm_Angle = 25;
static uint8_t Alarm_Delay = 3;
static uint16_t OverAngleTicks = 0;

static void Board_IO_Init(void);
static uint8_t Key_GetPress(void);
static int16_t LimitValue(int16_t value, int16_t min, int16_t max);
static uint8_t Calculate_PostureAngle(int16_t ax, int16_t ay, int16_t az);
static void Set_Buzzer(uint8_t on);
static void Set_LED(uint8_t on);
static void Show_Monitor(uint8_t angle, uint16_t light);
static void Show_SetAngle(void);
static void Show_SetDelay(void);
static void Handle_Monitor(void);
static void Handle_SetAngle(void);
static void Handle_SetDelay(void);

int main(void)
{
	OLED_Init();
	MPU6050_Init();
	AD_Init();
	Encoder_Init();
	Board_IO_Init();

	OLED_Clear();
	OLED_ShowString(1, 1, "Posture Monitor");
	OLED_ShowString(2, 1, "System Ready");
	Delay_ms(500);
	OLED_Clear();

	while (1)
	{
		switch (State)
		{
			case STATE_MONITOR:
				Handle_Monitor();
				break;

			case STATE_SET_ANGLE:
				Handle_SetAngle();
				break;

			case STATE_SET_DELAY:
				Handle_SetDelay();
				break;

			default:
				State = STATE_MONITOR;
				break;
		}

		Delay_ms(SAMPLE_PERIOD_MS);
	}
}

static void Board_IO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = BUZZER_GPIO_PIN | LED_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = KEY_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	Set_Buzzer(0);
	Set_LED(0);
}

static uint8_t Key_GetPress(void)
{
	if (GPIO_ReadInputDataBit(KEY_GPIO_PORT, KEY_GPIO_PIN) == 0)
	{
		Delay_ms(20);
		if (GPIO_ReadInputDataBit(KEY_GPIO_PORT, KEY_GPIO_PIN) == 0)
		{
			while (GPIO_ReadInputDataBit(KEY_GPIO_PORT, KEY_GPIO_PIN) == 0);
			Delay_ms(20);
			return 1;
		}
	}

	return 0;
}

static int16_t LimitValue(int16_t value, int16_t min, int16_t max)
{
	if (value < min)
	{
		return min;
	}
	if (value > max)
	{
		return max;
	}
	return value;
}

static uint8_t Calculate_PostureAngle(int16_t ax, int16_t ay, int16_t az)
{
	float x;
	float y;
	float z;
	float angle;

	x = (float)ax;
	y = (float)ay;
	z = (float)az;
	angle = (float)(atan2(fabs(x), sqrt(y * y + z * z)) * 57.29578);

	if (angle > 90.0f)
	{
		angle = 90.0f;
	}

	return (uint8_t)(angle + 0.5f);
}

static void Set_Buzzer(uint8_t on)
{
	GPIO_WriteBit(BUZZER_GPIO_PORT, BUZZER_GPIO_PIN, on ? Bit_RESET : Bit_SET);
}

static void Set_LED(uint8_t on)
{
	GPIO_WriteBit(LED_GPIO_PORT, LED_GPIO_PIN, on ? Bit_RESET : Bit_SET);
}

static void Show_Monitor(uint8_t angle, uint16_t light)
{
	OLED_ShowString(1, 1, "Posture Monitor");

	OLED_ShowString(2, 1, "Angle:");
	OLED_ShowNum(2, 7, angle, 3);
	OLED_ShowString(2, 10, "deg   ");

	OLED_ShowString(3, 1, "Light:");
	OLED_ShowNum(3, 7, light, 4);
	OLED_ShowString(3, 11, "     ");

	OLED_ShowString(4, 1, "Set:");
	OLED_ShowNum(4, 5, Alarm_Angle, 2);
	OLED_ShowString(4, 7, " D:");
	OLED_ShowNum(4, 10, Alarm_Delay, 2);
	OLED_ShowString(4, 12, "s    ");
}

static void Show_SetAngle(void)
{
	OLED_ShowString(1, 1, "Set Angle      ");
	OLED_ShowString(2, 1, "Alarm Angle:");
	OLED_ShowNum(3, 1, Alarm_Angle, 2);
	OLED_ShowString(3, 4, "deg  ");
	OLED_ShowString(4, 1, "Press Next     ");
}

static void Show_SetDelay(void)
{
	OLED_ShowString(1, 1, "Set Delay      ");
	OLED_ShowString(2, 1, "Alarm Delay:");
	OLED_ShowNum(3, 1, Alarm_Delay, 2);
	OLED_ShowString(3, 4, "sec  ");
	OLED_ShowString(4, 1, "Press Back     ");
}

static void Handle_Monitor(void)
{
	uint8_t angle;
	uint16_t light;
	uint16_t alarmTicks;
	int16_t ax, ay, az, gx, gy, gz;

	MPU6050_GetData(&ax, &ay, &az, &gx, &gy, &gz);
	angle = Calculate_PostureAngle(ax, ay, az);
	light = AD_GetValue();
	Encoder_GetDiff();
	alarmTicks = (uint16_t)Alarm_Delay * (1000 / SAMPLE_PERIOD_MS);

	if (angle > Alarm_Angle)
	{
		if (OverAngleTicks < alarmTicks)
		{
			OverAngleTicks ++;
		}
	}
	else
	{
		OverAngleTicks = 0;
	}

	Set_Buzzer(OverAngleTicks >= alarmTicks);
	Set_LED(light < LIGHT_ALARM_THRESHOLD);
	Show_Monitor(angle, light);

	if (Key_GetPress())
	{
		Set_Buzzer(0);
		Set_LED(0);
		Encoder_GetDiff();
		OLED_Clear();
		State = STATE_SET_ANGLE;
	}
}

static void Handle_SetAngle(void)
{
	int16_t diff;

	diff = Encoder_GetDiff();
	if (diff != 0)
	{
		Alarm_Angle = (uint8_t)LimitValue((int16_t)Alarm_Angle + diff, ALARM_ANGLE_MIN, ALARM_ANGLE_MAX);
	}

	Show_SetAngle();

	if (Key_GetPress())
	{
		Encoder_GetDiff();
		OLED_Clear();
		State = STATE_SET_DELAY;
	}
}

static void Handle_SetDelay(void)
{
	int16_t diff;

	diff = Encoder_GetDiff();
	if (diff != 0)
	{
		Alarm_Delay = (uint8_t)LimitValue((int16_t)Alarm_Delay + diff, ALARM_DELAY_MIN, ALARM_DELAY_MAX);
	}

	Show_SetDelay();

	if (Key_GetPress())
	{
		OverAngleTicks = 0;
		Encoder_GetDiff();
		OLED_Clear();
		State = STATE_MONITOR;
	}
}
