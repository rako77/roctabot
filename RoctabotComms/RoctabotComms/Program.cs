using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows.Input;
using System.IO.Ports;

namespace RoctabotComms
{
    class Program
    {
        static void Main(string[] args)
        {
            const Byte LEGS_NUM = 4;
            const Byte SERVO_NUM = 3;
            Keyboard.IsKeyDown(Key.Q);
            string comPort = GetComPort();
            SerialPort port = new SerialPort(comPort, 9600, Parity.None, 8, StopBits.One);
            Byte[,] legs = new Byte[LEGS_NUM, SERVO_NUM]; 
            for (int i = 0; i < legs.GetLength(0); ++i)
            {
                for (int j = 0; j < legs.GetLength(1); ++j)
                {
                    legs[i, j] = 90;
                }
            }

            while (true)
            {
                Thread.Sleep(100);

                if (Keyboard.IsKeyDown(Key.Q))
                {
                    port.Write("Q");
                }
                else if (Keyboard.IsKeyDown(Key.A))
                {
                    port.Write("A");
                }

                if (Keyboard.IsKeyDown(Key.W))
                {
                    port.Write("W");
                }
                else if (Keyboard.IsKeyDown(Key.S))
                {
                    port.Write("S");
                }

                if (Keyboard.IsKeyDown(Key.Z))
                {
                    port.Write("Z");
                }
                else if (Keyboard.IsKeyDown(Key.X))
                {
                    port.Write("X");
                }

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
    }
}
