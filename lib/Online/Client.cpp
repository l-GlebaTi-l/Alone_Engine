#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Net2.h"
#include "Client.h"
#include "../Game/structs.h"
#include "../Game/objects.h"

using namespace std;
using namespace net2;

extern int NUM_OBJECTS;
extern int NUM_PLAYERS;
extern int NUM_CARS;
extern int PARAM_SEND_CAR;

extern World_Objects *W__Objs;
extern World_Players *W__Players;
extern World_Cars *W__Cars;

namespace Client
{
    bool PARAM_Console_On_Online_low = 0;
    bool PARAM_Console_On_Online = 0;
    const int ServerPort = 30000;
    const int ClientPort = 30001;
    const int ProtocolId = 0x99887766;
    const float Time_IsConnected = 1.0f;
    const float DeltaTime = 0.04f;
    const float SendRate = 0.04f;
    const float TimeOut = 10.0f;

    int IsLoaded_obj(short g_id, World_Objects *tW__Objs, int tNUM_OBJECTS)
    {
        for(int i = 0; i < tNUM_OBJECTS; i++){
            if(g_id == tW__Objs[i].g_id)
                return i;
        }
        return -1;
    }
    int IsLoaded_player(short g_id, World_Players *tW__Players, int tNUM_PLAYERS)
    {
        for(int i = 0; i < tNUM_PLAYERS; i++){
            if(g_id == tW__Players[i].g_id)
                return i;
        }
        return -1;
    }
    int IsLoaded_car(short g_id, World_Cars *tW__Cars, int tNUM_CARS)
    {
        for(int i = 0; i < tNUM_CARS; i++){
            if(g_id == tW__Cars[i].g_id)
                return i;
        }
        return -1;
    }

    DWORD WINAPI Connect_Vizor(void* param);
    DWORD WINAPI Sender(void* param);
    DWORD WINAPI Reciever(void* param);
    #include "Packer.h"

    DWORD WINAPI CLIENT_CONNECT(LPVOID param)
    {
        if ( !InitializeSockets() )
        {
            printf( "failed to initialize sockets\n" );
            return 1;
        }

        Connection connection( ProtocolId, TimeOut );

        if ( !connection.Start( ClientPort ) )
        {
            printf( "could not start connection on port %d\n", ClientPort );
            return 1;
        }

        if(MessageBoxA(NULL, "Enter the ip?", "Local game", MB_YESNO | MB_ICONQUESTION | MB_SETFOREGROUND) == IDYES){
            int a, b, c, d;
            int p;
            cin >> a >> b >> c >> d >> p;
            connection.Connect( Address(a,b,c,d,p ) );
        }
        else
            connection.Connect( Address(127,0,0,1,ServerPort ) );

        bool connected = false;

    //	while ( true )
    //	{
        if ( !connected && connection.IsConnected() )
        {
            printf( "client connected to server\n" );
            connected = true;
        }

        if ( !connected && connection.ConnectFailed() )
        {
            printf( "connection failed\n" );
            return -1;
        }
    //
    //	}

        HANDLE threads[3];
        threads[0] = CreateThread(NULL, 0, Connect_Vizor, (void*)&connection, 0, 0);
        threads[1] = CreateThread(NULL, 0, Sender, (void*)&connection, 0, 0);
        threads[2] = CreateThread(NULL, 0, Reciever, (void*)&connection, 0, 0);
        WaitForMultipleObjects(3, threads, 1, INFINITE);

        ShutdownSockets();

        return 0;
    }

    DWORD WINAPI Connect_Vizor(void* param)
    {
        Connection* connection = (Connection*)param;
        while( true ){
            unsigned char packet[2];
            packet[0] = '~';
            connection->SendPacket( packet, sizeof( packet ) );

            connection->Update( Time_IsConnected );
            wait( Time_IsConnected );
        }
    }

    DWORD WINAPI Sender(void* param)
    {
        Connection* connection = (Connection*)param;
        while( true ){
            unsigned char packet[1024];
            unsigned char* s_packet = packet;
    //        if(Bob.IsInCar != 0){
    //            /// send about car
    //        }
            Pack(W__Players[0], s_packet);
            if(PARAM_SEND_CAR != -1)
                Pack(W__Cars[PARAM_SEND_CAR], s_packet);
            /// send about Bob
            connection->SendPacket( packet, sizeof( packet ) );

            connection->Update( DeltaTime );
            wait( DeltaTime );
        }
    }

    DWORD WINAPI Reciever(void* param)
    {
        Connection* connection = (Connection*)param;
        while( true ){
            while ( true )
            {
                unsigned char packet[1024];
                int bytes_read = connection->ReceivePacket( packet, sizeof(packet) );
                if ( bytes_read == 0 )
                    break;
                unsigned char* s_packet = packet;
                if(packet[0] != '~')
                    if(unPack(s_packet) != 1)
                        break;
//                s_packet = packet;
//                readPacket(s_packet);
                if(PARAM_Console_On_Online_low == 1)
                    cout << "Bytes of packet: " << bytes_read << endl;
            }

            connection->Update( DeltaTime );
            wait( DeltaTime );
        }
    }

}
