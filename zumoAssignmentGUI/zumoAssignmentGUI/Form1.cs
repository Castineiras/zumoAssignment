using System;
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
        }

        private void ForwardButton_Click(object sender, EventArgs e)
        {
            zumoPort.Write("forward");
        }

        private void BackButton_Click(object sender, EventArgs e)
        {
            zumoPort.Write("back");
        }

        private void TurnLeftButton_Click(object sender, EventArgs e)
        {
            zumoPort.Write("left");
        }

        private void TurnRightButton_Click(object sender, EventArgs e)
        {
            zumoPort.Write("right");
        }

        private void StopButton_Click(object sender, EventArgs e)
        {
            zumoPort.Write("stop");
        }

        private void SwitchControlButton_Click(object sender, EventArgs e)
        {
            zumoPort.Write("x");
        }
    }
}
