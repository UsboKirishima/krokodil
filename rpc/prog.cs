// C#
using System.Runtime.InteropServices;
using System;
namespace pshcmd
{
	public class CMD
	{
		[DllImport("msvcrt.dll")]
		public static extern int system(string cmd);

        public static void stupid_text() 
        {
            System.Console.WriteLine("WEATHER?????????");
        }

        public static void getWeather() 
        {
            system("curl https://wttr.in/");
        }

		public static void Main()
		{
            
			stupid_text();
            getWeather();
		}
	}
}