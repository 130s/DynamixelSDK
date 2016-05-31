/*
 * protocol1_packet_handler.h
 *
 *  Created on: 2016. 1. 26.
 *      Author: zerom, leon
 */

#ifndef DYNAMIXEL_SDK_INCLUDE_DYNAMIXEL_SDK_PROTOCOL1PACKETHANDLER_H_
#define DYNAMIXEL_SDK_INCLUDE_DYNAMIXEL_SDK_PROTOCOL1PACKETHANDLER_H_


#include "packet_handler.h"

namespace dynamixel
{

class WINDECLSPEC Protocol1PacketHandler : public PacketHandler
{
 private:
  static Protocol1PacketHandler *unique_instance_;

  Protocol1PacketHandler();

 public:
  static Protocol1PacketHandler *getInstance() { return unique_instance_; }

  virtual ~Protocol1PacketHandler() { }

  float   getProtocolVersion() { return 1.0; }

  void    printTxRxResult(int result);
  void    printRxPacketError(uint8_t error);

  int txPacket        (PortHandler *port, uint8_t *txpacket);
  int rxPacket        (PortHandler *port, uint8_t *rxpacket);
  int txRxPacket      (PortHandler *port, uint8_t *txpacket, uint8_t *rxpacket, uint8_t *error = 0);

  int ping            (PortHandler *port, uint8_t id, uint8_t *error = 0);
  int ping            (PortHandler *port, uint8_t id, uint16_t *model_number, uint8_t *error = 0);

  // broadcastPing
  int broadcastPing   (PortHandler *port, std::vector<uint8_t> &id_list);

  int action          (PortHandler *port, uint8_t id);
  int reboot          (PortHandler *port, uint8_t id, uint8_t *error = 0);
  int factoryReset    (PortHandler *port, uint8_t id, uint8_t option, uint8_t *error = 0);


  int readTx          (PortHandler *port, uint8_t id, uint16_t address, uint16_t length);
  int readRx          (PortHandler *port, uint16_t length, uint8_t *data, uint8_t *error = 0);
  int readTxRx        (PortHandler *port, uint8_t id, uint16_t address, uint16_t length, uint8_t *data, uint8_t *error = 0);

  int read1ByteTx     (PortHandler *port, uint8_t id, uint16_t address);
  int read1ByteRx     (PortHandler *port, uint8_t *data, uint8_t *error = 0);
  int read1ByteTxRx       (PortHandler *port, uint8_t id, uint16_t address, uint8_t *data, uint8_t *error = 0);

  int read2ByteTx     (PortHandler *port, uint8_t id, uint16_t address);
  int read2ByteRx     (PortHandler *port, uint16_t *data, uint8_t *error = 0);
  int read2ByteTxRx       (PortHandler *port, uint8_t id, uint16_t address, uint16_t *data, uint8_t *error = 0);

  int read4ByteTx     (PortHandler *port, uint8_t id, uint16_t address);
  int read4ByteRx     (PortHandler *port, uint32_t *data, uint8_t *error = 0);
  int read4ByteTxRx       (PortHandler *port, uint8_t id, uint16_t address, uint32_t *data, uint8_t *error = 0);

  int writeTxOnly     (PortHandler *port, uint8_t id, uint16_t address, uint16_t length, uint8_t *data);
  int writeTxRx           (PortHandler *port, uint8_t id, uint16_t address, uint16_t length, uint8_t *data, uint8_t *error = 0);

  int write1ByteTxOnly(PortHandler *port, uint8_t id, uint16_t address, uint8_t data);
  int write1ByteTxRx      (PortHandler *port, uint8_t id, uint16_t address, uint8_t data, uint8_t *error = 0);

  int write2ByteTxOnly(PortHandler *port, uint8_t id, uint16_t address, uint16_t data);
  int write2ByteTxRx      (PortHandler *port, uint8_t id, uint16_t address, uint16_t data, uint8_t *error = 0);

  int write4ByteTxOnly(PortHandler *port, uint8_t id, uint16_t address, uint32_t data);
  int write4ByteTxRx      (PortHandler *port, uint8_t id, uint16_t address, uint32_t data, uint8_t *error = 0);

  int regWriteTxOnly  (PortHandler *port, uint8_t id, uint16_t address, uint16_t length, uint8_t *data);
  int regWriteTxRx        (PortHandler *port, uint8_t id, uint16_t address, uint16_t length, uint8_t *data, uint8_t *error = 0);

  int syncReadTx      (PortHandler *port, uint16_t start_address, uint16_t data_length, uint8_t *param, uint16_t param_length);
  // SyncReadRx   -> GroupSyncRead class
  // SyncReadTxRx -> GroupSyncRead class

  // param : ID1 DATA0 DATA1 ... DATAn ID2 DATA0 DATA1 ... DATAn ID3 DATA0 DATA1 ... DATAn
  int syncWriteTxOnly (PortHandler *port, uint16_t start_address, uint16_t data_length, uint8_t *param, uint16_t param_length);

  // param : LEN1 ID1 ADDR1 LEN2 ID2 ADDR2 ...
  int bulkReadTx      (PortHandler *port, uint8_t *param, uint16_t param_length);
  // BulkReadRx   -> GroupBulkRead class
  // BulkReadTxRx -> GroupBulkRead class

  int bulkWriteTxOnly (PortHandler *port, uint8_t *param, uint16_t param_length);
};

}


#endif /* DYNAMIXEL_SDK_INCLUDE_DYNAMIXEL_SDK_PROTOCOL1PACKETHANDLER_H_ */
