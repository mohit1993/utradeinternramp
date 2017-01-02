#ifndef _CANCELORDER_INCLUDED

#define _CANCELORDER_INCLUDED

#include "standard.h"

class ModifyOrder;
class Order;
class TradeMessage;
class CancelOrder;

class CancelOrder {
	public:
		CancelOrder() = default;

		CancelOrder(string sym,char s,int q,int p){
			symbol = sym;
			side = s;
			qty = q;
			price = p;
		}

		string getSymbol(){
			return symbol;
		}

		char getSide(){
			return side;
		}

		int getPrice(){
			return price;
		}

		int getQuantity(){
			return qty;
		}

	private:
		string symbol;
		char side;
		int qty,price;
};

#endif