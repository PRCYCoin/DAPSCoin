<<<<<<< HEAD
// Copyright (c) 2015-2018 The PIVX developers
// Copyright (c) 2018-2020 The DAPS Project developers
=======
// Copyright (c) 2017-2020 The PIVX developers
>>>>>>> 6ed103f204953728b4b97b6363e44051b274582e
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "bip38.h"
<<<<<<< HEAD
#include "base58.h"
#include "hash.h"
#include "pubkey.h"
#include "util.h"
#include "utilstrencodings.h"

#include <openssl/aes.h>
#include <openssl/sha.h>
#include <secp256k1.h>
#include <string>

=======

#include "base58.h"
#include "crypto/aes.h"
#include "key_io.h"
#include "hash.h"
#include "utilstrencodings.h"
#include "random.h"

#include <secp256k1.h>
#include <string>

static bool Base58ToHex(const std::string& base58_str, std::string& hex_str)
{
    // Base58 decoding
    // it must be 39 bytes - and another 4 bytes for base58 checksum
    size_t key_size = 39 + 4;
    std::vector<unsigned char> vchKey;
    if (!DecodeBase58(base58_str.c_str(), vchKey, key_size) || vchKey.size() != key_size) {
        return false;
    }
    // Hex enconding
    std::stringstream ss;
    ss << std::hex;
    for (unsigned int i = 0; i < vchKey.size(); i++) {
        const unsigned char* c = vchKey.data() + i;
        ss << std::setw(2) << std::setfill('0') << (int)*c;
    }
    hex_str = ss.str();
    return true;
}

>>>>>>> 6ed103f204953728b4b97b6363e44051b274582e

/** 39 bytes - 78 characters
 * 1) Prefix - 2 bytes - 4 chars - strKey[0..3]
 * 2) Flagbyte - 1 byte - 2 chars - strKey[4..5]
 * 3) addresshash - 4 bytes - 8 chars - strKey[6..13]
 * 4) Owner Entropy - 8 bytes - 16 chars - strKey[14..29]
 * 5) Encrypted Part 1 - 8 bytes - 16 chars - strKey[30..45]
 * 6) Encrypted Part 2 - 16 bytes - 32 chars - strKey[46..77]
 */

void DecryptAES(uint256 encryptedIn, uint256 decryptionKey, uint256& output)
{
<<<<<<< HEAD
    AES_KEY key;
    AES_set_decrypt_key(decryptionKey.begin(), 256, &key);
    AES_decrypt(encryptedIn.begin(), output.begin(), &key);
=======
    AES256Decrypt(decryptionKey.begin()).Decrypt(output.begin(), encryptedIn.begin());
>>>>>>> 6ed103f204953728b4b97b6363e44051b274582e
}

void ComputePreFactor(std::string strPassphrase, std::string strSalt, uint256& prefactor)
{
    //passfactor is the scrypt hash of passphrase and ownersalt (NOTE this needs to handle alt cases too in the future)
<<<<<<< HEAD
    uint64_t s = uint256(ReverseEndianString(strSalt)).Get64();
=======
    uint64_t s = uint256S(ReverseEndianString(strSalt)).GetCheapHash();
>>>>>>> 6ed103f204953728b4b97b6363e44051b274582e
    scrypt_hash(strPassphrase.c_str(), strPassphrase.size(), BEGIN(s), strSalt.size() / 2, BEGIN(prefactor), 16384, 8, 8, 32);
}

void ComputePassfactor(std::string ownersalt, uint256 prefactor, uint256& passfactor)
{
    //concat prefactor and ownersalt
<<<<<<< HEAD
    uint512 temp(ReverseEndianString(HexStr(prefactor) + ownersalt));
    Hash(temp.begin(), 40, passfactor.begin()); //40 bytes is the length of prefactor + salt
    Hash(passfactor.begin(), 32, passfactor.begin());
=======
    uint512 temp = uint512S(ReverseEndianString(HexStr(prefactor) + ownersalt));
    Hash(temp.begin(), temp.end(), passfactor.begin(), passfactor.end());
>>>>>>> 6ed103f204953728b4b97b6363e44051b274582e
}

bool ComputePasspoint(uint256 passfactor, CPubKey& passpoint)
{
<<<<<<< HEAD
    //passpoint is the ec_mult of passfactor on secp256k1
    int clen = 65;
    return secp256k1_ec_pubkey_create(UBEGIN(passpoint), &clen, passfactor.begin(), true) != 0;
=======
    size_t clen = 65;
    secp256k1_context *ctx = secp256k1_context_create(SECP256K1_CONTEXT_SIGN);
    assert(ctx != nullptr);
    {
        // Pass in a random blinding seed to the secp256k1 context.
        std::vector<unsigned char, secure_allocator<unsigned char>> vseed(32);
        GetRandBytes(vseed.data(), 32);
        bool ret = secp256k1_context_randomize(ctx, vseed.data());
        assert(ret);
    }
    secp256k1_pubkey pubkey;

    //passpoint is the ec_mult of passfactor on secp256k1
    if (!secp256k1_ec_pubkey_create(ctx, &pubkey, passfactor.begin())) {
        secp256k1_context_destroy(ctx);
        return false;
    }

    secp256k1_ec_pubkey_serialize(ctx, (unsigned char*)passpoint.begin(), &clen, &pubkey, SECP256K1_EC_COMPRESSED);
    secp256k1_context_destroy(ctx);

    if (passpoint.size() != clen)
        return false;

    if (!passpoint.IsValid())
        return false;

    return true;
>>>>>>> 6ed103f204953728b4b97b6363e44051b274582e
}

void ComputeSeedBPass(CPubKey passpoint, std::string strAddressHash, std::string strOwnerSalt, uint512& seedBPass)
{
    // Derive decryption key for seedb using scrypt with passpoint, addresshash, and ownerentropy
<<<<<<< HEAD
    string salt = ReverseEndianString(strAddressHash + strOwnerSalt);
    uint256 s2(salt);
=======
    std::string salt = ReverseEndianString(strAddressHash + strOwnerSalt);
    uint256 s2(uint256S(salt));
>>>>>>> 6ed103f204953728b4b97b6363e44051b274582e
    scrypt_hash(BEGIN(passpoint), HexStr(passpoint).size() / 2, BEGIN(s2), salt.size() / 2, BEGIN(seedBPass), 1024, 1, 1, 64);
}

void ComputeFactorB(uint256 seedB, uint256& factorB)
{
    //factorB - a double sha256 hash of seedb
<<<<<<< HEAD
    Hash(seedB.begin(), 24, factorB.begin()); //seedB is only 24 bytes
    Hash(factorB.begin(), 32, factorB.begin());
}

std::string AddressToBip38Hash(std::string address)
{
    uint256 addrCheck;
    Hash((void*)address.c_str(), address.size(), addrCheck.begin());
    Hash(addrCheck.begin(), 32, addrCheck.begin());
=======
    Hash(seedB.begin(), seedB.end(), factorB.begin(), factorB.end());
}

std::string AddressToBip38Hash(const std::string& address)
{
    uint256 addrCheck = Hash(address.begin(), address.end());
>>>>>>> 6ed103f204953728b4b97b6363e44051b274582e

    return HexStr(addrCheck).substr(0, 8);
}

std::string BIP38_Encrypt(std::string strAddress, std::string strPassphrase, uint256 privKey, bool fCompressed)
{
<<<<<<< HEAD
    string strAddressHash = AddressToBip38Hash(strAddress);

    uint512 hashed;
    uint64_t salt = uint256(ReverseEndianString(strAddressHash)).Get64();
    scrypt_hash(strPassphrase.c_str(), strPassphrase.size(), BEGIN(salt), strAddressHash.size() / 2, BEGIN(hashed), 16384, 8, 8, 64);

    uint256 derivedHalf1(hashed.ToString().substr(64, 64));
    uint256 derivedHalf2(hashed.ToString().substr(0, 64));

    //block1 = (pointb[1...16] xor derivedhalf1[0...15])
    uint256 block1 = uint256((privKey << 128) ^ (derivedHalf1 << 128)) >> 128;

    //encrypt part 1
    uint512 encrypted1;
    AES_KEY key;
    AES_set_encrypt_key(derivedHalf2.begin(), 256, &key);
    AES_encrypt(block1.begin(), encrypted1.begin(), &key);

    //block2 = (pointb[17...32] xor derivedhalf1[16...31]
    uint256 p2 = privKey >> 128;
    uint256 dh12 = derivedHalf1 >> 128;
    uint256 block2 = uint256(p2 ^ dh12);

    //encrypt part 2
    uint512 encrypted2;
    AES_encrypt(block2.begin(), encrypted2.begin(), &key);

    string strPrefix = "0142";
    strPrefix += (fCompressed ? "E0" : "C0");

    uint512 encryptedKey(ReverseEndianString(strPrefix + strAddressHash));
=======
    std::string strAddressHash = AddressToBip38Hash(strAddress);

    uint512 hashed;
    uint64_t salt = uint256S(ReverseEndianString(strAddressHash)).GetCheapHash();
    scrypt_hash(strPassphrase.c_str(), strPassphrase.size(), BEGIN(salt), strAddressHash.size() / 2, BEGIN(hashed), 16384, 8, 8, 64);

    arith_uint256 derivedHalf1(hashed.ToString().substr(64, 64));
    arith_uint256 derivedHalf2(hashed.ToString().substr(0, 64));

    //block1 = (pointb[1...16] xor derivedhalf1[0...15])
    arith_uint256 block1 = ((UintToArith256(privKey) << 128) ^ (derivedHalf1 << 128)) >> 128;

    //encrypt part 1
    arith_uint512 encrypted1;
    AES256Encrypt enc(derivedHalf2.begin());
    enc.Encrypt(encrypted1.begin(), block1.begin());

    //block2 = (pointb[17...32] xor derivedhalf1[16...31]
    arith_uint256 p2 = UintToArith256(privKey) >> 128;
    arith_uint256 dh12 = derivedHalf1 >> 128;
    arith_uint256 block2 = p2 ^ dh12;

    //encrypt part 2
    arith_uint512 encrypted2;
    enc.Encrypt(encrypted2.begin(), block2.begin());

    std::string strPrefix = "0142";
    strPrefix += (fCompressed ? "E0" : "C0");

    arith_uint512 encryptedKey(ReverseEndianString(strPrefix + strAddressHash));
>>>>>>> 6ed103f204953728b4b97b6363e44051b274582e

    //add encrypted1 to the end of encryptedKey
    encryptedKey = encryptedKey | (encrypted1 << 56);

    //add encrypted2 to the end of encryptedKey
    encryptedKey = encryptedKey | (encrypted2 << (56 + 128));

    //Base58 checksum is the 4 bytes of dSHA256 hash of the encrypted key
    uint256 hashChecksum = Hash(encryptedKey.begin(), encryptedKey.begin() + 39);
<<<<<<< HEAD
    uint512 b58Checksum(hashChecksum.ToString().substr(64 - 8, 8));
=======
    arith_uint512 b58Checksum(hashChecksum.ToString().substr(64 - 8, 8));
>>>>>>> 6ed103f204953728b4b97b6363e44051b274582e

    // append the encrypted key with checksum (currently occupies 312 bits)
    encryptedKey = encryptedKey | (b58Checksum << 312);

    //43 bytes is the total size that we are encoding
    return EncodeBase58(encryptedKey.begin(), encryptedKey.begin() + 43);
}

bool BIP38_Decrypt(std::string strPassphrase, std::string strEncryptedKey, uint256& privKey, bool& fCompressed)
{
<<<<<<< HEAD
    std::string strKey = DecodeBase58(strEncryptedKey.c_str());

    //incorrect encoding of key, it must be 39 bytes - and another 4 bytes for base58 checksum
    if (strKey.size() != (78 + 8))
        return false;

    //invalid prefix
    if (uint256(ReverseEndianString(strKey.substr(0, 2))) != uint256(0x01))
        return false;

    uint256 type(ReverseEndianString(strKey.substr(2, 2)));
    uint256 flag(ReverseEndianString(strKey.substr(4, 2)));
    std::string strAddressHash = strKey.substr(6, 8);
    std::string ownersalt = strKey.substr(14, 16);
    uint256 encryptedPart1(ReverseEndianString(strKey.substr(30, 16)));
    uint256 encryptedPart2(ReverseEndianString(strKey.substr(46, 32)));

    fCompressed = (flag & uint256(0x20)) != 0;

    //not ec multiplied
    if (type == uint256(0x42)) {
        uint512 hashed;
        encryptedPart1 = uint256(ReverseEndianString(strKey.substr(14, 32)));
        uint64_t salt = uint256(ReverseEndianString(strAddressHash)).Get64();
        scrypt_hash(strPassphrase.c_str(), strPassphrase.size(), BEGIN(salt), strAddressHash.size() / 2, BEGIN(hashed), 16384, 8, 8, 64);

        uint256 derivedHalf1(hashed.ToString().substr(64, 64));
        uint256 derivedHalf2(hashed.ToString().substr(0, 64));
=======
    std::string strKey;
    if (!Base58ToHex(strEncryptedKey, strKey)) {
        // incorrect encoding of key
        return false;
    }

    // invalid prefix
    if (uint256S(ReverseEndianString(strKey.substr(0, 2))) != UINT256_ONE)
        return false;

    arith_uint256 type(ReverseEndianString(strKey.substr(2, 2)));
    arith_uint256 flag(ReverseEndianString(strKey.substr(4, 2)));
    std::string strAddressHash = strKey.substr(6, 8);
    std::string ownersalt = strKey.substr(14, 16);
    uint256 encryptedPart1 = uint256S(ReverseEndianString(strKey.substr(30, 16)));
    uint256 encryptedPart2 = uint256S(ReverseEndianString(strKey.substr(46, 32)));

    fCompressed = (flag & 0x20) != ARITH_UINT256_ZERO;

    //not ec multiplied
    if (type == arith_uint256(0x42)) {
        uint512 hashed;
        encryptedPart1 = uint256S(ReverseEndianString(strKey.substr(14, 32)));
        uint64_t salt = uint256S(ReverseEndianString(strAddressHash)).GetCheapHash();
        scrypt_hash(strPassphrase.c_str(), strPassphrase.size(), BEGIN(salt), strAddressHash.size() / 2, BEGIN(hashed), 16384, 8, 8, 64);

        const uint256& derivedHalf1 = uint256S(hashed.ToString().substr(64, 64));
        const uint256& derivedHalf2 = uint256S(hashed.ToString().substr(0, 64));
>>>>>>> 6ed103f204953728b4b97b6363e44051b274582e

        uint256 decryptedPart1;
        DecryptAES(encryptedPart1, derivedHalf2, decryptedPart1);

        uint256 decryptedPart2;
        DecryptAES(encryptedPart2, derivedHalf2, decryptedPart2);

        //combine decrypted parts into 64 bytes
<<<<<<< HEAD
        uint256 temp1 = decryptedPart2 << 128;
        temp1 = temp1 | decryptedPart1;

        //xor the decryption with the derived half 1 for the final key
        privKey = temp1 ^ derivedHalf1;

        return true;
    } else if (type != uint256(0x43)) //invalid type
        return false;
=======
        arith_uint256 temp1 = UintToArith256(decryptedPart2) << 128;
        temp1 = temp1 | UintToArith256(decryptedPart1);

        //xor the decryption with the derived half 1 for the final key
        privKey = ArithToUint256(temp1 ^ UintToArith256(derivedHalf1));

        return true;
    } else if (type != arith_uint256(0x43)) {
        //invalid type
        return false;
    }
>>>>>>> 6ed103f204953728b4b97b6363e44051b274582e

    bool fLotSequence = (flag & 0x04) != 0;

    std::string prefactorSalt = ownersalt;
    if (fLotSequence)
        prefactorSalt = ownersalt.substr(0, 8);

    uint256 prefactor;
    ComputePreFactor(strPassphrase, prefactorSalt, prefactor);

    uint256 passfactor;
    if (fLotSequence)
        ComputePassfactor(ownersalt, prefactor, passfactor);
    else
        passfactor = prefactor;

    CPubKey passpoint;
    if (!ComputePasspoint(passfactor, passpoint))
        return false;

    uint512 seedBPass;
    ComputeSeedBPass(passpoint, strAddressHash, ownersalt, seedBPass);

    //get derived halfs, being mindful for endian switch
<<<<<<< HEAD
    uint256 derivedHalf1(seedBPass.ToString().substr(64, 64));
    uint256 derivedHalf2(seedBPass.ToString().substr(0, 64));
=======
    const uint256 derivedHalf1 = uint256S(seedBPass.ToString().substr(64, 64));
    const uint256 derivedHalf2 = uint256S(seedBPass.ToString().substr(0, 64));
>>>>>>> 6ed103f204953728b4b97b6363e44051b274582e

    /** Decrypt encryptedpart2 using AES256Decrypt to yield the last 8 bytes of seedb and the last 8 bytes of encryptedpart1. **/
    uint256 decryptedPart2;
    DecryptAES(encryptedPart2, derivedHalf2, decryptedPart2);

    //xor decryptedPart2 and 2nd half of derived half 1
<<<<<<< HEAD
    uint256 x0 = derivedHalf1 >> 128; //drop off the first half (note: endian)
    uint256 x1 = decryptedPart2 ^ x0;
    uint256 seedbPart2 = x1 >> 64;

    /** Decrypt encryptedpart1 to yield the remainder of seedb. **/
    uint256 decryptedPart1;
    uint256 x2 = x1 & uint256("0xffffffffffffffff"); // set x2 to seedbPart1 (still encrypted)
    x2 = x2 << 64;                                   //make room to add encryptedPart1 to the front
    x2 = encryptedPart1 | x2;                        //combine with encryptedPart1
    DecryptAES(x2, derivedHalf2, decryptedPart1);

    //decrypted part 1: seedb[0..15] xor derivedhalf1[0..15]
    uint256 x3 = derivedHalf1 & uint256("0xffffffffffffffffffffffffffffffff");
    uint256 seedbPart1 = decryptedPart1 ^ x3;
    uint256 seedB = seedbPart1 | (seedbPart2 << 128);

    uint256 factorB;
    ComputeFactorB(seedB, factorB);

    //multiply passfactor by factorb mod N to yield the priv key
    privKey = factorB;
    if (!secp256k1_ec_privkey_tweak_mul(privKey.begin(), passfactor.begin()))
        return false;
=======
    arith_uint256 x0 = UintToArith256(derivedHalf1) >> 128; //drop off the first half (note: endian)
    arith_uint256 x1 = UintToArith256(decryptedPart2) ^ x0;
    arith_uint256 seedbPart2 = x1 >> 64;

    /** Decrypt encryptedpart1 to yield the remainder of seedb. **/
    uint256 decryptedPart1;
    arith_uint256 x2 = x1 & arith_uint256("0xffffffffffffffff"); // set x2 to seedbPart1 (still encrypted)
    x2 = x2 << 64;                                   //make room to add encryptedPart1 to the front
    x2 = UintToArith256(encryptedPart1) | x2;                        //combine with encryptedPart1
    DecryptAES(ArithToUint256(x2), derivedHalf2, decryptedPart1);

    //decrypted part 1: seedb[0..15] xor derivedhalf1[0..15]
    arith_uint256 x3 = UintToArith256(derivedHalf1) & arith_uint256("0xffffffffffffffffffffffffffffffff");
    arith_uint256 seedbPart1 = UintToArith256(decryptedPart1) ^ x3;
    arith_uint256 seedB = seedbPart1 | (seedbPart2 << 128);

    uint256 factorB;
    ComputeFactorB(ArithToUint256(seedB), factorB);

    //multiply passfactor by factorb mod N to yield the priv key
    secp256k1_context *ctx = secp256k1_context_create(SECP256K1_CONTEXT_SIGN);
    assert(ctx != nullptr);
    {
        // Pass in a random blinding seed to the secp256k1 context.
        std::vector<unsigned char, secure_allocator<unsigned char>> vseed(32);
        GetRandBytes(vseed.data(), 32);
        bool ret = secp256k1_context_randomize(ctx, vseed.data());
        assert(ret);
    }
    privKey = factorB;
    if (!secp256k1_ec_privkey_tweak_mul(ctx, privKey.begin(), passfactor.begin())) {
        secp256k1_context_destroy(ctx);
        return false;
    }
    secp256k1_context_destroy(ctx);
>>>>>>> 6ed103f204953728b4b97b6363e44051b274582e

    //double check that the address hash matches our final privkey
    CKey k;
    k.Set(privKey.begin(), privKey.end(), fCompressed);
    CPubKey pubkey = k.GetPubKey();
<<<<<<< HEAD
    string address = CBitcoinAddress(pubkey.GetID()).ToString();
=======
    std::string address = EncodeDestination(pubkey.GetID());
>>>>>>> 6ed103f204953728b4b97b6363e44051b274582e

    return strAddressHash == AddressToBip38Hash(address);
}
