// Whoel Porgram decompsiostion
//    This is an outline/code of how the whole program will be. 
//    #+HEADER: :noweb yes :tangle Wow.cpp   :colnames no :comments org
//    #+HEADER: includes <iostream> <cmath>
//    #+HEADER: includes "<cmath>"
//    #+HEADER: includes "<vector>"
//    #+HEADER: includes "<climits>"

int SectorSize = 512;
int SectorNum = 1000;
int inodeCount = 21;





#include <iostream>
using namespace std;



class inode{
	private: 
	    bool isFile;
	    const uint SizeMax = SectorSize/inodeCount;
	    const uint dataBlocksMax = SectorNum;
	    uint Size=0;
	    uint* Block;
	    
	    double log2(uint num){return log10(num)/log10(2);}
	    
	    

	public:
	    inode(){
		isFile=true;
		Block=new uint[SectorNum];
	    }
	    
	    void writeInode(){
		//Saddly bitmap won't be much use here. Cause their size is determine at compile time. So gonna have to use vector<bool>
		bool Bitmap[1 ];
		std::cout << log2(5); 		
		
		//Get bit representation of Size
		

		//Get bit representation of Blocks
		
		
		
		
	    }
	    bool setSectorSize(uint Size){
		if(Size>=SizeMax)
			return false;
		this->Size=Size;
		return true;

	    }
	    bool setBlocks(uint Blocks[], int size){
		return true;

	    }
	    void printMe(){ std::cout <<
		    isFile <<'\t' <<
		    SizeMax <<'\t' <<
		    dataBlocksMax << '\t' <<
		    Size << '\t' <<
		    std::endl;
	    }
};






int main(){
   inode temp;
   temp.writeInode();
    return 0;
}
