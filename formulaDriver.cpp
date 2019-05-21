#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
using std::vector;
using std::cout;
using std::cin;
using std::endl; 
using std::string;
using std::setw;
using std::setfill;
using std::ifstream;
using std::ofstream;
using std::getline;
using std::istringstream;
using std::stringstream;
using std::ostringstream;
using std::stringstream;
using std::ostream;

struct litskiDetails {
  unsigned int index;
  string name;
  float servingSize;
  float servingPrice;
  float purchaseQuanity;
  float purchasePrice;
    
  litskiDetails() {
    index = 0;
    name = "ingredient";
    servingSize = 0;
    servingPrice = 0;
    purchaseQuanity = 0;
    purchasePrice = 0;
  }
  
  // Overlod operator <<
  // Allows convinient stream output of moves
  friend ostream& operator<< (ostream& outs, const litskiDetails& lsd) {
    outs << std::left << setw(3) << setfill(' ') << lsd.index
         << std::left << setw(25) << setfill(' ')  << lsd.name
         << std::left << setw(20) << setfill(' ') << lsd.servingSize
         << std::left << setw(20) << setfill(' ') << lsd.servingPrice
         << std::left << setw(20) << setfill(' ') << lsd.purchaseQuanity
         << std::left << setw(20) << setfill(' ') << lsd.purchasePrice;
    return outs;
  }
};

class Litski {
  
    public: 
    
    // Navigate options   
    void MainMenu();
    
    // Add item
    void addIngredient(vector<litskiDetails> formulaHolder);
    
    // Remove item
    void removeIngredient();
    
    // Output Total price
    // include serving and unit price
    string outputFormula(vector<litskiDetails> &formula);
    
    // Calculate LCD on quantity
    // store as new array w/ updated details
    int minPurchase();
    
    // confirming changes
    void validateFormula(vector<litskiDetails> formulaHolder);
    
    // Save ingredient list
    bool saveFormula(vector<litskiDetails> formulaAppender, string filename);
    
    // load ingredient list
    bool loadFormula(string filename);
    
    // calculate leftover
    int overflowServings();
  
    void Exit();
       
  private:
  
    litskiDetails tokenizeFormula(string input);
    vector<litskiDetails> formula, formulaHolder,formulaAppender;
    int option, counter = 0;
    float size, price, quantity;
    string filename;
 
  };

int main() {
  Litski L;
  
  L.loadFormula("formula.txt");
  L.MainMenu();
  
  return 0;
}

void Litski::MainMenu() {
  cout << std::left << setw(3) << setfill(' ') << "#" << "Main Menu" << endl
       << std::left << setw(3) << setfill(' ') << "1" << "Add Ingredient" << endl
       << std::left << setw(3) << setfill(' ') << "2" << "Remove Ingredient" << endl
       << std::left << setw(3) << setfill(' ') << "3" << "Output" << endl
       << std::left << setw(3) << setfill(' ') << "4" << "Min Purchase" << endl
       << std::left << setw(3) << setfill(' ') << "5" << "Overflow" << endl
       << std::left << setw(3) << setfill(' ') << "6" << "Load new formula" << endl
       << std::left << setw(3) << setfill(' ') << "7" << "Exit" << endl
       << "Enter Option: ";
  cin >> option;
  switch (option) {
    case 1: {
      addIngredient(formulaHolder);
      break;
    }
    case 2: {
      removeIngredient();
      break;
    }
    case 3: {
      cout << outputFormula(formula) << endl;
      MainMenu();
      break;
    }
    case 4: {
      minPurchase();
      break;
    }
    case 5: {
      cout << overflowServings();
      break;
    }
    case 6: {
      loadFormula(filename);
      break;
    }
    case 7: {
      Exit();
      break;
    }
  }
}

void Litski::addIngredient(vector<litskiDetails> formulaHolder) {
  litskiDetails lsd;
  // automatically keep track of index
  counter += 1;
  lsd.index = formula.size() + counter;
  cout << "\nFill in the following\nName: ";
    cin >> lsd.name;
  cout << "Purchase Price: ";
    cin >> price;
    lsd.purchasePrice = price;
  cout << "Quantity(grams): ";
    cin >> quantity;
    lsd.purchaseQuanity = quantity;
    cin.ignore(256, '\n');
  cout << "Serving Size(grams): ";
    cin >> size;
    lsd.servingSize = size;
  lsd.servingPrice = price / (quantity/size);
  formulaHolder.push_back(lsd);
  validateFormula(formulaHolder);
}

void Litski::validateFormula(vector<litskiDetails> formulaHolder) {
  cout << "\nPlease verify that the following details are correct:" << endl;
  outputFormula(formulaHolder);
    cout << std::left << setw(3) << setfill(' ') << "#" << "Options" << endl
       << std::left << setw(3) << setfill(' ') << "1" << "Confirm" << endl
       << std::left << setw(3) << setfill(' ') << "2" << "Edit" << endl
       << std::left << setw(3) << setfill(' ') << "3" << "Add another Ingredient" << endl
       << std::left << setw(3) << setfill(' ') << "4" << "Main Menu" << endl
       << "Enter Option: ";
    cin >> option;
  if (option == 1) {
    cout << "Enter filename: ";
      cin >> filename;
    saveFormula(formulaHolder, filename);
  }
  else if (option == 2) {
    counter--;
    // does not reindex curreently
    if ( formulaHolder.size() == 1)
      addIngredient(formulaHolder);
    else {
      formulaHolder.pop_back();
      addIngredient(formulaHolder);
    }
  }
  else if (option == 3) 
    addIngredient(formulaHolder);
  else if (option == 4)
    MainMenu();
}

bool Litski::saveFormula(vector<litskiDetails> formulaHolder, string filename) {
    cout << "\nOpening " << filename <<  " for appending..." << endl;
    // Declare our Stream and open all at once
    ofstream fout(filename, std::ios::app);
    // Output/Append to move.txt
    if (fout.good()) {
      for ( unsigned int i = 0; i< formulaHolder.size(); i++)
      fout << formulaHolder.at(i).index << "," 
        << formulaHolder.at(i).name << ","
        << formulaHolder.at(i).servingSize << ","
        << formulaHolder.at(i).servingPrice<< ","
        << formulaHolder.at(i).purchaseQuanity << ","
        << formulaHolder.at(i).purchasePrice
        << "\n";
        // Close out Streams
      fout.close();
      // clear vectors
      formulaHolder.clear();
      formula.clear();
      loadFormula(filename);
      cout << endl << "Save was successful\n\n";
      outputFormula(formula);
      MainMenu();
    }  
    else {
      cout << "Failed to append\n";
     }
  return false;
}


void Litski::removeIngredient() {
  
}

string Litski::outputFormula(vector<litskiDetails> &formula) {
  // header
  cout << std::left << setw(3) << setfill(' ') << "#"
      << std::left << setw(25) << setfill(' ')  << "Name"
      << std::left << setw(20) << setfill(' ') << "Serving Size(g)"
      << std::left << setw(20) << setfill(' ') << "Price per Serving"
      << std::left << setw(20) << setfill(' ') << "Quanity(g)"
      << std::left << setw(20) << setfill(' ') << "Price per unit"
      << endl;
  // contents
  for (auto i = formula.begin(); i != formula.end(); i++) {
    cout << *i << endl;
  }
  cout << endl;
  return "";
} 

int Litski::minPurchase() {
  
}

int Litski::overflowServings() {
  
}

bool Litski::loadFormula(string filename) {
    // open file
  ifstream inputFile;
  inputFile.open(filename);
  // if open
  if(inputFile.is_open()) {
    string fileLine;
    unsigned int i = 0;
    // load fileline data into vector
    while (getline(inputFile, fileLine)) {
      // ignore comment lines with # in file
      if ( fileLine[0] != '#') {
        formula.push_back(tokenizeFormula(fileLine));
        i++;
      }
    } 
    inputFile.close();
    cout << filename << " was loaded\n\n";
    return true;
  }
  else {
    cout << "No file was loaded.\n";
    return false;
  }
}

litskiDetails Litski::tokenizeFormula(string input) {
  litskiDetails lsd;
  string convertIndex, convertServingSize, convertServingPrice, convertPurchaseQuantity, convertPurchasePrice;
  istringstream ss(input);
  // convert to #
  // index
  getline(ss, convertIndex, ',');
    stringstream ssCRN(convertIndex); 
    ssCRN >> lsd.index;
    // clear string + buffer so it can be used again
    ssCRN.str("");
    ssCRN.clear();   
  // name
  getline(ss, lsd.name, ',');
  // Serving Size
  getline(ss, convertServingSize, ',');
   ssCRN << " " << convertServingSize;
    ssCRN >> lsd.servingSize;
    ssCRN.str("");
    ssCRN.clear();
  // Price per Serving
  getline(ss, convertServingPrice, ',');
   ssCRN << " " << convertServingPrice;
    ssCRN >> lsd.servingPrice;
    ssCRN.str("");
    ssCRN.clear(); 
  // Total Purchase Quantity
  getline(ss, convertPurchaseQuantity, ',');
  ssCRN << " " << convertPurchaseQuantity;
    ssCRN >> lsd.purchaseQuanity;
    ssCRN.str("");
    ssCRN.clear(); 
  // Total Purchase Price
  getline(ss, convertPurchasePrice, ',');
  ssCRN << " " << convertPurchasePrice;
    ssCRN >> lsd.purchasePrice;
    ssCRN.str("");
    ssCRN.clear(); 
  return lsd;
}

void Litski::Exit() {
  
  
  cout << "\nSuccesfully exited program\n";
}