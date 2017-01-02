#include "EXCHANGE.h"

int main(){

	vector<Order> orders;
	string inputOrderString;
	
	while(cin>>inputOrderString){
		switch(TypeOfOrder(inputOrderString)){
			case 'N': {
				Order tempOrder;
				tempOrder = ParseOrderString(inputOrderString);
				orders.push_back(tempOrder);
				break;
			}

			case 'M': {
				ModifyOrder temp;
				temp = ParseModifyString(inputOrderString);
				int index = SearchOrders(orders,temp);
				if(index != -1){
					orders[index].updateValues(temp);
				}
				break;
			}

			case 'T': {
				TradeMessage temp;
				temp = ParseTradeString(inputOrderString);
				int index = SearchOrders(orders,temp);
				if(index != -1){
					orders[index].trade(temp);
				}
				break;
			}

			case 'X': {
				CancelOrder temp;
				temp = ParseCancelString(inputOrderString);
				int index = SearchOrders(orders,temp);
				if(index != -1){
					orders[index].cancelOrder(temp);
				}
				break;
			}

			case 'Q': {
				QueryOrders(orders,inputOrderString);
				break;
			}
		}
	}

	cout<<endl;
	return 0;
}