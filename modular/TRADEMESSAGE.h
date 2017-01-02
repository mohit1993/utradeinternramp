#ifndef _TRADE_INCLUDED
#define _TRADE_INCLUDED

#include "standard.h"

class ModifyOrder;
class Order;
class TradeMessage;
class CancelOrder;

class TradeMessage {
	public:
		TradeMessage() = default;

		TradeMessage(string sym,int q,int p){
			symbol = sym;
			quantity = q;
			price = p;
		}

		string getSymbol(){
			return symbol;
		}

		int getPrice(){
			return price;
		}

		int getQuantity(){
			return quantity;
		}

	private:
		string symbol;
		int quantity,price;
};

#endif