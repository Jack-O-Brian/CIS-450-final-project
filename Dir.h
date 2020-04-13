#ifndef DIR_H
#define DIR_H
#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>
#include <climits>
#include <bitset>
#include <cassert>
#include "BitData.h"



int DirCreate(string path){ 
	inode child=getInode(path);
	size_t found = path.find_last_of("/");
	inode parent=getInode(path.substr(0,found));
	if(parent.size==inode().size){ // Parent does not exist
		return -1;
	}
	else{
		if (child.size != inode().size){ // Child alreayd exist
			return -2; 
		}
		else if (path.length()>256 ){ // Checking if path exceeds 256 characters
			return -3;
		}
		else{ // Can make dirctioanry.
			child.isFile=false;

			dir Dir;
			pos posDir;
			pos posParDir;
			pos posInode;

			posInode=getFreeInode();
			posDir=getFreeDataBlock();
			cout << 6 + parent.alloc[0] << "\tPROBLEM HERE" << endl;
			posParDir=getFirDir( 6+parent.alloc[0]); // TODO Might be reason of problem


			if(posDir.Count!=-1 && posInode.Count!=-1 && posParDir.Count!=-1){ // This means there is free space for a new direcotry
				string temp=path.substr(found+1);
				dir NewDir(temp, 0);
				writeDirSectDir(WorkDisk[posParDir.Sect], posParDir.Count, NewDir );
				writeDirSectDir(WorkDisk[posDir.Sect], posDir.Count, NewDir );
				dir parDir=readDirSectDir(WorkDisk[posParDir.Sect], posParDir.Count);
				child.alloc[0]=posInode.Alloc;
				child.size=0;
				writeInodeSectInode(WorkDisk[posInode.Sect], posInode.Count, child);

				// Update size
				parent.size++;
				forloop(3,6){
					forloop2(0,35){
						if(parent.alloc[0]==readInodeSectInode(WorkDisk[i],j).alloc[0]){
							writeInodeSectInode(WorkDisk[i],j, parent);

						}
					}
				}
				

				/* cout << readInodeSectBit(WorkDisk[posInode.Sect], posInode.Count); */
				/* cout << "\nToo busy printin\n"; */
				/* cout << "ParentNode\t" << parent.size << '\t' << parent.alloc[0] << endl; */
				/* cout << "Path\t" << path << '\t' << path.substr(0,found) << endl; */
				/* cout << "Dir\t" << posDir.Count << '\t' << posDir.Sect << endl; */
				/* cout << "ParDir\t" << posParDir.Count << '\t' << posParDir.Sect << endl; */
				/* cout << "ChildNode\t" << child.size << '\t' << child.alloc[0] << endl; */
				/* cout << "New Inode\t" << posInode.Sect << '\t' << posInode.Count << endl; */
				/* cout << "New Dir\t" << parDir.Name << '\t' << parDir.inodePlace  << endl; */
				/* cout << endl; */




				return 0;
			}
			else // There is no more space for a new directory
				return -4;


		}

	}
}

int DirSize(string path){ // Get the size of the dctionary
	inode inodepath=getInode(path);
	if (inodepath.size == inode().size){ // Child alreayd exist
		return -1; 
	}
	else{
		return inodepath.size;
	}

}

int DirUnlink(string path){ //Remove a file.
	inode delNode=getInode(path);
	size_t found = path.find_last_of("/");
	inode parent=getInode(path.substr(0,found));
	if(delNode.size==-1){ // File does not exist
		return -1;
	}
	else if ( DirSize(path)!=0){ //Path is not empty. 
		cout << "NOT EMPTY\t" << DirSize(path) << endl;
		return -2;
	}
	else if ( delNode.alloc[0]==6){ // 6 is where the root directory is. TODO mkae this look easier to read for Stenier
		return -3;
	}
	else{ // Now we can delete it. Hurray. TODO make a getInode iwth possiton of the inode, so I don't have to ifnd it twice like a stupid
		forloop(3,6){ // Deleting inode.
			forloop2(0,35){
				if(delNode.alloc[0]==readInodeSectInode(WorkDisk[i],j).alloc[0]){
					writeInodeSect(WorkDisk[i], j, "0");
				}
			}
		}
		bitset<132> temp(0);
		writeDirSect(WorkDisk[delNode.alloc[0]], 0,temp); // Deleting the acutal entry.

		// Now we gotta decrease the parent' inode siz
		parent.size--;
		forloop(3,6){
			forloop2(0,35){
				if(parent.alloc[0]==readInodeSectInode(WorkDisk[i],j).alloc[0]){
					writeInodeSectInode(WorkDisk[i],j, parent);
				}
			}
		}

		//Now, we must find the parent dictionary file of del, and remove it
		size_t found = path.find_last_of("/");
		string child=path.substr(found);
		forloop(0, 32){
			bitset<132>  dirBit(readDirSect(WorkDisk[parent.alloc[0]], i));
			if(dirBit!=0){
				dir Dir=getBitDir(dirBit);
				if(Dir.Name==child){ // Found the cihld directory in parent
					writeInodeSect(WorkDisk[parent.alloc[0]]  , i, "0");
				}

			}
			

		}
	}

}


#endif
