/*
 * Copyright (c) 2015, <copyright holder> <email>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *     * Neither the name of the <organization> nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY <copyright holder> <email> ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <copyright holder> <email> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "DisassemblyModel.h"
#include "Logger.h"


DisassemblyModel::DisassemblyModel(Memory& memory, QObject *parent)
    : memory(memory), QAbstractTableModel(parent)
{
}

int DisassemblyModel::rowCount(const QModelIndex & /*parent*/) const
{
   return this->memory.size();
}

int DisassemblyModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 2;
}

QVariant DisassemblyModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if(orientation == Qt::Horizontal) {

        if (role == Qt::DisplayRole)
    {
        switch(section) {
            case 0:
                return QString("Memory address");
            case 1:
                return QString("Value");
        }
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
                return QString("%1")
                   .arg(index.row());
            case 1:
                return QString("%1")
                   .arg(this->memory.read(index.row()));
        }
    }
    return QVariant();
}