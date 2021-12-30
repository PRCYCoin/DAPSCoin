// Copyright (c) 2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_ZMQ_ZMQPUBLISHNOTIFIER_H
#define BITCOIN_ZMQ_ZMQPUBLISHNOTIFIER_H

#include "zmqabstractnotifier.h"

class CBlockIndex;

class CZMQAbstractPublishNotifier : public CZMQAbstractNotifier
{
private:
<<<<<<< HEAD
    uint32_t nSequence; // upcounting per message sequence number
=======
    uint32_t nSequence{0}; // upcounting per message sequence number
>>>>>>> 6ed103f204953728b4b97b6363e44051b274582e

public:

    /* send zmq multipart message
       parts:
          * command
          * data
          * message sequence number
    */
    bool SendMessage(const char *command, const void* data, size_t size);

    bool Initialize(void *pcontext);
    void Shutdown();
};

class CZMQPublishHashBlockNotifier : public CZMQAbstractPublishNotifier
{
public:
    bool NotifyBlock(const CBlockIndex *pindex);
};

class CZMQPublishHashTransactionNotifier : public CZMQAbstractPublishNotifier
{
public:
    bool NotifyTransaction(const CTransaction &transaction);
};

<<<<<<< HEAD
class CZMQPublishHashTransactionLockNotifier : public CZMQAbstractPublishNotifier
{
public:
    bool NotifyTransactionLock(const CTransaction &transaction);
};

=======
>>>>>>> 6ed103f204953728b4b97b6363e44051b274582e
class CZMQPublishRawBlockNotifier : public CZMQAbstractPublishNotifier
{
public:
    bool NotifyBlock(const CBlockIndex *pindex);
};

class CZMQPublishRawTransactionNotifier : public CZMQAbstractPublishNotifier
{
public:
    bool NotifyTransaction(const CTransaction &transaction);
};

<<<<<<< HEAD
class CZMQPublishRawTransactionLockNotifier : public CZMQAbstractPublishNotifier
{
public:
    bool NotifyTransactionLock(const CTransaction &transaction);
};

=======
>>>>>>> 6ed103f204953728b4b97b6363e44051b274582e
#endif // BITCOIN_ZMQ_ZMQPUBLISHNOTIFIER_H
