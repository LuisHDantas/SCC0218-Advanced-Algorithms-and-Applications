#include <iostream>
#include <unordered_map>

using namespace std;

int main(){
    int numCourses;

    //map where the key is the student's ID and the value is the course they are taking
    unordered_map<int, int> data;
    //map where the key is the course ID and the value is the number of students
    unordered_map<int, int> dataCourses;

    //gets the number of courses
    cin >> numCourses;

    for(int i=0; i<numCourses; i++){
        //gets number of students on the course
        int numStudents;
        cin >> numStudents;

        //gets each student
        for(int j=0; j<numStudents; j++){
            int idStudent;
            cin >> idStudent;

            //if student is not already taking a course
            if(data.find(idStudent) == data.end()){
                data[idStudent] = i;
                dataCourses[i]++;
            }
            //if student is taking multiples courses, he is removed from all courses
            else if(data[idStudent] != i){
                dataCourses[data[idStudent]]--;
                data[idStudent] = -1;
            }
        }
    }

    //prints the number of students in each course
    for(int i=0; i<numCourses; i++)
        cout << dataCourses[i] << " ";
    

    return 0;
}