/*********************************************************************************************************
 *                                              ����ͷ�ļ�
 *********************************************************************************************************/
#include "Main.h"
#include "stm32f10x_conf.h"
#include "DataType.h"
#include "NVIC.h"
#include "SysTick.h"
#include "RCC.h"
#include "Timer.h"
#include "UART1.h"
#include "OLED.h"
#include "RunClock.h"

#include "LEDNew.h"
#include "KeyNew.h"
#include "Game.h"

/*********************************************************************************************************
 *                                              �ڲ�����
 *********************************************************************************************************/
i16 ControlFlag = 0;

/*********************************************************************************************************
 *                                              �ڲ���������
 *********************************************************************************************************/
static void InitSoftware(void); //��ʼ�������ص�ģ��
static void InitHardware(void); //��ʼ��Ӳ����ص�ģ��
static void Proc2msTask(void);  // 2ms��������
static void Proc1SecTask(void); // 1s��������

/*********************************************************************************************************
 *                                              �ڲ�����ʵ��
 *********************************************************************************************************/
static void InitHardware(void)
{
    SystemInit();      //ϵͳ��ʼ��
    InitRCC();         //��ʼ��RCCģ��
    InitNVIC();        //��ʼ��NVICģ��
    InitUART1(115200); //��ʼ��UARTģ��
    InitTimer();       //��ʼ��Timerģ��
    InitSysTick();     //��ʼ��SysTickģ��
    InitOLED();        //��ʼ��OLEDģ��

    LEDInit();
    KeyInit();
}

static void Proc2msTask(void)
{
    if (Get2msFlag()) //�ж�2ms��־״̬
    {
        MicroSec += 2;     //��Ϸʱ��
        GameProcess();     //��Ϸ����
        KeyCheck();        //����������
        KeyFunction();     //����������⼰����ʵ��
        OLEDRefreshGRAM(); //ˢ��OLED����ʾ

        Clr2msFlag();
    }
}

static void Proc1SecTask(void)
{

    if (Get1SecFlag())
    {
        Clr1SecFlag();
    }
}

/**
 * @brief �򵥵�С��Ϸ
 *
 * @author Younger
 */
int main(void)
{
    InitHardware(); //��ʼ��Ӳ����غ���
    InitGame();     //��ʼ����Ϸ����
    while (1)
    {
        Proc2msTask();
    }
}
