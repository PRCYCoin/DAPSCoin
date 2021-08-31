// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2018 The PIVX developers
// Copyright (c) 2018-2020 The DAPS Project developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

std::string CDNSSeedData::getHost(uint64_t requiredServiceBits) const {
    //use default host for non-filter-capable seeds or if we use the default service bits (NODE_NETWORK)
    if (!supportsServiceBitsFiltering || requiredServiceBits == NODE_NETWORK)
        return host;

    return strprintf("x%x.%s", requiredServiceBits, host);
}

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256("0000039a711dba61e12c29fb86542fa059e9616aafe9b4c61e065d393f31535e"))
    (32653, uint256("eaab21ed33e4f1245310693023bbbdb1ae3066b1ba14bebb028a3a994de241c2"))
    (146898, uint256("a0e3853d98c6d60febd57ad2c879e590bda09de271527b396efc5be22ab5ce9e"))
    (146899, uint256("22c90bbb2ae11c3bd5fd6c716d543f8f207e6379e14d26fc04ba7220681dd13b"))
    (146900, uint256("a879e6b5f62ed437d2108366a8152130c21df38322556f06dd71ad08854210b8"))
    (147000, uint256("e60eb87bdbeaee7582826418c8c4504637e51684a3e631b5683390497a4e2535"))
    (147200, uint256("55fcf4abbd7a1b3aa91460378c3b833f9d1569780b0a1e7e6ee2d1b3a4256b24"))
    (147400, uint256("15d8ed0575995a4b3ab8337d87213943abb9e3fba5389c57cbd48a2751f78a5d"))
    (188549, uint256("cfe3696e23e393fa9230f84dfa16a505ac3f40fd147a79adba8a54fa17d24e91"))
    (209577, uint256("5231320be89de8a0fdebbd45d4d0c58abb1ea7a134ba52a11a2036f32d90e66c"))
    (458733, uint256("51d7f917147f3bec3f2e6767fd70c14730a0b0773a7b967e827336e936cf50e2"))
    (458734, uint256("35ff8e3884036187ed56e7d4a4adda3e0f75eac5655afd4cef8605954b28362f"))
    (719455, uint256("ff67a6645a36a82a3885c989951680917c9e2de90f59665c8130701ccdcbb9f9")) // Blocks surrounding chain split
    (719456, uint256("d56f2e69ab04a02ad766d45c98916c85aac3fa4d2b03a8f4a73a67d81c5260b3")) // Blocks surrounding chain split
    (719457, uint256("2cda22a56c901fc8bb9ef7ae9690756a8107845ab3086c4ab4a97f1c0688a41d")) // Blocks surrounding chain split
    (719538, uint256("038a354dcdf04090defc8457f70569f908bbc645a50644d61b33dac014e6cf84")) // Block many people are getting stuck on
    (803585, uint256("34ffd432abf79afeac0b0c005538de9b4c3e9f31ea4a63b627ce3cf5fa56a133")) // First PoA block after Hard Fork
    ;
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1604141839, // * UNIX timestamp of last checkpoint block
    1765448,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    1440        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x00000561b6da32b1b305690648d7eec908a538e9b9f496f1a9ad5d20ed533af8"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1536808115,
    0,
    0};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x519fc91c13da2eb1301e87ebb7db993f15b57fb1fd7f3e172411bf4262c2efdb"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1536808341,
    0,
    0};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xa4;
        pchMessageStart[1] = 0xb7;
        pchMessageStart[2] = 0x79;
        pchMessageStart[3] = 0x84;
        nDefaultPort = 53572;
        bnProofOfWorkLimit = ~uint256(0) >> 1; // DAPScoin starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // DAPScoin: 1 day
        nTargetSpacing = 1 * 60;  // DAPScoin: 1 minute
        nMaturity = 100;
        nMasternodeCountDrift = 20;
        MAX_MONEY = 2000000000.0;
        nMaxMoneyOut = MAX_MONEY * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 500;
        nStartPOABlock = 560;
        nModifierUpdateBlock = 615800;
        nPoABlockTime = 60 * 60; //a PoA block every 30 minutes
        nMinNumPoSBlocks = 59;
        nMaxNumPoSBlocks = 120;
        nSoftForkBlock = 125000; // Soft fork block for difficulty change
        nHardForkBlock = 670000; // Hard fork block for PoA updates
        nTreasuryForkBlock = 1180000; // Treasury fork
        nTreasuryForkBlockVersion = 5; // Treasury fork

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         *
         * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
         *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
         *   vMerkleTree: e0028e
         */
        const char* pszTimestamp = "30 September 2019 DAPS Coin Development Team - Privacy Is A Right, Not A Privilege";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("041db2a1b75bc00fc1a18e9f8de27c65fede32eb9ac1c11e2587402a66732656d71f7b5de649c8dc7f94aeb433485ce3122ba856644b02e433c2d5fc94ea26bf8e") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1569750052; //09/29/2019 @ 9:40am (UTC)
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 18289272;

        //change blockhash from 0x00000e9468bba3df97334bfb5015543488a0fb38193c82b101472937590e3037 because of transaction structure change
        if(genesis.GetHash()!=uint256("0000039a711dba61e12c29fb86542fa059e9616aafe9b4c61e065d393f31535e"))
        {
            printf("Searchingforgenesisblock...\n");
            uint256 hashTarget=uint256().SetCompact(genesis.nBits);

            printf("hashTarget:%s\n",hashTarget.ToString().c_str());

            while(uint256(genesis.GetHash())>hashTarget)
            {
                printf("loop:%s\n",genesis.GetHash().ToString().c_str());
                ++genesis.nNonce;
                if(genesis.nNonce==0)
                {
                    printf("NONCEWRAPPED,incrementingtime");
                    std::cout<<std::string("NONCEWRAPPED,incrementingtime:\n");
                    ++genesis.nTime;
                }
                if(genesis.nNonce%10000==0)
                {
                    printf("Mainnet:nonce%08u:hash=%s\n",genesis.nNonce,genesis.GetHash().ToString().c_str());
                }
            }
            printf("block.nTime=%u\n",genesis.nTime);
            printf("block.nNonce=%u\n",genesis.nNonce);
            printf("block.GetHash=%s\n",genesis.GetHash().ToString().c_str());
            printf("hashMerkleRoot=%s\n",genesis.hashMerkleRoot.ToString().c_str());

        }



        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0000039a711dba61e12c29fb86542fa059e9616aafe9b4c61e065d393f31535e"));
        assert(genesis.hashMerkleRoot == uint256("4dc798fa29a037570075a87a39c9a54c210f005c4c59c72f32036a87273f4cf8"));

        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("seed.dapscoin.com", "seed.dapscoin.com"));        // Single node address
        vSeeds.push_back(CDNSSeedData("seed1.dapscoin.com", "seed1.dapscoin.com"));        // Single node address
        vSeeds.push_back(CDNSSeedData("seed2.dapscoin.com", "seed2.dapscoin.com"));        // Single node address
        vSeeds.push_back(CDNSSeedData("seed3.dapscoin.com", "seed3.dapscoin.com"));        // Single node address
        vSeeds.push_back(CDNSSeedData("seed4.dapscoin.com", "seed4.dapscoin.com"));        // Single node address
        vSeeds.push_back(CDNSSeedData("seed5.dapscoin.com", "seed5.dapscoin.com"));        // Single node address
        vSeeds.push_back(CDNSSeedData("vps.dapscoin.com", "vps.dapscoin.com"));        // Single node address
        vSeeds.push_back(CDNSSeedData("vps1.dapscoin.com", "vps1.dapscoin.com"));        // Single node address
        vSeeds.push_back(CDNSSeedData("vps2.dapscoin.com", "vps2.dapscoin.com"));        // Single node address
        vSeeds.push_back(CDNSSeedData("vps3.dapscoin.com", "vps3.dapscoin.com"));        // Single node address
        vSeeds.push_back(CDNSSeedData("vps4.dapscoin.com", "vps4.dapscoin.com"));        // Single node address
        vSeeds.push_back(CDNSSeedData("vps5.dapscoin.com", "vps5.dapscoin.com"));        // Single node address

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 30);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 13);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 212);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        nExtCoinType = 0x80000166;

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strObfuscationPoolDummyAddress = "D87q2gC9j6nNrnzCsg4aY6bHMLsT9nUhEw";
        nStartMasternodePayments = 1546809115; //Wed, 25 Jun 2014 20:36:16 GMT
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xa5;
        pchMessageStart[1] = 0xb8;
        pchMessageStart[2] = 0x7a;
        pchMessageStart[3] = 0x85;
        nDefaultPort = 53574;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // DAPScoin: 1 day
        nTargetSpacing = 1 * 60;  // DAPScoin: 1 minute
        nLastPOWBlock = 500;
        nStartPOABlock = 560;
        nPoABlockTime = 30 * 60;  //1 PoA block every 30 minutes
        nMinNumPoSBlocks = 20;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 51197; //approx Mon, 17 Apr 2017 04:00:00 GMT
        MAX_MONEY = 5000000000.0;
        nMaxMoneyOut = MAX_MONEY * COIN;
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 9908000; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 9891737; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 9891730; //Last valid accumulator checkpoint
        nBlockEnforceInvalidUTXO = 9902850; //Start enforcing the invalid UTXO's
        nSoftForkBlock = 0; // Soft fork block for difficulty change - testnet started with it
        nHardForkBlock = 92000; // Hard fork block for PoA updates
        nTreasuryForkBlock = 0;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1590109816;
        genesis.nNonce = 16517940;

        if(genesis.GetHash()!=uint256("00000bbcb4a383121aba2a64bc37241b91ea0be6c7584e869d3ca1c05b03a793"))
        {
            printf("Searchingforgenesisblock...\n");
            uint256 hashTarget=uint256().SetCompact(genesis.nBits);

            printf("hashTarget:%s\n",hashTarget.ToString().c_str());

            while(uint256(genesis.GetHash())>hashTarget)
            {
                printf("loop:%s\n",genesis.GetHash().ToString().c_str());
                ++genesis.nNonce;
                if(genesis.nNonce==0)
                {
                    printf("NONCEWRAPPED,incrementingtime");
                    std::cout<<std::string("NONCEWRAPPED,incrementingtime:\n");
                    ++genesis.nTime;
                }
                if(genesis.nNonce%10000==0)
                {
                    printf("Mainnet:nonce%08u:hash=%s\n",genesis.nNonce,genesis.GetHash().ToString().c_str());
                }
            }
            printf("block.nTime=%u\n",genesis.nTime);
            printf("block.nNonce=%u\n",genesis.nNonce);
            printf("block.GetHash=%s\n",genesis.GetHash().ToString().c_str());
            printf("hashMerkleRoot=%s\n",genesis.hashMerkleRoot.ToString().c_str());

        }

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("00000bbcb4a383121aba2a64bc37241b91ea0be6c7584e869d3ca1c05b03a793"));

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("testnet.dapscoin-seeds.com", "testnet.dapscoin-seeds.com"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet dapscoin addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet dapscoin script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet dapscoin BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet dapscoin BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet dapscoin BIP44 coin type is '1' (All coin's testnet default)
        nExtCoinType = 0x80000001;

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strObfuscationPoolDummyAddress = "y57cqfGRkekRyDRNeJiLtYVEbvhXrNbmox";
        nStartMasternodePayments = 1420837558; //Fri, 09 Jan 2015 21:05:58 GMT
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0x7e;
        pchMessageStart[3] = 0xac;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // Dapscoin: 1 day
        nTargetSpacing = 1 * 60;        // Dapscoin: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1569319143;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 12359;
        nTreasuryForkBlock = 0;

        if(genesis.GetHash()!=uint256("2ed32054ce47f012ff186e6116b4906a8cd9d73ff5c689a8623bf36aed774536"))
        {
            printf("Searchingforgenesisblock...\n");
            uint256 hashTarget=uint256().SetCompact(genesis.nBits);

            printf("hashTarget:%s\n",hashTarget.ToString().c_str());

            while(uint256(genesis.GetHash())>hashTarget)
            {
                printf("loop:%s\n",genesis.GetHash().ToString().c_str());
                ++genesis.nNonce;
                if(genesis.nNonce==0)
                {
                    printf("NONCEWRAPPED,incrementingtime");
                    std::cout<<std::string("NONCEWRAPPED,incrementingtime:\n");
                    ++genesis.nTime;
                }
                if(genesis.nNonce%10000==0)
                {
                    printf("Mainnet:nonce%08u:hash=%s\n",genesis.nNonce,genesis.GetHash().ToString().c_str());
                }
            }
            printf("block.nTime=%u\n",genesis.nTime);
            printf("block.nNonce=%u\n",genesis.nNonce);
            printf("block.GetHash=%s\n",genesis.GetHash().ToString().c_str());
            printf("hashMerkleRoot=%s\n",genesis.hashMerkleRoot.ToString().c_str());

        }

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 51476;

        assert(hashGenesisBlock == uint256("2ed32054ce47f012ff186e6116b4906a8cd9d73ff5c689a8623bf36aed774536"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

static CChainParams* pCurrentParams = 0;

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
