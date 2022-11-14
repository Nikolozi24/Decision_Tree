#include<iostream>
#include<cmath>
#include<vector>
#include<math.h>
#include<array>
class Desicsion_tree
{
public:
	Desicsion_tree() = default;
	double  I(std::vector<double> vc);
	std::pair<double, double> Remainder(std::vector<std::vector<double>>  vc);
	std::pair<double, double> Gain(std::vector<double> vc, double Remainder);
};
double Desicsion_tree::I(std::vector<double> a) {
	double sum = 0;
	double size = a.size();
	for (int i = 0; i < size; i++) {
		sum += a[i];
	}
	double value = 0;
	for (int i = 0; i < size; i++) {
		if ((a[i] / sum) == 0) {
			value = 0;
		}
		else {
			value -= (a[i] / sum) * log2(a[i] / sum);
		}
	}
	return value;
}
std::pair<double, double> Desicsion_tree::Remainder(std::vector<std::vector<double>>  vc) {
	double mainLengh = 0;
	double sum = 0;
	double size = vc.size();
	std::pair<double, double> pair;
	for (int i = 0; i < size; i++) {
		std::vector<double> newVec = vc[i];
		for (int j = 0; j < newVec.size(); j++) {
			mainLengh += newVec[j];
		}
	}
	for (int i = 0; i < size; i++) {
		double Entropy = I(vc[i]);
		double helper = 0;
		std::vector<double> newVec = vc[i];
		for (int i = 0; i < newVec.size(); i++) {
			helper += newVec[i];
		}
		double helper2 = helper / mainLengh;
		sum += helper2 * Entropy;
	}
	std::cout << "\n";
	pair.first = sum;
	pair.second = 1 - sum;
	return pair;
}
std::pair<double, double> Desicsion_tree::Gain(std::vector<double> vc, double Remainder) {
	std::pair<double, double> pair;
	double Entropy = I(vc);
	pair.first = Remainder;
	pair.second = Entropy - Remainder;
	return pair;
}
bool findinvector(std::vector<std::string> vc, std::string name){
    int i ;
    int size = vc.size();
    for(i=0; i<size; i++){
        if(vc[i]==name){
            return true;
        }
    }
    return false;
}
std::vector<double> findIndexesAnd_Return_Vector(std::array<std::array<std::string,11> ,12> examples , int index, std::string name){
    std::vector<double> indexsOfName;
    for(int i=0; i<12; i++){
      std::array<std::string,11>  example =  examples[i];
      if(example[index]==name){
          indexsOfName.push_back(i);
      }
    }
    return indexsOfName;
}
std::vector<std::vector<double>> retInfo(std::array<std::array<std::string,11> ,12> examples , int index){
        std::vector<std::string> vc;
       std::vector<std::vector<double>> vc1;
        int i , j ;
        for(i=0; i<12; i++){
            std::array<std::string,11> example = examples[i];
            if(!findinvector(vc , example[index])){
                vc.push_back(example[index]);
            }
        }
    std::vector<std::pair<double , double>> posNeg;
 
    for(i = 0;i<vc.size(); i++){
        std::vector<double> vc3 = findIndexesAnd_Return_Vector(examples, index ,vc[i]);
        vc1.push_back(vc3);
    }
    
    for(i=0; i<vc1.size(); i++){
        std::vector<double> temp = vc1[i];
        for(j = 0 ; j<temp.size(); j++){
            std::array<std::string ,11> example  = examples[temp[j]];
            if(example[12]=="yes"){
                posNeg[i].first = (posNeg[i].first)+1;
            }
            else{
                posNeg[i].second = (posNeg[i].second)+1;
            }
        }
    }
    
    for(int  i =0; i<posNeg.size(); i++){
        std::cout<<i<<" first: "<<posNeg[i].first<<"\n"<<i<<" Second :"<<posNeg[i].second<<"\n";
    }
    
    for(int i =0; i<posNeg.size(); i++){
        vc1[i].push_back(posNeg[i].first);
        vc1[i].push_back(posNeg[i].second);
    }
    
    return vc1;
    
}
int main() {
/*	//patrons example
	std::vector<double> vc1 = { 0,2 };
	std::vector<double> vc2 = { 4,0 };
	std::vector<double> vc3 = { 2,4 };
	//Type examples
	std::vector<double> vc4 = { 1,1 };
	std::vector<double> vc5 = { 1,1 };
	std::vector<double> vc6 = { 2,2 };
	std::vector<double> vc7 = { 2,2 };
	//Alt examples
	std::vector<double>vc8 = { 3,3 };
	std::vector<double>vc9 = { 3,3 };
	//Res examples
	std::vector<double> vc10 = { 3,2 };//yes
	std::vector<double> vc11 = { 3,4 };//no
	//WillWait
	std::vector<double> WillWait = { 6,6 };
	std::vector<std::vector<double>> Patrons, Type, Alt, Res;
	//Patrons
	Patrons.push_back(vc1);
	Patrons.push_back(vc2);
	Patrons.push_back(vc3);
	//Type
	Type.push_back(vc4);
	Type.push_back(vc5);
	Type.push_back(vc6);
	Type.push_back(vc7);
	//Alt
	Alt.push_back(vc8);
	Alt.push_back(vc9);
	//Res
	Res.push_back(vc10);
	Res.push_back(vc11);
	//*/
	Desicsion_tree a;
	std::pair<double, double> pairPattrons, pairType, pairAlt, pairRes;
	pairPattrons = a.Gain(WillWait, a.Remainder(Patrons).first);
	pairType = a.Gain(WillWait, a.Remainder(Type).first);
	pairAlt = a.Gain(WillWait, a.Remainder(Alt).first);
	pairRes = a.Gain(WillWait, a.Remainder(Res).first);
	std::cout << " XXXXXXXXXXXXX  Patrons XXXXXXXXXXXX \n";
	std::cout << " Remainder: " << pairPattrons.first << std::endl;
	std::cout << " Gain:  " << pairPattrons.second << std::endl;
	std::cout << " XXXXXXXXXXXXX  Type XXXXXXXXXXXX \n";
	std::cout << " Remainder: " << pairType.first << std::endl;
	std::cout << " Gain:  " << pairType.second << std::endl;
	std::cout << " XXXXXXXXXXXXX  Alt XXXXXXXXXXXX \n";
	std::cout << " Remainder: " << pairAlt.first << std::endl;
	std::cout << " Gain:  " << pairAlt.second << std::endl;
	std::cout << " XXXXXXXXXXXXX  Res XXXXXXXXXXXX \n";
	std::cout << " Remainder: " << pairRes.first << std::endl;
	std::cout << " Gain:  " << pairRes.second << std::endl;
}