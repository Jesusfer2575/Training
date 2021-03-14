#include<iostream>
#include<vector>
using namespace std;

class SubrectangleQueries {
  public:
    vector<vector<int> > rectangle;
    SubrectangleQueries(vector<vector<int>>& rectangle) {
      this->rectangle = rectangle;
    }
    
    void printRectangle() {
      int rows = (this->rectangle).size();
      for (int i = 0; i < rows ; i++) {
        int columns = this->rectangle[i].size();
        for (int j = 0; j < columns ; j++) {
          cout << this->rectangle[i][j] << " ";
        }
        cout << "\n";
      }
    }

    void updateSubrectangle(int row1, int col1, int row2, int col2, int newValue) {
      for (int i = row1; i <= row2 ; i++) {
        int columns = this->rectangle[i].size();
        for (int j = col1; j <= col2 ; j++) 
          this->rectangle[i][j] = newValue;
      }
    }
    
    int getValue(int row, int col) {
      return this->rectangle[row][col];
    }
};

int main() {
  vector<vector<int> > rectangle{{1,2,1}, {4,3,4}, {3,2,1}, {1,1,1}};
  SubrectangleQueries* sb = new SubrectangleQueries(rectangle);
  // sb->updateSubrectangle(row1,col1,row2,col2,newValue);
  sb->printRectangle();
  int param_1 = sb->getValue(0,2);
  cout << param_1 << "\n";

  sb->updateSubrectangle(0,0,3,2,5);
  sb->printRectangle();
  int param_2 = sb->getValue(0,2);
  cout << param_2 << "\n";
  return 0;
}