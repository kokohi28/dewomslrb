// Main Class DEWO BASESTATION
//
// 22/04/2017 by Koko Himawan <himawan.koko@gmail.com>
//
// Change Log's :
// 22/04/2017 - 1st release, Basic Function & Constant
//                           MSLRB(Middle Size League Robo Soccer) module
// ...

#ifndef __DEWO_H__
#define __DEWO_H__

#include "TcpHandler.h"
#include "UdpHandler.h"
#include <pthread.h>

class Dewo {
public:
    enum TEAM_SIDE {
        SIDE_CYAN       = 65, // 'A'
        SIDE_MAGENTA    = 66, // 'B'
    };

private:
    Tools::TcpHandler*      mTCPRefBox; // Untuk jalur ke refbox (as Client)
    Tools::UdpHandler*      mUdpRobo; // Untuk jalur ke robot (as Server)
    pthread_t               mTid_Refbox;
    pthread_t               mTid_Robo;

    static Dewo*            sInstance;         // Singleton reference

    int                     mRefState;

    unsigned int            m_MainControl;      // Main Control which used
    int                     m_Command;          // Main Control which used
    int                     m_PrevCommand;      // Prev Command
    int                     m_Side;
    ////////////////////////////////////////////
    bool                    InitConfig();
    void                    DeInit();

    bool                    ProcessInput();
    bool                    PreProcess();
    bool                    PostProcess();

public:
    Dewo();
    ~Dewo();

    static Dewo*            GetInst();

    void                    DestroyInst();
    void                    Init(int side);
    void                    MainLoop();

    // Set - Get
    void                    SetMainControl(unsigned int control) {m_MainControl = control;}
    unsigned int            GetMainControl() {return m_MainControl;}
    void                    SetCommand(int command) {m_Command = command;}
    int                     GetCommand() {return m_Command;}
    void                    SetPreviousCommand(int command) {m_PrevCommand = command;}
    int                     GetPreviousCommand() {return m_PrevCommand;}

    Tools::TcpHandler*      getHandler_RefBox() {return mTCPRefBox;}
    Tools::UdpHandler*      getHandler_Robo() {return mUdpRobo;}
    int                     getTeamSide() {return m_Side;}
    int                     getState_RefState() {return mRefState;}
    void                    setState_RefState(int state) {mRefState = state;}
};

#endif /* __DEWO_H__ */