#include"all.h"
#include"allclass.h"
#include<iostream>
#include<map>
#include<vector>
#include<fstream>
#include<stdlib.h>	

vector <Cnode*>  N_list;
map <unsigned int,int>  L_MAP;			//map line no to bool value; -1 if not initilized
map <unsigned int,Cnode*>  N_MAP;			//map line no to node;
map <unsigned int,Cnode*>  NO_MAP;			//map line no to node;
map <unsigned int,Cnode*>  NODE_MAP;				//node number to node map;





void gen_graph(int **GR,int n)
{
	Cnode *ctemp;
	set<unsigned int>::iterator its;
	int v1,v2,v3,l2,l3;

	cout<<"---------------------CIRCUIT GRAPH---------------"<<endl;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			GR[i][j]=0;
		}
	}

	map<unsigned int,Cnode*>::iterator it;

	for(it=N_MAP.begin();it!=N_MAP.end();it++)
	{
		ctemp=it->second;
		v1=ctemp->node_num;
		//cout<<"node="<<v1<<"   "<<ctemp->node_type<<endl;


		if(ctemp->node_type==GT)
		{
			its=(ctemp->listfanin).begin();
			l2=*(its);
			l3=*(++its);
			v2=N_MAP[l2]->node_num;			
			v3=N_MAP[l3]->node_num;			

//			GR[v1][v2]=1;
			GR[v2][v1]=1;
//			GR[v1][v3]=1;
			GR[v3][v1]=1;
		}
/*		else if(ctemp->node_type==PI)
		{
			 	
			v2=N_MAP[ctemp->line_no]->node_num;
			v1=ctemp->node_num;
			GR[v1][v2]=1;
			GR[v2][v1]=1;	
		}
*/
	}			
	for(it=NO_MAP.begin();it!=NO_MAP.end();it++)
	{
		ctemp=it->second;
		v1=ctemp->node_num;
		v2=N_MAP[ctemp->line_no]->node_num;

//		GR[v1][v2]=1;
		GR[v2][v1]=1;	
	}							
			
		




		
	for(int i=0;i<n;i++)
	{
		cout<<i<<"->";
		for(int j=0;j<n;j++)
		{
			if(GR[i][j]!=0)
			{
				cout<<"  "<<j;
			}
		}

		cout<<endl;
	}
	cout<<"-----------------------------------------------------------"<<endl;


}







void print_all_line(void)
{
	map<unsigned int ,int>::iterator it;
	for(it=L_MAP.begin();it!=L_MAP.end();it++)
	{
		if(N_MAP[it->first]->node_type==PI)
		{
			cout<<it->first<< " -->"<<it->second<<endl;;
		}
	}

}



unsigned int update_line(int line_no,int set_v)		//return -1 if not possible else return >=0;
{
	int pv=L_MAP[line_no];
	int nv;
	nv=CON_LINE[pv][set_v];
//	cout<<" val="<<pv<<" nv="<<nv<<endl; 
	if(pv==-1)
	{	
		L_MAP[line_no]=set_v;
		return(set_v);
	}
	else if(nv==-1)
	{
		return(nv);
	}
	else
	{
		L_MAP[line_no]=nv;
		return(nv);
	}

	
}	
	



void read_ckt(ifstream &f)
{
	unsigned int ntype;
	unsigned int node_no;
	unsigned int line_no;	//node output line no
	unsigned int inp1;	//node input1
	unsigned int inp2;	//node input2
	unsigned int gtype;	//gate type of node if it is input then same type as input



	static int  i;

	while(true)
	{
		if(f.eof())
		{
			break;
		}
		f>>node_no;
		f>>ntype;
		gtype=ntype;
		if(ntype==0)
		{
			f>>gtype;
		}

		
		//create net cnode object;
		Cnode *thisN;
		thisN= new Cnode(ntype) ;
		//	cout<<thisN<<" "<<i<<endl;

		NODE_MAP.insert(pair<unsigned int,Cnode*>(node_no,thisN));


		switch(gtype){
			case PI:
			{
				f>>line_no;
				thisN->node_num=node_no;
				thisN->node_type=ntype;
				thisN->line_no=line_no;
			//	cout<<ntype<<"PI "<<node_no<<endl;
				//L_MAP[line_no]=-1;
				//N_MAP[line_no]=thisN;
				L_MAP.insert(pair<unsigned int,int>(line_no,-1));
				N_MAP.insert(pair<unsigned int,Cnode*>(line_no,thisN));
			}break;
			case G_NAND:
			{
				f>>line_no;
				f>>inp1;		
				f>>inp2;	
				thisN->node_num=node_no;
				thisN->node_type=ntype;
				thisN->line_no=line_no;
				thisN->listfanin.insert(inp1);
				thisN->listfanin.insert(inp2);
				
				//L_MAP[line_no]=-1;
				//N_MAP[line_no]=thisN;
				L_MAP.insert(pair<unsigned int,int>(line_no,-1));
				N_MAP.insert(pair<unsigned int,Cnode*>(line_no,thisN));
			        //set<unsigned int>::iterator it=(thisN->listfanin).begin();
				//cout<<" input 1="<<*(it)<<endl;
				//cout<<" input 2="<<*(++it)<<endl;
				
				
						


			}break;	
			case PO:
			{
		                f>>line_no;
	                        thisN->node_num=node_no;
        	                thisN->node_type=ntype;
                                thisN->line_no=line_no;

                                //L_MAP[line_no]=-1;
                                //N_MAP[line_no]=thisN;
				L_MAP.insert(pair<unsigned int,int>(line_no,-1));
				NO_MAP.insert(pair<unsigned int,Cnode*>(line_no,thisN));
                        }break;
	
			

		}
		N_list.push_back(thisN);
		//cout<<"  "<<N_list[i++]->node_type<<endl;
		//delete(thisN);
		
	}

}
int num_frez_line=1;

void findcont_vector(unsigned int line_no,int cvalue)
{
	
	Cnode *Ctemp=N_MAP[line_no];
	unsigned int input1;
	unsigned int input2;
	unsigned int out;
	out=Ctemp->line_no;
	set<unsigned int>::iterator it;
	if(Ctemp->node_type!=PI)	//&&Ctemp->node_type!=PO)
	{
		it=(Ctemp->listfanin).begin();
		input1=*(it);
		input2=*(++it);
		
		
		if(update_line(line_no,cvalue)<0)
		{
			return;
		}

		for(int i=0;i<2;i++)
		{
			for(int j=0;j<2;j++)
			{
				if(NANDTABLE[i][j]==cvalue)
				{
		//			cout<<"i="<<i <<" j="<<j<<endl;
					num_frez_line=num_frez_line-1+2;
					findcont_vector(input1,i);
					findcont_vector(input2,j);
					//L_MAP[input1]=-1;
					//L_MAP[input2]=-1;
				}
			}
		}

	}
	else		//input line
	{
		if(update_line(line_no,cvalue)<0)
		{
			return;
		}
		
		num_frez_line=num_frez_line-1;
		if(num_frez_line==0)
		{
			cout<<"bingo"<<endl;
			print_all_line();
			exit(1);
		}
		cout<<" line no="<<line_no<<endl;
		cout<<" lvalue="<<L_MAP[line_no]<<endl;
		cout<<"-------------------------------"<<endl;
		
	}
	
}


int objf=1;
void findob_vector(int **GR,int line_no,int n)
{
	Cnode *cnode=N_MAP[line_no];
	Cnode *ctemp;
	int i=cnode->node_num;
	int inp1;
	int inp2;
	if(NO_MAP.find(line_no)!=NO_MAP.end())		//if the line is  output
	{
		return;
	}

	for(int j=0;j<n;j++)
	{
		//cout<<"i,j"<<i<<" "<<j<<endl;
		if(GR[i][j]!=0 )
		{
			
			ctemp=NODE_MAP[j];
	//		cout<<" "<<ctemp->node_num<<endl;
			set<unsigned int>::iterator it=(ctemp->listfanin).begin();
			inp1=*(it);
			inp2=*(++it);
//			cout<<inp1;				
	//		cout<<"  "<<inp2<<endl;				
			
			if(inp1==i)
			{
				if(L_MAP[inp2]=-1)
				{
					L_MAP[inp2]=1;		//for nand only;
					objf++;			
				}
				else
				{
					objf--;
				}
			}
			else
			{
				if(L_MAP[inp1]=-1)
				{
					L_MAP[inp1]=1;		//for nand only;
					objf++;			
				}
				else
				{
					objf--;
				}
			}
				
			findob_vector(GR,ctemp->line_no,n);

	
		}
	//	cout<<endl;
	}


}
		


main(int argc,char *argv[])
{

	ifstream infile;
	//infile.open("ctest17.ckt",fstream::in);
	infile.open(argv[1],fstream::in);

//read circuit 
	read_ckt(infile);
	
//allocate memory for graph 
	map<unsigned int,Cnode*>::iterator it;
	int n=13;
	int** ary=new int*[n];
	for(int i=0;i<n;i++)
	{
		ary[i]=new int[n];
	}
//generate_graph	
	gen_graph(ary,n);

cout<<"--------------------controllability ----------------"<<endl;

	int ln,cv;
	cout<<"enter line no:"<<endl;;
	cin>>ln;
	cout<<"enter controllable value: ";
	cin>>cv;
findcont_vector(ln,cv);



//to find obs
	//set all_line to zero;
cout<<"--------------------observability -------------------"<<endl;
	
	map<unsigned int ,int>::iterator it1;
	for(it1=L_MAP.begin();it1!=L_MAP.end();it1++)
	{
		it1->second=0;
	}
	
	cout<<"enter line no:"<<endl;
	cin>>ln;
	findob_vector(ary,ln,n);


	for(it1=L_MAP.begin();it1!=L_MAP.end();it1++)
	{
		cout<<" line no"<<it1->first<<" value="<<it1->second<<endl;

	}

}

