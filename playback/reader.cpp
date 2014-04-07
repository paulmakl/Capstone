#include "reader.h"

reader::reader(string p){
    path = p;
}

void reader::read()
{
	myfile.open(path.c_str());

    vector <vector <string> > data;
    string line;
    int i = 0;
    while (getline(myfile, line))
    {   
        if (line.at(0) == '$') {
            line.erase(0,1);
            string temp = lowercase(line);
            if ( temp == "size" ) {
                setVideoSize();
                cout << vid.size.x << " " << vid.size.y << " " << vid.size.z << " " << vid.numParticles << "\n";
            }else if (is_number(line)){
                int num = atoi(line.c_str());
                vid.addState();
                setVideoState(num);
                cout << "state " << num << " read\n";
            }
            else{
                cout << "nou";
            }
        }

    }
}

/*
 * option specific functions
 */

void reader::setVideoSize(){
    string temp;
    getline(myfile, temp);
    vector<string> sizes;
    sizes = chop(temp);
    vid.size.x = atoi(sizes[0].c_str());
    vid.size.y = atoi(sizes[1].c_str());
    vid.size.z = atoi(sizes[2].c_str());
    vid.numParticles = atoi(sizes[3].c_str());
}

void reader::setVideoState(int stateNum){
    int i = 0;
    string temp;
    vid.states[stateNum].init(vid.numParticles);
    
    while (i < vid.numParticles) {
        getline(myfile, temp);
        vector<string> pdata;
        pdata = chop(temp);
        vid.states[stateNum].particles[i].pos.x = 0;
        vid.states[stateNum].particles[i].pos.y = 0;
        vid.states[stateNum].particles[i].pos.z = 0;
        
        vid.states[stateNum].particles[i].pos.x = atof(pdata[0].c_str());
        vid.states[stateNum].particles[i].pos.y = atof(pdata[1].c_str());
        vid.states[stateNum].particles[i].pos.z = atof(pdata[2].c_str());
        i+= 1;
    }
}

/*
 * Helper Functions
 */

bool reader::is_number(string s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

vector<string> reader::chop(string line){
    std::istringstream ss(line);
    std::string token;
    std::vector<string> ret;
    
    while(std::getline(ss, token, ',')) {
        ret.push_back(token);
    }
    return ret;
}

string reader::lowercase(string str)
{
    string ret = str;
    std::transform(ret.begin(), ret.end(), ret.begin(), ::tolower);
    return ret;
}
