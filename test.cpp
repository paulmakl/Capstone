#include <iostream>
#include <fstream>

/*
 *  * Main function
 *   */
int main(int argc, char** argv)
{
	std::ofstream myfile;
	myfile.open("video.txt");
        myfile << "Writing this to a file.\n";
	myfile.close();
	return 0;
};
