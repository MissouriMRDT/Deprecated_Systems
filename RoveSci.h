#ifndef ROVESCI_H
#define ROVESCI_H

int16_t roveSci_Grove_ReadHumid(int data_pin);
int16_t roveSci_FC28_ReadHumid(int data_pin);
int16_t roveSci_SHT10_ReadHumid(int data_pin, int clock_pin);
float roveSci_SHT10_ReadTemp(int data_pin, int clock_pin);
float roveSci_DS18B20_ReadTemp(int data_pin);

#endif