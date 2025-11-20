#include "CLI.h"
#include <iostream>
#include <limits>
#include <cstdlib>
#include "NormalFactory.h"
#include "PremiumFactory.h"
#include "RestrictedFactory.h"

using namespace std;

// 대여한 책 목록

CLI::CLI(LibrarySystem& system) : sys_(system) {}

int CLI::promptInt(const string& label) {
    while (true) {
        cout << label;
        int v;
        if (cin >> v) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return v;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "잘못된 입력입니다. 다시 입력해주세요." << endl;
    }
}

string CLI::promptStr(const string& label) {
    cout << label;
    string s;
    getline(cin, s);
    return s;
}

void CLI::pause() {
    cout << "계속하려면 엔터를 누르세요..." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void CLI::clearScreen() {
#ifdef _WIN32
    //system("cls");
#else
    //cout << "\x1B[2J\x1B[H";
#endif
}

void CLI::run() { roleMenu(); }

void CLI::roleMenu() {
    while (true) {
        clearScreen();
        cout << "\n===== 도서관 시스템 =====" << endl;
        cout << "1) 사용자" << endl;
        cout << "2) 관리자" << endl;
        cout << "0) 종료" << endl;
        int sel = promptInt("선택: ");
        switch (sel) {
        case 1: userMenu(); break;
        case 2: adminMenu(); break;
        case 0: return;
        default: cout << "없는 메뉴입니다." << endl; break;
        }
    }
}

void CLI::userMenu() {
    // login or register
    clearScreen();
    cout << "\n-- 사용자 로그인/회원가입 --" << endl;
    string id = promptStr("아이디: ");
    string pw = promptStr("비밀번호: ");

    currentUser_ = sys_.authenticate(id, pw);
    if (!currentUser_) {
        cout << "존재하지 않는 사용자입니다. 새로 가입하시겠습니까? (y/n): ";
        char yn; cin >> yn;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (yn == 'y' || yn == 'Y') {
            string name = promptStr("이름: ");
            sys_.addUser(id, pw, name, new NormalFactory());
            currentUser_ = sys_.authenticate(id, pw);
            cout << name << "님, 가입 완료되었습니다." << endl;
        }
        else {
            return;
        }
    }

    while (true) {
        clearScreen();
        cout << "\n-- 사용자 메뉴 -- (" << currentUser_->getName() << ", " << currentUser_->getGrade() << ")" << endl;
        cout << "1) 도서 목록 보기" << endl;
        cout << "2) 도서 대여" << endl;
        cout << "3) 도서 예약" << endl;
        cout << "4) 도서 반납" << endl;
        cout << "0) 이전" << endl;
        int sel = promptInt("선택: ");
        switch (sel) {
        case 1: userBrowse(); break;
        case 2: userRent(); break;
        case 3: userReserve(); break;
        case 4: userReturn(); break;
        case 0: return;
        default: cout << "없는 메뉴입니다." << endl; break;
        }
    }
}

void CLI::adminMenu() {
    // simple admin password
    clearScreen();
    cout << "\n-- 관리자 로그인 --" << endl;
    string pw = promptStr("관리자 비밀번호(admin): ");
    if (pw != "admin") { cout << "인증 실패" << endl; return; }

    while (true) {
        clearScreen();
        cout << "\n-- 관리자 메뉴 --" << endl;
        cout << "1) 도서 목록" << endl;
        cout << "2) 도서 추가" << endl;
        cout << "3) 도서 삭제" << endl;
        cout << "4) 재고 설정" << endl;
        cout << "5) 사용자 목록" << endl;
        cout << "6) 사용자 멤버십 변경" << endl;
        cout << "0) 이전" << endl;
        int sel = promptInt("선택: ");
        switch (sel) {
        case 1: adminListBooks(); break;
        case 2: adminAddBook(); break;
        case 3: adminRemoveBook(); break;
        case 4: adminSetStock(); break;
        case 5: adminListUsers(); break;
        case 6: adminChangeMembership(); break;
        case 0: return;
        default: cout << "없는 메뉴입니다." << endl; break;
        }
    }
}

void CLI::userBrowse() {
    clearScreen();
    auto books = sys_.listBooks();
    if (books.empty()) { cout << "등록된 도서가 없습니다." << endl; return; }
    cout << "\nID\t제목\t재고" << endl;
    for (const auto& b : books) {
        cout << b.getId() << "\t" << b.getTitle() << "\t" << sys_.getStock(b.getId()) << endl;
    }
}

void CLI::userRent() {
    clearScreen();
    int id = promptInt("대여할 도서 ID: ");
    Book* book = sys_.getBook(id);
    if (!book) { cout << "도서를 찾을 수 없습니다." << endl; return; }

    int days = promptInt("대여일 수: ");
    if (days <= 0) { cout << "대여일은 1일 이상이어야 합니다." << endl; return; }

    double fee = currentUser_->calculateRentalFee(days);
    clearScreen();
    cout << "\n=== 대여 정보 ===" << endl;
    cout << "도서: " << book->getTitle() << endl;
    cout << "대여일: " << days << "일" << endl;
    cout << "대여비: " << fee << "원" << endl;
    cout << "================\n" << endl;

    cout << "대여하시겠습니까? (y/n): ";
    char yn; cin >> yn;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (yn == 'y' || yn == 'Y') {
        sys_.rental().rentBook(currentUser_, book);
    }
    else {
        cout << "대여가 취소되었습니다." << endl;
    }
}

void CLI::userReserve() {
    int id = promptInt("예약할 도서 ID: ");
    Book* book = sys_.getBook(id);
    if (!book) { cout << "도서를 찾을 수 없습니다." << endl; return; }
    sys_.rental().reserveBook(currentUser_, book);
}

void CLI::userReturn() {
    int id = promptInt("반납할 도서 ID: ");
    Book* book = sys_.getBook(id);
    if (!book) { cout << "도서를 찾을 수 없습니다." << endl; return; }
    sys_.rental().returnBook(currentUser_, book);
}

void CLI::adminListBooks() { userBrowse(); }

void CLI::adminAddBook() {
    int id = promptInt("도서 ID: ");
    string title = promptStr("제목: ");
    string author = promptStr("저자: ");
    int qty = promptInt("초기 재고: ");
    if (sys_.addBook(id, title, author, qty)) cout << "추가되었습니다." << endl;
    else cout << "이미 존재하는 ID입니다." << endl;
}

void CLI::adminRemoveBook() {
    int id = promptInt("삭제할 도서 ID: ");
    if (sys_.removeBook(id)) cout << "삭제되었습니다." << endl;
    else cout << "해당 도서가 없습니다." << endl;
}

void CLI::adminSetStock() {
    int id = promptInt("도서 ID: ");
    int qty = promptInt("재고 수량: ");
    if (sys_.setBookStock(id, qty)) cout << "재고가 업데이트되었습니다." << endl;
    else cout << "해당 도서가 없습니다." << endl;
}

void CLI::adminListUsers() {
    clearScreen();
    auto users = sys_.listUsers();
    if (users.empty()) { cout << "사용자가 없습니다." << endl; return; }
    cout << "\n이름\tID\t등급" << endl;
    for (auto* u : users) {
        cout << u->getName() << "\t" << u->getId() << "\t" << u->getGrade() << endl;
    }
}

void CLI::adminChangeMembership() {
    string id = promptStr("변경할 사용자 ID: ");
    cout << "등급 선택: 1) Normal  2) Premium  3) Restricted" << endl;
    int sel = promptInt("선택: ");
    AbstractMembershipFactory* m = nullptr;
    switch (sel) {
    case 1: m = new NormalFactory(); break;
    case 2: m = new PremiumFactory(); break;
    case 3: m = new RestrictedFactory(); break;
    default: cout << "없는 메뉴" << endl; return;
    }
    if (sys_.setUserMembership(id, m)) cout << "변경되었습니다." << endl;
    else cout << "사용자를 찾을 수 없습니다." << endl;
}
