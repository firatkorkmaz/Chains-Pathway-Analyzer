/* Chains: Analysis of All the Possible Pathways Between Two Specific Points to Feature the Cheapest Route */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
using namespace std;
// A New pNode Type is Defined which Represents A Pair of One Integer Array with 2 Elements and One Single Integer
typedef pair<array<int, 2>, int> pNode;  // Array Gets the Given Point Pairs with Directed Connections; Integer Gets Their Given Costs


// This Function is Called Recursively to Calculate All the Possible Pathways which are Stored in the "chains" Vector
void calculator(int &start, int &init, int &stop, vector<vector<pNode>> &nodes, vector<pair<vector<pNode>, int>> &chains, pair<vector<pNode>, int> &filler){
    // "start" is the Starting Point and "stop" is the Stopping Point, which Never Change
    // "init" is the First Point to Look up in the Point Pairs of the "nodes" Vector for Every Related Recursive Call, which Always Changes
    // "index" Gives the Location of pNodes in the "nodes" Vector, which Contains Point Pairs Starting with the Current "init" Value
    int index = distance(nodes.begin(), find_if(begin(nodes), end(nodes),
                [init](vector<pNode> &item){return item.at(0).first[0] == init;}));

    if(index == int(nodes.size())){ // If There is Not any pNode in the "nodes" Vector which Starts with the "init" Point,
        return;                     // ...Stop the Current Execution of This "calculator" Function and Return Back to the Previous Execution or to the main()
    }

    for(int i=0; i<int(nodes.at(index).size()); i++){  // For Each pNode Pair in the Sub-Vector of "nodes" Vector where pNode Points Start with the "init" Value

        // As Long as filler Has Vector-Int Pairs & The Second Point in the Latest pNode of Its Vector Part != The First Point of the Current pNode in "nodes"
        while(int(filler.first.size())>0 && filler.first.back().first[1] != nodes.at(index).at(i).first[0]){
                filler.second -= filler.first.back().second;    // Subtract the Costs of Removed Unnecessary Nodes
                filler.first.pop_back();  // Remove the Latest Unnecessary pNodes from the Vector Part of "filler" in Order to Add New pNodes for New Pathways
        }

        int x = nodes.at(index).at(i).first[1]; // Get the Second Point of the Current pNode in This Call of the calculator()
        // "check" is the Index of pNode Element in the Vector Part of "filler" which Has the "x" Point as Its Own First Point (Was This Point Visited Before?)
        int check = distance(filler.first.begin(), find_if(begin(filler.first), end(filler.first), [x](pNode &item) {return item.first[0] == x;}));

        if(int(filler.first.size())>0 && check != int(filler.first.size()) && (check != 0 || start != stop)){
            continue;    // Do Not Let Moving from One Point to Any Others which were Visited Before, Except the Very First (Starting) Point
        }                // " && (check != 0" Enables Going Back to the Very First (Starting) Point If It will Also Be the Destination Point
        // " || start != stop)" Ensures that A Pre-Visited Point can Only Be Visited Again If It is Already the Destination (Stopping) Point

        filler.first.push_back(nodes.at(index).at(i));  // Add A Possible pNode to the Vector of "filler" which can Be A Part of any Pathway
        filler.second += filler.first.back().second;    // Add the Cost of This Newly Added pNode

        if(nodes.at(index).at(i).first[1] == stop){     // If the Second Point of the Added pNode is the Destination Point
            chains.push_back(filler);                   // Add the "filler" Pair to the "chains" Vector of Pairs and Skip...
            continue;                                   // ...to Creating A New pNode Vector for the Next Possible Pathway
        }
        else{   // Until Finishing A Full Possible Pathway, Continue Adding New pNodes to the "filler" by Calling This Function Recursively
            calculator(start, nodes.at(index).at(i).first[1], stop, nodes, chains, filler);
        }
    }

return;
}


int main(int argc, char* argv[]){

    string filename;

    if(argv[1]){             // If the Filename is Provided as An Input Argument to Run the Program
        istringstream inputfile(argv[1]);
        inputfile >> filename;
    }
    else{	                                // If the Filename is Not Provided as An Input Argument
        cout << "\nEnter the Filename to Read: ";              // Ask the User to Enter It Manually
        cin >> filename;
    }

    cout << endl;

    ifstream infile(filename);
    if(!infile){                             // If There is No Test File with the Entered File Name
        cout << "There is No Such File as: " << filename << endl;
        cout << endl << endl << "-------------" << endl;
		system("pause");
        return 0;
    }

    string lines;                   // The Line Data that is Read from the Test File
    int start, stop;                // Starting and Stopping Points of the Pathways
    getline(infile, lines);         // Get the First Line of the File to Obtain Starting and Stopping Points
    istringstream first(lines);
    first >> start >> stop;         // Get the Starting and Stopping Points from the String Type Numerical Data

    vector<vector<pNode>> nodes;

    int begins, ends, cost, dist, same;
    while(getline(infile, lines)){          // While Getting Each Line from the File
        istringstream rest(lines);
        rest >> begins >> ends >> cost;     // Assign the point1-point2-cost Values to the begins-ends-cost Variables

        // dist: Index of the Sub-Vector of pNodes Starting with point1. If There Exists Any, dist will Be < nodes.size()
        dist = distance(nodes.begin(), find_if(begin(nodes), end(nodes), [begins]
                    (vector<pNode> &item) {return item.at(0).first[0] == begins;}));

        if(dist == int(nodes.size())){   // Check If No pNode Starting with point1 Exists in any Sub-Vector of the "nodes"
            nodes.push_back(vector<pNode>());   // Then Push A New Empty pNode Sub-Vector at the End of the "nodes" Vector
        }

        pNode new_pNode = pNode({begins, ends}, cost);  // The New pNode to Add

        // same: Index of Any pNode in the Sub-Vector which is Identical to the New pNode (for Preventing Data Redundancy)
        same = distance(nodes.at(dist).begin(), find_if(begin(nodes.at(dist)), end(nodes.at(dist)),
                                            [new_pNode](pNode &item) {return item == new_pNode;}));

        if(same == int(nodes.at(dist).size())){      // If There is No pNode Identical to the New pNode in This Sub-Vector
            nodes.at(dist).push_back(new_pNode);     // Add the New pNode in This Sub-Vector that Has the Index: "dist"
        }

    }infile.close();        // Close the Text File


    /////////////////////////////////////////////////////////////////////////////////////////////
    // NOTE: Let's Create A New Text File which will Also Store All the Printed Results
    size_t ind = filename.find_last_of('.');        // The Last Occurrence of '.' in the Filename
    string savename = filename.substr(0, ind) + "_results" + filename.substr(ind);

	fstream sFile;
	sFile.open(savename, ios::out);            // Create A New File to Rewrite All the Data to It
    /////////////////////////////////////////////////////////////////////////////////////////////


    // Sort both "nodes" Vector and Its Sub-Vectors
    sort(nodes.begin(), nodes.end(), [](vector<pNode> &left, vector<pNode> &right){return left.at(0).first[0] < right.at(0).first[0];});
    for(int i=0; i<int(nodes.size()); i++){
        sort(nodes.at(i).begin(), nodes.at(i).end(), [](pNode &left, pNode &right){return left.first < right.first;});
	}

    int init = start;

    vector<pair<vector<pNode>, int>> chains;    // The Vector of Pairs with pNode Vectors (Pathways) and Total Costs
    pair<vector<pNode>, int> filler;            // The Pair of One pNode Vector (Pathway Points) and Its Total Cost
    filler.second = 0;                          // Total Cost of A Pathway, Starting with 0

    calculator(start, init, stop, nodes, chains, filler);               // Initial Call of the calculator() Function

    // Optional: Sorting Chains by Their Chain Lengths in Ascending Order to See the Pathways with the Least Moves on Top
    sort(chains.begin(), chains.end(), [](pair<vector<pNode>, int> &left, pair<vector<pNode>, int> &right){return left.first.size() < right.first.size();});
    // Sorting Chains by Their Total Cost Values in Ascending Order to See the Cheapest Pathways on Top
    sort(chains.begin(), chains.end(), [](pair<vector<pNode>, int> &left, pair<vector<pNode>, int> &right){return left.second < right.second;});

    cout << "From " << start << " to " << stop << ", There are " << int(chains.size()) << " Pathways:\n" << endl;
    sFile << "From " << start << " to " << stop << ", There are " << int(chains.size()) << " Pathways:\n" << endl;

    // Printing All the Possible Pathways with Their Total Cost Values Between the Given Points
    for(int i=0; i<int(chains.size()); i++){
        cout << "[" << chains.at(i).second << "]: " << start;
        sFile << "[" << chains.at(i).second << "]: " << start;
        for(int j=0; j<int(chains.at(i).first.size()); j++){
            cout << "-" << chains.at(i).first.at(j).first[1];
            sFile << "-" << chains.at(i).first.at(j).first[1];
        }cout << endl; sFile << endl;
    }cout << endl; sFile << endl;


    if(start == stop){
        cout << "=========================\n" << endl;
        sFile << "=========================\n" << endl;
    }

    cout << "The Shortest Pathways from " << start << " to " << stop << ":\n" << endl;
    sFile << "The Shortest Pathways from " << start << " to " << stop << ":\n" << endl;

    // Printing Only the Pathways with the Lowest Total Cost Values Between the Given Points
    for(int i=0; i<int(chains.size()); i++){
        if(chains.at(i).second <= chains.at(0).second){
            cout << "[" << chains.at(i).second << "]: " << start;
            sFile << "[" << chains.at(i).second << "]: " << start;
            for(int j=0; j<int(chains.at(i).first.size()); j++){
                cout << "-" << chains.at(i).first.at(j).first[1];
                sFile << "-" << chains.at(i).first.at(j).first[1];
            }cout << endl; sFile << endl;
        }
        else break;
    }

    ////////////////////////////////////////////////////////////////////////////////////

    // If the Starting and Stopping Points are Different, the Pathways from the Stopping...
    if(start != stop){  // ...Point Back to the Starting Point are Also Calculated and Printed

        cout << "\n-------------------------\n" << endl;
        sFile << "\n-------------------------\n" << endl;

        int start_b = stop;
        int stop_b  = start;
        int init_b = stop;

        vector<pair<vector<pNode>, int>> chains_b;  // The Vector of Pairs with pNode Vectors (Pathways) and Total Costs
        pair<vector<pNode>, int> filler_b;          // The Pair of One pNode Vector (Pathway Points) and Its Total Cost
        filler_b.second = 0;                        // Total Cost of A Pathway, Starting with 0

        calculator(start_b, init_b, stop_b, nodes, chains_b, filler_b);     // Initial Call of the calculator() Function

        // Optional: Sorting chains_b by Their Chain Lengths in Ascending Order to See the Pathways with the Least Moves on Top
        sort(chains_b.begin(), chains_b.end(), [](pair<vector<pNode>, int> &left, pair<vector<pNode>, int> &right){return left.first.size() < right.first.size();});
        // Sorting Chains by Their Total Cost Values in Ascending Order to See the Cheapest Pathways on Top
        sort(chains_b.begin(), chains_b.end(), [](pair<vector<pNode>, int> &left, pair<vector<pNode>, int> &right){return left.second < right.second;});

        cout << "From " << start_b << " to " << stop_b << ", There are " << int(chains_b.size()) << " Pathways:\n" << endl;
        sFile << "From " << start_b << " to " << stop_b << ", There are " << int(chains_b.size()) << " Pathways:\n" << endl;

        // Printing All the Possible Pathways with Their Total Cost Values Between the Given Points
        for(int i=0; i<int(chains_b.size()); i++){
            cout << "[" << chains_b.at(i).second << "]: " << start_b;
            sFile << "[" << chains_b.at(i).second << "]: " << start_b;
            for(int j=0; j<int(chains_b.at(i).first.size()); j++){
                 cout << "-" << chains_b.at(i).first.at(j).first[1];
                 sFile << "-" << chains_b.at(i).first.at(j).first[1];
            }cout << endl; sFile << endl;
        }cout << endl; sFile << endl;

        cout << "The Shortest Pathways from " << start_b << " to " << stop_b << ":\n" << endl;
        sFile << "The Shortest Pathways from " << start_b << " to " << stop_b << ":\n" << endl;

        // Printing Only the Pathways with the Lowest Total Cost Values Between the Given Points
        for(int i=0; i<int(chains_b.size()); i++){
            if(chains_b.at(i).second <= chains_b.at(0).second){
                cout << "[" << chains_b.at(i).second << "]: " << start_b;
                sFile << "[" << chains_b.at(i).second << "]: " << start_b;
                for(int j=0; j<int(chains_b.at(i).first.size()); j++){
                    cout << "-" << chains_b.at(i).first.at(j).first[1];
                    sFile << "-" << chains_b.at(i).first.at(j).first[1];
                }cout << endl; sFile << endl;
            }
            else break;
        }


        // This Final Section Combines the Bidirectional Two Cheapest-Shortest Pathways Between the Given Two Points
        cout << "\n=========================\n" << endl;
        sFile << "\n=========================\n" << endl;
        cout << "The Shortest Pathways from " << start << " to " << stop_b << " Through " << stop << ":\n" << endl;
        sFile << "The Shortest Pathways from " << start << " to " << stop_b << " Through " << stop << ":\n" << endl;

        // chains_c will Store the Final Pathways List with the Lowest Cost which Shows Going Back to the Starting Point.
        vector<pair<vector<pNode>, int>> chains_c;  // The Vector of Pairs with pNode Vectors (Pathways) and Total Costs.
        pair<vector<pNode>, int> temp_c;


        for(int i=0; i<int(chains.size()); i++){
            if(chains.at(i).second <= chains.at(0).second){
                for(int j=0; j<int(chains_b.size()); j++){
                    if(chains_b.at(j).second <= chains_b.at(0).second){
                        temp_c.second = chains.at(i).second + chains_b.at(j).second;
                        // cout << "[" << chains.at(i).second + chains_b.at(j).second << "]: " << start;
                        for(int i_=0; i_<int(chains.at(i).first.size()); i_++){
                            // cout << "-" << chains.at(i).first.at(i_).first[1];
                            temp_c.first.push_back(chains.at(i).first.at(i_));
                        }
                        for(int j_=0; j_<int(chains_b.at(j).first.size()); j_++){
                            temp_c.first.push_back(chains_b.at(j).first.at(j_));
                            // cout << "-" << chains_b.at(j).first.at(j_).first[1];
                        }
                        chains_c.push_back(temp_c);
                        temp_c.first.clear();
                        temp_c.second = 0;
                        // cout << endl;
                    }
                    else break;
                }
            }
            else break;
        }


        // Optional: Sorting chains_c by Their chain lengths in Ascending Order to See the Pathways with the Least Moves on Top
        sort(chains_c.begin(), chains_c.end(), [](pair<vector<pNode>, int> &left, pair<vector<pNode>, int> &right){return left.first.size() < right.first.size();});

        for(int i=0; i<int(chains_c.size()); i++){
            cout << "[" << chains_c.at(i).second << "] " << chains_c.at(i).first.at(0).first[0];
            sFile << "[" << chains_c.at(i).second << "] " << chains_c.at(i).first.at(0).first[0];
            for(int j=0; j<int(chains_c.at(i).first.size()); j++){
                cout << "-" << chains_c.at(i).first.at(j).first[1];
                sFile << "-" << chains_c.at(i).first.at(j).first[1];
            }cout << endl; sFile << endl;
        }
    }

    sFile.close();

    cout << endl << "Written in: " << savename << endl;


cout << endl << endl << "-------------" << endl;
system("pause");
return 0;
}
