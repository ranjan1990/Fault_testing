import sys;
G_PI=    0   # Primary Input.
G_BRNCH= 1   # Forward Branch.
G_XOR =  2   # XOR Gate.
G_OR  =  3   #// OR Gate.
G_NOR =  4   #// NOR Gate.
G_NOT  = 5   #// NOT Gate.
G_NAND = 6   #// NAND Gate.
G_AND  = 7   #// AND Gate.
G_XNOR = 8   #// XNOR Gate. Not implemented in out circuits.




#f1=open("c17.bench","r")
try:
	f1=open(sys.argv[1],"r")
except:
	print sys.argv[1],"file not found"
	exit(0);

outfile=sys.argv[1]+".ckt"
f2=open(outfile,"w");

LINE_MAP={}	#"gate":[lineno,#fanout]
lno=0;	   #total number of line
node_no=0; #total number of node
while(True):
	l=f1.readline();
	
	if(l==""):
		break;
	else:
		l=l.replace(" ","");
		if(l.find("INPUT(")>-1):
			line=l[l.find("(")+1:l.find(")")]
			if(LINE_MAP.has_key(line)):
				LINE_MAP[line][1]=LINE_MAP[line][1]+1;
			else:
				LINE_MAP[line]=[lno,1];
				lno=lno+1;
			#node specification	
			ntype=1;
			line_no=LINE_MAP[line][0];
			node_num=node_no;
			node_no=node_no+1;
			print  node_num,ntype,line_no
			f2.write(str(node_num)+" "+str(ntype)+" "+str(line_no)+"\n")
	
		elif(l.find("OUTPUT(")>-1):
			#handle output 
			line=l[l.find("(")+1:l.find(")")]
			if(LINE_MAP.has_key(line)):
				LINE_MAP[line][1]=LINE_MAP[line][1]+1;
			else:
				LINE_MAP[line]=[lno,1];
				lno=lno+1;
			
			#node specification	
			ntype=3;
			line_no=LINE_MAP[line][0];
			node_num=node_no;
			node_no=node_no+1;
			print node_num,ntype,line_no
			f2.write(str(node_num)+" "+str(ntype)+" "+str(line_no)+"\n")
			#f2.write(str(node_num)+str(ntype)+str(line_no)+"\n")

		elif(l.find("=AND(")>-1):	
			ntype=0
			line=l[l.find("(")+1:l.find(")")]
			line=line.split(",")
			line0=line[0]
			line1=line[1]
                        if(LINE_MAP.has_key(line0)):
                                LINE_MAP[line0][1]=LINE_MAP[line0][1]+1;
                        else:
                                LINE_MAP[line1]=[lno,1];
                                lno=lno+1;
                        if(LINE_MAP.has_key(line1)):
                                LINE_MAP[line1][1]=LINE_MAP[line1][1]+1;
                        else:
                                LINE_MAP[line1]=[lno,1];
                                lno=lno+1;

			out1=l[:l.find("=")]
			if(LINE_MAP.has_key(out1)):
                                LINE_MAP[out1][1]=LINE_MAP[out1][1]+1;
                        else:
                                LINE_MAP[out1]=[lno,1];
                                lno=lno+1;

			#node specification	
			ntype=0;
			gtype=G_AND
			line_no=LINE_MAP[out1][1];
			node_num=node_no;
			node_no=node_no+1;
			input1=LINE_MAP[line0][0]
			input2=LINE_MAP[line1][0]
			print node_num,ntype,line_no,input1,input2
			f2.write(str(node_num)+" "+str(ntype)+" "+str(line_no)+" "+str(input1)+" "+str(input2)+"\n")


		elif(l.find("=NAND(")>-1):	
			ntype=0
			line=l[l.find("(")+1:l.find(")")]
                        line=line.split(",")
                        line0=line[0]
                        line1=line[1]
                        if(LINE_MAP.has_key(line0)):
                                LINE_MAP[line0][1]=LINE_MAP[line0][1]+1;
                        else:
                                LINE_MAP[line0]=[lno,1];
                                lno=lno+1;

			#print "x==",line
                        if(LINE_MAP.has_key(line1)):
                                LINE_MAP[line1][1]=LINE_MAP[line1][1]+1;
                        else:
                                LINE_MAP[line1]=[lno,1];
                                lno=lno+1;

                        out1=l[:l.find("=")]
                        if(LINE_MAP.has_key(out1)):
                                LINE_MAP[out1][1]=LINE_MAP[out1][1]+1;
                        else:
                                LINE_MAP[out1]=[lno,1];
                                lno=lno+1;

			ntype=0;
			gtype=6
			line_no=LINE_MAP[out1][0];
			node_num=node_no;
			node_no=node_no+1;
			input1=LINE_MAP[line0][0]
			input2=LINE_MAP[line1][0]
			print node_num,ntype,gtype,line_no,input1,input2

			f2.write(str(node_num)+" "+str(ntype)+" "+str(gtype)+" "+str(line_no)+" "+str(input1)+" "+str(input2)+"\n")




		elif(l.find("OR(")>-1):	
			ntype=0
			line=l[l.find("(")+1:l.find(")")]
                        line=line.split(",")
                        line0=line[0]
                        line1=line[1]
                        if(LINE_MAP.has_key(line0)):
                                LINE_MAP[line0][1]=LINE_MAP[line0][1]+1;
                        else:
                                LINE_MAP[line1]=[lno,1];
                                lno=lno+1;
                        if(LINE_MAP.has_key(line1)):
                                LINE_MAP[line1][1]=LINE_MAP[line1][1]+1;
                        else:
                                LINE_MAP[line1]=[lno,1];
                                lno=lno+1;

                        out1=l[:l.find("=")]
                        if(LINE_MAP.has_key(out1)):
                                LINE_MAP[out1][1]=LINE_MAP[out1][1]+1;
                        else:
                                LINE_MAP[out1]=[lno,1];
                                lno=lno+1;
			ntype=0;
			gtype=G_OR
			line_no=LINE_MAP[out1][0];
			node_num=node_no;
			node_no=node_no+1;
			input1=LINE_MAP[line0][0]
			input2=LINE_MAP[line1][0]
			print node_num,ntype,gtype,line_no,input1,input2

			f2.write(str(node_num)+" "+str(ntype)+" "+str(gtype)+" "+str(line_no)+" "+str(input1)+" "+str(input2)+"\n")
			#f2.write(str(node_num)+str(ntype)+str(line_no)+str(input1)+str(input2)+"\n")

		elif(l.find("NOR(")>-1):	
			ntype=0
			line=l[l.find("(")+1:l.find(")")]
                        line=line.split(",")
                        line0=line[0]
                        line1=line[1]
                        if(LINE_MAP.has_key(line0)):
                                LINE_MAP[line0][1]=LINE_MAP[line0][1]+1;
                        else:
                                LINE_MAP[line1]=[lno,1];
                                lno=lno+1;
                        if(LINE_MAP.has_key(line1)):
                                LINE_MAP[line1][1]=LINE_MAP[line1][1]+1;
                        else:
                                LINE_MAP[line1]=[lno,1];
                                lno=lno+1;

                        out1=l[:l.find("=")]
                        if(LINE_MAP.has_key(out1)):
                                LINE_MAP[out1][1]=LINE_MAP[out1][1]+1;
                        else:
                                LINE_MAP[out1]=[lno,1];
                                lno=lno+1;	

			ntype=0;
                        gtype=G_NOR
                        line_no=LINE_MAP[out1][0];
                        node_num=node_no;
                        node_no=node_no+1;
                        input1=LINE_MAP[line0][0]
                        input2=LINE_MAP[line1][0]
                        print node_num,ntype,gtype,line_no,input1,input2

			f2.write(str(node_num)+" "+str(ntype)+" "+str(gtype)+" "+str(line_no)+" "+str(input1)+" "+str(input2)+"\n")
                        #f2.write(str(node_num)+str(ntype)+str(line_no)+str(input1)+str(input2)+"\n")
                elif(l.find("NOT(")>-1):
                        ntype=0
             		line=l[l.find("(")+1:l.find(")")]
                        line0=line[0]
               		if(LINE_MAP.has_key(line0)):
                	       	LINE_MAP[line0][1]=LINE_MAP[line0][1]+1;
                        else:
                                LINE_MAP[line0]=[lno,1];
                                lno=lno+1;

                        out1=l[:l.find("=")]
                        if(LINE_MAP.has_key(out1)):
       	                	LINE_MAP[out1][1]=LINE_MAP[out1][1]+1;
	               	else:
        	               	LINE_MAP[out1]=[lno,1];
                                lno=lno+1;
			ntype=0;
                        gtype=G_NOT
                        line_no=LINE_MAP[out1][0];
                        node_num=node_no;
                        node_no=node_no+1;
                        input1=LINE_MAP[line0][0]
                        print node_num,ntype,gtype,line_no,input1
                        f2.write(str(node_num)+" "+str(ntype)+" "+str(gtype)+" "+str(line_no)+" "+str(input1)+"\n")




				
print "-------------------line MAP--------------------"
print "line    line_no count"
for v in LINE_MAP.viewitems():
	print v[0],"    ",v[1][0],"      ",v[1][1]





