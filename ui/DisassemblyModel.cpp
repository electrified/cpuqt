#include "DisassemblyModel.h"
#include "Logger.h"
#include "utils.h"


DisassemblyModel::DisassemblyModel(QtBadgerMemory* memory, QObject *parent)
    : memory(memory), QAbstractTableModel(parent)
{
    this->disassembler = new Disassembler(memory);
}

int DisassemblyModel::rowCount(const QModelIndex & /*parent*/) const
{
   return this->memory->size();
}

int DisassemblyModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 4;
}

QVariant DisassemblyModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if (role == Qt::DisplayRole)
    {
        if(orientation == Qt::Horizontal) {

                switch(section) {
                case 0:
                    return QString("Status");
                case 1:
                    return QString("Memory address");
                case 2:
                    return QString("Value");
                case 3:
                    return QString("Disassembly");
                }
        } else if (orientation == Qt::Vertical) {
            return utils::int_to_hex(section);
        }
    }
    return QAbstractTableModel::headerData(section, orientation, role);
}

QVariant DisassemblyModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        switch(index.column()) {
            case 0:
                if (pc == index.row()) {
                    return QString(">");
                }
                break;
            case 1:
                return utils::int_to_hex(index.row());
            case 2:
                return utils::int_to_hex(this->memory->read(index.row()));
            case 3:
                std::string mnemonic = this->disassembler->getDisassembly(index.row());
                return QString::fromStdString(mnemonic);
        }
    }
    return QVariant();
}

void DisassemblyModel::memoryUpdated(const std::uint16_t address) {
//    QModelIndex start = );
//    QModelIndex end = );
    emit dataChanged(createIndex(address, 0), createIndex(address, 3));
}

void DisassemblyModel::programCounterUpdated(const std::uint16_t newPC) {
    emit dataChanged(createIndex(pc, 0), createIndex(pc, 0));
    pc = newPC;
    emit dataChanged(createIndex(pc, 0), createIndex(pc, 0));
}

void DisassemblyModel::forceDisassembly() {
    this->disassembler->disassemble();
}