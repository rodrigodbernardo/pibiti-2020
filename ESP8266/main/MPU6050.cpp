#include "MPU6050.h"
#include <Wire.h>

void MPU::setup()
{
  write(PWR_MGMT_1, 0);
  write(GYRO_CONFIG, GYRO_SCALE);
  write(ACCEL_CONFIG, ACCEL_SCALE);
}

void MPU::write(int REG, int VAL)
{
  Wire.beginTransmission(MPU_ADDR); //inicia a comunicacao com o endereço do MPU6050
  Wire.write(REG);                  //envia o registrador com o qual se deseja trabalhar
  Wire.write(VAL);                  //escreve o valor no registrador
  Wire.endTransmission();           //termina a transmissao
}

void MPU::read()
{
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(ACCEL_XOUT);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, (uint8_t)14);

  //incompleto
}
