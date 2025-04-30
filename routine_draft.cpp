//----------------NOYON CPP TEMPLATE---------------\

#include<bits/stdc++.h>
using namespace std;

#define endl "\n"
#define ll long long
#define pr pair<string, string>


void file()
{
    freopen("RoutineInput.txt", "r", stdin);
    freopen("RoutineOutput.txt", "w", stdout);
    freopen("RoutineError.txt", "w", stderr);
}
//For class in a week:
int number_of_courses;
struct SECTION{
	string section_name, teacher_name;
	string day1_name, starting_time1, end_time1;
	string day2_name = "-1", starting_time2 = "-1", end_time2 = "-1";
	vector<int> DP;  //for storing which section of nextCourse can we pick if we choose this section;
};
struct COURSES{
	int number_of_class, number_of_sections;
	string course_name;
	vector<SECTION> sections;

};
struct __CLASS{
    string course_name, teacher_name, section_name;
    string start_time, end_time;
};

bool sortFun(__CLASS &a, __CLASS &b);
void print_routine(vector<COURSES> &taken);
void print_taken_input();
void input_routine_details();
void input_teacher_name();
bool time_match(pr class1, pr class2);
bool day_match(SECTION sec1, SECTION sec2, int sec1_num_of_class, int sec2_num_of_class);
bool is_valid(SECTION section, int size);
void generate_routine(int course_index);
string valid_time(string s);
void solve();


map<string,string> teacher;
vector<COURSES> vec;
vector<COURSES> taken;
vector<vector<COURSES>> takenList;
int cnt = 1, tcnt = 1, number_of_days;

bool sortFun(__CLASS &a, __CLASS &b){
    return (a.start_time<b.start_time);
}
void print_routine(vector<COURSES> &taken){
    cout<<"New Routine: "<<cnt++<<"\n---------------------------------------\n";

    //------------------FUll print----------------------
    // for(int i=0;i<number_of_courses;i++){
    //     if(teacher[taken[i].sections[0].teacher_name].size()<3){
    //         teacher[taken[i].sections[0].teacher_name] = taken[i].sections[0].teacher_name;
    //     }
    //     cout<<"Couse name: "<<taken[i].course_name<<", \tTeacher: "<<teacher[taken[i].sections[0].teacher_name]<<", \tSecion name: "<<taken[i].sections[0].section_name<<endl;
    //     cout<<"\t\tNumber Of class: "<<taken[i].number_of_class<<endl;
    //     cout<<"\t\t"<<taken[i].sections[0].day1_name<<", Start: "<<taken[i].sections[0].starting_time1<<" End: "<<taken[i].sections[0].end_time1<<endl;
    //     if(taken[i].number_of_class==2)
    //         cout<<"\t\t"<<taken[i].sections[0].day2_name<<", Start: "<<taken[i].sections[0].starting_time2<<" End: "<<taken[i].sections[0].end_time2<<endl;
    //     cout<<"                    -----\n";
    // }
    // cout<<"-------------------------------------------------------\n\n\n\n";

    //---------------------------Formated print---------------------
    map<string, vector<__CLASS>> mp;
    for(int i=0;i<number_of_courses;i++){
        __CLASS info;
        info.course_name = taken[i].course_name;
        info.section_name = taken[i].sections[0].section_name;
        info.teacher_name = taken[i].sections[0].teacher_name;
        info.start_time = taken[i].sections[0].starting_time1;
        info.end_time = taken[i].sections[0].end_time1;
        mp[taken[i].sections[0].day1_name].push_back(info);

        if(taken[i].number_of_class==2){
            __CLASS info;
            info.course_name = taken[i].course_name;
            info.section_name = taken[i].sections[0].section_name;
            info.teacher_name = taken[i].sections[0].teacher_name;
            info.start_time = taken[i].sections[0].starting_time2;
            info.end_time = taken[i].sections[0].end_time2;
            mp[taken[i].sections[0].day2_name].push_back(info);
        }
    }

    // cout<<"        |   8:30-10:00     |    10:00-11:30     |      11:30-1:00     |      1:30-3:00     |     3:00-4:30     | \n";
    for(auto it: mp){
        auto day_name = it.first;
        auto info_list = it.second;
        sort(info_list.begin(), info_list.end(), sortFun);
        cout<<day_name<<" -> ";
        for(auto &it: info_list){
            // cout<<"\t\t"<<it.start_time<<" - "<<it.end_time<<"\t\t|  ";
            string s = "               "+it.start_time+" - "+it.end_time+"  ";
            while(s.size()<35)
                s = s +  " ";
            cerr<<s.size()<<endl;
            cout<<s<<"| ";
        }
        cout<<endl<<"     ";
        int i=0;
        for(auto &it: info_list){
            // cout<<it.course_name<<" ("<<it.section_name<<") |  ";
            string s = "    "+it.course_name+" ("+it.section_name+")";
            while(s.size()<35)
                s = s +  " ";
            cerr<<s.size()<<endl;
            cout<<s<<"| ";
        }
        cout<<endl<<"     ";
        for(auto &it: info_list){
            // cout<<teacher[it.teacher_name]<<" ("<<it.teacher_name<<") |  ";
            string s = "    "+ teacher[it.teacher_name]+" ("+it.teacher_name+")";
            while(s.size()<35)
                s = s +  " ";
            cerr<<s.size()<<endl;
            cout<<s<<"| ";
        }
        cout<<endl<<endl;
    }
    cout<<"-------------------------------------------------------\n\n\n\n";
    return;
}
void print_taken_input(){
    // for(int i=0;i<number_of_courses;i++){
    //     cerr<<vec[i].course_name<<endl;
    //     cerr<<vec[i].number_of_sections<<endl;
    //     cerr<<vec[i].number_of_class<<endl;

    //     for(int j=0;j<vec[i].number_of_sections;j++){
    //         if(teacher[vec[i].sections[j].teacher_name].size()<3){
    //             teacher[vec[i].sections[j].teacher_name] = vec[i].sections[j].teacher_name;
    //         }
    //         cerr<<vec[i].sections[j].section_name<<" "<<teacher[vec[i].sections[j].teacher_name]<<" ("<<vec[i].sections[j].teacher_name<<")"<<endl;
    //         cerr<<vec[i].sections[j].day1_name<<" -> "<<vec[i].sections[j].starting_time1<<" "<<vec[i].sections[j].end_time1<<endl;
    //         if(vec[i].number_of_class==2){
    //             cerr<<vec[i].sections[j].day2_name<<" -> "<<vec[i].sections[j].starting_time2<<" "<<vec[i].sections[j].end_time2<<endl;
    //         }
    //     }
    //     cerr<<"-----------------------------\n";
    // }
    for(int i=0;i<number_of_courses;i++){
        cerr<<vec[i].course_name<<" "<<vec[i].number_of_sections<<endl;
        for(int j=0;j<vec[i].number_of_sections;j++){
            if(teacher[vec[i].sections[j].teacher_name].size()<3){
                teacher[vec[i].sections[j].teacher_name] = vec[i].sections[j].teacher_name;
            }
            cerr<<vec[i].sections[j].section_name<<" "<<teacher[vec[i].sections[j].teacher_name]<<" ("<<vec[i].sections[j].teacher_name<<")"<<endl<<endl;
        }
        cerr<<"-----------------------------\n";
    }
}
void input_routine_details(){
    cin>>number_of_courses;
    vec.resize(number_of_courses);
    taken.resize(number_of_courses);

    for(int i=0;i<number_of_courses;i++){
        cin>>vec[i].course_name;
        cin>>vec[i].number_of_sections;
        cin>>vec[i].number_of_class;

        taken[i].course_name = vec[i].course_name;
        taken[i].number_of_sections = vec[i].number_of_sections;
        taken[i].number_of_class = vec[i].number_of_class;

        vec[i].sections.resize(vec[i].number_of_sections);
        for(int j=0;j<vec[i].number_of_sections;j++){
            cin>>vec[i].sections[j].section_name;
            cin>>vec[i].sections[j].teacher_name;
            cin>>vec[i].sections[j].day1_name;
            cin>>vec[i].sections[j].starting_time1;
            cin>>vec[i].sections[j].end_time1;
            vec[i].sections[j].starting_time1 = valid_time(vec[i].sections[j].starting_time1);
            vec[i].sections[j].end_time1 = valid_time(vec[i].sections[j].end_time1);
            if(vec[i].number_of_class==2){
                cin>>vec[i].sections[j].day2_name;
                cin>>vec[i].sections[j].starting_time2;
                cin>>vec[i].sections[j].end_time2;
                vec[i].sections[j].starting_time2 = valid_time(vec[i].sections[j].starting_time2);
                vec[i].sections[j].end_time2 = valid_time(vec[i].sections[j].end_time2);
            }
        }
    }
}
void input_teacher_name(){
    freopen("teacher_name.txt", "r", stdin);
    string s;
    while(cin>>s){
        cin>>teacher[s];
        // cerr<<s<<" "<<teacher[s]<<endl;
    }
}
bool time_match(pr class1, pr class2){
    if(class1.first>=class2.second)  {
        // cerr<<"Condition true1: "<<class1.first<<" "<<class2.second<<endl;
        return true;
    }
        
    if(class1.second<=class2.first){
        // cerr<<"Condition true1: "<<class1.second<<" "<<class2.first<<endl;
        return true;
    }
    return false;
}
bool day_match(SECTION sec1, SECTION sec2, int sec1_num_of_class, int sec2_num_of_class){
    if(sec1_num_of_class==1) {
        if(sec2_num_of_class==1){
            bool flag = true;
            if(sec1.day1_name==sec2.day1_name)
                flag &= time_match({sec1.starting_time1,sec1.end_time1}, {sec2.starting_time1,sec2.end_time1});
            return flag;
        }
        else{
            bool flag = true;
            if(sec1.day1_name==sec2.day1_name)
                flag &= time_match({sec1.starting_time1,sec1.end_time1}, {sec2.starting_time1,sec2.end_time1});
            if(sec1.day1_name==sec2.day2_name)    
                flag &= time_match({sec1.starting_time1,sec1.end_time1}, {sec2.starting_time2,sec2.end_time2});
            return flag;
        }
    }
    else{
        if(sec2_num_of_class==1){
            bool flag = true;
            if(sec1.day1_name==sec2.day1_name)
                flag &= time_match({sec1.starting_time1,sec1.end_time1}, {sec2.starting_time1,sec2.end_time1});
            if(sec1.day2_name==sec2.day1_name)    
                flag &= time_match({sec1.starting_time2,sec1.end_time2}, {sec2.starting_time1,sec2.end_time1});
            return flag;
        }
        else{
            bool flag = true;
            if(sec1.day1_name==sec2.day1_name)
                flag &= time_match({sec1.starting_time1,sec1.end_time1}, {sec2.starting_time1,sec2.end_time1});
            if(sec1.day1_name==sec2.day2_name)    
                flag &= time_match({sec1.starting_time1,sec1.end_time1}, {sec2.starting_time2,sec2.end_time2});
            if(sec1.day2_name==sec2.day1_name)
                flag &= time_match({sec1.starting_time2,sec1.end_time2}, {sec2.starting_time1,sec2.end_time1});
            if(sec1.day2_name==sec2.day2_name)    
                flag &= time_match({sec1.starting_time2,sec1.end_time2}, {sec2.starting_time2,sec2.end_time2});
            return flag;
        }
    }
    return false;
}
bool is_valid(SECTION section, int size){
    bool flag = true;
    for(int i=0;i<size;i++){
        flag &= day_match(taken[i].sections[0], section, vec[i].number_of_class, vec[size].number_of_class);
    }
    return flag;
}

void generate_routine(int course_index){
    if(course_index>=number_of_courses){
        //All conditions must be written here: for example:
        // if(taken[0].sections[0].teacher_name!="FIF") return;
        // if(taken[1].sections[0].teacher_name!="WT") return;
        // Number of class must be 2 for all courses
        // if(taken[0].number_of_class!=2) return;

        // To check whether selected teacher is my favorite or not
        // if(taken[1].sections[0].teacher_name!="WT" || taken[2].sections[0].teacher_name!="WT") return;
        
        // To check whether selected day is my choice or not
        // if(taken[2].sections[0].day1_name!="MON") return;
        // if(taken[1].sections[0].teacher_name!="WT" && taken[1].sections[0].teacher_name!="JA") return;
        // if(taken[2].sections[0].teacher_name!="SR") return;

        // if(taken[2].sections[0].teacher_name=="PR" || 
        //     taken[2].sections[0].teacher_name=="RA" ||
        //     taken[2].sections[0].teacher_name=="MAS" ||
        //     taken[2].sections[0].teacher_name=="JI" ||
        //     taken[2].sections[0].teacher_name=="MMM" ||
        //     taken[2].sections[0].teacher_name=="SFR" ||
        //     taken[2].sections[0].teacher_name=="RP" ||
        //     taken[2].sections[0].teacher_name=="SH" ||
        //     taken[2].sections[0].teacher_name=="MAQ" ||
        //     taken[2].sections[0].teacher_name=="ZH"
        //     ) return;

        // TO check whether number of days are 3 or not
        number_of_days = 2;
        map<string, int> mp;
        for(auto &it: taken){
            mp[it.sections[0].day1_name]++;
            if(it.number_of_class==2){
                mp[it.sections[0].day2_name]++;
            }
        }
        if(mp.size()==number_of_days){
            // print();
            takenList.push_back(taken);
            cnt++;
            cerr<<"------This was right\n\n";
        }
        mp.clear();
        tcnt++;
        return;
    }
    bool flag = false;
    for(int i=0;i<vec[course_index].number_of_sections;i++){
        if(is_valid(vec[course_index].sections[i], course_index)){
            taken[course_index].sections.push_back(vec[course_index].sections[i]);
            generate_routine(course_index+1);
            taken[course_index].sections.pop_back();
            flag = true;
        }
    }
    if(!flag) return;
}
string valid_time(string s){
    if(s[1]==':'){\
        // cerr<<s<<" ";
        if(s[0]>='8') {
            s = "0" + s ;
        }
        else{
            s = "1" + s;
            s[1] += 2;
        }
        // cerr<<s<<endl;

    }
    return s;
}
void solve(){
    
    input_routine_details();
    input_teacher_name();


    print_taken_input();
    

    generate_routine(0);
    cout<<"Total Combination: "<<tcnt<<endl;
    cout<<"Total "<<number_of_days<<"days Combination: "<<cnt<<endl;
    cnt = 1;
    for(auto it: takenList){
        print_routine(it);
    }
}  

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    

    file();

    int T=1;
    // cin>>T;
    for(int i=1;i<=T;i++){
        // cout<<"Case "<<i<<": ";
        // cerr<<"\n\nCase "<<i<<": \n";
        solve();
    }
    return 0;
}
