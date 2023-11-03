/* Adding Unique Pairs to Vector of Vectors in Groups */

#include <algorithm>
#include <iostream>
#include <vector>
#include <array>
using namespace std;


int main(int argc, char *argv[]){

    typedef pair<array<int, 2>, int> pNode;  	// Definition of Pair Type "pNode" as Having One Array of 2 Integers and One Integer
    vector<pNode> temp;                     	// pNode Type Vector (Pair of Int and Int[2])

    // Adding Random pNode Pairs to the pNode Vector: "temp"
    temp.push_back(pNode({1, 0}, 15));  		// Small Route from 1 to 0 with 15 Cost
    temp.push_back(pNode({0, 3}, 10));  		// Small Route from 0 to 3 with 10 Cost
    temp.push_back(pNode({2, 1}, 12));  		// Small Route from 2 to 1 with 12 Cost
    temp.push_back(pNode({3, 2}, 20));  		// Small Route from 3 to 2 with 20 Cost
    temp.push_back(pNode({1, 3}, 18));  		// Small Route from 1 to 3 with 18 Cost
    temp.push_back(pNode({3, 0}, 23));  		// Small Route from 3 to 0 with 23 Cost
    temp.push_back(pNode({2, 3}, 14));  		// Small Route from 2 to 3 with 14 Cost
    temp.push_back(pNode({0, 2}, 12));  		// Small Route from 0 to 2 with 12 Cost
    temp.push_back(pNode({3, 1}, 24));  		// Small Route from 3 to 1 with 24 Cost
    temp.push_back(pNode({2, 0}, 30));  		// Small Route from 2 to 0 with 30 Cost
    temp.push_back(pNode({0, 1}, 16));  		// Small Route from 0 to 1 with 16 Cost
		
    temp.push_back(pNode({1, 2}, 27));  		// Small Route from 1 to 2 with 27 Cost
    temp.push_back(pNode({1, 2}, 10));  		// The Same Small Route from 1 to 2 will Not Be Allowed!


    int element_1;              // For the 1st Element of the Int Array in pNode Pairs
    int index_1;                // For the Index of Sub-Vectors

    int element_2;              // For the 2nd Element of the Int Array in pNode Pairs
    int index_2;                // For the Index of pNodes in Sub-Vectors

    vector<vector<pNode>> nodes;

    for(int i=0; i<int(temp.size()); i++){
        element_1 = temp.at(i).first[0];       // Getting the First Element of the Int Array in pNode Pair, which is A Single Int Value

		// index_1: Index of the pNode Sub-Vectors which Have pNodes with the First Elements of Int Arrays that are Equal to "element_1"
        index_1 = distance(nodes.begin(), find_if(begin(nodes), end(nodes),
                                                [element_1](vector<pNode> &item){return item.at(0).first[0] == element_1;}));

        if(index_1 == int(nodes.size())){	    // If "nodes" does Not Have any pNode Vector which Has A pNode with array<int, 2>()[0] = "element_1"
            nodes.push_back(vector<pNode>());	// Adding New Empty pNode Sub-Vector to the "nodes" Vector and Now the "index_1" is the Index of This
        }

        else{									// This "else" Block Prevents Adding the pNode of the Same Small Route to any Sub-Vector
            element_2 = temp.at(i).first[1];    // Getting array<int, 2>()[1] from the pNode(array<int, 2>, int) in the "temp" Vector

            // index_2: Index of the pNode Pair which Has array<int, 2>()[1] = "element_2"
            index_2 = distance(nodes.at(index_1).begin(), find_if(begin(nodes.at(index_1)), end(nodes.at(index_1)),
                                                             [element_2](pNode &item){return item.first[1] == element_2;}));

            if (index_2 < int(nodes.at(index_1).size()))    // If A pNode with the Same array<int, 2> is Already in the Related Sub-Vector
                continue;                                   // Do Not Add This pNode of the Same Small Route Again to the Related Sub-Vector
        }

		nodes.at(index_1).push_back(temp.at(i));	// Add the Current pNode from the temp Vector to the pNode Sub-Vector at index = "index_1"
    }

    // All the pNodes Have Been Added to the "nodes" Vector of pNode Vectors as Grouped by the array<int, 2>[0] Values


    // Sorting the Elements (Pairs) of pNode Sub-Vectors by the array<int, 2>() Elements of pNode Pairs
    for(int j=0; j<int(nodes.size()); j++){
        sort(nodes.at(j).begin(), nodes.at(j).end(), [](auto &left, auto &right){return left.first < right.first;});
    }
    // Sorting the Sub-Vectors of "nodes" Vector by the array<int, 2>()[0] Values of pNode Pairs in Each Sub-Vector
    sort(nodes.begin(), nodes.end(), [](auto &left, auto &right){return left.at(0).first[0] < right.at(0).first[0];});


    // Printing the Content of "nodes" Vector
    for(int m=0; m<int(nodes.size()); m++){
        for(int n=0; n<int(nodes.at(m).size()); n++){
            cout << nodes.at(m).at(n).first[0] << ", " << nodes.at(m).at(n).first[1] << ": " << nodes.at(m).at(n).second << endl;
        }cout << endl;
    }



cout << endl << "-------------" << endl;
system("pause");
return 0;
}
