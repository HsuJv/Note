using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

// “空白页”项模板在 http://go.microsoft.com/fwlink/?LinkId=234238 上有介绍

namespace ClasstableTable
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class StudentPage : Page
    {
        string usrname;

        public StudentPage()
        {
            this.InitializeComponent();
        }

        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            usrname = e.Parameter as string;
            textBlock.Text = "Welcome, " + usrname + "!";
        }

        private void bttnBack_Click(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(MainPage));
        }

        private void bttnAddClass_Click(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(AddClass), usrname);
        }


        private void bttnViewWeek_Click(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(WeekClass), usrname);
        }

        private void bttnViewMonth_Click(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(TotalClass), usrname);
        }

        private void bttnHomeworkNote_Click(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(Note), usrname);
        }
    }
}
//添加课程、今日课程、本周课程、全部课程、作业备忘录