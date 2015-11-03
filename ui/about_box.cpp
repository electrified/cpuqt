#include "about_box.h"
#include "ui_about_box.h"

Dialog::Dialog(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog) { ui->setupUi(this); }

Dialog::~Dialog() { delete ui; }
