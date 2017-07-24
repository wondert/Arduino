/*
 *  Copyright 2016 Google Inc. All Rights Reserved.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */
#ifndef _GOOSCI_BLE_GATT_H_
#define _GOOSCI_BLE_GATT_H_

class GoosciBleGatt {
  public:
    GoosciBleGatt(int req, int rdy, int rst);
    bool begin(int advTimeout = 180, int advInterval = 0x0050);
    void get_address();
    void print_address();
    void pollACI (void);
    void getDeviceName(char *name);
    void setDeviceName(const char *deviceName);
    void setLongName(const char *deviceName);
    void setDeviceDescription(const char *desc);
    void setSensorConfig(const char *config, int size);
    bool isInitialized(void);
    bool isReadyToSend(void);
    bool sendData(const char *buffer, int32_t size);
};

#endif
