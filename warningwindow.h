#ifndef WARNINGWINDOW_H
#define WARNINGWINDOW_H

#include <QDialog>

namespace Ui {
class WarningWindow;
}

class WarningWindow : public QDialog
{
    Q_OBJECT
signals:
    /* emit this sinal if yes or no buttons were clicked
     * first bool is for checker(checked/unchrcked) and second for Yes/No */
    void YesNoClicked(const bool&, const bool&);
public:
    explicit WarningWindow(QWidget *parent = nullptr);
    ~WarningWindow();
private slots:
   void on_Button_Yes_clicked();
   void on_Button_No_clicked();

private:
    Ui::WarningWindow *ui_w;
};

#endif // WARNINGWINDOW_H
