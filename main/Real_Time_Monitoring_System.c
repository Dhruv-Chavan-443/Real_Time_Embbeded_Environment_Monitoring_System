#include <stdio.h>
#define LIMIT 30
#define SENSOR_ADDRESS 0x48
#define TEMP_REG 0x02
#define I2C_DONE 0
#define I2C_ERROR 1
#define I2C_ACK 0
#define I2C_NACK 1
#define IMU_CS 0
#define ACCEL_X_REG 0x00
#define ACCEL_Y_REG 0x01
#define ACCEL_Z_REG 0x02
#define SPI_DONE 0
#define SPI_ERROR 1
#define TIMER_TICKS 2000
#define TIMER_EVENTS 5
#define TX_READY 0
volatile unsigned char Sensor_Register[4];
volatile unsigned char I2C_Status = 0;
volatile unsigned char ACK = 0;
volatile int IMU_Register[3];
volatile unsigned char SPI_Status = 0;
volatile unsigned char timer_flag = 0;
volatile unsigned int timer_count = 0;
volatile unsigned int event_count = 0;
volatile unsigned char UART_Status = 0;
volatile unsigned char UART_Data = 0;
typedef struct imu
{
    int x;
    int y;
    int z;
} Imu_Data;
void Temperature_Read()
{
    printf("Reading Temperature.....\n");
}
void Inertial_Read()
{
    printf("Reading IMU....\n");
}
void Process_Data()
{
    printf("Processing Data....\n");
}
unsigned char I2C_Read(unsigned char device_address, unsigned char register_address)
{
    if (device_address == SENSOR_ADDRESS)
    {
        ACK = I2C_ACK;
        I2C_Status = (1 << I2C_DONE);
        return Sensor_Register[register_address];
    }
    ACK = I2C_NACK;
    I2C_Status = (1 << I2C_ERROR);
    return 0;
}
void Sensor_Init()
{
    Sensor_Register[0x00] = 0xAB;
    Sensor_Register[0x01] = 0x01;
    Sensor_Register[0x02] = 25;
    Sensor_Register[0x03] = 0x00;
}
void IMU_Init()
{
    IMU_Register[ACCEL_X_REG] = 2;
    IMU_Register[ACCEL_Y_REG] = 0;
    IMU_Register[ACCEL_Z_REG] = 4;
}
unsigned char Sensor_Read()
{
    return I2C_Read(SENSOR_ADDRESS, TEMP_REG);
}
int SPI_Read(unsigned char chip_select, unsigned char register_address)
{
    if (chip_select == IMU_CS)
    {
        SPI_Status = (1 << SPI_DONE);
        return IMU_Register[register_address];
    }
    SPI_Status = (1 << SPI_ERROR);
    return 0;
}
unsigned char IMU_Read(Imu_Data *imu)
{
    imu->x = SPI_Read(IMU_CS, ACCEL_X_REG);
    if (SPI_Status != (1 << SPI_DONE))
        return 0;
    imu->y = SPI_Read(IMU_CS, ACCEL_Y_REG);
    if (SPI_Status != (1 << SPI_DONE))
        return 0;
    imu->z = SPI_Read(IMU_CS, ACCEL_Z_REG);
    if (SPI_Status != (1 << SPI_DONE))
        return 0;
    return 1;
}
unsigned char Process_Temperature(unsigned char temperature)
{
    if (temperature > LIMIT)
        return 1;
    else
        return 0;
}
unsigned char Process_IMU(Imu_Data *imu)
{
    if ((imu->x > 5 || imu->x < -5) || (imu->y > 5 || imu->y < -5))
    {
        return 1;
    }
    return 0;
}
void I2C_Status_Condition()
{
    if (I2C_Status & (1 << I2C_DONE))
    {
        printf("I2C Communication: Success\n");
    }
    else
    {
        printf("I2C Communication: Error\n");
    }
}
void ACK_Status_Condition()
{
    if (ACK == I2C_NACK)
    {
        printf("Sensor Dosen't Acknowledge\n");
    }
    else
    {
        printf("Sensor does acknowledge\n");
    }
}
void SPI_Status_Condition()
{
    if (SPI_Status & (1 << SPI_DONE))
    {
        printf("SPI Communication: Working\n");
    }
    else
    {
        printf("SPI Communication: Failed\n");
    }
}
void Sensor_Status_Condition(unsigned char sensor_status)
{
    if (sensor_status)
    {
        printf("Sensor Status: Abnormal\n");
    }
    else
    {
        printf("Sensor Status: Normal\n");
    }
}
void IMU_Status_Condition(unsigned char IMU_status)
{
    if (IMU_status)
    {
        printf("IMU Status: Abnormal\n");
    }
    else
    {
        printf("IMU Status: Normal\n");
    }
}
unsigned char System_Status(unsigned char sensor_status, unsigned char IMU_status)
{
    if (sensor_status == 0 && IMU_status == 0)
        return 0;
    return 1;
}
void System_Status_Condition(unsigned char system_status)
{
    if (system_status)
    {
        printf("System Status: Abnormal\n");
    }
    else
    {
        printf("System Status: Normal\n");
    }
}
void Buzzer_Control(unsigned char buzzer)
{
    if (buzzer)
    {
        // Buzzer hardware ON
        printf("Buzzer On!!!\n");
    }
    else
    {
        // Buzzer hardware OFF
        printf("Buzzer Off!!!\n");
    }
}
void Timer_ISR()
{
    timer_count++;
    if (timer_count >= TIMER_TICKS)
    {
        timer_count = 0;
        timer_flag = 1;
    }
}
void UART_Transmitter(unsigned char data)
{
    if (UART_Status & (1 << TX_READY))
    {
        UART_Data = data;
        printf("%c", UART_Data);
    }
    else
    {
        printf("UART TX: Not Ready\n");
    }
}
void UART_Transmit_String(const unsigned char *str)
{
    while (*str != '\0')
    {
        UART_Transmitter(*str);
        str++;
    }
}
void UART_Transmit_Number(int number)
{
    int temp[10] = {};
    int i = 0;
    if (number == 0)
    {
        UART_Transmitter('0');
        return;
    }
    while (number > 0)
    {
        temp[i] = number % 10;
        number /= 10;
        i++;
    }
    for (int j = i-1; j >= 0; j--)
    {
        UART_Transmitter(temp[j] + '0');
    }
}
void UART_Send_Sensor_Data(unsigned char temperature,Imu_Data *imu){
    UART_Transmit_String("Temperature: ");
    UART_Transmit_Number(temperature);
    UART_Transmitter('\n');
    UART_Transmit_String("X: ");
    UART_Transmit_Number(imu->x);
    UART_Transmitter('\n');
    UART_Transmit_String("Y: ");
    UART_Transmit_Number(imu->y);
    UART_Transmitter('\n');
    UART_Transmit_String("Z: ");
    UART_Transmit_Number(imu->z);
    UART_Transmitter('\n');

}
int main()
{
    while (1)
    {
        if (timer_flag == 1)
        {
            printf("Timer Event has Occured\n");
            Temperature_Read();
            Sensor_Init();
            unsigned char temperature = Sensor_Read();
            ACK_Status_Condition();
            I2C_Status_Condition();
            if (I2C_Status == (1 << I2C_DONE))
            {
                Process_Data();
                unsigned char sensor_status = Process_Temperature(temperature);
                Sensor_Status_Condition(sensor_status);
                Inertial_Read();
                Imu_Data imu;
                IMU_Init();
                if (IMU_Read(&imu))
                {
                    SPI_Status_Condition();
                    Process_Data();
                    unsigned char IMU_status = Process_IMU(&imu);
                    IMU_Status_Condition(IMU_status);
                    UART_Status |= (1 << TX_READY);
                    UART_Send_Sensor_Data(temperature,&imu);
                    unsigned char system_status = System_Status(sensor_status, IMU_status);
                    System_Status_Condition(system_status);
                    Buzzer_Control(system_status);
                }
                else
                {
                    SPI_Status_Condition();
                    printf("IMU: Error\n");
                }
            }
            else
            {
                printf("Temperature: Error\n");
            }
            /*event_count++;
            if(event_count==TIMER_EVENTS){
                printf("5 Seconds Passed!!!\n");
                break;
            }*/
            timer_flag = 0;
            break;
        }
        Timer_ISR();
    }
}