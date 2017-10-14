#include "i2c.h"

#include "user_board.h"

#include "user_dht12.h"

HAL_StatusTypeDef DHT12_Init(DHT12_HandleTypeDef * dht12) {
  dht12 -> TxFlag = 0;
  dht12 -> RxFlag = 0;
  dht12 -> Lock = 0;

  dht12 -> Data.TempHigh = 0;
  dht12 -> Data.TempLow = 0;
  dht12 -> Data.HumidHigh = 0;
  dht12 -> Data.HumidLow = 0;

  return HAL_OK;
}

HAL_StatusTypeDef DHT12_GetSensorData(DHT12_HandleTypeDef * dht12) {
  uint8_t buf[4];
  DHT12_Read(dht12, buf);
  DHT12_PrepareData(dht12, buf);
  return HAL_OK;
}

HAL_StatusTypeDef DHT12_Read(DHT12_HandleTypeDef * dht12, uint8_t * buf) {
  __HAL_LOCK(dht12);
  HAL_I2C_Mem_Read_DMA(&DHT12_I2C_INTERFACE, DHT12_SLAVE_ADDR, 0x00, 0x01, buf, 0x04);
  while(!dht12 -> RxFlag);
  dht12 -> RxFlag = 0;
  __HAL_UNLOCK(dht12);
  return HAL_OK;
}

HAL_StatusTypeDef DHT12_PrepareData(DHT12_HandleTypeDef * dht12, uint8_t * buf) {
  dht12 -> Data.HumidHigh = buf[0];
  dht12 -> Data.HumidLow = buf[1];
  dht12 -> Data.TempHigh = buf[2];
  dht12 -> Data.TempLow = buf[3];
  return HAL_OK;
}
