#ifndef DISASSEMBLYMODEL_H
#define DISASSEMBLYMODEL_H
#include <QAbstractTableModel>
#include "Z80/Memory.h"
#include "Z80/processor.h"
#include "Z80/disassembler.h"
#include "ui/qtbadgermemory.h"

class DisassemblyModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    DisassemblyModel(QtBadgerMemory* memory, QObject *parent);
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    void forceDisassembly();
private:
    Memory* memory;
    Disassembler* disassembler;
    std::uint16_t pc = 0;
public slots:
    void memoryUpdated(const std::uint16_t address);
    void programCounterUpdated(const std::uint16_t address);
};

#endif // DISASSEMBLYMODEL_H
