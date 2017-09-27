//***************************************
// Name      : get the config file
//
// Author    : by fh
//
// Date      : 2017-9-26
// 
// LastChange: 2017-9-26
//***************************************
#include<iostream>
#include<regex> 
#include<fstream>

template <typename T> class Conf{
	private:
		int flag = 0;

	public:
		int GetFlag(){return flag;}

		T GetIniKey(const std::string title,const std::string key,const std::string filename){	
			T tmp;
			const std::string next = "[[[:alnum:]]*]";
			const std::string t = "[\[]"+title+"]";
			std::string row,row_sub;
			std::stringstream row_temp;
			std::regex r1,r2,r3;
			std::smatch results;
			r1 = t;
			r2 = key;
			r3 = next;
			
			if(typeid(T)!=typeid(std::string)&&typeid(T)!=typeid(int)&&typeid(T)!=typeid(double)){
				std::cout<<"parameter is not exist"<<std::endl;
				flag = -1;
				return tmp;
			}
			
			std::ifstream in;
			in.open(filename);
			if(!in){
				std::cout<<".ini can't open!"<<std::endl;
				flag = -2;
				return tmp;
			}
			while(!in.eof()){
				getline(in,row);
				if(regex_search(row,results,r1)){
					do{
						getline(in,row);
						if(regex_search(row,results,r2)){
							row_sub = row.substr(key.length()+1);
							row_temp<<row_sub;
							row_temp>>tmp;
							flag = 0;
							return tmp;
						}
					}while(!regex_search(row,results,r3)&&!in.eof());
					std::cout<<"can't find the key"<<std::endl;
					flag = -3;
					return tmp;
				}
			}
			std::cout<<"can't find the title"<<std::endl;
			flag = -4;
			return tmp;
		}
};

//example
/*
int main()
{
	Conf<double> conf;
	double s;
	s = conf.GetIniKey("TEST","test","test.ini");
	if(conf.GetFlag()==0){
		std::cout<<s<<std::endl;
	}
	return 0;
}*/
