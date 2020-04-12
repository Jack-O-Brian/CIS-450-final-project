#ifndef DK_H
#define DK_H

#include <iostream>
#include <cmath>
#include <vector>
#include <climits>
#include <bitset>
#include <cassert>
#include "FS.h"



int Disk_Init(disk(Disk) ){ // Setup the disk
	// Set each sector 0
	for(int i=0; i<SectorNum; i++){ 
		Disk[i]=0;
	}

	//Bitmap results The reason 1 is the first indoe and datablcok is root, and thus, it's unvaliable at first.
	Disk[0]=SBNum; //Sueprblock setting
	Disk[1]=1;
	Disk[2]=1; 

	// TODO Manually create root, so to better understand process
	inode Root; // Used later
	Root.isFile=false;
	Root.size=SectorSize;
	inodeSet(&Root, 0, 1); // How to set inodes

	//This is creating the root folder. Later on, we will make it with DirCreate("/")

	string inodeString=writeBitDataInode(Root).to_string();
	bitset<SectorSize*8> inodeBit(inodeString);
	int x=34;
	inodeSetStr(Disk[3], x, inodeString);
	if(inodeSubStr(Disk[3], x) != inodeString ){
		cout << inodeSubStr(Disk[3], x) << endl << endl << inodeString << endl << endl;
		for(int i=0; i<35; i++){
			cout << i << '\t' << inodeSubStr(Disk[3], i) <<endl << endl;
		}

	}



	return 0;

}

// Save and load functions
int Disk_Load(){ // workDisk->extDisk
	for(int i=0; i<SectorNum; i++ )
		ExtDisk[i]=WorkDisk[i];
	return 0;
}

int Disk_Save(){ // extDisk->workDisk
	for(int i=0; i<SectorNum; i++ )
		WorkDisk[i]=ExtDisk[i];
	return 0;
}

// Read and write Functions The method signetuare is differnt, disk is not supposed to be there.
int Disk_Write( string &buffer, int sector){ // I did not check for buffer being null. IDK what to do in that scenario. 
	if(buffer.length()!=SectorBit || sector <0 || sector >= SectorNum ){ // One of these conditions happne, which are INVLAID
		diskErrMsg="E_READ_INVALID_PARM";
		return -1;
	}
	else{
		bitset<SectorBit> Write(buffer);
		WorkDisk[sector]=Write;

	}

	return 0;
}

int Disk_Read( string &buffer, int sector){ // I did not check for buffer being null. IDK what to do in that scenario. 
	if(sector <0 || sector >= SectorNum ){ // One of these conditions happne, which are INVLAID
		diskErrMsg="E_READ_INVALID_PARM";
		return -1;
	}
	else{
		cout << "NO";
		bitset<SectorBit> Read(buffer);
		Read=WorkDisk[sector];
		buffer=Read.to_string();



	}

	return 0;
}



#endif