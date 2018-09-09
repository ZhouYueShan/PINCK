#include "UEwasp97.h"
#include<fstream>

using namespace std;
const double pi=3.1415926;
const double g=9.8;
int RANGE;
double T_FULL=344.792;//15.5MPa下水的饱和温度
double p=15.5,h,T,ETA,U,hl,hg,RAMD,CP;//水的物性参数
double Nt=1930;//全堆热功率
double q_l,q_avg=54.46;//线功率密度和热流功率密度
double T_in=293,T_out=326;//平均通道进出口温度
double H_in,H_out;//平均通道进出口焓
double G_avg,Gh;//平均通道和热通道的热流密度
double height=3.66,Def=2.922;//堆芯高度和等效半径
double S;//全释热面积
double T_range;//燃料组件每边的长度
double P_range;//栅距
double N;//燃料棒根数
double De;//通道当量直径
double dcs=10;//包壳外径
double dci=8.6;//包壳内径
double ru=8.46;//燃料芯块的外径
double A_l,A_b;//单位长度的外表面积和通道的面积
double N1=17,N2=17,Off_N=25;
double F_R_N=1.55;//核焓升热管因子
double F_H_E=1.033;//工程焓升热管因子
double F_G=1.05;//定位格架修正因子
double F_C=1;//冷壁修正因子
double F_Q_E=1.04;//热流密度工程热点因子
double F_S=1;//DNBR不均匀因子
double ETA_avg,ETA_h_avg,p_avg;
double f,f_h;//摩擦压降系数
double f_g;
double f_gh;
double ppp_old,ppp_new,det_p_em,det_p_am,det_p_fm,det_p_gd,det_p_dh,det_p_eh,det_p_ah,det_p_fh,det_p_h;
double det=1-1/1.03;
double c1;
double p1;
int step;
int step_const;
double *h_step,*w_3_q_DNB,*xe,*DNBR,*Re,*Pr,*Nu,*H,*tcs,*tci,*tu,*to;


void get_Nt(double *Nt);
void get_dcs(double *dcs);
void get_dci(double *dci);
void get_ru(double *ru);
void get_q_l(double *q_l);
void get_q_avg(double *q_avg);
void get_height(double *height);
void get_Def(double *Def);
void get_p(double *p);
void get_T_in(double *T_in);
void get_T_out(double *T_out);
void get_rod(double *N1,double *N2,double *Off_N);
void get_F_R_N(double *F_R_N);
void get_F_H_E(double *F_H_E);
void get_F_G(double *F_G);
void get_F_C(double *F_C);
void get_F_Q_E(double *F_Q_E);
void get_F_S(double *F_S);
void get_S(double Nt,double q_avg,double *S);
void get_N(double S,double height,double dcs,double *N);
void get_T_range(double Def,double N,double *T_range);
void get_P_range(double T_range,double dcs,double *P_range);
void get_A_l(double dcs,double *A_l);
void get_A_b(double dcs,double P_range,double *A_b);
void get_G_avg(double q_avg,double A_l,double height,double A_b,double *G_avg);
void get_De(double A_b,double A_l,double *De);
void main_cal();
void get_gh();
void get_Min_DNBR();
void get_Max_to();
void write_DNBR();
void write_h();
void write_tcs();
void write_tci();
void write_tu();
void write_to();
double k_u_t(double t);
void menu1();
void menu2();
void menu3();



int main()
{
	cout<<"This is a program for the calaulation of Single-Channel Model!"<<endl;
	//initial
	get_S(Nt,q_avg,&S);
	get_N(S,height,dcs,&N);
	get_T_range(Def,N,&T_range);
	get_P_range(T_range,dcs,&P_range);
	get_A_l(dcs,&A_l);
	get_A_b(dcs,P_range,&A_b);
	get_G_avg(q_avg,A_l,height,A_b,&G_avg);
	get_De(A_b,A_l,&De);
	p1=p*1e6;
	c1=q_avg*1e4*A_l/(G_avg*A_b)/1000;
	step_const=height/0.01;
	Gh=G_avg;
	PT2ETA97(p,(T_in+T_out)/2,&ETA_avg,&RANGE);
    f=0.184*pow(G_avg*De/ETA_avg,-0.2);
	f_g=f*0.01/De*G_avg*G_avg/2;
	f_gh=f*0.01/De*Gh*Gh/2;
	h_step=new double[step_const];
	w_3_q_DNB=new double[step_const];
	xe=new double[step_const];
	DNBR=new double[step_const];
	Re=new double[step_const];
	Pr=new double[step_const];
	Nu=new double[step_const];
	H=new double[step_const];
	tcs=new double[step_const];
	tci=new double[step_const];
	tu=new double[step_const];
	to=new double[step_const];
    //initial end
	menu1();
	char choice1;
	char choice2;
	char choice3;
	cout<<"please input your choose:";
	cin>>choice1;
	while(true&&choice1!='q'){
		switch(choice1){
		case 'e':{
			menu2();
			cout<<"please input your choose:";
			cin>>choice2;
			while(true&&choice2!='q'){
				switch(choice2){
				case 'l':{get_Nt(&Nt);break;}
				case 'w':{get_dcs(&dcs);break;}
			    case 'e':{get_dci(&dci);break;}
			    case 'r':{get_ru(&ru);break;}
				case 't':{get_p(&p);break;}
				case 'y':{get_q_avg(&q_avg);break;}
				case 'u':{get_height(&height);break;}
				case 'i':{get_Def(&Def);break;}
				case 'o':{get_T_in(&T_in);break;}
				case 'p':{get_T_out(&T_out);break;}
				case 'a':{get_rod(&N1,&N2,&Off_N);break;}
				case 's':{get_F_R_N(&F_R_N);break;}
				case 'd':{get_F_H_E(&F_H_E);break;}
				case 'f':{get_F_G(&F_G);break;}
				case 'g':{get_F_C(&F_C);break;}
				case 'h':{get_F_Q_E(&F_Q_E);break;}
				case 'j':{get_F_S(&F_S);break;}
				default:break;
				}
				menu2();
		        cout<<"please input your choose:";
	            cin>>choice2;
			}
			get_S(Nt,q_avg,&S);
			get_N(S,height,dcs,&N);
			get_T_range(Def,N,&T_range);
			get_P_range(T_range,dcs,&P_range);
			get_A_l(dcs,&A_l);
			get_A_b(dcs,P_range,&A_b);
			get_G_avg(q_avg,A_l,height,A_b,&G_avg);
			get_De(A_b,A_l,&De);
			p1=p*1e6;
			c1=q_avg*1e4*A_l/(G_avg*A_b)/1000;
			step_const=height/0.01;
			Gh=G_avg;
			PT2ETA97(p,(T_in+T_out)/2,&ETA_avg,&RANGE);
            f=0.184*pow(G_avg*De/ETA_avg,-0.2);
			f_g=f*0.01/De*G_avg*G_avg/2;
			f_gh=f*0.01/De*Gh*Gh/2;
			h_step=new double[step_const];
			w_3_q_DNB=new double[step_const];
			xe=new double[step_const];
			DNBR=new double[step_const];
			Re=new double[step_const];
			Pr=new double[step_const];
			Nu=new double[step_const];
			H=new double[step_const];
			tcs=new double[step_const];
			tci=new double[step_const];
			tu=new double[step_const];
			to=new double[step_const];
			break;
				 }
		case 'c':{main_cal();cout<<"主计算结束"<<endl;break;}
		case 'w':{
			menu3();
			cout<<"please input your choose:";
			cin>>choice3;
			while(true&&choice3!='q'){
				switch(choice3){
				case 'd':{write_DNBR();break;}
				case 'h':{write_h();break;}
			    case 't':{write_tcs();break;}
			    case 'u':{write_tci();break;}
				case 'z':{write_tu();break;}
				case 'a':{write_to();break;}
				case 'q':break;
				default:break;
				}
				menu3();
				cout<<"please input your choose:";
	            cin>>choice3;
			}
			break;
				 }
		case 'l':{
			cout<<"堆芯热功率Nt="<<Nt<<endl;
	        //cout<<"q_l="<<q_l<<endl;
	        cout<<"热流密度q_avg="<<q_avg<<endl;
			cout<<"线功率密度q_l="<<q_avg*pi*dcs*1e-1<<"(W/cm)"<<endl;
	        cout<<"堆芯等效高度height="<<height<<endl;
			cout<<"堆芯等效直径Def="<<Def<<endl;
			cout<<"包壳外径dcs="<<dcs<<endl;
			cout<<"包壳内径dci="<<dci<<endl;
			cout<<"燃料棒外径ru="<<ru<<endl;
			cout<<"进口温度T_in="<<T_in<<endl;
	        cout<<"出口温度T_out="<<T_out<<endl;
			cout<<"组件排列为："<<N1<<"*"<<N2<<"-"<<Off_N<<endl;
			//cout<<N1<<endl;
			//cout<<N2<<endl;
			//cout<<Off_N<<endl;
			cout<<"核焓升热管因子:"<<F_R_N<<endl;
			cout<<"工程焓升热管因子:"<<F_H_E<<endl;
			cout<<"定位格架修正因子:"<<F_G<<endl;
			cout<<"冷壁修正因子:"<<F_C<<endl;
			cout<<"热流密度工程热点因子:"<<F_Q_E<<endl;
			cout<<"W-3公式热流密度分布不均匀修正因子:"<<F_S<<endl;
			cout<<"计算得到的一些参数如下:"<<endl;
			cout<<"全部燃料棒根数："<<N<<endl;
	        cout<<"总传热面积："<<S<<endl;
			cout<<"组件边长："<<T_range<<endl;
			cout<<"栅距："<<P_range<<endl;
	        cout<<"通道面积："<<A_b<<endl;
			cout<<"通道当量直径De="<<De<<endl;
	        cout<<"平均通道流量I(Kg/m^2*s):"<<G_avg<<endl;
			break;
				 }
		case 'g':{get_gh();break;}
		case 'm':{get_Min_DNBR();break;}
		case 't':{get_Max_to();break;}
		case 'q':break;
		default:break;
	}
		menu1();
		cout<<"please input your choose:";
	    cin>>choice1;
	}
	
	system("pause");
	return 0;
}

void get_Nt(double *Nt)
{
	cout<<"请输入堆芯热功率(MW):";
	cin>>*Nt;
}
void get_dcs(double *dcs)
{
	cout<<"请输入燃料包壳外径(mm):";
	cin>>*dcs;
}
void get_dci(double *dci)
{
	cout<<"请输入燃料包壳内径(mm):";
	cin>>*dci;
}
void get_ru(double *ru)
{
	cout<<"请输入燃料棒外径(mm):";
	cin>>*ru;
}
void get_q_l(double *q_l)
{
	cout<<"请输入燃料棒线功率(W/cm):";
	cin>>*q_l;
}
void get_q_avg(double *q_avg)
{
	cout<<"请输入燃料棒面功率密度(W/cm^2):";
	cin>>*q_avg;
}
void get_height(double *height)
{
	cout<<"请输入堆芯高度(m):";
	cin>>*height;
}
void get_Def(double *Def)
{
	cout<<"请输入堆芯等效半径:";
	cin>>*Def;
}
void get_p(double *p)
{
	cout<<"请输入系统压力(MPa):";
	cin>>*p;
}
void get_T_in(double *T_in)
{
	cout<<"请输入平均通道入口温度(C):";
	cin>>*T_in;
}
void get_T_out(double *T_out)
{
	cout<<"请输入平均通道出口温度(C):";
	cin>>*T_out;
}
void get_rod(double *N1,double *N2,double *Off_N)
{
	cout<<"请输入组件分布情况(N*N-X):";
	cin>>*N1>>*N2>>*Off_N;
}
void get_F_R_N(double *F_R_N)
{
	cout<<"请输入核焓升热管因子:";
	cin>>*F_R_N;
}
void get_F_H_E(double *F_H_E)
{
	cout<<"请输入工程焓升热管因子:";
	cin>>*F_H_E;
}
void get_F_G(double *F_G)
{
	cout<<"请输入定位格架修正因子:";
	cin>>*F_G;
}
void get_F_C(double *F_C)
{
	cout<<"请输入冷壁修正因子:";
	cin>>*F_C;
}
void get_F_Q_E(double *F_Q_E)
{
	cout<<"请输入热流密度工程热点因子:";
	cin>>*F_Q_E;
}
void get_F_S(double *F_S)
{
	cout<<"请输入W-3公式热流密度分布不均匀修正因子:";
	cin>>*F_S;
}
void get_S(double Nt,double q_avg,double *S)
{
	*S=Nt*1e6*0.974/(q_avg*1e4);
}
void get_N(double S,double height,double dcs,double *N)
{
	*N=S/(pi*dcs*1e-3*height);
}
void get_T_range(double Def,double N,double *T_range)
{
	*T_range=sqrt(pi/4*Def*Def*(N1*N2-Off_N)/N);
}
void get_P_range(double T_range,double dcs,double *P_range)
{
	*P_range=(T_range-dcs*1e-3)/(N1-1);
}
void get_A_l(double dcs,double *A_l)
{
	*A_l=pi*dcs*1e-3;
}
void get_A_b(double dcs,double P_range,double *A_b)
{
	*A_b=P_range*P_range-pi/4*dcs*dcs*1e-6;
}
void get_G_avg(double q_avg,double A_l,double height,double A_b,double *G_avg)
{
	PT2H97(p,T_in,&H_in,&RANGE);
	PT2H97(p,T_out,&H_out,&RANGE);
	*G_avg=q_avg*1e4*A_l*height/(A_b*1000*(H_out-H_in));
}
void get_De(double A_b,double A_l,double *De)
{
	*De=4*A_b/A_l;
}
double k_u_t(double t)
{
	return 38.24*(log(t+402.55)-log(402.55))+4.788*1e-13/4*(pow(t+273.15,4)-pow(273.15,4));

}


void main_cal()
{
	PT2ETA97(p,T_in,&ETA,&RANGE);
	PT2U97(p,T_in,&U,&RANGE);
	PT2H97(p,T_in,&H_in,&RANGE);
	ppp_old=ETA/U;
	PT2ETA97(p,(T_in+T_out)/2,&ETA,&RANGE);
	PT2U97(p,(T_in+T_out)/2,&U,&RANGE);
	p_avg=ETA/U;
	det_p_em=0;
	det_p_am=0;
	det_p_fm=0;
	
	
	//平均通道计算压降
	cout<<"通道压降计算中......";
	for(step=0;step<step_const;step++)
	{
		h=H_in+c1*height/2*(1-cos(pi*step/100/height));
		//cout<<"h="<<h<<endl;
		PH2T97(p,h,&T,&RANGE);
		//cout<<"T="<<T<<endl;
		PT2ETA97(p,T,&ETA,&RANGE);
		//*cout<<"ETA="<<ETA<<endl;*//
		PT2U97(p,T,&U,&RANGE);
		//*cout<<"U="<<U<<endl;*//
		ppp_new=ETA/U;
		det_p_am+=G_avg*G_avg*(1/ppp_old-1/ppp_new);
		det_p_fm+=f_g/ppp_new;
		det_p_em+=ppp_new*g*1/100;
		//*cout<<"det_p_em="<<det_p_em<<endl;*//
		ppp_old=ppp_new;
		//*system("pause");
	}
	double ff1=2*P_range*1000*1.6/(P_range*P_range*1e6-pi/4*ru*ru);
	det_p_gd=8*6.5*ff1*ff1*G_avg*G_avg/(2*p_avg);
	cout<<endl;
	//cout<<"平均通道压降计算如下："<<endl;
	//cout<<"det_p_am="<<det_p_am<<endl;
	//cout<<"det_p_em="<<det_p_em<<endl;
	//cout<<"det_p_fm="<<det_p_fm<<endl;
	//cout<<"det_p_gd="<<det_p_gd<<endl;
	//cout<<"det_p_m="<<det_p_am+det_p_em+det_p_fm<<endl;
	det_p_dh=pow(1-det,2-0.2)*det_p_fm+(1-det)*(1-det)*(det_p_am+det_p_gd)+det_p_em;
	//cout<<"det_p_dh="<<det_p_dh<<endl;
	//system("pause");

	//热通道冷却剂Gh计算
	cout<<"热管冷却剂流量计算中......";
	double count=0;
	double flag1,flag2;
	do{
	count++;
	PT2ETA97(p,T_in,&ETA,&RANGE);
	PT2U97(p,T_in,&U,&RANGE);
	PT2H97(p,T_in,&H_in,&RANGE);
	ppp_old=ETA/U;
	det_p_eh=0;
	det_p_ah=0;
	det_p_fh=0;
	for(step=0;step<step_const;step++)
	{
		h=H_in+c1*G_avg/Gh*F_R_N*F_H_E*height/2*(1-cos(pi*step/100/height));
		//cout<<"h="<<h<<endl;*//
		PH2T97(p,h,&T,&RANGE);
		//cout<<"T="<<T<<endl;
		PT2ETA97(p,T,&ETA,&RANGE);
		//*cout<<"ETA="<<ETA<<endl;
		PT2U97(p,T,&U,&RANGE);
		//*cout<<"U="<<U<<endl;*//
		ppp_new=ETA/U;
		det_p_ah+=Gh*Gh*(1/ppp_old-1/ppp_new);
		det_p_fh+=f_gh/ppp_new;
		det_p_eh+=ppp_new*g*1/100;
		//*cout<<"det_p_em="<<det_p_em<<endl;*//
		ppp_old=ppp_new;
	}
	//cout<<"T="<<T<<endl;
	det_p_h=det_p_ah+det_p_eh+det_p_fh+det_p_gd;
	if(count==1)flag1=det_p_h-det_p_dh;
	if(flag1<0)Gh=Gh+1;
	else Gh=Gh-1;
	flag2=det_p_h-det_p_dh;
	//cout<<"det_p_h-det_p_dh="<<det_p_h-det_p_dh<<endl;
	//cout<<"error="<<(det_p_h-det_p_dh)/det_p_dh<<endl;
	//*system("pause");
	//PT2ETA97(p,(T_in+T)/2,&ETA_h_avg,&RANGE);
    //f_h=0.184*pow(Gh*De/ETA_h_avg,-0.2);
	f_gh=f*0.01/De*Gh*Gh/2;}while((abs(det_p_h-det_p_dh)/det_p_dh)>1e-4&&flag1*flag2>=0);
	cout<<endl;
	//cout<<"Gh="<<Gh<<endl;
	

	cout<<"DNBR计算中......";
	//热管冷却剂焓场计算
	for(step=0;step<step_const;step++)
	{
		h_step[step]=H_in+c1*G_avg/Gh*F_R_N*F_H_E*height/2*(1-cos(pi*step/100/height));
		//cout<<"h_step["<<step<<"]="<<h_step[step]<<endl;
		PH2T97(p,h_step[step],&T,&RANGE);
		//cout<<"T="<<T<<endl;
		//T2HL97(T,&hl,&range);
		P2HL97(p,&hl,&RANGE);
		//cout<<"hl="<<hl<<endl;
		P2HG97(p,&hg,&RANGE);
		//cout<<"hg="<<hg<<endl;
		xe[step]=(h_step[step]-hl)/(hg-hl);
		//cout<<"xe["<<step<<"]="<<xe[step]<<endl;
		w_3_q_DNB[step]=3.154*1e6*((2.022-6.238*1e-8*p1)+(0.1722-1.43*1e-8*p1)*exp((18.177-5.987*1e-7*p1)*xe[step]))*((0.1484-1.596*xe[step]+0.1729*xe[step]*abs(xe[step]))*0.2049*9.366+1.037)*(1.157-0.869*xe[step])*(0.2664+0.8357*exp(-124*De))*(0.8258+0.341*1e-6*(hl-H_in)*1000);
		//cout<<"w_3_q_DNB["<<step<<"]="<<w_3_q_DNB[step]<<endl;
		DNBR[step]=w_3_q_DNB[step]/F_S/(q_avg*1e4*pi/2*sin(pi*0.01*(step+1)/height)*F_R_N*F_Q_E)*F_G*F_C;
		//cout<<"DNBR["<<step<<"]="<<DNBR[step]<<endl;
		//system("pause");
	}

	cout<<endl;
	cout<<"温度场计算中......";
	///温度场计算
	for(step=0;step<step_const;step++)
	{
		//tcs温度场
		PH2T97(p,h_step[step],&T,&RANGE);
	    PT2U97(p,T,&U,&RANGE);
		PT2RAMD97(p,T,&RAMD,&RANGE);
		PT2CP97(p,T,&CP,&RANGE);
		Re[step]=Gh*De/U;
		Pr[step]=CP*U/RAMD;
		Nu[step]=0.023*pow(Re[step],0.8)*pow(Pr[step],0.4);
		H[step]=RAMD*Nu[step]/De;
		tcs[step]=T+q_avg*1e4*F_R_N*F_Q_E*pi/2*sin(pi*0.01*step/height)/H[step];
		double T_temp,T_temp1,T_temp2;
		T_temp1=tcs[step]-T;
		T_temp=T_FULL+25*pow(q_avg*1e4*F_R_N*F_Q_E*pi/2*sin(pi*0.01*step/height)/1E6,0.25)*exp(-p/6.2);
		T_temp2=T_temp-T;
		//cout<<"T_temp1="<<T_temp1<<"    "<<"T_temp2="<<T_temp2<<endl;
		if(tcs[step]>T_temp)tcs[step]=T_temp;
		//cout<<"tcs["<<step<<"]="<<tcs[step]<<endl;


		//tci温度场
		double k_c;
		double T_temp3,T_temp4;//包壳的定性温度
		T_temp4=tcs[step];
		do{
			T_temp3=(T_temp4+tcs[step])/2;
			T_temp4++;
		    k_c=0.00547*(1.8*T_temp3+32)+13.8;
		    tci[step]=tcs[step]+q_avg*dcs/((dcs+dci)/2)*1e4*F_R_N*F_Q_E*dcs*1e-3/2*pi/2*sin(pi*0.01*step/height)/k_c*log(dcs/dci);
			//tci[step]=tcs[step]+q_avg*1e4*F_R_N*F_Q_E*dcs*1e-3/2*pi/2*sin(pi*0.01*step/height)/k_c*log(dcs/dci);
			//cout<<"det:"<<tci[step]-T_temp4<<endl;
		}while(abs(tci[step]-T_temp4)>1);
		//cout<<"tci["<<step<<"]="<<tci[step]<<endl;

		//tu温度场
		double h_g=5678;
		tu[step]=tci[step]+q_avg*dcs/((ru+dci)/2)*1e4*F_R_N*F_Q_E*pi/2*sin(pi*0.01*step/height)/h_g;
		//tu[step]=tci[step]+q_avg*1e4*F_R_N*F_Q_E*pi/2*sin(pi*0.01*step/height)/h_g;
		//cout<<"tu["<<step<<"]="<<tu[step]<<endl;

		
		//to温度场
		double k_u_t1,k_u_t2,tmp;
		double q_lll;
		k_u_t1=k_u_t(tu[step]);
		//cout<<"k_u_t1="<<k_u_t1<<endl;
		q_lll=q_avg*1e4*pi/2*sin(pi*0.01*(step)/height)*pi*dcs*1e-3*F_R_N*F_Q_E/4/pi/100;
		k_u_t2=k_u_t1+q_lll;
		//cout<<"k_u_t2="<<k_u_t2<<endl;
		to[step]=tu[step];
		do{
			tmp=k_u_t(to[step]);
			//cout<<"tmp="<<tmp<<endl;
			//cout<<"to["<<step<<"]="<<to[step]<<endl;
			//cout<<"det:"<<abs(k_u_t2-tmp)<<endl;
			to[step]=to[step]+10;
			//system("pause");
			
		}while(abs(k_u_t2-tmp)>1);
		//cout<<"to["<<step<<"]="<<to[step]<<endl;
	}
	cout<<endl;
}
void get_gh()
{
	cout<<"平均通道压降计算如下(没有考虑形阻压降)："<<endl;
	cout<<"加速压降："<<det_p_am<<endl;
	cout<<"提升压降："<<det_p_em<<endl;
	cout<<"摩擦压降："<<det_p_fm<<endl;
	cout<<"定位格架压降："<<det_p_gd<<endl;
	cout<<"平均通道总压降："<<det_p_am+det_p_em+det_p_fm+det_p_gd<<endl;
	cout<<"热管压降："<<det_p_dh<<endl;
	cout<<"热管流量是："<<Gh<<endl;
}
void get_Min_DNBR()
{
	double min=1e10;
	for(int i=0;i<step_const;i++)
	{
		if(DNBR[i]<min)min=DNBR[i];
	}
	cout<<"最小DNBR是："<<min<<endl;
}
void get_Max_to()
{
	double max=0;
	for(int i=0;i<step_const;i++)
	{
		if(to[i]>max)max=to[i];
	}
	cout<<"燃料棒中心最大温度是："<<max<<endl;
}
void write_DNBR()
{
	ofstream file1;
	file1.open("DNBR.txt");
	for(int i=0;i<step_const;i++)
	{
		file1<<DNBR[i]<<endl;
	}
	file1.close();
	cout<<"Done!"<<endl;
}
void write_h()
{
	ofstream file2;
	file2.open("h_step.txt");
	for(int i=0;i<step_const;i++)
	{
		file2<<h_step[i]<<endl;
	}
	file2.close();
	cout<<"Done!"<<endl;
}
void write_tcs()
{
	ofstream file3;
	file3.open("tcs.txt");
	for(int i=0;i<step_const;i++)
	{
		file3<<tcs[i]<<endl;
	}
	file3.close();
	cout<<"Done!"<<endl;
}
void write_tci()
{
	ofstream file4;
	file4.open("tci.txt");
	for(int i=0;i<step_const;i++)
	{
		file4<<tci[i]<<endl;
	}
	file4.close();
	cout<<"Done!"<<endl;
}
void write_tu()
{
	ofstream file5;
	file5.open("tu.txt");
	for(int i=0;i<step_const;i++)
	{
		file5<<tu[i]<<endl;
	}
	file5.close();
	cout<<"Done!"<<endl;
}
void write_to()
{
	ofstream file6;
	file6.open("to.txt");
	for(int i=0;i<step_const;i++)
	{
		file6<<to[i]<<endl;
	}
	file6.close();
	cout<<"Done!"<<endl;
}






	
void menu1()
{
	cout<<"---------------Menu Control Volume---------------"<<endl;
	cout<<"e ---编辑参数             l ---查看参数"<<endl;
	cout<<"c ---计算                 g ---热管流量和压降"<<endl;
	cout<<"m ---最小DNBR             t ---最大燃料棒中心温度"<<endl;
	cout<<"w ---写入文件             q ---退出"<<endl;
	cout<<"----------------------End------------------------"<<endl;
}
void menu2()
{
	cout<<"------------------Edit Parameters---------------------"<<endl;
	cout<<"l ---热功率                   w ----包壳外径"<<endl;
	cout<<"e ---包壳内径                 r ----燃料棒内径"<<endl;
	cout<<"t ---系统压力                 y ----面功率"<<endl;
	cout<<"u ---堆芯高度                 i ----堆芯等效半径"<<endl;
	cout<<"o ---入口温度                 p ----出口温度"<<endl;
	cout<<"a ---组件分布                 s ----核焓升热管因子"<<endl;
	cout<<"d ---工程焓升热管因子         f ----定位格架修正因子"<<endl;
	cout<<"g ---冷壁修正因子             h ----热流密度工程热点因子"<<endl;
	cout<<"j ---W-3公式热流密度修正因子  q ---返回上一级"<<endl;
	cout<<"------------------------End----------------------------"<<endl;
}
void menu3()
{
	cout<<"--------------------Write To File-------------------"<<endl;
	cout<<"d ---DNBR                   h ---热管焓场"<<endl;
	cout<<"t ---tcs                    u ---tci"<<endl;
	cout<<"z ---tu                     a ---to"<<endl;
	cout<<"q ---返回上一级"<<endl;
	cout<<"-------------------------End------------------------"<<endl;
	
}