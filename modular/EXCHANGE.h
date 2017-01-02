#ifndef _EXCHANGE_INCLUDED

#define _EXCHANGE_INCLUDED

#include "standard.h"

#include "ORDER.h"
#include "CANCELORDER.h"
#include "MODIFYORDER.h"
#include "TRADEMESSAGE.h"

char TypeOfOrder(string);

CancelOrder   ParseCancelString(string);
ModifyOrder   ParseModifyString(string);
Order 		  ParseOrderString(string);
TradeMessage  ParseTradeString(string);

int SearchOrders(vector<Order>, ModifyOrder  obj);
int SearchOrders(vector<Order>, TradeMessage obj);
int SearchOrders(vector<Order>, CancelOrder  obj);

#endif