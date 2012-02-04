/***************************************************************************
 *  The FreeMedForms project is a set of free, open source medical         *
 *  applications.                                                          *
 *  (C) 2008-2012 by Eric MAEKER, MD (France) <eric.maeker@gmail.com>      *
 *  All rights reserved.                                                   *
 *                                                                         *
 *  The FreeAccount plugins are free, open source FreeMedForms' plugins.   *
 *  (C) 2010-2011 by Pierre-Marie Desombre, MD <pm.desombre@medsyn.fr>     *
 *  and Eric Maeker, MD <eric.maeker@gmail.com>                            *
 *  All rights reserved.                                                   *
 *                                                                         *
 *  This program is free software: you can redistribute it and/or modify   *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation, either version 3 of the License, or      *
 *  (at your option) any later version.                                    *
 *                                                                         *
 *  This program is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with this program (COPYING.FREEMEDFORMS file).                   *
 *  If not, see <http://www.gnu.org/licenses/>.                            *
 ***************************************************************************/
/***************************************************************************
 *  Main Developpers : Pierre-Marie DESOMBRE <pm.desombre@medsyn.fr>,      *
 *                     Eric MAEKER, <eric.maeker@gmail.com>                *
 *  Contributors :                                                         *
 *      NAME <MAIL@ADRESS>                                                 *
 ***************************************************************************/
#include "controlreceiptsIO.h"
#include "ui_controlreceipts.h"

#include <QMessageBox>
#include <QDebug>

enum { WarnDebugMessage = false };

using namespace AccountDB;
using namespace Constants;

ControlReceipts::ControlReceipts(QWidget * parent):QWidget(parent),ui(new Ui::ControlReceiptsWidget)
{
    ui->setupUi(this);
    int h = parent->height();
    int w = parent->width();
    resize(w,h);
    setAutoFillBackground(true);
    ui->resultLabel->setText("");
    ui->resultLabel->setWordWrap(true);
    m_accountModel = new AccountModel(this);
    m_userUuid = m_accountModel->getUserUuid();
    m_typeOfMoney = trUtf8("Euros");
    ui->beginDateEdit->setDate(QDate::currentDate());
    ui->endDateEdit->setDate(QDate::currentDate());
    ui->searchButton->setShortcut(QKeySequence::InsertParagraphSeparator);
    ui->deleteButton->setShortcut(QKeySequence::Delete);
    ui->quitButton->setShortcut(QKeySequence("Ctrl+q"));
    search();
    connect(ui->searchButton,SIGNAL(pressed()),this,SLOT(search()));
    connect(ui->deleteButton,SIGNAL(pressed()),this,SLOT(deleteLine()));
    connect(ui->duesButton,SIGNAL(pressed()),this,SLOT(printDues()));
    connect(ui->printButton,SIGNAL(pressed()),this,SLOT(print()));
    connect(ui->quitButton,SIGNAL(pressed()),this,SLOT(closeAction()));
}

ControlReceipts::~ControlReceipts(){}

void ControlReceipts::resizeControlReceipts(QWidget * parent){
    int h = parent->height();
    int w = parent->width();
    resize(w,h);    
}

void ControlReceipts::search(){
    refresh();
    QString dateBeginStr = ui->beginDateEdit->date().toString("yyyy-MM-dd");
    QString dateEndStr = ui->endDateEdit->date().toString("yyyy-MM-dd");
    QString filterEdit = "%"+ui->filterEdit->text()+"%";
    QString fieldKey = ui->fieldComboBox->currentText();
    QString field = m_mapCombo.value(fieldKey);
    QString filter = QString("%1 = '%2'").arg("USER_UID",m_userUuid);
    filter += " AND ";
    filter += QString("%1 LIKE '%2'").arg(field,filterEdit);
    filter += " AND ";
    filter += QString("%1 NOT LIKE '%2' AND ").arg(field,"0.0");
    filter += QString("DATE BETWEEN '%1' AND '%2'").arg(dateBeginStr,dateEndStr);
    m_accountModel->setFilter(filter);
    if (WarnDebugMessage)
    	      qDebug() << __FILE__ << QString::number(__LINE__) << " filter =" << m_accountModel->filter() ;
    if (WarnDebugMessage)
    	      qDebug() << __FILE__ << QString::number(__LINE__) << " rowCount =" << QString::number(m_accountModel->rowCount()) ;
    ui->tableView->setModel(m_accountModel);
    ui->tableView->setShowGrid(false);
    ui->tableView->setColumnHidden(ACCOUNT_ID,true);
    ui->tableView->setColumnHidden(ACCOUNT_UID,true);
    ui->tableView->setColumnHidden(ACCOUNT_USER_UID,true);
    ui->tableView->setColumnHidden(ACCOUNT_PATIENT_UID,true);
    ui->tableView->setColumnHidden(ACCOUNT_SITE_ID,true);
    ui->tableView->setColumnHidden(ACCOUNT_INSURANCE_ID,true);
    ui->tableView->setColumnHidden(ACCOUNT_MEDICALPROCEDURE_XML,true);
    ui->tableView->setColumnHidden(ACCOUNT_TRACE,true);
    ui->tableView->horizontalHeader()->setResizeMode(QHeaderView::Interactive);
    ui->tableView->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->setCascadingSectionResizes (true);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    //ui->tableView->resizeColumnsToContents();
    coloringDoubles();
    QString textResult = textOfSums(m_accountModel);
    ui->resultLabel->setText(textResult);
    //refreshFilter(filter);
}

void ControlReceipts::deleteLine(){
  QModelIndex index = ui->tableView->QAbstractItemView::currentIndex();
  if(!index.isValid()){
      QMessageBox::warning(0,trUtf8("Error"),trUtf8("Please select a line to delete."),QMessageBox::Ok);
      return;
      }
  int rowToDelete = index.row();
  if(m_accountModel->getDoublesRows.contains(rowToDelete)){
          m_accountModel->getDoublesRows.removeAll(rowToDelete);
          if (m_accountModel->getDoublesRows.size()<1)
          {
          	m_accountModel->getDoublesRows.clear();
                }
          }
  if(m_accountModel->removeRows(rowToDelete,1,QModelIndex())){
          QMessageBox::information(0,trUtf8("Information"),trUtf8("Line is deleted."),QMessageBox::Ok);
                   
      }
  QString textResult = textOfSums(m_accountModel);
  ui->resultLabel->setText(textResult);
  //const QString filter = m_accountModel->filter();
  coloringDoubles();
          search();
  /*if (WarnDebugMessage)
    	      qDebug() << __FILE__ << QString::number(__LINE__) << " filter =" << filter ;
  refreshFilter(filter);*/
}

QString ControlReceipts::textOfSums(AccountModel * model){
    QString labelText;
    QString labelTextStr;
    double cash = 0.00;
    double chq = 0.00;
    double visa = 0.00;
    double banking = 0.00;
    double other = 0.00;
    double dues = 0.00;
    double totalReceived = 0.00;
    double totals = 0.00;
   int modelRowCount = model->rowCount(QModelIndex());
   if (WarnDebugMessage)
    	      qDebug() << __FILE__ << QString::number(__LINE__) << " modelRowCount = " << QString::number(modelRowCount);
   for(int i = 0; i < modelRowCount ; i ++){
       QSqlRecord rowRecord = model->record(i);//ligne d'enregistrement
       cash  += rowRecord.value(ACCOUNT_CASHAMOUNT).toDouble();
       chq  += rowRecord.value(ACCOUNT_CHEQUEAMOUNT).toDouble();
       visa += rowRecord.value(ACCOUNT_VISAAMOUNT).toDouble();
       banking += rowRecord.value(ACCOUNT_INSURANCEAMOUNT).toDouble();
       other += rowRecord.value(ACCOUNT_OTHERAMOUNT).toDouble();
       dues  += rowRecord.value(ACCOUNT_DUEAMOUNT).toDouble();
       }
    totals = cash + chq + visa + banking + other + dues;
    totalReceived = cash + chq + banking + other + visa;
    QString cashStr = trUtf8("Cash");
    QString chqStr = trUtf8("Chq");
    QString visaStr = trUtf8("CB");
    QString bankingStr = trUtf8("Banking");
    QString otherStr = trUtf8("Others");
    QString duesStr = trUtf8("Dues");
    QString totStr = "<font size = 3 color = ""blue"">Totaux = </font><font size = 3 color = ""red"">"+QString::number(totals)+" "+m_typeOfMoney+" </font>  ";
    QString totReceived = "<font size = 3 color = ""blue"">Totaux reçus = </font><font size = 3 color = ""red"">"+QString::number(totalReceived)+" "+m_typeOfMoney+" </font><br/>";
    QString sumsStr = "<font size = 3 color = ""blue"">"+cashStr+" = </font><font size = 3 color = ""red"">"+QString::number(cash)+" "+m_typeOfMoney+"  </font>"+
                "<font size = 3 color = ""blue"">"+chqStr+" = </font><font size = 3 color = ""red"">"+QString::number(chq)+" "+m_typeOfMoney+"  </font>"+
                "<font size = 3 color = ""blue"">"+visaStr+" = </font><font size = 3 color = ""red"">"+QString::number(visa)+" "+m_typeOfMoney+"  </font>"+
                "<font size = 3 color = ""blue"">"+bankingStr+" = </font><font size = 3 color = ""red"">"+QString::number(banking)+" "+m_typeOfMoney+"  </font><br/>"+
                "<font size = 3 color = ""blue"">"+otherStr+" = </font><font size = 3 color = ""red"">"+QString::number(other)+" "+m_typeOfMoney+"  </font>"+
                "<font size = 3 color = ""blue"">"+duesStr+" = </font><font size = 3 color = ""red"">"+QString::number(dues)+" "+m_typeOfMoney+"</font>";
    labelTextStr = totStr+totReceived+sumsStr;
    labelText = "<html><body>"+labelTextStr+"</body></html>";
    return labelText;
    }

void ControlReceipts::printDues(){
    QMessageBox::information(0,trUtf8("Information"),trUtf8("Not yet"),QMessageBox::Ok);
}

void ControlReceipts::print(){
    QMessageBox::information(0,trUtf8("Information"),trUtf8("Not yet"),QMessageBox::Ok);	
}

void ControlReceipts::coloringDoubles(){
    int rowCount = m_accountModel->rowCount();
    int columnCount = m_accountModel->columnCount();
    if (WarnDebugMessage)
        qDebug() << __FILE__ << QString::number(__LINE__) << QString::number(rowCount) << " " << QString::number(columnCount);
    QList<int> listRows;
    for (int i = 0; i < rowCount; i += 1)
    {
    	QList<QVariant> dataRow ;

    	for (int c = 1; c < columnCount; c += 1)
    	{
    	        QModelIndex index = m_accountModel->index(i,c,QModelIndex());
    		dataRow << m_accountModel->data(index,Qt::DisplayRole);
    	}
        if (WarnDebugMessage)
            qDebug() << __FILE__ << QString::number(__LINE__) << " dataRow.size =" << QString::number(dataRow.size());
    	for (int j = i; j < rowCount ; j += 1)
    	{
    	           if(j!=i){
    		    	QList<QVariant> dataAfterRow ;
    	                for (int c = 1; c < columnCount; c += 1)
    	                {
    	                        QModelIndex indexAfter = m_accountModel->index(j,c,QModelIndex());
    		                dataAfterRow += m_accountModel->data(indexAfter,Qt::DisplayRole);
    	                }
    	                
                        if (WarnDebugMessage)
                            qDebug() << __FILE__ << QString::number(__LINE__) << " dataAfterRow.size =" << QString::number(dataAfterRow.size());
    	                if (dataAfterRow == dataRow)
    	                {
                            if (WarnDebugMessage) {
                                qDebug() << __FILE__ << QString::number(__LINE__) << " dataAfterRow= "<< dataAfterRow;
    	                        qDebug() << __FILE__ << QString::number(__LINE__) << QString::number(i) << QString::number(j);
                            }
                            listRows << i << j;
    	                }
    	                else{}
    	           }
    	}

    }
    m_accountModel->getDoublesRows = listRows;
    if (WarnDebugMessage)
        qDebug() << __FILE__ << QString::number(__LINE__) << " listRows = " << QString::number(listRows.size());

    m_accountModel->submit();
}

void ControlReceipts::refresh(){
    delete m_accountModel;
    m_accountModel = new AccountModel(this);
    if (!m_accountModel->setHeaderData(ACCOUNT_PATIENT_NAME,Qt::Horizontal ,trUtf8("Patient") , Qt::EditRole)) {
        if (WarnDebugMessage)
            qWarning() << __FILE__ << QString::number(__LINE__) << "Unable to set header data" ;
    }
    m_accountModel->setHeaderData(ACCOUNT_DATE,Qt::Horizontal ,trUtf8("Date") , Qt::EditRole);
    m_accountModel->setHeaderData(ACCOUNT_MEDICALPROCEDURE_TEXT,Qt::Horizontal ,trUtf8("Acts") , Qt::EditRole);
    m_accountModel->setHeaderData(ACCOUNT_COMMENT,Qt::Horizontal ,trUtf8("Comment") , Qt::EditRole);
    m_accountModel->setHeaderData(ACCOUNT_CASHAMOUNT,Qt::Horizontal ,trUtf8("Cash") , Qt::EditRole);
    m_accountModel->setHeaderData(ACCOUNT_CHEQUEAMOUNT,Qt::Horizontal ,trUtf8("Checks") , Qt::EditRole);
    m_accountModel->setHeaderData(ACCOUNT_VISAAMOUNT,Qt::Horizontal ,trUtf8("Credit card") , Qt::EditRole);
    m_accountModel->setHeaderData(ACCOUNT_INSURANCEAMOUNT,Qt::Horizontal ,trUtf8("Insurance") , Qt::EditRole);
    m_accountModel->setHeaderData(ACCOUNT_OTHERAMOUNT,Qt::Horizontal ,trUtf8("Other") , Qt::EditRole);
    m_accountModel->setHeaderData(ACCOUNT_DUEAMOUNT,Qt::Horizontal ,trUtf8("Due") , Qt::EditRole);
    m_accountModel->setHeaderData(ACCOUNT_DUEBY,Qt::Horizontal ,trUtf8("by") , Qt::EditRole);
    m_accountModel->setHeaderData(ACCOUNT_ISVALID,Qt::Horizontal ,trUtf8("Valid") , Qt::EditRole);
    m_mapCombo.clear();
    m_mapCombo.insert(trUtf8("Patient"),"PATIENT_NAME");
    m_mapCombo.insert(trUtf8("Cash"),"CASH");
    m_mapCombo.insert(trUtf8("Check"),"CHEQUE");
    m_mapCombo.insert(trUtf8("Credit card"),"VISA");
    m_mapCombo.insert(trUtf8("Banking"),"BANKING");
    m_mapCombo.insert(trUtf8("Other"),"OTHER");
    m_mapCombo.insert(trUtf8("Due"),"DUE");
    m_mapCombo.insert(trUtf8("Due by"),"DUE_BY");
    QStringList listForCombo;
    listForCombo = m_mapCombo.keys();
    listForCombo.prepend(trUtf8("Patient"));
    listForCombo.removeDuplicates();
    ui->fieldComboBox->clear();
    ui->fieldComboBox->addItems(listForCombo);
    ui->fieldComboBox->setEditText(trUtf8("Patient"));
}

void ControlReceipts::refreshFilter(const QString & filter){
    delete m_accountModel;
    m_accountModel = new AccountModel(this);
    m_accountModel->setFilter(filter);
    if (!m_accountModel->setHeaderData(ACCOUNT_PATIENT_NAME,Qt::Horizontal ,trUtf8("Patient") , Qt::EditRole))
    {
        if (WarnDebugMessage)
            qWarning() << __FILE__ << QString::number(__LINE__) << "Unable to set header data" ;
        }
    m_accountModel->setHeaderData(ACCOUNT_DATE,Qt::Horizontal ,trUtf8("Date") , Qt::EditRole);
    m_accountModel->setHeaderData(ACCOUNT_MEDICALPROCEDURE_TEXT,Qt::Horizontal ,trUtf8("Acts") , Qt::EditRole);
    m_accountModel->setHeaderData(ACCOUNT_COMMENT,Qt::Horizontal ,trUtf8("Comment") , Qt::EditRole);
    m_accountModel->setHeaderData(ACCOUNT_CASHAMOUNT,Qt::Horizontal ,trUtf8("Cash") , Qt::EditRole);
    m_accountModel->setHeaderData(ACCOUNT_CHEQUEAMOUNT,Qt::Horizontal ,trUtf8("Checks") , Qt::EditRole);
    m_accountModel->setHeaderData(ACCOUNT_VISAAMOUNT,Qt::Horizontal ,trUtf8("Credit card") , Qt::EditRole);
    m_accountModel->setHeaderData(ACCOUNT_INSURANCEAMOUNT,Qt::Horizontal ,trUtf8("Insurance") , Qt::EditRole);
    m_accountModel->setHeaderData(ACCOUNT_OTHERAMOUNT,Qt::Horizontal ,trUtf8("Other") , Qt::EditRole);
    m_accountModel->setHeaderData(ACCOUNT_DUEAMOUNT,Qt::Horizontal ,trUtf8("Due") , Qt::EditRole);
    m_accountModel->setHeaderData(ACCOUNT_DUEBY,Qt::Horizontal ,trUtf8("by") , Qt::EditRole);
    m_accountModel->setHeaderData(ACCOUNT_ISVALID,Qt::Horizontal ,trUtf8("Valid") , Qt::EditRole);
    ui->tableView->setModel(m_accountModel);
    ui->tableView->setColumnHidden(ACCOUNT_ID,true);
    ui->tableView->setColumnHidden(ACCOUNT_UID,true);
    ui->tableView->setColumnHidden(ACCOUNT_USER_UID,true);
    ui->tableView->setColumnHidden(ACCOUNT_PATIENT_UID,true);
    ui->tableView->setColumnHidden(ACCOUNT_SITE_ID,true);
    ui->tableView->setColumnHidden(ACCOUNT_INSURANCE_ID,true);
    ui->tableView->setColumnHidden(ACCOUNT_MEDICALPROCEDURE_XML,true);
    ui->tableView->setColumnHidden(ACCOUNT_TRACE,true);
    ui->tableView->horizontalHeader()->setResizeMode(QHeaderView::Interactive);
    ui->tableView->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
}

void ControlReceipts::closeAction(){
    emit isClosing();
    emit close();
}

void ControlReceipts::changeEvent(QEvent *e) {
    QWidget::changeEvent(e);
    if (e->type()==QEvent::LanguageChange) {
        ui->retranslateUi(this);
        if (WarnDebugMessage)
            qDebug() << __FILE__ << QString::number(__LINE__) << " langage changed " ;
        search();
        }
}
