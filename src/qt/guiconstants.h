// Copyright (c) 2011-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2018 The PIVX developers
<<<<<<< HEAD
// Copyright (c) 2018-2020 The DAPS Project developers
=======
>>>>>>> 6ed103f204953728b4b97b6363e44051b274582e
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_GUICONSTANTS_H
#define BITCOIN_QT_GUICONSTANTS_H

/* Milliseconds between model updates */
static const int MODEL_UPDATE_DELAY = 1000;

/* AskPassphraseDialog -- Maximum passphrase length */
static const int MAX_PASSPHRASE_SIZE = 1024;

<<<<<<< HEAD
/* Prcycoin GUI -- Size of icons in status bar */
=======
/* Pivx GUI -- Size of icons in status bar */
>>>>>>> 6ed103f204953728b4b97b6363e44051b274582e
static const int STATUSBAR_ICONSIZE = 16;

static const bool DEFAULT_SPLASHSCREEN = true;

/* Invalid field background style */
#define STYLE_INVALID "background:#FF8080"

/* Transaction list -- unconfirmed transaction */
<<<<<<< HEAD
#define COLOR_UNCONFIRMED QColor(128, 128, 128)
/* Transaction list -- negative amount */
#define COLOR_NEGATIVE QColor(255, 0, 0)
=======
#define COLOR_UNCONFIRMED QColor(91, 76, 134)
/* Transaction list -- negative amount */
#define COLOR_NEGATIVE QColor(206, 0, 188)
>>>>>>> 6ed103f204953728b4b97b6363e44051b274582e
/* Transaction list -- bare address (without label) */
#define COLOR_BAREADDRESS QColor(140, 140, 140)
/* Transaction list -- TX status decoration - open until date */
#define COLOR_TX_STATUS_OPENUNTILDATE QColor(64, 64, 255)
<<<<<<< HEAD
/* Transaction list -- TX status decoration - offline */
#define COLOR_TX_STATUS_OFFLINE QColor(192, 192, 192)
=======
>>>>>>> 6ed103f204953728b4b97b6363e44051b274582e
/* Transaction list -- TX status decoration - default color */
#define COLOR_BLACK QColor(51, 51, 51)
/* Transaction list -- TX status decoration - conflicted */
#define COLOR_CONFLICTED QColor(255, 0, 0)
/* Transaction list -- TX status decoration - orphan (Light Gray #D3D3D3) */
#define COLOR_ORPHAN QColor(211, 211, 211)
/* Transaction list -- TX status decoration - stake (BlueViolet #8A2BE2) */
#define COLOR_STAKE QColor(138,43,226)
/* Tooltips longer than this (in characters) are converted into rich text,
   so that they can be word-wrapped.
 */
static const int TOOLTIP_WRAP_THRESHOLD = 80;

/* Maximum allowed URI length */
static const int MAX_URI_LENGTH = 255;

/* QRCodeDialog -- size of exported QR Code image */
#define EXPORT_IMAGE_SIZE 256

<<<<<<< HEAD
/* Number of frames in spinner animation */
#define SPINNER_FRAMES 35

#define QAPP_ORG_NAME "PRCY"
#define QAPP_ORG_DOMAIN "prcycoin.com"
#define QAPP_APP_NAME_DEFAULT "PRCYcoin-Qt"
#define QAPP_APP_NAME_TESTNET "PRCYcoin-Qt-testnet"
=======

#define QAPP_ORG_NAME "PIVX"
#define QAPP_ORG_DOMAIN "pivx.org"
#define QAPP_APP_NAME_DEFAULT "PIVX-Qt"
#define QAPP_APP_NAME_TESTNET "PIVX-Qt-testnet"
>>>>>>> 6ed103f204953728b4b97b6363e44051b274582e

#endif // BITCOIN_QT_GUICONSTANTS_H
