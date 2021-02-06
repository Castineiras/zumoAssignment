﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;

namespace zumoAssignmentGUI
{
    public partial class Form1 : Form
    {
        SerialPort zumoPort = new SerialPort("COM5", 9600, Parity.None, 8, StopBits.One);

        public Form1()
        {
            InitializeComponent();
            zumoPort.Open();
            zumoPort.DataReceived += new SerialDataReceivedEventHandler(SerialPortDataReceived);
            zumoPort.DtrEnable = true;
            zumoPort.NewLine = "\n";
        }

        private void ForwardButton_Click(object sender, EventArgs e)
        {
            zumoPort.Write("f");
        }

        private void BackButton_Click(object sender, EventArgs e)
        {
            zumoPort.Write("b");
        }

        private void TurnLeftButton_Click(object sender, EventArgs e)
        {
            zumoPort.Write("l");
        }

        private void TurnRightButton_Click(object sender, EventArgs e)
        {
            zumoPort.Write("r");
        }

        private void StopButton_Click(object sender, EventArgs e)
        {
            zumoPort.Write("s");
        }

        private void SwitchControlButton_Click(object sender, EventArgs e)
        {
            zumoPort.Write("x");
        }
        private void RoomLeftButton_Click(object sender, EventArgs e)
        {
            zumoPort.Write("q");
        }

        private void RoomRightButton_Click(object sender, EventArgs e)
        {
            zumoPort.Write("e");
        }
        private void EndOfJunctionButton_Click(object sender, EventArgs e)
        {
            zumoPort.Write("b");
        }

        private void SerialPortDataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            Invoke(new Action(() =>
            {
                SerialTextBox.Text += zumoPort.ReadLine() + "\n";
                zumoPort.DiscardInBuffer();
            }));
        }
    }
}
