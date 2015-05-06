#ifdef ALL_H_
#include"all.h"
#endif

#include<set>
using namespace std;
class Cnode
{
	public:
		unsigned int node_num;		//graph node  number unique		   
		unsigned int node_type;       //type PI,GATE,PO,FO
		unsigned int line_no;	     //node output line no,incase output node inputid line_no 
		unsigned int gate_type;	    //gate type if the node is gate then NAND or NOR or etc etc.
		set <unsigned int> listfanin;	    //set line number of the fanin to the node
		set <unsigned int> listfanout;	
		Cnode(int Ntype);
		static unsigned int total_node;
		static unsigned int totalPI;
		static unsigned int totalPO;

};

unsigned int Cnode::total_node=0;
unsigned int Cnode::totalPI=0;
unsigned int Cnode::totalPO=0;
//circuit line class 
class Cline
{
	public:
		unsigned int line_no;		//line no 
		bool is_sa0;			//stuck at zero
		bool is_sa1;			//stuck at one
		Cline(int lno);

};


//for each line this class is maintained
class Tlist
{
	public:	
		int line_num;	//line number 
		bool sa_val;	//stuck at value
		bool istestpossible; //may be 0 while collaspsing;
		string testVector;

		
		Tlist (int inLineNumber, bool inStuckAtValue, string inTestVector);
		Tlist (int inLineNumber, bool inStuckAtValue);


};


Tlist::Tlist (int inLineNumber, bool inStuckAtValue)
{
	this->line_num=inLineNumber;
	this->sa_val=inStuckAtValue;
	this->istestpossible=false;

}

Tlist::Tlist (int inLineNumber, bool inStuckAtValue,string inTestVector)
{
	this->line_num=inLineNumber;
	this->sa_val=inStuckAtValue;
	this->istestpossible=true;
	this->testVector=inTestVector;
}


Cline::Cline(int l_no)
{
	this->is_sa0=true;
	this->is_sa1=true;
	this->line_no=l_no;
}

Cnode::Cnode(int Ntype)
{
	total_node++;
	this->node_type=Ntype;
	if(Ntype==PI)
	{
		totalPI++;
	}
	if(Ntype==PO)
	{
		totalPO++;
	}
	this->node_num=total_node;
}



