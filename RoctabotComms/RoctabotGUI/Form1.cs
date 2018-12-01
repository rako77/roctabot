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

namespace RoctabotGUI
{
    public partial class Form1 : Form
    {
        public class Leg
        {
            public int legNumber { get; set; }
            public int ForearmAngle { get; set; }
            public int BicepAngle { get; set; }
            public int ShoulderAngle { get; set; }

            public static bool Equals(Leg obj1, Leg obj2)
            {
                return obj1.legNumber == obj2.legNumber&&
                obj1.ForearmAngle == obj2.ForearmAngle&&
                obj1.BicepAngle == obj2.BicepAngle&&
                obj1.ShoulderAngle == obj2.ShoulderAngle;
            }

            
        }

        Leg[] legs = new Leg[4];
        Leg[] oldLegs = new Leg[4];
        SerialPort port;
        public Form1()
        {
            InitializeComponent();
            for (int i = 0; i < legs.Length; ++i)
            {
                legs[i] = new Leg();
                legs[i].legNumber = i;
                legs[i].ForearmAngle = 90;
                legs[i].BicepAngle = 90;
                legs[i].ShoulderAngle = 90;
            }
            legCopy();
            dataGridView1.DataSource = legs;

            string comPort = GetComPort();
            port = new SerialPort(comPort, 9600, Parity.None, 8, StopBits.One);
            port.Open();
        }

        private void legCopy()
        {
            for (int i = 0; i < legs.Length; ++i)
            {
                oldLegs[i] = new Leg();
                oldLegs[i].legNumber = legs[i].legNumber;
                oldLegs[i].ForearmAngle = legs[i].ForearmAngle;
                oldLegs[i].BicepAngle = legs[i].BicepAngle;
                oldLegs[i].ShoulderAngle = legs[i].ShoulderAngle;
            }
        }

        private static string GetComPort()
        {
            var names = SerialPort.GetPortNames();
            if (names.Length == 1)
            {
                return names[0];
            }
            throw new NotSupportedException();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < legs.Length; ++i)
            {
                if (!Leg.Equals(oldLegs[i],legs[i]))
                {
                    port.Write(new Byte[] { (Byte)legs[i].legNumber, (Byte)legs[i].ForearmAngle, (Byte)legs[i].BicepAngle, (Byte)legs[i].ShoulderAngle, (Byte)120 }, 0, 5);
                }
            }
            legCopy();

        }
    }
}
