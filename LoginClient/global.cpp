#include "global.h"
QString gate_url_prefix = "";
std::function<void(QWidget*)> repolish = [](QWidget* w){
    w->style()->unpolish(w);
    w->style()->polish(w);
};
QString XorString(QString input){
    QString result = input;
    int length = input.length();
    length %= 255;
    length++; //防止length为0
    for(int i = 0;i < input.length();i++){
        result[i] = QChar(input[i].unicode() ^ length);
    }
    return result;
}
