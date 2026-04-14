#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <cctype>

#define NOMINMAX
#include <Windows.h>

enum enPassStrenght
{
    weak,
    fair,
    good,
    strong,
    veryStrong
};

struct stPasswordReport
{
    bool hasMinLenght = false;
    bool hasBonusLength = false;
    bool hasUpper = false;
    bool hasLower = false;
    bool hasDigit = false;
    bool hasSpecial = false;
    bool hasSpace = false;
    int score = 0;

    enPassStrenght passStrength{};
};

void printHeader()
{
    std::cout << std::right << std::setw(5) << " " << "========================================" << std::endl;
    std::cout << std::right << std::setw(12) << " " << "Password Strength Checker" << std::endl;
    std::cout << std::right << std::setw(5) << " " << "========================================" << std::endl;
}

std::string readPassword()
{
    std::string pass = "";
    
    std::cout << std::right << std::setw(5) << " " << "Enter Password : ";
    std::getline(std::cin, pass);

    return pass;
}

void pressKey()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << std::right << std::setw(5) << " ";
    system("pause");
}

void clear()
{
    system("cls");
}

enum enPassParams
{
    upper,
    lower,
    digit,
    special,
    space
};

struct stPassParams
{
    char upper;
    std::string lower = "";
    std::string digit = "";
    std::string special = "";
};

void checkPassParams(const std::string& pass,stPassParams& passChars, stPasswordReport& report)
{
    for (const char& c : pass)
    {
        if (isupper((unsigned char)c))
        {
            report.hasUpper = true;
            passChars.upper = c;
        }
        else if (islower((unsigned char)c))
        {
            report.hasLower = true;
            passChars.lower += c;
        }
        else if (isdigit((unsigned char)c))
        {
            report.hasDigit = true;
            passChars.digit += c;
        }
        else if (ispunct((unsigned char)c))
        {
            report.hasSpecial = true;
            passChars.special += c;
        }
        else if (isspace((unsigned char)c))
            report.hasSpace = true;
    }
}

void decidePassStrength(stPasswordReport& pass)
{
    if (pass.score <= 2)
        pass.passStrength = enPassStrenght::weak;
    else if(pass.score < 4)
        pass.passStrength = enPassStrenght::fair;
    else if(pass.score < 5)
        pass.passStrength = enPassStrenght::good;
    else if(pass.score < 6)
        pass.passStrength = enPassStrenght::strong;
    else
        pass.passStrength = enPassStrenght::veryStrong;
}

std::string printPassStrength(enPassStrenght pass)
{
    switch (pass)
    {
    case enPassStrenght::fair: return "Fair";
    case enPassStrenght::good: return "Good";
    case enPassStrenght::strong: return "Strong";
    case enPassStrenght::veryStrong: return "Very Strong";
    case enPassStrenght::weak: return "Weak";
    default: return "";
    }
}

int calculatePassScore(const stPasswordReport& passR)
{
    return passR.hasBonusLength + passR.hasDigit + passR.hasLower + passR.hasMinLenght + !passR.hasSpace + passR.hasSpecial + passR.hasUpper;
}

void checkingPass(const std::string& pass, stPassParams& passChars, stPasswordReport& passReport)
{
    passReport.hasMinLenght = pass.length() >= 8;
    passReport.hasBonusLength = pass.length() >= 12;
    
    checkPassParams(pass, passChars, passReport);

    passReport.score = calculatePassScore(passReport);
    decidePassStrength(passReport);
}

void printResults(const std::string& pass, const stPassParams& passChars, const stPasswordReport& passReport)
{
    std::cout << std::right << std::setw(5) << " " << "-------------------------------------------" << std::endl;
    
    std::cout << std::right << std::setw(5) << " " << "[" << (passReport.hasMinLenght ? "YES" : "NO") << "] Length >= 8 "
        << "(" << pass.length() << " chars)." << std::endl;
    std::cout << std::right << std::setw(5) << " " << "[" << (passReport.hasBonusLength ? "YES" : "NO") << "] Length >= 12 "
        << "(" << pass.length() << " chars)." << std::endl;
    std::cout << std::right << std::setw(5) << " " << "[" << (passReport.hasUpper ? "YES" : "NO") << "] Has Uppercase "
        << "(" << passChars.upper << ")." << std::endl;
    std::cout << std::right << std::setw(5) << " " << "[" << (passReport.hasLower ? "YES" : "NO") <<"] Has Lowercase "
        << "(" << passChars.lower << ")." << std::endl;
    std::cout << std::right << std::setw(5) << " " << "[" << (passReport.hasDigit ? "YES" : "NO") << "] Has Digit "
        << "(" << passChars.digit << ")." << std::endl;
    std::cout << std::right << std::setw(5) << " " << "[" << (passReport.hasSpecial ? "YES" : "NO") << "] Has Special Char "
        << "(" << passChars.special << ")." << std::endl;
    std::cout << std::right << std::setw(5) << " " << "[" << (!passReport.hasSpace ? "YES" : "NO") << "] No Space " << std::endl;

    std::cout << std::right << std::setw(5) << " " << "-------------------------------------------" << std::endl;
    std::cout << std::right << std::setw(14) << " " << "Score : " << passReport.score << " / 7" << std::endl;
    std::cout << std::right << std::setw(14) << " " << "Strength : " << printPassStrength(passReport.passStrength) << std::endl;
    std::cout << std::right << std::setw(5) << " " << "-------------------------------------------" << std::endl;

}

void startCheckingPass()
{
    char check = 'y';

    while (tolower(check) == 'y')
    {
        stPasswordReport passRep{};
        stPassParams passChars{};
        clear();
        printHeader();

        std::string pass = readPassword();
        checkingPass(pass,passChars,passRep);
        
        std::cout << std::endl << std::right << std::setw(5) << " " << "Checking Pass (" << pass << ") ";

        for (short j = 0;j < 5;j++)
        {
            std::cout << ".";
            Sleep(1000);
        }
        std::cout << std::endl;
        
        printResults(pass,passChars,passRep);

        std::cout << std::right << std::setw(6) << " " << "Check another ? [y/Y] : ";
        std::cin >> std::setw(1) >> check;
        
        pressKey();
    }
}

int main()
{
    startCheckingPass();

    return 0;
}