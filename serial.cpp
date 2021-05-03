#include "serial.h"
#include "ui_serial.h"

Serial::Serial(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::Serial)
{
  ui->setupUi(this);
  //user
  system_init();
}

Serial::~Serial()
{
  delete ui;
}
/******************************
 *           FUNTIONS
 *****************************/
void Serial::system_init()
 {
   global_port.setParity(QSerialPort::NoParity);
   global_port.setDataBits(QSerialPort::Data8);
   global_port.setStopBits(QSerialPort::OneStop);
   connect(ui->btn_open,&QPushButton::clicked,this,&Serial::btn_open_port);
   connect(ui->btn_send,&QPushButton::clicked,this,&Serial::btn_send_data);
   connect(&global_port,&QSerialPort::readyRead,this,&receive_data);
   connect(ui->btn_close,&QPushButton::clicked,this,&Serial::btn_set_close);
  }
/******************************
 *           SLOTS
 * ****************************/
void Serial::btn_open_port(bool)
{
/***************PORT NAME****************/
//  qDebug()<<ui->cmb_port_name->currentIndex();
  switch (ui->cmb_port_name->currentIndex()) {
    case 0:
  global_port.setPortName("COM1");
      break;
    case 1:
  global_port.setPortName("COM2");
      break;
    case 2:
  global_port.setPortName("COM3");
      break;
    case 3:
  global_port.setPortName("COM4");
      break;
    case 4:
  global_port.setPortName("COM5");
      break;
    case 5:
  global_port.setPortName("COM6");
      break;
    case 6:
  global_port.setPortName("COM7");
      break;
    default:
         global_port.setPortName("COM8");
      break;
    }
/***************BOUD RATE********************/
                  switch (ui->cmb_baund_rate->currentIndex()) {
                    case 0:
                         global_port.setBaudRate(QSerialPort::Baud115200);
                      break;
                    case 1:
                         global_port.setBaudRate(QSerialPort::Baud57600);
                      break;
                    case 2:
                         global_port.setBaudRate(QSerialPort::Baud38400);
                      break;
                    case 3:
                         global_port.setBaudRate(QSerialPort::Baud19200);
                      break;
                    case 4:
                         global_port.setBaudRate(QSerialPort::Baud9600);
                      break;
                    case 5:
                         global_port.setBaudRate(QSerialPort::Baud4800);
                      break;
                    case 6:
                         global_port.setBaudRate(QSerialPort::Baud2400);
                      break;
                    default:
                         global_port.setBaudRate(QSerialPort::Baud1200);
                      break;
           }
  global_port.open(QIODevice::ReadWrite);
//  //TEST
//  global_port.write("1");
  ui->label_1->setText("connected");

    }
/********************send data***********************************/
void Serial::btn_send_data(bool)
{
  QString data = ui->lint_send_data->text();
  QByteArray array = data.toLatin1();
  global_port.write(array);
}

/********************receive data**********************************/
void Serial::receive_data()
{
  QByteArray array = global_port.readAll();
//  qDebug()<<array;
  if(ui->checkBox->checkState() == Qt::Checked)
    {
      ui->plainTextEdit->insertPlainText(QString(array.toHex(' ')).append(' '));
    }
  else{
      ui->plainTextEdit->insertPlainText(QString(array));
    }

}

/*******************CLOSE************************************/
void Serial::btn_set_close(bool)
{
  global_port.close();
  ui->label_1->setText("Disconnected");
}
