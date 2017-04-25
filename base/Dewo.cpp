// Main Class DEWO BASESTATION
//
// 22/04/2017 by Koko Himawan <himawan.koko@gmail.com>
//
// Change Log's :
// 22/04/2017 - 1st release, Basic Function & Constant
//                           MSLRB(Middle Size League Robo Soccer) module
// ...

#include "Dewo.h"
#include "Consts.h"
#include "ConfigParser.h"
#include <stdint.h> // typedef : int8_t, uint8_t, uint16_t ...
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Tools.h"
#include <string.h>

#define THREAD_ID_REF_BOX     100 // Unique
#define THREAD_ID_ROBO        101 // Unique

/******************* VARs ***************************/
std::string gConfigPath = "";
unsigned int gCountPic = 0;

bool                    g_REF_BOX_LOOP = true;      // Control the life of TCP RefBoxHandler
bool                    g_ROBO_LOOP = true;         // Control the life of UDP RoboHandler
bool                    g_MAIN_LOOP = true;         // Control the life of the program

/******************* Prototype **********************/
void *_thread_tcp_refbox(void *vargp);
void *_thread_udp_robo(void *vargp);
void debugRefereeData(int idx);

/****************************************************/
/****************************************************/
/******************* MAIN ***************************/

// Ex Using: ./Dewo cfg.cfg
//           ./Dewo cfg.cfg CYAN
//           ./Dewo cfg.cfg MAG

int main(int argc, const char *argv[]) {
    DBG_N("[MAIN] >> START!");

    int side = Dewo::SIDE_CYAN; // Default as Cyan team
    if (argc > 2) {
        // Side
        if (strcmp(argv[2], "MAG") == 0) {
            side = Dewo::SIDE_MAGENTA;
            DBG_I("[MAIN] as MAGENTA TEAM!");
        } else {
            side = Dewo::SIDE_CYAN;
            DBG_I("[MAIN] as CYAN TEAM!");
        }

        // Config path
        gConfigPath = argv[1];
    } else if (argc > 1) {
        DBG_I("[MAIN] as Default CYAN TEAM!");

        // Config path
        gConfigPath = argv[1];
    } else {
        DBG_W("[MAIN] CYAN TEAM, Not passing config file, use predefined instead!");
    }

    // Init module
    Dewo::GetInst()->Init(side);

    // Loop
    Dewo::GetInst()->MainLoop();

    // End
    Dewo::GetInst()->DestroyInst(); // release all memory
    DBG_N("[MAIN] END!!! <<");

    return 0;
}

/****************************************************/
/****************************************************/
/******************* DEWO ***************************/
Dewo::Dewo() :
    mRefState(Consts::REF_UNKNOWN),
    m_Side(Dewo::SIDE_CYAN),
    m_MainControl((unsigned int) Consts::CONTROL_CONSOLE),
    m_Command(Consts::BASE_IDLE),
    m_PrevCommand(Consts::BASE_IDLE) {
}

Dewo::~Dewo() {
}

Dewo *Dewo::sInstance = NULL;

Dewo *Dewo::GetInst() {
    if (!sInstance) {
        DBG_W("[Dewo] NewInstance()");
        sInstance = new Dewo();
    }
    return sInstance;
}

void Dewo::DestroyInst() {
    // DeInit first
    DeInit();

    // Release all
    Tools::ConfigParser::GetInst()->DestroyInst();

    SAFE_DEL(mTCPRefBox);
    SAFE_DEL(mUdpRobo);

    SAFE_DEL(sInstance);
    DBG_W("[Dewo] DestroyInstance()");
}

// Primary Init's
void Dewo::Init(int side) {
    // Read config file first
    if (gConfigPath.empty()) {
        Tools::ConfigParser::GetInst()->Init();
    } else {
        Tools::ConfigParser::GetInst()->Init(gConfigPath);
    }

    // Set which team side
    m_Side = side;

    // Set Main Input Control
    unsigned char control;
    Tools::ConfigParser::GetInst()->GetCommandParameter(control);
    SetMainControl((unsigned int) control);

    // Init referee box tcp handler
    std::string ref_ip      = Tools::ConfigParser::GetInst()->GetRefBox_IP();
    unsigned int ref_port   = Tools::ConfigParser::GetInst()->GetRefBox_Port();
    mTCPRefBox              = new Tools::TcpHandler(ref_ip.c_str(), ref_port);
    if (!mTCPRefBox->Init()) {
        DBG_E("[Dewo] TCP RefBox Not ready");
        g_REF_BOX_LOOP = false; // Don't Loop TCP REfBox thread
    } else {

    }

    // Init Robo udp handler
    unsigned int udp_port   = Tools::ConfigParser::GetInst()->GetBase_Udp_Port(); 
    mUdpRobo                = new Tools::UdpHandler(udp_port);
    if (!mUdpRobo->Init()) {
        DBG_E("[Dewo] Udp Robo Not ready");
        g_ROBO_LOOP = false; // Don't Loop UDP Robo thread
    } else {
        // mUdpRobo->WriteData(std::string("\n"));
    }

    // Create Thread and Loop for Ref-Box, Robo
    pthread_create(&mTid_Refbox, NULL, _thread_tcp_refbox, (void *) THREAD_ID_REF_BOX);
    pthread_create(&mTid_Robo, NULL, _thread_udp_robo, (void *) THREAD_ID_ROBO);

    DBG_I("[Dewo] Init Done");
}

// Primary DeInit
void Dewo::DeInit() {
    pthread_exit(NULL);
}

void *_thread_tcp_refbox(void *vargp) {
    // int tid = (int) vargp;

    while (g_REF_BOX_LOOP) {
        int data = Dewo::GetInst()->getHandler_RefBox()->ReadData();
        Dewo::GetInst()->setState_RefState(data);

        // printf("[Dewo] Ref Tcp Data:%d\n", data);
        debugRefereeData(data);
    }

    DBG_I("[Dewo] _thread_tcp_refbox STOP!!!");
}

void debugRefereeData(int idx) {
    char data[128][30]; // length as keyboard char data, max 30 char
    /////// assign value
    // Referee
    strcpy(data[Consts::REF_UNKNOWN]           , "UNKNOWN"); // CYAN_UNKNOWN // MAG_UNKNOWN
    strcpy(data[Consts::REF_START]             , "REF_START");
    strcpy(data[Consts::REF_STOP]              , "REF_STOP");
    strcpy(data[Consts::REF_DROPBALL]          , "REF_DROPBALL");
    strcpy(data[Consts::REF_PARK]              , "REF_PARK");
    strcpy(data[Consts::REF_END_PART]          , "REF_END_PART");
    strcpy(data[Consts::REF_RESET]             , "REF_RESET");
    strcpy(data[Consts::REF_END_GAME]          , "REF_END_GAME");

    // Cyan
    strcpy(data[Consts::CYAN_KICK_OFF]         , "CYAN_KICK_OFF");
    strcpy(data[Consts::CYAN_FREE_KICK]        , "CYAN_FREE_KICK");
    strcpy(data[Consts::CYAN_GOAL_KICK]        , "CYAN_GOAL_KICK");
    strcpy(data[Consts::CYAN_THROW_IN]         , "CYAN_THROW_IN");
    strcpy(data[Consts::CYAN_CORNER]           , "CYAN_CORNER");
    strcpy(data[Consts::CYAN_PENALTY]          , "CYAN_PENALTY");
    strcpy(data[Consts::CYAN_GOAL]             , "CYAN_GOAL");
    strcpy(data[Consts::CYAN_REPAIR]           , "CYAN_REPAIR");
    strcpy(data[Consts::CYAN_RED_CARD]         , "CYAN_RED_CARD");
    strcpy(data[Consts::CYAN_YELLOW_CARD]      , "CYAN_YELLOW_CARD");

    // Magenta
    strcpy(data[Consts::MAG_KICK_OFF]          , "MAG_KICK_OFF");
    strcpy(data[Consts::MAG_FREE_KICK]         , "MAG_FREE_KICK");
    strcpy(data[Consts::MAG_GOAL_KICK]         , "MAG_GOAL_KICK");
    strcpy(data[Consts::MAG_THROW_IN]          , "MAG_THROW_IN");
    strcpy(data[Consts::MAG_CORNER]            , "MAG_CORNER");
    strcpy(data[Consts::MAG_PENALTY]           , "MAG_PENALTY");
    strcpy(data[Consts::MAG_GOAL]              , "MAG_GOAL");
    strcpy(data[Consts::MAG_REPAIR]            , "MAG_REPAIR");
    strcpy(data[Consts::MAG_RED_CARD]          , "MAG_RED_CARD");
    strcpy(data[Consts::MAG_YELLOW_CARD]       , "MAG_YELLOW_CARD");

    printf("[Dewo] Ref Tcp Data:%d %s\n", idx, data[idx]);
}

void *_thread_udp_robo(void *vargp) {
    // int tid = (int) vargp;

    while (g_ROBO_LOOP) {
        std::string data = Dewo::GetInst()->getHandler_Robo()->ReadData();
        // TODO!!! Recheck data from client and process based command/instruction/request format

        int state   = Dewo::GetInst()->getState_RefState();
        int side    = Dewo::GetInst()->getTeamSide();
        // Dewo::GetInst()->getHandler_Robo()->WriteData(state);

        // Format [side][state];
        char buffer[3];
        buffer[0] = side;
        buffer[1] = state;
        Dewo::GetInst()->getHandler_Robo()->WriteData(buffer);

        // printf("Ref Udp Data:%s\n", data.c_str());
    }

    DBG_I("[Dewo] _thread_tcp_refbox STOP!!!");
}

// Main Loop
void Dewo::MainLoop() {
    // Primary Loop and logic's
    while (g_MAIN_LOOP) {
        /*** INPUT ***/
        if (!ProcessInput()) break;

        /*** PRE PROCESS ***/
        if (!PreProcess()) break;

        /*** POST PROCESS ***/
        if (!PostProcess()) break;        
    }
}

bool Dewo::ProcessInput() {
    switch (GetMainControl()) {
        /*** Console(Terminal) Input by keyboard stroke ***/
        case Consts::CONTROL_CONSOLE: {
            if (Tools::KeyHit()) {
                int command = (int) getchar();
                printf("[DEWO] Keyboard Input: %d\n", command);
                SetCommand(command);
            }
        }
            break;
        /*** Tcp/Udp(Network) data ***/
        case Consts::CONTROL_NETWORK:
            break;
        // TODO
        case Consts::CONTROL_SEMI_AUTO:
            break;
        // TODO
        case Consts::CONTROL_FULL_AUTO:
        // TODO
            break;
        default:
            DBG_W("[Dewo] INPUT MODE NOT DEFINED!");
            break;
    }

    return true;
}

bool Dewo::PreProcess() {
    switch (GetCommand()) {
        case Consts::BASE_IDLE: {
            // DBG_I("[Dewo] Consts::BASE_IDLE");
            // switch (getState_RefState()) {
            //     case Consts::REF_END_GAME : {
            //         // TODO!!! Happy Ending XD
            //         DBG_I("[Dewo] Referee Box END GAME");

            //         // g_MAIN_LOOP = false; // Seems need tested more
            //     }
            //         break;
            //     case Consts::REF_START : {
            //         DBG_I("[Dewo] Referee Box START");
            //     }
            //         break;
            //     case Consts::REF_STOP : {
            //         DBG_I("[Dewo] Referee Box STOP");
            //     }
            //         break;
            //     case Consts::REF_DROPBALL : {
            //         DBG_I("[Dewo] Referee Box DROP BALL");
            //     }
            //         break;
            //     case Consts::REF_PARK : {
            //         DBG_I("[Dewo] Referee Box PARK");
            //     }
            //         break;
            //     case Consts::REF_END_PART : {
            //         DBG_I("[Dewo] Referee Box END PART");
            //     }
            //         break;
            //     case Consts::REF_RESET : {
            //         DBG_I("[Dewo] Referee Box RESET GAME");
            //     }
            //         break;                    
            //     default:
            //         break;
            // }
        }
            break;
        case Consts::BASE_WAKE_UP_ROBO: {
            // DBG_I("[Dewo] Consts::BASE_WAKE_UP_ROBO");

            // Experimental
            mUdpRobo->WriteData((int) Consts::REF_UNKNOWN);

            SetCommand((int) Consts::BASE_IDLE);
        }
            break;
        case Consts::BASE_PILOT_MODE: {
            // DBG_I("[Dewo] Consts::BASE_PILOT_MODE");
            SetCommand((int) Consts::BASE_IDLE);
        }
            break;
        case Consts::BASE_SHUTDOWN_ALL: {
            return false;
        }
            break;
        default:
            break;
    }

    return true;
}

bool Dewo::PostProcess() {
    return true;
}