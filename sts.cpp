#include <iostream>
#include <string>
#include <vector>
#include<cmath>
#include<chrono>
#include<ctime>

using namespace std;

class Planet {
    public:
        string name;
        double x_cord,y_cord,z_cord;
        // vector<Planet*> destinations;
        Planet(string name,double x_cord,double y_cord,double z_cord) {
            this->name = name;
            this->x_cord=x_cord;
            this->y_cord=y_cord;
            this->z_cord=z_cord;
        }
        double getx(){
            return x_cord;
        }
        double gety(){
            return y_cord;
        }
        double getz(){
            return z_cord;
        }
        string get_name(){
            return name;
        }
        double getDistance(Planet* other) const {
        return sqrt(pow(this->x_cord - other->getx(), 2) + pow(this->y_cord - other->gety(), 2) + pow(this->z_cord - other->getz(), 2));
    }
};

class Traveller{
    protected:
        int id;
    public:
        static int given_id;
        string name;
        vector<int> list_of_tickets;
        string trav_id;
        string get_name(){
            return name;
        }
        int get_id(){
            return id;
        }
        string get_trav_id(){
            return trav_id;
        }
        void update_id(string id){
            this->trav_id=id;
        }
        
};

class Astrounaut:public Traveller{
    public:
    int experience;
    void push_astro();
    Astrounaut(string name,int experience,string trav_id){
        this->name=name;
        this->experience=experience;
        given_id++;
        this->trav_id=trav_id;
    }
    void set_id(){
        id=given_id;
    }

};

vector<Astrounaut*> list_of_astro;

void Astrounaut::push_astro(){
    list_of_astro.push_back(this);
}



class passenger:public Traveller{
    int validity;
    public:
        passenger(string name,string trav_id){
            this->name=name;
            this->validity=10;
            given_id++;
            this->trav_id=trav_id;
        }
        void set_id(){
            id=given_id;
        }
};

class commander:public Traveller{
    public:
        int experience;
        string license_id;
        void push_commander();
        commander(string name,int experience,string license_id){
            this->name=name;
            this->experience=experience;
            this->license_id=license_id;
            push_commander();
        }
        void set_id(){
            id=given_id;
        }
};
vector<commander*> list_of_commander;

void commander::push_commander(){
    list_of_commander.push_back(this);
}

class Ticket {
    int price;
    public:
        Traveller* Passenger;
        Planet* source;
        Planet* destination;
        int date;
        int month;
        int year;
        static int ticket_id;
        bool isReturnTrip;
        void push_global(Ticket* ticket);
        Ticket(Planet* source, Planet* destination, int date,int month,int year, bool isReturnTrip, Traveller*Passenger) {
            this->Passenger=Passenger;
            this->source = source;
            this->destination = destination;
            this->date = date;
            this->month=month;
            this->year=year;
            this->isReturnTrip = isReturnTrip;
            push_global(this);
            // this->ticket_id=rand();
            cout<<"your ticket has been booked"<<endl;
            ticket_id++;
        }

        void update(Planet* source, Planet* destination, int date,int month,int year, bool isReturnTrip){
            this->source = source;
            this->destination = destination;
            this->date = date;
            this->month=month;
            this->year=year;
            this->isReturnTrip = isReturnTrip;
            cout<<"your trip has been updated"<<endl;
        }

        int cost(){
            tm travel_date={
                0,
                0,
                0,
                date,
                month-1,
                year-1900,              
                0,
                0,
                0
            };
            time_t travel_time=mktime(&travel_date);
            int K=source->getDistance(destination);
            auto now = chrono::system_clock::now();
            time_t now_c = chrono::system_clock::to_time_t(now);
            int days_until_travel = ceil(difftime( now_c,travel_time) / (60 * 60 * 24)) + 1;
            return K/days_until_travel;
        }

        void print_ticket(){
            cout<<"passenger name:"<<this->Passenger->name<<endl;
            cout<<"ticket_id:"<<this->ticket_id<<endl;
            cout<<"source planet:"<<this->source->name<<endl;
            cout<<"destination planet:"<<this->destination->name<<endl;
            cout<<"date of travel:"<<this->date<<"-"<<this->month<<"-"<<year<<endl;
            cout<<"return_ticket:"<<this->isReturnTrip<<endl;
            cout<<"price"<<this->get_price();
        }

        void push(){
            Passenger->list_of_tickets.push_back(this->ticket_id);
        }

        void getname(){
            cout<<Passenger->get_name()<<endl;
        }
        void getid(){
            cout<<Passenger->get_id()<<endl;
        }void set_price(){
            price=cost();
        }
        int get_price(){
            return price;
        }
        Ticket* find(int ticket_id);
        void delete_ticket(int ticket_id);
};

int Ticket::ticket_id=0;
int Traveller::given_id=0;

vector<Ticket*> tickets;

Ticket* Ticket::find(int ticketid){
    vector<Ticket*>::iterator ptr;
    for(ptr=tickets.begin();ptr!=tickets.end();ptr++){
        if((*ptr)->ticket_id==ticket_id){
            return *ptr;
        }
    }
    return nullptr;
}

void Ticket::delete_ticket(int ticket_id){
    vector<Ticket*>::iterator ptr;
    *ptr=find(ticket_id);
    tickets.erase(ptr); 
}


void Ticket::push_global(Ticket* ticket){
    tickets.push_back(ticket);
}


class space_travel{
    private:
        vector<Traveller*> list_of_travellers;
        Astrounaut* astro;
        commander* commando;
    
    public:
        Planet* source;
        Planet* destination;
        int date;
        int month;
        int year;
        int id;
        void add_traveller(Traveller* pass){
            list_of_travellers.push_back(pass);
        }
        space_travel(){
            cout<<"space travel created";
        }
        void list_traveller(){
            vector<Traveller*>::iterator ptr;
            for(ptr=list_of_travellers.begin();ptr!=list_of_travellers.end();ptr++){
                cout<<"name:"<<(*ptr)->name<<"  "<<"id: "<<(*ptr)->trav_id<<endl;
            }
        }
        void set_astro(string id){
            vector<Astrounaut*>::iterator ptr;
            for(ptr=list_of_astro.begin();ptr!=list_of_astro.end();ptr++){
                if(id==(*ptr)->trav_id) astro=*ptr;
            }
            cout<<"Astronaut with id "<<id<<" has been assigned"<<endl;
        }
        void set_commando(string id){
            vector<commander*>::iterator ptr;
            for(ptr=list_of_commander.begin();ptr!=list_of_commander.end();ptr++){
                if(id==(*ptr)->trav_id) commando=*ptr;
            }
            cout<<"commander with id "<<id<<" has been assigned"<<endl;
        }
        void update_commando(string id){
            vector<commander*>::iterator ptr;
            for(ptr=list_of_commander.begin();ptr!=list_of_commander.end();ptr++){
                if(id==(*ptr)->trav_id) commando=*ptr;
            }
            cout<<"commander with id "<<id<<" has been assigned"<<endl;
        }
        void update_astro(string id){
            vector<Astrounaut*>::iterator ptr;
            for(ptr=list_of_astro.begin();ptr!=list_of_astro.end();ptr++){
                if(id==(*ptr)->trav_id) astro=*ptr;
            }
            cout<<"Astronaut with id "<<id<<" has been assigned"<<endl;
        }
        int get_id(){
            return id;
        }
        void set_id(int id){
            this->id=id;
        }
};

int main(){

    Planet*Earth = new Planet("Earth", 0, 0, 0);
    Planet*Mars = new Planet("Mars", 100, 200, 30);
    Planet* Jupiter = new Planet("Jupiter", 500, 50, 35);

    Astrounaut* Astro1 = new Astrounaut("Astro1", 10, "ABCD");
    Astrounaut* Astro2 = new Astrounaut("Astro2", 15, "EFGH");

    commander* Comm1 = new commander("Comm1", 20, "abcd");
    commander* Comm2 = new commander("Comm2", 13, "efgh");

    passenger* Pass1 = new passenger("Pass1", "Pass1_ID");
    passenger* Pass2 = new passenger("Pass2", "Pass2_ID");
    passenger* Pass3 = new passenger("Pass3", "Pass3_ID");
    passenger* Pass4 = new passenger("Pass4", "Pass4_ID");
    passenger* Pass5 = new passenger("Pass5", "Pass5_ID");
    passenger* Pass6 = new passenger("Pass6", "Pass6_ID");
    passenger* Pass7 = new passenger("Pass7", "Pass7_ID");
    passenger* Pass8 = new passenger("Pass8", "Pass8_ID");
    passenger* Pass9 = new passenger("Pass9", "Pass9_ID");
    passenger* Pass10 = new passenger("Pass10", "Pass10_ID");
    passenger* Pass11 = new passenger("Pass11", "Pass11_ID");

    Ticket* Ast_ticket = new Ticket(Earth, Mars, 21, 3, 2023, 0, Astro1);
    Ticket* Com_ticket = new Ticket(Earth, Mars, 21, 3, 2023, 0, Comm1);
    Ticket* Pas_ticket1 = new Ticket(Earth, Mars, 21, 3, 2023, 0, Pass5);
    Ticket* Pass_ticket2 = new Ticket(Earth, Mars, 21, 3, 2023, 0, Pass7);
    Ticket* Pass_ticket3= new Ticket(Earth, Mars, 21, 3, 2023, 0, Pass11);

    int i,j,k,flag;
    flag=0;
    for (i = 0; i <= tickets.size(); i++)
    {
        for (j = 0; j <= tickets.size(); j++)
        {
            if (i == j)
                continue;
            for (k = 0; k <= tickets.size(); k++)
            {
                if (j == k || i == k)
                    continue;
                if ((tickets[i]->source)->name == (tickets[j]->source)->name && (tickets[i]->source)->name == (tickets[k]->source)->name && (tickets[i]->destination)->name == (tickets[j]->destination)->name && (tickets[i]->destination)->name == (tickets[k]->destination)->name && tickets[i]->date == tickets[j]->date && tickets[i]->date == tickets[k]->date && tickets[i]->month == tickets[j]->month && tickets[i]->month == tickets[k]->month&& tickets[i]->year == tickets[j]->year && tickets[i]->year == tickets[k]->year)
                {
                    flag = 1;
                    break;
                }
            }
            if (flag)
                break;
        }
        if (flag)
            break;
    }

    if (flag)
    {
        space_travel travel;
        travel.id = 1;
        travel.source = tickets[i]->source;
        travel.destination = tickets[i]->destination;
        travel.date = tickets[i]->date;
        travel.add_traveller(tickets[i]->Passenger);
        travel.add_traveller(tickets[j]->Passenger);
        travel.add_traveller(tickets[k]->Passenger);
        travel.set_astro("ABCD");
        travel.set_commando("EFGH");
        travel.list_traveller();
    }

    

    return 0;
}
