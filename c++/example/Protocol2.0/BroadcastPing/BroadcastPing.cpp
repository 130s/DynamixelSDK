/*
 * BroadcastPing.cpp
 *
 *  Created on: 2016. 2. 21.
 *      Author: leon
 */

//
// *********     BroadcastPing Example      *********
//
//
// Available DXL model on this example : All models using Protocol 2.0
// This example is tested with two DXL PRO 54-200, and an USB2DYNAMIXEL
// Be sure that DXL PRO properties are already set as %% ID : 1 / Baudnum : 3 (Baudrate : 1000000) / Min voltage limit : under 110 (when using 12V power supplement)
//

#ifdef __linux__
#include <unistd.h>
#include <fcntl.h>
#include <getopt.h>
#include <termios.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

#include "DynamixelSDK.h"

// Protocol version
#define PROTOCOL_VERSION                2.0

// Default setting
#define BAUDRATE                        1000000
#define DEVICENAME                      "/dev/ttyUSB0"

using namespace ROBOTIS;

#ifdef __linux__
int _getch()
{
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

int _kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}
#endif

int main()
{
    // Initialize PortHandler instance
    // Set the port path
    // Get methods and members of PortHandlerLinux or PortHandlerWindows
    PortHandler *portHandler = PortHandler::GetPortHandler(DEVICENAME);

    // Initialize Packethandler instance
    PacketHandler *packetHandler = PacketHandler::GetPacketHandler(PROTOCOL_VERSION);

    int dxl_comm_result = COMM_TX_FAIL;                     // Communication result

    std::vector<UINT8_T> vec;                               // DXL data storages

    // Open port
    if(portHandler->OpenPort())
    {
        printf("Succeeded to open the port!\n");
    }
    else
    {
        printf("Failed to open the port!\n");
        printf("Press any key to terminate...\n");
        _getch();
        return 0;
    }

    // Set port baudrate
    if( portHandler->SetBaudRate(BAUDRATE))
    {
        printf("Succeeded to change the baudrate!\n");
    }
    else
    {
        printf("Failed to change the baudrate!\n");
        printf("Press any key to terminate...\n");
        _getch();
        return 0;
    }

    // Try to broadcast ping the DXL
    dxl_comm_result = packetHandler->BroadcastPing(portHandler, vec);
    if(dxl_comm_result != COMM_SUCCESS)
        packetHandler->PrintTxRxResult(dxl_comm_result);

    // Try to broadcastping the DXL
    printf("Detected DXL : \n");
    for(int i = 0; i < (int)vec.size(); i++)
    {
    	printf("[ID:%03d]\n", vec.at(i));
    }

    // Close port
    portHandler->ClosePort();

    printf("Press Enter key to terminate...\n");
    _getch();
    return 0;
}
