#include "cpuqt2.h"


#include <QtWidgets/QLabel>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QAction>

cpuqt2::cpuqt2()
{
    QLabel* label = new QLabel( this );
    label->setText( "Hello World!" );
    setCentralWidget( label );
    QAction* action = new QAction(this);
    action->setText( "Quit" );
    connect(action, SIGNAL(triggered()), SLOT(close()) );
    menuBar()->addMenu( "File" )->addAction( action );
}

cpuqt2::~cpuqt2()
{}

#include "cpuqt2.moc"
