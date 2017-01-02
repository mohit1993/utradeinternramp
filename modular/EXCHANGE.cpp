#include "EXCHANGE.h"

char TypeOfOrder(string s){
	return s[0];
}

int SearchOrders(vector<Order> orders,ModifyOrder obj){

	int result = -1;

	for(int index = 0; index != orders.size();index++){
		if(orders[index].match(obj) == true){
			result = index;
			break;
		}
	}

	return result;
}

int SearchOrders(vector<Order> orders, TradeMessage obj){

	int result = -1;

	for(int index = 0; index != orders.size();index++){
		if(orders[index].match(obj) == true){
			result = index;
			break;
		}
	}

	return result;
}

int SearchOrders(vector<Order> orders, CancelOrder obj){

	int result = -1;

	for(int index = 0; index != orders.size();index++){
		if(orders[index].match(obj) == true){
			result = index;
			break;
		}
	}

	return result;
}

ModifyOrder ParseModifyString(string order){
	string symbol = "";
	char side;
	int oq=0,nq=0,op=0,np=0;

	int stage = 6;

	int i=2;

	while(i < order.size()){
		switch(stage){
			case 6: {
				while(order[i]!= ','){
					symbol += order[i];
					i++;
				}
				i++;
				stage--;
				break;
			}

			case 5: {
				side = order[i];
				i+=2;
				stage--;
				break;
			}

			case 4: {
				while(order[i]!= ','){
					oq = oq*10 + (int)order[i] - 48;
					i++;
				}
				i++;
				stage--;
				break;
			}

			case 3: {
				while(order[i]!= ','){
					nq = nq*10 + (int)order[i] - 48;
					i++;
				}

				i++;
				stage--;
				break;
			}

			case 2: {
				while(order[i]!= ','){
					op = op*10 + (int)order[i] - 48;
					i++;
				}
				i++;
				stage--;
				break;
			}

			case 1: {
				while(i < order.size() && order[i]!= ','){
					np = np*10 + (int)order[i] - 48;
					i++;
				}
				i++;
				stage--;
				break;
			}

			default : cout<<"\nInvalid Stage: "<<stage; 
		}
	}

	ModifyOrder temp(symbol,side,oq,nq,op,np);

	return temp;

}

TradeMessage ParseTradeString(string order){
	string symbol = "";
	int qty=0,price=0;

	int stage = 3; // Implies the number of data types left to parse;

	/* priority 
			4. Symbol
			3. Side
			2. Quantity
			1. Price
	*/

	int i=2; // 2 because 0 = Type of Order...and 1 = ,
	while(i < order.size()){
		switch(stage){
			case 3: {
				while(order[i]!= ','){
					symbol += order[i];
					i++;
				}
				i++;
				stage--;
				break;
			}

			case 2: {
				while(order[i]!= ','){
					qty = qty*10 + (int)order[i] - 48;
					i++;
				}
				i++;
				stage--;
				break;
			}

			case 1: {
				while(i < order.size() && order[i]!= ','){
					price = price*10 + (int)order[i] - 48;
					i++;
				}
				i++;
				stage--;
				break;
			}

			default : cout<<"\nInvalid Stage: "<<stage; 
		}
	}

	TradeMessage temp(symbol,qty,price);

	return temp;
}

CancelOrder ParseCancelString(string order){
	string symbol = "";
	char side;
	int qty=0,price=0;

	int stage = 4; // Implies the number of data types left to parse;

	/* priority 
			4. Symbol
			3. Side
			2. Quantity
			1. Price
	*/

	int i=2; // 2 because 0 = Type of Order...and 1 = ,
	while(i < order.size()){
		switch(stage){
			case 4: {
				while(order[i]!= ','){
					symbol += order[i];
					i++;
				}
				i++;
				stage--;
				break;
			}

			case 3: {
				side = order[i];
				i+=2;
				stage--;
				break;
			}

			case 2: {
				while(order[i]!= ','){
					qty = qty*10 + (int)order[i] - 48;
					i++;
				}
				i++;
				stage--;
				break;
			}

			case 1: {
				while(i < order.size() && order[i]!= ','){
					price = price*10 + (int)order[i] - 48;
					i++;
				}
				i++;
				stage--;
				break;
			}

			default : cout<<"\nInvalid Stage: "<<stage; 
		}
	}

	CancelOrder temp(symbol,side,qty,price);

	return temp;
}

Order ParseOrderString(string order){
	string symbol = "";
	char side;
	int qty=0,price=0;

	int stage = 4; // Implies the number of data types left to parse;

	/* priority 
			4. Symbol
			3. Side
			2. Quantity
			1. Price
	*/

	int i=2; // 2 because 0 = Type of Order...and 1 = ,
	while(i < order.size()){
		switch(stage){
			case 4: {
				while(order[i]!= ','){
					symbol += order[i];
					i++;
				}
				i++;
				stage--;
				break;
			}

			case 3: {
				side = order[i];
				i+=2;
				stage--;
				break;
			}

			case 2: {
				while(order[i]!= ','){
					qty = qty*10 + (int)order[i] - 48;
					i++;
				}
				i++;
				stage--;
				break;
			}

			case 1: {
				while(i < order.size() && order[i]!= ','){
					price = price*10 + (int)order[i] - 48;
					i++;
				}
				i++;
				stage--;
				break;
			}

			default : cout<<"\nInvalid Stage: "<<stage; 
		}
	}

	Order temp(symbol,side,qty,price);

	return temp;
}