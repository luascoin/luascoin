// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2019 The Luascoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

/**
 * Money parsing/formatting utilities.
 */
#ifndef LUASCOIN_UTIL_MONEYSTR_H
#define LUASCOIN_UTIL_MONEYSTR_H

#include <amount.h>
#include <attributes.h>

#include <string>

/* Do not use these functions to represent or parse monetary amounts to or from
 * JSON but use AmountFromValue and ValueFromAmount for that.
 */
std::string FormatMoney(const CAmount& n);
NODISCARD bool ParseMoney(const std::string& str, CAmount& nRet);
NODISCARD bool ParseMoney(const char* pszIn, CAmount& nRet);

#endif // LUASCOIN_UTIL_MONEYSTR_H
