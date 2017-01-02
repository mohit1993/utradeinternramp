#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class ModifyOrder;
class Order;
class TradeMessage;
class CancelOrder;

Order ParseOrderString(string);

int SearchOrders(vector<Order>, ModifyOrder  obj);
int SearchOrders(vector<Order>, TradeMessage obj);
int SearchOrders(vector<Order>, CancelOrder  obj);

char TypeOfOrder(string);

ModifyOrder  ParseModifyString(string);
TradeMessage ParseTradeString(string);
CancelOrder  ParseCancelString(string);

bool OrderComparator(Order&,Order&);
void QueryOrders(vector<Order>&,string&);

class Order{

	public:
		Order() = default;

		Order(string sym,char s,int q,int p){
			symbol = sym;
			side = s;
			qty = q;
			price = p;
		}

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

void Order::showOrder(int r){
	cout<<endl;
	if(side == 'B') cout<<"BUY:";
	else if(side == 'S') cout<<"SELL:";

	cout<<" (Rank "<<r<<") "<<qty<<", "<<price;
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
	// 	cout<<*it<<endl;
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

ostream& operator<<(ostream& out, const Order& obj)  {
    out << obj.symbol << ' ' << obj.side << ' ' << obj.qty << ' ' << obj.price;  
    return out;  
}

void Order::updateValues(ModifyOrder obj){

	price = obj.getNewPrice();
	qty = obj.getNewQuantity();
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

void Order::trade(TradeMessage obj){
	int q = obj.getQuantity();
	if(qty >= q){
		qty = qty - q;
	}
	return;
}

int main(){

	vector<Order> orders;
	string inputOrderString;

	Order tempOrder;

	while(cin>>inputOrderString){
		switch(TypeOfOrder(inputOrderString)){
			case 'N': {
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
	
	// for(vector<Order>::iterator it = orders.begin();it != orders.end(); it++){
	// 	cout<<*it<<endl;
	// }

	cout<<endl;
	return 0;
}


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