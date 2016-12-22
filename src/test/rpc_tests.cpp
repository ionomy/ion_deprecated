#include <boost/test/unit_test.hpp>
#include <boost/foreach.hpp>

#include "base58.h"
#include "util.h"
#include "rpcclient.h"
#include "rpcserver.h"
#include "wallet.h"

using namespace std;
using namespace json_spirit;

BOOST_AUTO_TEST_SUITE(rpc_tests)

// Actually run some of the RPC tests over RPC
struct RPCServerFixture
{
    RPCServerFixture() {
        SoftSetArg("-rpcuser", "diamondrpc");
        SoftSetArg("-rpcpassword", "dbrxGK62DXSJ6Cm3zgurPs3ML9uKxfwv5Z");
        StartRPCThreads();
    }

    ~RPCServerFixture() {
        StopRPCThreads();
    }
};

// Read a response object and return false if there is an error found
bool readResponse(Object obj, int &error_code) {
    // Initialize our error code as 0 because otherwise it may not have a value.
    error_code = 0;

    const Value &error = find_value(obj, "error");

    if (error.type() != null_type)
    {
        error_code = find_value(error.get_obj(), "code").get_int();
        return false;
    }

    return true;
}

Object callRPC(string strMethod, vector<string> strParams) {
    Array params = RPCConvertValues(strMethod, strParams);
    return CallRPC(strMethod, params);
}

BOOST_FIXTURE_TEST_CASE(rpc_scrapes, RPCServerFixture)
{
    // Wait a little bit to try to make sure the thread is fully started
    MilliSleep(100);

    /* This is a valid private key and address, do NOT use this key in a real
     * wallet, your coins will not be secure! */
    string strValidAddress = "ino6A7pZSa4Adsa6jLEzWvQfFW4WmLe2Ye";
    string strValidPrivKey = "PhWG55HKGLu6VVS27CyYrJ7q8z4xuFzqTGvj7ReRTn73ATTsCQgU";
    string strValidAddress2 = "iXDFQSLFFZ448bxXF9KPoJTSjqgCmQptRQ";

    // error: {"code":-8,"message":"Staking address must be in wallet."}
    string strMethod = "setscrapeaddress";
    vector<string> strParams;
    strParams.push_back(strValidAddress);
    strParams.push_back(strValidAddress2);

    Object obj = callRPC(strMethod, strParams);

    int error_code;
    BOOST_CHECK(!readResponse(obj, error_code));
    BOOST_CHECK_EQUAL(error_code, RPC_INVALID_PARAMETER);

    strMethod = "getscrapeaddress";
    strParams.clear();
    strParams.push_back(strValidAddress);

    obj = callRPC(strMethod, strParams);

    BOOST_CHECK(!readResponse(obj, error_code));
    BOOST_CHECK_EQUAL(error_code, RPC_INVALID_PARAMETER);

    strMethod = "deletescrapeaddress";

    obj = callRPC(strMethod, strParams);

    BOOST_CHECK(!readResponse(obj, error_code));
    BOOST_CHECK_EQUAL(error_code, RPC_INVALID_PARAMETER);

    // Import a valid private key for testing on.
    strMethod = "importprivkey";
    strParams.clear();
    strParams.push_back(strValidPrivKey);
    strParams.push_back("test");

    obj = callRPC(strMethod, strParams);

    BOOST_CHECK(readResponse(obj, error_code));

    // // error: {"code":-5,"message":"Invalid address."}
    strMethod = "setscrapeaddress";
    strParams.clear();
    strParams.push_back("ino6A7pZSa4A");
    strParams.push_back("iXDFQSLFFZ44");

    obj = callRPC(strMethod, strParams);

    BOOST_CHECK(!readResponse(obj, error_code));
    BOOST_CHECK_EQUAL(error_code, RPC_INVALID_ADDRESS_OR_KEY);

    strMethod = "getscrapeaddress";
    strParams.clear();
    strParams.push_back("ino6A7pZSa4A");

    obj = callRPC(strMethod, strParams);

    BOOST_CHECK(!readResponse(obj, error_code));
    BOOST_CHECK_EQUAL(error_code, RPC_INVALID_ADDRESS_OR_KEY);

    strMethod = "deletescrapeaddress";
    strParams.clear();
    strParams.push_back("ino6A7pZSa4A");

    obj = callRPC(strMethod, strParams);

    BOOST_CHECK(!readResponse(obj, error_code));
    BOOST_CHECK_EQUAL(error_code, RPC_INVALID_ADDRESS_OR_KEY);

    // error: {"code":-5,"message":"Invalid scrape address."}
    strMethod = "setscrapeaddress";
    strParams.clear();
    strParams.push_back(strValidAddress);
    strParams.push_back("iXDFQSLFFZ44");

    obj = callRPC(strMethod, strParams);

    BOOST_CHECK(!readResponse(obj, error_code));
    BOOST_CHECK_EQUAL(error_code, RPC_INVALID_ADDRESS_OR_KEY);

    // error: {"code":-8,"message":"Cannot set scrape address to the same as staking address."}
    strParams.clear();
    strParams.push_back(strValidAddress);
    strParams.push_back(strValidAddress);

    obj = callRPC(strMethod, strParams);

    BOOST_CHECK(!readResponse(obj, error_code));
    BOOST_CHECK_EQUAL(error_code, RPC_INVALID_PARAMETER);

    // error: ("code":-1,"message":"No scrape address set for address <staking address>")
    strMethod = "getscrapeaddress";
    strParams.clear();
    strParams.push_back(strValidAddress);

    obj = callRPC(strMethod, strParams);

    BOOST_CHECK(!readResponse(obj, error_code));
    BOOST_CHECK_EQUAL(error_code, RPC_WALLET_ERROR);

    strMethod = "deletescrapeaddress";

    obj = callRPC(strMethod, strParams);

    BOOST_CHECK(!readResponse(obj, error_code));
    BOOST_CHECK_EQUAL(error_code, RPC_WALLET_ERROR);

    // Valid setscrapeaddress
    strMethod = "setscrapeaddress";
    strParams.clear();
    strParams.push_back(strValidAddress);
    strParams.push_back(strValidAddress2);

    obj = callRPC(strMethod, strParams);

    BOOST_CHECK(readResponse(obj, error_code));

    // Valid getscrapeaddress
    strMethod = "getscrapeaddress";
    strParams.clear();
    strParams.push_back(strValidAddress);

    obj = callRPC(strMethod, strParams);

    BOOST_CHECK(readResponse(obj, error_code));

    // Valid deletescrapeaddress
    strMethod = "deletescrapeaddress";

    obj = callRPC(strMethod, strParams);

    BOOST_CHECK(readResponse(obj, error_code));
}

BOOST_AUTO_TEST_SUITE_END()
