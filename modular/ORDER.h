#ifndef _ORDER_INCLUDED

#define _ORDER_INCLUDED

#include "standard.h"

class Order;
class ModifyOrder;
class Order;
class TradeMessage;
class CancelOrder;

class Order {

	public:
		Order() = default;

		Order(string sym,char s,int q,int p);

		friend ostream& operator<<(ostream& out, const Order& obj);

		void updateValues(ModifyOrder);

		void trade(TradeMessage);

		void cancelOrder(CancelOrder);

		bool match(ModifyOrder);

		bool match(TradeMessage);

		bool match(CancelOrder);

		friend bool OrderComparator(Order&,Order&);

		friend void QueryOrders(vector<Order>&,string&);

		void showOrder(int);

	private:
		string symbol;
		char side;
		int qty,price;
};

bool OrderComparator(Order&,Order&);
void QueryOrders(vector<Order>&,string&);

#endif