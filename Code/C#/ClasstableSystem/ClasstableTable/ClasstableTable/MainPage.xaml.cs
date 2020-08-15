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
using Windows.UI.Popups;
using Windows.Storage;

// “空白页”项模板在 http://go.microsoft.com/fwlink/?LinkId=234238 上有介绍

namespace ClasstableTable
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
        }

        private int signIn(string usrname, string pwd)
        {
            if (tboxUsername.Text == "Admin" && pboxPwd.Password.ToString() == "admin")
            {
                return 3;
            }
            ApplicationDataCompositeValue composite;
            ApplicationDataContainer localSettings = ApplicationData.Current.LocalSettings;
            if (localSettings.Values["UsrNum"] == null)
                return 0;
            int lastIndex = Convert.ToInt32(localSettings.Values["UsrNum"].ToString());
            for (int i = 0; i < lastIndex; i++)
            {
                try
                {
                    if (localSettings.Values["U"+i.ToString()] != null)
                    {
                        composite = localSettings.Values["U"+i.ToString()] as ApplicationDataCompositeValue;
                        if (usrname == composite["Usrname"] as string && pwd == composite["Pwd"] as string)
                        {
                            return Convert.ToInt32(composite["Authority"].ToString());
                        }
                    }
                }
                catch
                {
                    return 0;
                }
            }
            return 0;
        }

        private async void bttn_SignIn_Click(object sender, RoutedEventArgs e)
        {
            int c = 1;
            if (string.IsNullOrEmpty(tboxUsername.Text))
            {
                MessageDialog msg = new MessageDialog("The username cannot be empty", "Warning");
                UICommand CancelCommand = new UICommand();
                CancelCommand.Label = "Cancel";
                msg.Commands.Add(CancelCommand);
                IUICommand selectedCommand = await msg.ShowAsync();
                c = 0;
            }
            else if ((c = signIn(tboxUsername.Text, pboxPwd.Password.ToString())) == 0)
            {
                MessageDialog msg = new MessageDialog("Invalid username or wrong password", "Warning");
                UICommand CancelCommand = new UICommand();
                CancelCommand.Label = "Cancel";
                msg.Commands.Add(CancelCommand);
                IUICommand selectedCommand = await msg.ShowAsync();
            }
            if (c == 1)
            {
                Frame.Navigate(typeof(StudentPage), tboxUsername.Text);
            }
            else if (c == 2)
            {
                Frame.Navigate(typeof(TeacherPage), tboxUsername.Text);
            }
            else if (c == 3)
            {
                Frame.Navigate(typeof(Admin));
            }
        }

        private void bttn_SignUp_Click(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(AddUser));
        }

        private void Grid_KeyDown(object sender, KeyRoutedEventArgs e)
        {
            if (e.Key == Windows.System.VirtualKey.Enter)
            {
                bttn_SignIn_Click(null, null);
            }
        }
    }
}
//登陆、注册、退出
//权限1--学生
//权限2--教师