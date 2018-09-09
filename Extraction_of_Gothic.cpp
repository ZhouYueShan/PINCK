#include<stdio.h>
#include<cmath>
#include<iostream>
#include<fstream>
#include<ctime>


using namespace std;
int vol=5;     //��������Ŀ��ȫ�ֱ���
int junc=6;    //������Ŀ��ȫ�ֱ���
int line_count=0;  //ͳ���ļ�����
int Output_count=0;//ͳ�ƶ��ٴ��������
int Out_vol=1;    //Ҫ����Ŀ�����
int Out_junc=1;   //Ҫ���������
int Out_step=1;   //Ҫ�����ʱ�䲽��
char *file_name="ap1000";
double vol_array[10][50][120]={0};
double junc_array[20][20][120]={0};

double str2dig(char *str);
double extraction_of_gothic();
                //�����Ʋ˵�
void menu1();  
                //������ѹ�����
void pressure_menu2();
void show_vol_pressure1();
void show_vol_pressure2();
                //����ѹ�����
void pressure_diff_menu3();
void show_junc_pressure_diff1();
void show_junc_pressure_diff2();
                //�����ٶ����
void velocities_menu4();
void show_junc_velocities_liquid1();
void show_junc_velocities_liquid2();
void show_junc_velocities_vapor1();
void show_junc_velocities_vapor2();
void show_junc_velocities_drop1();
void show_junc_velocities_drop2();
                //�������¶����
void temperature_menu5();
void show_vol_temperature_liquid1();
void show_vol_temperature_liquid2();
void show_vol_temperature_vapor1();
void show_vol_temperature_vapor2();
void show_vol_temperature_drop1();
void show_vol_temperature_drop2();
                //��������ݷݶ����
void void_fraction_menu6();
void show_vol_void_fraction_liquid1();
void show_vol_void_fraction_liquid2();
void show_vol_void_fraction_vapor1();
void show_vol_void_fraction_vapor2();
void show_vol_void_fraction_drop1();
void show_vol_void_fraction_drop2();

int main()
{
	menu1();
	char choice1;
	char choice2;
	cout<<"Please input your choose:";
	cin>>choice1;
	while(true&&choice1!='q')
	{
		switch(choice1)
		{
		case 'e':{extraction_of_gothic();break;}
		case 'c':{cout<<"���������������Ŀ(now is "<<vol<<"):";cin>>vol;break;}
		case 'm':{cout<<"��������������Ŀ(now is "<<junc<<"):";cin>>junc;break;}
		case 'p':
			{
				pressure_menu2();
				cout<<"Please input your choose:";
				cin>>choice2;
				while(true&&choice2!='q')
				{
					switch(choice2){
					case 'v':{cout<<"ѡ��Ҫ����Ŀ�����(1->"<<vol<<")(now is "<<Out_vol<<"��:";cin>>Out_vol;break;}
					case 't':{cout<<"ѡ��Ҫ�����ʱ�䲽��(1->"<<Output_count<<")��now is "<<Out_step<<"):";cin>>Out_step;break;}
					case 'a':{show_vol_pressure1();break;}
				    case 's':{show_vol_pressure2();break;}
				    case 'q':break;
				    default:break;
					}
					pressure_menu2();
					cout<<"Please input your choose:";
				    cin>>choice2;
				}
				break;
			}
		case 'g':
			{
				pressure_diff_menu3();
				cout<<"Please input your choose:";
				cin>>choice2;
				while(true&&choice2!='q')
				{
					switch(choice2){
					case 'v':{cout<<"ѡ��Ҫ���������(1->"<<junc<<")(now is "<<Out_junc<<"��:";cin>>Out_junc;break;}
					case 't':{cout<<"ѡ��Ҫ�����ʱ�䲽��(1->"<<Output_count<<")��now is "<<Out_step<<"):";cin>>Out_step;break;}
					case 'a':{show_junc_pressure_diff1();break;}
				    case 's':{show_junc_pressure_diff2();break;}
				    case 'q':break;
				    default:break;
					}
					pressure_diff_menu3();
					cout<<"Please input your choose:";
				    cin>>choice2;
				}
				break;
			}
		case 'v':
			{
				velocities_menu4();
				cout<<"Please input your choose:";
				cin>>choice2;
				while(true&&choice2!='q')
				{
					switch(choice2){
					case 'v':{cout<<"ѡ��Ҫ���������(1->"<<junc<<")(now is "<<Out_junc<<"��:";cin>>Out_junc;break;}
					case 't':{cout<<"ѡ��Ҫ�����ʱ�䲽��(1->"<<Output_count<<")��now is "<<Out_step<<"):";cin>>Out_step;break;}
					case 'l':{show_junc_velocities_liquid1();break;}
				    case 'o':{show_junc_velocities_liquid2();break;}
					case 'i':{show_junc_velocities_vapor1();break;}
				    case 'p':{show_junc_velocities_vapor2();break;}
				    case 'd':{show_junc_velocities_drop1();break;}
					case 'f':{show_junc_velocities_drop2();break;}
				    case 'q':break;
				    default:break;
					}
					velocities_menu4();
					cout<<"Please input your choose:";
				    cin>>choice2;
				}
				break;
			}
		case 't':
			{
				temperature_menu5();
				cout<<"Please input your choose:";
				cin>>choice2;
				while(true&&choice2!='q')
				{
					switch(choice2){
					case 'v':{cout<<"ѡ��Ҫ����Ŀ�����(1->"<<vol<<")(now is "<<Out_vol<<"��:";cin>>Out_vol;break;}
					case 't':{cout<<"ѡ��Ҫ�����ʱ�䲽��(1->"<<Output_count<<")��now is "<<Out_step<<"):";cin>>Out_step;break;}
					case 'l':{show_vol_temperature_liquid1();break;}
				    case 'o':{show_vol_temperature_liquid2();break;}
					case 'i':{show_vol_temperature_vapor1();break;}
				    case 'p':{show_vol_temperature_vapor2();break;}
				    case 'd':{show_vol_temperature_drop1();break;}
					case 'f':{show_vol_temperature_drop2();break;}
				    case 'q':break;
				    default:break;
					}
					temperature_menu5();
					cout<<"Please input your choose:";
				    cin>>choice2;
				}
				break;
			}
		case 'f':
			{
				void_fraction_menu6();
				cout<<"Please input your choose:";
				cin>>choice2;
				while(true&&choice2!='q')
				{
					switch(choice2){
					case 'v':{cout<<"ѡ��Ҫ����Ŀ�����(1->"<<vol<<")(now is "<<Out_vol<<"��:";cin>>Out_vol;break;}
					case 't':{cout<<"ѡ��Ҫ�����ʱ�䲽��(1->"<<Output_count<<")��now is "<<Out_step<<"):";cin>>Out_step;break;}
					case 'l':{show_vol_void_fraction_liquid1();break;}
				    case 'o':{show_vol_void_fraction_liquid2();break;}
					case 'i':{show_vol_void_fraction_vapor1();break;}
				    case 'p':{show_vol_void_fraction_vapor2();break;}
				    case 'd':{show_vol_void_fraction_drop1();break;}
					case 'f':{show_vol_void_fraction_drop2();break;}
				    case 'q':break;
				    default:break;
					}
					void_fraction_menu6();
					cout<<"Please input your choose:";
				    cin>>choice2;
				}
				break;
			}
		case 'q':break;
		default:break;
		}
		menu1();
		cout<<"Please input your choose:";
		cin>>choice1;
	}
	return 0;

}

double str2dig(char *str)
{
	return atof(str);
}
double extraction_of_gothic()
{
	ifstream file1,file2,file3;
	ofstream temp_file;
	file1.open("ap100");
	char line[200];
	char word[30];
	char temp_word[30];
	double var;
	int flag_output=0;
	int flag_lumped=0;
	int flag_junction=0;
	int circle=0;
	int flag_vol=0;
	int flag_junc=0;
	int flag_firstword=0;
	int flag_is_dig_line=0;
	while(!file1.eof())
	{
		file1.getline(line,200);
		temp_file.open("temp_ap1000.txt");
		temp_file<<line;
		temp_file.close();
		file3.open("temp_ap1000.txt");
		file3>>temp_word;
		file3.close();
		file2.open("temp_ap1000.txt");
		int col;
		col=0;
		flag_firstword=0;
		flag_is_dig_line=0;
		if(temp_word[0]>='0'&&temp_word[0]<='9'){flag_is_dig_line=1;}
		//cout<<"line:"<<line<<endl;
		//cout<<"first_word:"<<temp_word<<endl;
		
		while(!file2.eof())
		{
			file2>>word;
			var=str2dig(word);
			//cout<<"word="<<word<<"   var="<<var<<"  flag_junc="<<flag_junc<<endl;
			
			if(word[0]=='O'&&word[1]=='u'&&word[2]=='t'){flag_output=1;flag_lumped=0;flag_junction=0;Output_count++;circle=0;}
			if(word[0]=='L'&&word[1]=='u'&&word[2]=='m'&&word[3]=='p'&&word[4]=='e'&&word[5]=='d'){flag_lumped=1;}
			if(word[0]=='J'&&word[1]=='u'&&word[2]=='n'){flag_junction=1;}
			//cout<<"flag_output="<<flag_output<<"   flag_junction="<<flag_junction<<endl;
			
			for(int vol_i=1;vol_i<=vol;vol_i++)
			{
				if(flag_firstword==0&&flag_is_dig_line==1&&flag_lumped==1&&flag_junction==0&&var==vol_i){flag_vol=vol_i;flag_firstword=1;circle++;}
			}
			//cout<<"flag_vol="<<flag_vol<<endl;
			//system("pause");
			for(int junc_i=1;junc_i<=junc;junc_i++)
			{
				if(flag_firstword==0&&flag_is_dig_line==1&&flag_junction==1&&var==junc_i){flag_junc=junc_i;flag_firstword=1;}
			}
		
			if(flag_output==1&&flag_junction==0&&flag_is_dig_line==1&&circle!=0)
			{
				//cout<<"flag_vol="<<flag_vol<<"  word="<<word<<"  var="<<var<<endl;
				//cout<<"circle="<<circle<<endl;
				if((circle-1)/vol==0)
				{
					vol_array[flag_vol][col][Output_count]=var;
					//cout<<"vol["<<flag_vol<<"]["<<col<<"]["<<Output_count<<"]="<<vol_array[flag_vol][col][Output_count]<<endl;
					//system("pause");
				}
				if((circle-1)/vol==1)
				{
					vol_array[flag_vol][col+13][Output_count]=var;
					//cout<<"vol["<<flag_vol<<"]["<<col+13<<"]["<<Output_count<<"]="<<vol_array[flag_vol][col+13][Output_count]<<endl;
				}
				if((circle-1)/vol==2)
				{
					vol_array[flag_vol][col+25][Output_count]=var;
					//cout<<"vol["<<flag_vol<<"]["<<col+25<<"]["<<Output_count<<"]="<<vol_array[flag_vol][col+25][Output_count]<<endl;
				}
				if((circle-1)/vol==3)
				{
					vol_array[flag_vol][col+30][Output_count]=var;
					//cout<<"vol["<<flag_vol<<"]["<<col+30<<"]["<<Output_count<<"]="<<vol_array[flag_vol][col+30][Output_count]<<endl;
				}
				col++;
				//system("pause");
			}
			if(flag_output==1&&flag_junction==1&&flag_is_dig_line==1)
			{
				
				junc_array[flag_junc][col][Output_count]=var;
				//cout<<"junc["<<flag_junc<<"]["<<col<<"]["<<Output_count<<"]="<<junc_array[flag_junc][col][Output_count]<<endl;
				col++;
				//system("pause");
			}
		}
		file2.close();
		line_count++;
		//cout<<"��"<<line_count<<"line ends."<<endl;
		//system("pause");
	}
	cout<<"Output line counts:"<<line_count<<endl;
	cout<<"Output summary counts:"<<Output_count<<endl;
	return 0;
}
void menu1()
{
	cout<<"------------------Main Control Menu-----------------"<<endl;
	cout<<"   e ---��ȡ���ļ�             p ---�鿴ѹ��"<<endl;
	cout<<"   c ---���¿�������Ŀ         g ---�鿴ѹ��"<<endl;
	cout<<"   m ---����������Ŀ           v ---�鿴�ٶ�"<<endl;
	cout<<"   w ---д���ļ�               t ---�鿴�¶�"<<endl;
	cout<<"   a ---�߼����               f ---�鿴���ݷݶ�"<<endl;
	cout<<"   q ---�˳�   "<<endl;
	cout<<"------------------------End--------------------------"<<endl;
}
void pressure_menu2()
{
	cout<<"------------------Pressure Control Menu-----------------"<<endl;
	cout<<"   v ---������                 t ---ʱ�䲽��"<<endl;
	cout<<"   a ---ָ����������ʱ��       s ---ָ��ʱ���������"<<endl;
	cout<<"   q ---������һ��"<<endl;
	cout<<"----------------------End------------------------"<<endl;
}
void show_vol_pressure1()
{
	cout<<"Volume:"<<Out_vol<<" ѹ����ʱ��仯��:"<<endl;
	for(int i=1;i<=Output_count;i++)
	{
		cout<<"Step["<<i<<"]="<<vol_array[Out_vol][1][i]<<endl;
	}
}
void show_vol_pressure2()
{
	cout<<"Step:"<<Out_step<<" �����������ѹ����:"<<endl;
	for(int i=1;i<=vol;i++)
	{
		cout<<"Volume["<<i<<"]="<<vol_array[i][1][Out_step]<<endl;
	}

}
void pressure_diff_menu3()
{
	cout<<"------------------Pre_diff Control Menu-----------------"<<endl;
	cout<<"   v ---ָ������               t ---ʱ�䲽��"<<endl;
	cout<<"   a ---ָ��������ʱ��         s ---ָ��ʱ��������"<<endl;
	cout<<"   q ---������һ��"<<endl;
	cout<<"----------------------End------------------------"<<endl;
}
void show_junc_pressure_diff1()
{
	cout<<"Junction:"<<Out_junc<<" ѹ����ʱ��仯��:"<<endl;
	for(int i=1;i<=Output_count;i++)
	{
		cout<<"Step["<<i<<"]="<<junc_array[Out_junc][5][i]<<endl;
	}
}
void show_junc_pressure_diff2()
{
	cout<<"Step:"<<Out_step<<" ����������ѹ����:"<<endl;
	for(int i=1;i<=junc;i++)
	{
		cout<<"Junction["<<i<<"]="<<junc_array[i][5][Out_step]<<endl;
	}
}
void velocities_menu4()
{
	cout<<"-------------------Velocities Control Menu------------------"<<endl;
	cout<<"   v ---ָ������                   t ---ʱ�䲽��"<<endl;
	cout<<"   l ---Һ��ָ��������ʱ��         o ---Һ��ָ��ʱ��������"<<endl;
	cout<<"   i ---����ָ��������ʱ��         p ---����ָ��ʱ��������"<<endl;
	cout<<"   d ---Һ��ָ��������ʱ��         f ---Һ��ָ��ʱ��������"<<endl;
	cout<<"   q ---������һ��"<<endl;
	cout<<"----------------------End------------------------"<<endl;
}
void show_junc_velocities_liquid1()
{
	cout<<"Junction:"<<Out_junc<<" Һ���ٶ���ʱ��仯��:"<<endl;
	for(int i=1;i<=Output_count;i++)
	{
		cout<<"Step["<<i<<"]="<<junc_array[Out_junc][6][i]<<endl;
	}
}
void show_junc_velocities_liquid2()
{
	cout<<"Step:"<<Out_step<<" ����������Һ���ٶ���:"<<endl;
	for(int i=1;i<=junc;i++)
	{
		cout<<"Junction["<<i<<"]="<<junc_array[i][6][Out_step]<<endl;
	}
}
void show_junc_velocities_vapor1()
{
	cout<<"Junction:"<<Out_junc<<" �����ٶ���ʱ��仯��:"<<endl;
	for(int i=1;i<=Output_count;i++)
	{
		cout<<"Step["<<i<<"]="<<junc_array[Out_junc][7][i]<<endl;
	}
}
void show_junc_velocities_vapor2()
{
	cout<<"Step:"<<Out_step<<" ���������������ٶ���:"<<endl;
	for(int i=1;i<=junc;i++)
	{
		cout<<"Junction["<<i<<"]="<<junc_array[i][7][Out_step]<<endl;
	}
}
void show_junc_velocities_drop1()
{
	cout<<"Junction:"<<Out_junc<<" Һ���ٶ���ʱ��仯��:"<<endl;
	for(int i=1;i<=Output_count;i++)
	{
		cout<<"Step["<<i<<"]="<<junc_array[Out_junc][8][i]<<endl;
	}
}
void show_junc_velocities_drop2()
{
	cout<<"Step:"<<Out_step<<" ����������Һ���ٶ���:"<<endl;
	for(int i=1;i<=junc;i++)
	{
		cout<<"Junction["<<i<<"]="<<junc_array[i][8][Out_step]<<endl;
	}
}
void temperature_menu5()
{
	cout<<"-------------------Temperature Control Menu------------------"<<endl;
	cout<<"   v ---ָ��������                 t ---ʱ�䲽��"<<endl;
	cout<<"   l ---Һ��ָ��������ʱ��         o ---Һ��ָ��ʱ��������"<<endl;
	cout<<"   i ---����ָ��������ʱ��         p ---����ָ��ʱ��������"<<endl;
	cout<<"   d ---Һ��ָ��������ʱ��         f ---Һ��ָ��ʱ��������"<<endl;
	cout<<"   q ---������һ��"<<endl;
	cout<<"----------------------End------------------------"<<endl;
}
void show_vol_temperature_liquid1()
{
	cout<<"Volume:"<<Out_vol<<" Һ���¶���ʱ��仯��:"<<endl;
	for(int i=1;i<=Output_count;i++)
	{
		cout<<"Step["<<i<<"]="<<vol_array[Out_vol][10][i]<<endl;
	}
}
void show_vol_temperature_liquid2()
{
	cout<<"Step:"<<Out_step<<" �����������Һ���¶���:"<<endl;
	for(int i=1;i<=vol;i++)
	{
		cout<<"Vol["<<i<<"]="<<vol_array[i][10][Out_step]<<endl;
	}
}
void show_vol_temperature_vapor1()
{
	cout<<"Volume:"<<Out_vol<<" �����¶���ʱ��仯��:"<<endl;
	for(int i=1;i<=Output_count;i++)
	{
		cout<<"Step["<<i<<"]="<<vol_array[Out_vol][11][i]<<endl;
	}
}
void show_vol_temperature_vapor2()
{
	cout<<"Step:"<<Out_step<<" ����������������¶���:"<<endl;
	for(int i=1;i<=vol;i++)
	{
		cout<<"Vol["<<i<<"]="<<vol_array[i][11][Out_step]<<endl;
	}
}
void show_vol_temperature_drop1()
{
	cout<<"Volume:"<<Out_vol<<" Һ���¶���ʱ��仯��:"<<endl;
	for(int i=1;i<=Output_count;i++)
	{
		cout<<"Step["<<i<<"]="<<vol_array[Out_vol][12][i]<<endl;
	}
}
void show_vol_temperature_drop2()
{
	cout<<"Step:"<<Out_step<<" �����������Һ���¶���:"<<endl;
	for(int i=1;i<=vol;i++)
	{
		cout<<"Vol["<<i<<"]="<<vol_array[i][12][Out_step]<<endl;
	}
}
void void_fraction_menu6()
{
	cout<<"----------------Void_Fraction Control Menu---------------"<<endl;
	cout<<"   v ---ָ��������                 t ---ʱ�䲽��"<<endl;
	cout<<"   l ---Һ��ָ��������ʱ��         o ---Һ��ָ��ʱ��������"<<endl;
	cout<<"   i ---����ָ��������ʱ��         p ---����ָ��ʱ��������"<<endl;
	cout<<"   d ---Һ��ָ��������ʱ��         f ---Һ��ָ��ʱ��������"<<endl;
	cout<<"   q ---������һ��"<<endl;
	cout<<"----------------------End------------------------"<<endl;
}
void show_vol_void_fraction_liquid1()
{
	cout<<"Volume:"<<Out_vol<<" Һ��ݶ���ʱ��仯��:"<<endl;
	for(int i=1;i<=Output_count;i++)
	{
		cout<<"Step["<<i<<"]="<<vol_array[Out_vol][5][i]<<endl;
	}
}
void show_vol_void_fraction_liquid2()
{
	cout<<"Step:"<<Out_step<<" �����������Һ��ݶ���:"<<endl;
	for(int i=1;i<=vol;i++)
	{
		cout<<"Vol["<<i<<"]="<<vol_array[i][5][Out_step]<<endl;
	}
}
void show_vol_void_fraction_vapor1()
{
	cout<<"Volume:"<<Out_vol<<" �����ݶ���ʱ��仯��:"<<endl;
	for(int i=1;i<=Output_count;i++)
	{
		cout<<"Step["<<i<<"]="<<vol_array[Out_vol][6][i]<<endl;
	}
}
void show_vol_void_fraction_vapor2()
{
	cout<<"Step:"<<Out_step<<" ����������������ݶ���:"<<endl;
	for(int i=1;i<=vol;i++)
	{
		cout<<"Vol["<<i<<"]="<<vol_array[i][6][Out_step]<<endl;
	}
}
void show_vol_void_fraction_drop1()
{
	cout<<"Volume:"<<Out_vol<<" Һ�ηݶ���ʱ��仯��:"<<endl;
	for(int i=1;i<=Output_count;i++)
	{
		cout<<"Step["<<i<<"]="<<vol_array[Out_vol][7][i]<<endl;
	}
}
void show_vol_void_fraction_drop2()
{
	cout<<"Step:"<<Out_step<<" �����������Һ�ηݶ���:"<<endl;
	for(int i=1;i<=vol;i++)
	{
		cout<<"Vol["<<i<<"]="<<vol_array[i][7][Out_step]<<endl;
	}
}