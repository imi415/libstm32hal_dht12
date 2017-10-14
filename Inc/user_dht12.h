#ifndef __USER_DHT12_H
#define __USER_DHT12_H

#define DHT12_I2C_INTERFACE BOARD_DHT12_I2C_INTERFACE
#define DHT12_SLAVE_ADDR 0xB8

typedef struct {
  uint8_t TempHigh;
  uint8_t TempLow;
  uint8_t HumidHigh;
  uint8_t HumidLow;
} DHT12_DataTypeDef;

typedef struct {
  DHT12_DataTypeDef Data;

  uint8_t TxFlag;
  uint8_t RxFlag;

  HAL_LockTypeDef Lock;
} DHT12_HandleTypeDef;

HAL_StatusTypeDef DHT12_Init(DHT12_HandleTypeDef * dht12);
HAL_StatusTypeDef DHT12_GetSensorData(DHT12_HandleTypeDef * dht12);
HAL_StatusTypeDef DHT12_Read(DHT12_HandleTypeDef * dht12, uint8_t * buf);
HAL_StatusTypeDef DHT12_PrepareData(DHT12_HandleTypeDef * dht12, uint8_t * buf);

#endif
