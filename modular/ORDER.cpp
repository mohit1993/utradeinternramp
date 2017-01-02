#include "ORDER.h"
#include "MODIFYORDER.h"
#include "TRADEMESSAGE.h"
#include "CANCELORDER.h"

Order::Order(string sym,char s,int q,int p){
			symbol = sym;
			side = s;
			qty = q;
			price = p;
		}

bool OrderComparator(Order& order1,Order& order2){

	if(order1.symbol > order2.symbol) return true;

	else if(order1.symbol == order2.symbol){
		if(order1.side < order2.side) return true;
		
		else if(order1.side == order2.side){
			if(order1.side == 'B' && order1.price > order2.price) return true;
			
			else if(order1.side == 'S' && order1.price < order2.price) return true;

			else return false;
		}
		else return false;
	}
	else return false;
}


ostream& operator<<(ostream& out, const Order& obj)  {
    out << obj.symbol << ' ' << obj.side << ' ' << obj.qty << ' ' << obj.price;  
    return out;  
}

void Order::updateValues(ModifyOrder obj){

	price = obj.getNewPrice();
	qty = obj.getNewQuantity();
}

void Order::trade(TradeMessage obj){
	int q = obj.getQuantity();
	if(qty >= q){
		qty = qty - q;
	}
	return;
}

void Order::cancelOrder(CancelOrder obj){
	int q = obj.getQuantity();
	if(qty >= q){
		qty = qty - q;
	}
	return;
}

bool Order::match(ModifyOrder obj){
	if(symbol != obj.getSymbol()) {
		return false;
	}
	
	else if(side != obj.getSide()){
		return false;
	}
	
	else if(qty != obj.getOldQuantity()){
		return false;
	}
	
	else if(price != obj.getOldPrice()){ 
		return false;
	}
	
	else return true;
}

bool Order::match(TradeMessage obj){
	if(symbol != obj.getSymbol()) {
		return false;
	}

	else if(price != obj.getPrice()){ 
		return false;
	}
	
	else return true;
}

bool Order::match(CancelOrder obj){
	if(symbol != obj.getSymbol()){
		return false;
	}

	else if(side != obj.getSide()){
		return false;
	}

	else if(price != obj.getPrice()){ 
		return false;
	}
	
	else return true;
}

void QueryOrders(vector<Order> &orders,string &query){

	string symbol;
	int rank = 0,size = query.size(),i=2,temprank=1;

	bool isSymbolRead = false; 
	
	while(i < size){
		if(isSymbolRead == false){
				while(query[i] != ','){
				symbol += query[i];
				i++;
			}
			i++;
			isSymbolRead = true;
		}

		else{
			while(i < size && query[i]!= ','){
				rank = rank*10 + (int)query[i] - 48;
				i++;
			}
			i++;
		}
	}

	if(rank == 0) return;

	sort(orders.begin(),orders.end(),OrderComparator);

	// for(vector<Order>::iterator it = orders.begin();it != orders.end(); it++){
	//   cout<<*it<<endl;
	// }

	cout<<"SYMBOL: "<<symbol;

	for(vector<Order>::iterator it = orders.begin();it != orders.end(); it++){
		if(temprank <= rank && it->symbol != symbol) continue;

		else if(temprank > 2*rank) break;
		
		else if(temprank > rank && it->symbol != symbol) break;

		else if(temprank <= rank && it->symbol == symbol && it->side == 'B'){
			it->showOrder(temprank);
			temprank++;
		}
		else if(it->symbol == symbol && it->side == 'S'){
			it->showOrder((temprank-rank));
			temprank++;
		}
	}
}

void Order::showOrder(int r){
	cout<<endl;
	if(side == 'B') cout<<"BUY:";
	else if(side == 'S') cout<<"SELL:";

	cout<<" (Rank "<<r<<") "<<qty<<", "<<price;
}