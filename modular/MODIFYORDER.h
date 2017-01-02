#ifndef _MODIFYORDER_INCLUDED

#define _MODIFYORDER_INCLUDED

#include "standard.h"
#include "ORDER.h"

class ModifyOrder {
	public:
		ModifyOrder() = default;

		ModifyOrder(string sym,char s,int oq,int nq,int op,int np){
			symbol = sym;
			side = s;
			old_qty = oq;
			new_qty = nq;
			old_price = op;
			new_price = np;
		}
		
		int getNewPrice(){
			return new_price;
		}

		int getNewQuantity(){
			return new_qty;
		}

		string getSymbol(){
			return symbol; 
		}

		char getSide(){
			return side;
		}

		int getOldQuantity(){
			return old_qty;
		}

		int getOldPrice(){
			return old_price;
		}

	private:
		string symbol;
		char side;
		int old_qty,new_qty,old_price,new_price;
};

#endif