#define BOOST_TEST_MODULE Ion Test Suite
#include <boost/test/unit_test.hpp>

#include "main.h"
#include "wallet.h"

int MIN_PROTO_VERSION = 60027;

CWallet* pwalletMain;
CClientUIInterface uiInterface;

bool fConfChange;
bool fMinimizeCoinAge;
unsigned int nNodeLifespan;
unsigned int nDerivationMethodIndex;
unsigned int nMinerSleep;
bool fUseFastIndex;

extern bool fPrintToConsole;
struct TestingSetup {
    TestingSetup() {
        fPrintToConsole = true; // don't want to write to debug.log file
        pwalletMain = new CWallet();
        bitdb.MakeMock();
        LoadBlockIndex(true);
        bool fFirstRun;
        pwalletMain = new CWallet("wallet.dat");
        pwalletMain->LoadWallet(fFirstRun);
        RegisterWallet(pwalletMain);
    }
    ~TestingSetup()
    {
        delete pwalletMain;
        pwalletMain = NULL;
        bitdb.Flush(true);
    }
};

BOOST_GLOBAL_FIXTURE(TestingSetup);

volatile bool fRequestShutdown = false;

void Shutdown(void* parg)
{
  exit(0);
}

void StartShutdown()
{
  fRequestShutdown = true;
  exit(0);
}

bool ShutdownRequested()
{
    return fRequestShutdown;
}
