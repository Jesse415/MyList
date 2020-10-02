#include <iostream>
#include <cstdio>
#include <cstring>

int ErrorCheck();

int CheckForNeg(int Value);

class MyList {

private:
    int IntCount;                                   // the number of integers currently stored in IntArray
    int MaxSize;                                    // the maximum size of IntArray (defaults to 10)
    int *IntArray;                                  // a pointer to the IntArray IntArray always contains -999 at index 0
    bool SortedList;                                // a flag to indicate whether this list is to be sorted ascending (true = sorted, false = unsorted)

    int BinarySearch(int Value) {                   // this function is private because it should only be called by Search()
        int Left = 1, Middle, Right;

        Right = IntCount;
        Middle = (Left + Right) / 2;

        while (Left <= Right) {
            if (IntArray[Middle] == Value) {
                return Middle;
            } else if (IntArray[Middle] < Value) {
                Left = Middle + 1;
            } else {
                Right = Middle - 1;
            }
            Middle = (Left + Right) / 2;
        }
        if (Left > Right) {
            return 0;
        }
        return 0;
    }

    void SortListFc(int *ArrayToSort) {                     //Sort list function
        for (int i = 1; i <= IntCount; i++) {
            for (int j = i + 1; j <= IntCount; j++) {
                if (ArrayToSort[j] < ArrayToSort[i]) {
                    int temp = ArrayToSort[i];
                    ArrayToSort[i] = ArrayToSort[j];
                    ArrayToSort[j] = temp;
                }
                SortedList = true;
            }
        }
    }

public:
    MyList() {                                              // the default constructor
        MaxSize = 10;
        IntCount = 0;
        IntArray = new int[MaxSize];
        IntArray[0] = -999;
        SortedList = false;                                  // defaults to unsorted
    }

    explicit MyList(int InputSize) {                         // constructor with custom array size
        MaxSize = InputSize;
        IntCount = 0;
        IntArray = new int[MaxSize];
        IntArray[0] = -999;
        SortedList = false;
    }

    int Search(int Value) {                         // search for value passed return index
        if (SortedList) {
            return BinarySearch(Value);
        } else {
            for (int i = 1; i <= MaxSize; i++) {
                if (IntArray[i] == Value) {
                    return i;
                }
            }
        }
    }

    int GetIndex(int Value) {                      // return the value of IntArray at that index
        int i = Search(Value);

        if (IntArray[i] == Value) {
            return i;
        } else {
            return 0;
        }
    }

    void GetMaxSize() {
        std::cout << MaxSize << std::endl;
    }

    void SetSortedList() {
        if (!SortedList) {
            SortListFc(IntArray);
        } else {
            std::cout << "List is already sorted. Type display to check." << std::endl;
        }
        SortedList = true;
    }

    void UnSortList() {
        SortedList = false;
    }

    void AddInt(int Value) {                                       //adding int, if list is sorted put in right slot, and move array over
        if (Value <= -999) {
            std::cout << "Number always has to be greater than -999" << std::endl;
            return;
        } else if (IntCount >= MaxSize) {
            std::cout << "Error. The array is full!" << std::endl;
        } else if (SortedList) {
            for (int i = 1; i < MaxSize; i++) {
                if (Value < IntArray[i]) {
                    int j = i;
                    for (int k = IntCount + 1; k >= j; k--) {
                        IntArray[k] = IntArray[k - 1];
                        if (k == j) {
                            IntArray[k] = Value;
                            IntCount++;
                            return;
                        }
                    }
                }
            }
        } else if (!SortedList) {                                  //if not sorted, add to the end and print array
            if (IntCount <= MaxSize) {
                IntArray[IntCount + 1] = Value;
                IntCount++;
            }
        }
    }

    void Display() {                                              //print the number IntCount, then loop through and print the list
        std::cout << IntCount << std::endl;
        for (int i = 0; i <= IntCount; i++) {
            std::cout << "IntArray[" << i << "] = " << IntArray[i] << std::endl;
        }
        std::cout << std::endl;
    }

    bool Delete(int Value) {
        int i = Search(Value);                                   //call search function, receive the index to remove
        if (SortedList) {
            if (i > 0) {
                for (i; i < IntCount; i++) {
                    IntArray[i] = IntArray[i + 1];
                }
                IntCount--;
            }
        } else {
            IntArray[i] = IntArray[IntCount--];
        }
        return true;
    }
};

int main() {
    MyList ML1;
    char Change[100];
    bool ValidStr = false;
    int NumChange;

    while (!ValidStr) {
        std::cout << "The default size of array is 10. Would you like to Change it? [Yes/No]: " << std::endl;
        std::cin >> Change;

        if ((strcmp(Change, "yes")) == 0
            || (strcmp(Change, "Yes")) == 0
            || (strcmp(Change, "Y")) == 0
            || (strcmp(Change, "y")) == 0) {

            std::cout << "What number would you like to Change it to? " << std::endl;

            NumChange = ErrorCheck();               //error checking for integer

            NumChange = CheckForNeg(NumChange);     //error checking for positive integer

            ML1 = MyList(NumChange);
            ValidStr = true;

        } else if ((strcmp(Change, "No")) == 0
                   || (strcmp(Change, "no")) == 0
                   || (strcmp(Change, "N")) == 0
                   || (strcmp(Change, "n")) == 0) {
            ML1 = MyList();
            ValidStr = true;
        } else {
            std::cout << "Your input is not valid! Try again!" << std::endl;
        }
    }


//read in instructions from the user in an infinite loop: add, delete, sort, unsort, display, quit
    char UserInput[100];
    bool LoopControl = true;

    while (LoopControl) {
        std::cout << "Please enter add, delete, sort, unsort, display, max_size, get_index or quit" << std::endl;
        std::cin >> UserInput;

        int Value;

        if (strcmp(UserInput, "quit") == 0) {
            std::cout << "program quitting" << std::endl;
            LoopControl = false;
        } else if (strcmp(UserInput, "add") == 0) {
            std::cout << "please enter the value to add" << std::endl;
            Value = ErrorCheck();
            ML1.AddInt(Value);
        } else if (strcmp(UserInput, "delete") == 0) {
            std::cout << "please enter the value to be deleted" << std::endl;
            Value = ErrorCheck();
            ML1.Delete(Value);
        } else if (strcmp(UserInput, "display") == 0) {
            ML1.Display();
        } else if (strcmp(UserInput, "sort") == 0) {
            std::cout << "List will now be sorted." << std::endl;
            ML1.SetSortedList();
        } else if (strcmp(UserInput, "unsort") == 0) {
            std::cout << "List will no longer be sorted." << std::endl;
            ML1.UnSortList();
        } else if (strcmp(UserInput, "max_size") == 0) {
            ML1.GetMaxSize();
        } else if (strcmp(UserInput, "get_index") == 0) {
            std::cout << "What value are you searching for?" << std::endl;
            Value = ErrorCheck();
            int Result = ML1.GetIndex(Value);
            std::cout << "Index value index is " << Result << std::endl;
        } else {
            std::cout << "Incorrect input" << std::endl;
        }
    }
    return 0;
};

//function to check all std::cin for proper integers

int ErrorCheck() {
    int Check;
    while (!(std::cin >> Check)) {
        std::cin.clear();
        std::cin.ignore(100, '\n');
        std::cout << "Your input is not valid! Try again!" << std::endl;
    }
    return Check;
}

//function checking for negative value input for list size

int CheckForNeg(int Value) {
    if (Value <= 0) {
        while (Value <= 0) {
            std::cout << "Your input can not be a negative. Try again." << std::endl;
            Value = ErrorCheck();
        }
    }
}
