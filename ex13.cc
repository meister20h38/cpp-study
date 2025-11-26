/*
 * @file SkeltonEx13.cpp
 * @brief Skelton of Ex-13 ofin PL04: Programming C++
 * @author Keitaro Naruse
 * @author Kosei Fujita
 * @date 2022-11-17
 * @date 2025-11-26
 * @copyright MIT License
*/
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <stdexcept>
#include <iomanip> 

using namespace std;

// vectorの中央値を計算する
double median(vector<double> vec) {
    typedef vector<double>::size_type vec_sz;
    vec_sz size = vec.size();
    if (size == 0) throw domain_error("median of an empty vector");
    sort(vec.begin(), vec.end());
    vec_sz mid = size / 2;
    return size % 2 == 0 ? (vec[mid] + vec[mid - 1]) / 2 : vec[mid];
}

// 評価点（中間、期末、宿題）から成績を計算する
double grade(double midterm, double final, double homework) {
    return 0.2 * midterm + 0.4 * final + 0.4 * homework;
}

// 宿題のvectorを受け取って成績を計算する
double grade(double midterm, double final, const vector<double>& hw) {
    if (hw.size() == 0) throw domain_error("student has no homework");
    return grade(midterm, final, median(hw));
}

// 入力ストリームから宿題の点数を読み込む
istream& read_hw(istream& in, vector<double>& hw) {
    if (in) {
        hw.clear();
        double x;
        while (in >> x) hw.push_back(x);
        in.clear(); // 次の入力のためにストリームのエラー状態をクリア
    }
    return in;
}

/*
    Core class
        Provide core functions for student information
*/
class Core{
    //  Put code below
    friend class Student_info;
public:
    Core() : midterm(0), final(0) {}
    Core(istream& is) { read(is); }
    virtual ~Core() {}

    string name() const { return n; }

    // 仮想関数: 成績計算
    virtual double grade() const {
        return ::grade(midterm, final, homework);
    }

    // 仮想関数: 入力読み込み
    virtual istream& read(istream& in) {
        read_common(in);
        read_hw(in, homework);
        return in;
    }

    // 仮想関数: 演習の回答数が0かどうかを判定
    virtual bool valid() const {
        return !homework.empty();
    }
    
protected:
    // Handleクラス(Student_info)のための仮想コピーコンストラクタ
    virtual Core* clone() const { return new Core(*this); }

    istream& read_common(istream& in) {
        in >> n >> midterm >> final;
        return in;
    }

    double midterm, final;
    vector<double> homework;

private:
    string n;
};

/*
    Grad class
        Provide a class for a graduate student
*/
class Grad: public Core {
    //  Put code below
    public:
    Grad() : thesis(0) {}
    Grad(istream& is) { read(is); }

    // オーバーライド: 成績計算（論文点数を考慮）
    double grade() const {
        return min(Core::grade(), thesis);
    }

    // オーバーライド: 入力読み込み（論文点数を読み込む）
    istream& read(istream& in) {
        read_common(in);
        in >> thesis;
        read_hw(in, homework);
        return in;
    }

protected:
    // Handleクラスのための仮想コピーコンストラクタ
    Grad* clone() const { return new Grad(*this); }

private:
    double thesis;
};

/*
    Student_info class
        Provide a hundle class
*/
class Student_info{
//  Put code below
//  Student_info class should have valid() function
public:
    // コンストラクタ
    Student_info() : cp(0) {}
    Student_info(istream& is) : cp(0) { read(is); }
    
    // コピーコンストラクタ
    Student_info(const Student_info& s) : cp(0) {
        if (s.cp) cp = s.cp->clone();
    }

    // 代入演算子
    Student_info& operator=(const Student_info& s) {
        if (&s != this) {
            delete cp;
            if (s.cp)
                cp = s.cp->clone();
            else
                cp = 0;
        }
        return *this;
    }
   
   // デストラクタ
    ~Student_info() { delete cp; }

    // 入力読み込み: 先頭の文字でCoreかGradかを判断して生成
    istream& read(istream& is) {
        delete cp;
        
        char ch;
        is >> ch; // 'U' or 'G' を読み込む

        if (ch == 'U' || ch == 'u') {
            cp = new Core(is);
        } else if (ch == 'G' || ch == 'g') {
            cp = new Grad(is);
        } else {
            cp = 0; // 不正な入力またはEOF
        }
        return is;
    }

    string name() const {
        if (cp) return cp->name();
        throw std::runtime_error("uninitialized Student_info");
    }
    
    double grade() const {
        if (cp) return cp->grade();
        throw std::runtime_error("uninitialized Student_info");
    }

    // 演習の回答数チェック
    // cpが存在し、かつその指すオブジェクトのhomeworkが空でない場合にtrue
    bool valid() const {
        if (cp) return cp->valid();
        return false;
    }

    static bool compare(const Student_info& s1, const Student_info& s2) {
        return s1.name() < s2.name();
    }

private:
    Core* cp;
};

/*
    main()
*/
int main(int argc, char* argv[])
{
    std::vector<Student_info> students;
    Student_info record;
    std::string::size_type maxlen = 0;

    while( record.read(cin) ){
        maxlen = std::max( maxlen, record.name().size() );
        students.push_back( record );
    }
    
    std::sort(students.begin(), students.end(), Student_info::compare);
    
    for(std::vector<Student_info>::size_type i = 0; i != students.size(); ++i){
        std::cout << students[i].name()
	      << std::string(maxlen + 1 - students[i].name().size(), ' ');
        if( students[i].valid() ){
            double final_grade = students[i].grade();
            std::streamsize prec = std::cout.precision();
            std::cout << std::setprecision(3) << final_grade
		    << std::setprecision(prec);
        }
        else{
            std::cout << "Caanot evaluate";
        }
        std::cout << std::endl;
    }
    
    return 0;
}
