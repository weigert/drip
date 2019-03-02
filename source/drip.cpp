/*
Author: Nicholas McDonald
Version: 1.0
*/

//Drip Main Source
#include "CImg.h"
#include <math.h>
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace cimg_library;

//Function for Euclidean Color Distance
int euclideanColor(const int a[3], const int b[3]);

int main( int argc, char* args[] ) {
	//Check if we have a filename.
	if(argc<2){
		std::cout<<"stain: Missing Filename"<<std::endl;
		return 0;
	}

	//Open the Image Data
	CImg<unsigned char> img(args[1]);
	const int width = img.width();
	const int height = img.height();

	//Color Distance to Associate Regions
	const int dist = std::atoi(args[2]);

	//Assignment of Tiles to regions
	short assign[width*height];
	assign[0] = 0;	//First Region of 0th Tile
	int assignments = 1; //Number of Assigned Regions

	//Loop Through Every Tile
	for(int i = 0; i < width; i++){
		for(int j = 0; j < height; j++){

			//Current Index
			int ind = j+i*height;

			//Find all 4 Neighbors
			int neighbors[4] = {( i-1 > 0 ) ? j+(i-1)*height : -1, ( j-1 > 0) ? j-1+i*height : -1, ( i+1 < width ) ? j+(i+1)*height : -1, ( j+1 < height ) ? j+(i+1)*height : -1};
			int nx[4] = {i-1, i, i+1, i};
			int ny[4] = {j, j-1, j, j+1};

			//Color of the Current Tile
			int a_rgb[3] = {img(i,j,0,0), img(i,j,0,1), img(i,j,0,2)};

			//Loop Through All Neighbors
			for(int k = 0; k < 4; k++){

				//See if it is not off the grid
				if(neighbors[k] >= 0){

					//Check if we have an assignment (neighbor has region)
					if(assign[neighbors[k]] >= 0){

						//Get RGB Values of Neighbor
						int b_rgb[3] = {img(nx[k],ny[k],0,0), img(nx[k],ny[k],0,1), img(nx[k],ny[k],0,2)};

						//If colors are similar enough
						if(euclideanColor(a_rgb, b_rgb) < dist){

							//Current Region Size
							int size = 0;

							//Determine the Region Size
							for(int l = 0; l < ind; l++){
								if(assign[l] == assign[neighbors[k]]){
									size++;
								}
							}

							//Assign ourselves to that region, average colors with average color of region
							assign[ind] = assign[neighbors[k]];

							//Set our Weighted Color Average
							int c_rgb[3] = {(a_rgb[0]+b_rgb[0]*size)/(size+1),
															(a_rgb[1]+b_rgb[1]*size)/(size+1),
															(a_rgb[2]+b_rgb[2]*size)/(size+1)};

							//And reset it (this is the drip effect)
							c_rgb[0] = a_rgb[0];
							c_rgb[1] = a_rgb[1];
							c_rgb[2] = a_rgb[2];

							//Set our Color
							img(i,j,0,0) = c_rgb[0];
							img(i,j,0,1) = c_rgb[1];
							img(i,j,0,2) = c_rgb[2];

							//Loop through the Pixels
							for(int l = 0; l < ind; l++){

								//Check if were in the same region
								if(assign[l] == assign[ind]){
									//Set the Color of the Node
									img(nx[k],ny[k],0,0) = c_rgb[0];
									img(nx[k],ny[k],0,1) = c_rgb[1];
									img(nx[k],ny[k],0,2) = c_rgb[2];
								}
							}
						}
						//Colors are not similar enough, we don't have a region. Make new region
						else{
							assign[ind] = assignments;
							assignments++;
						}
					}
				}
			}
		}
	}

	//Display the Image
	//Display the Image
	std::ostringstream out;
  out << std::setw(5) << std::setfill('0') << std::to_string((int)dist);
	std::string newname = "output"+out.str()+".png";
	//std::string newname = (std::string)filename+std::to_string(dist)+".png";
	img.save_png(newname.c_str());

	return 0;
}

int euclideanColor(const int a[3], const int b[3]){
	return sqrt(pow(b[0]-a[0],2)+pow(b[1]-a[1],2)+pow(b[2]-a[2],2));
}
