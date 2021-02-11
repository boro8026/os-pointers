// compile: g++ -std=c++11 -o pointers pointers.cpp
#include <iostream>
#include <string>
#include <stdbool.h>
#include <string.h>
#include <math.h>


typedef struct Student {
    int id;
    char *f_name;
    char *l_name;
    int n_assignments;
    double *grades;
} Student;

int promptInt(std::string message, int min, int max);
double promptDouble(std::string message, double min, double max);
void calculateStudentAverage(void *object, double *avg);

int main(int argc, char **argv)
{
    Student student;
    double average;

    // Sequence of user input -> store in fields of `student`
    //Get the students ID
    student.id = promptInt("Please enter the student's id number: ",0,999999999);

    //Get the students first name
    student.f_name = new char[128];
    std::cout << "Please enter the student's first name: ";
    std::cin >> student.f_name;
    
    //Get the students last name
    student.l_name = new char[128];
    std::cout << "Please enter the student's last name: ";
    std::cin >> student.l_name;
    std::cin.ignore();

    //Get the number of graded assignments
    student.n_assignments = promptInt("Please enter how many assignments were graded: ",1,134217728);
    std::cout << std::endl;
    //Get all of the grades
    student.grades = new double[student.n_assignments];

    double newGrade;
    std::string mainTemplate = "Please enter grade for assignment ";
    for(int index = 0; index < student.n_assignments; index++)
    {
        std::string finalTemplate = mainTemplate + std::to_string(index) + ": "; //creates a correctly formatted prompt
        newGrade = promptDouble(finalTemplate,0,1000);      //get all of the grade values
        student.grades[index] = newGrade;
    }

    double avg = student.n_assignments; //setting average to number of assignments to pass it to the method
    calculateStudentAverage(student.grades,&avg);

    std::cout <<std::endl;
    std::cout << "Student: " << student.f_name << " " << student.l_name << " [" << student.id << "]" << std::endl;
    std::cout << "  Average grade: " << avg << std::endl;

    return 0;
}

/*
   message: text to output as the prompt
   min: minimum value to accept as a valid int
   max: maximum value to accept as a valid int
*/
int promptInt(std::string message, int min, int max)
{
    bool validInput = false;
    std::string input;

    while(!validInput) //While there has not been a valid input entered
    {
        std::cout << message; //output message
        std::getline(std::cin, input); //get the users input
        validInput = true;

        if(input == "") //if empty string entered, not a valid input
        {
            validInput = false;
        }

        for(char currChar: input) //if any of the characters is not a digit, not a valid input
        {
            if(!isdigit(currChar))
            {
                validInput = false;
            }
        }
        if(!validInput) //if not a valid input, prompt them with error message
        {
            std::cout << "Sorry, I cannot understand your answer" << std::endl;
        }

        if(validInput && (stoi(input) < min || stoi(input) > max)) //if input is out of range
        {
            std::cout << "Input out of range. Must be between: " << min << " and " << max << "inclusive" << std::endl;
            validInput = false;
        }
    }
    return stoi(input);
}

/*
   message: text to output as the prompt
   min: minimum value to accept as a valid double
   max: maximum value to accept as a valid double
*/
double promptDouble(std::string message, double min, double max)
{
    bool validInput = false;
    std::string input;

    while(!validInput) //While there has not been a valid input
    {
        std::cout << message; //prompt user
        std::getline(std::cin, input); //get users value
        validInput = true;

        if(input == "") //if empty string, thats an in valid input
        {
            validInput = false;
        }

        int decimalCounter = 0;
        for(char currChar: input) //for each character in the inputted string
        {
            if((int)currChar == 46) //if the character is a decimal point, increment counter
            {
                decimalCounter++;
            }
            else if(!isdigit(currChar)) //if anything is not a digit or decimal point, invalid
            {
                validInput = false;
            }
        }
        if(decimalCounter > 1) //if there are more than one decimal, invalid input
        {
            validInput = false;
        }

        if(!validInput) //prompt user with error
        {
            std::cout << "Sorry, I cannot understand your answer" << std::endl;
        }

        if(validInput && (stod(input) < min || stod(input) > max)) //if the input is out of bounds
        {
            std::cout << "Input out of range. Must be between: " << min << " and " << max << std::endl;
            validInput = false;
        }
    }
    return stod(input);
}

/*
   object: pointer to anything - your choice! (but choose something that will be helpful)
   avg: pointer to a double (can store a value here)
*/
void calculateStudentAverage(void *object, double *avg)
{
    double *arr = (double*)object; //store the grades of the student from void *object
    double sizeOfArr = *avg; //get the value of number of assignments
    double sum = 0;
    for(int index = 0; index < sizeOfArr; index++) //calculate sum of all the grades
    {
        sum += arr[index];
    }
    double result = sum / sizeOfArr; //get average

    result *= 10.0;
    int holdResult = result; //truncate the decimal
    if(holdResult - result <= -.5) //If the decimal is less than or equal to -.5, round up
    {
        result = ceil(result);
    }
    else //round down
    {
        result = floor(result);
    }

    *avg = result/10.0; //set the pointer equal to the calculated average
}
