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
using Windows.Storage;
using Windows.UI.Popups;

// “空白页”项模板在 http://go.microsoft.com/fwlink/?LinkId=234238 上有介绍

namespace ClasstableTable
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class AddUser : Page
    {

        public AddUser()
        {
            this.InitializeComponent();
        }

        private void bttnBack_Click(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(MainPage));
        }

        private async void bttnSubmit_Click(object sender, RoutedEventArgs e)
        {
            if (string.IsNullOrEmpty(txtBoxUsername.Text))
            {
                MessageDialog msg = new MessageDialog("The username cannot be empty", "Warning");
                UICommand CancelCommand = new UICommand();
                CancelCommand.Label = "Cancel";
                msg.Commands.Add(CancelCommand);
                IUICommand selectedCommand = await msg.ShowAsync();
            }
            else if (string.IsNullOrEmpty(passwordBox.Password.ToString()))
            {
                MessageDialog msg = new MessageDialog("The password cannot be empty", "Warning");
                UICommand CancelCommand = new UICommand();
                CancelCommand.Label = "Cancel";
                msg.Commands.Add(CancelCommand);
                IUICommand selectedCommand = await msg.ShowAsync();
            }
            else if (passwordBox.Password.ToString() != passwordBoxComfirm.Password.ToString())
            {
                MessageDialog msg = new MessageDialog("You are ought to type in the same password twice", "Warning");
                UICommand CancelCommand = new UICommand();
                CancelCommand.Label = "Cancel";
                msg.Commands.Add(CancelCommand);
                IUICommand selectedCommand = await msg.ShowAsync();
            }
            else
            {
                ApplicationDataCompositeValue composite = new ApplicationDataCompositeValue();
                composite["Usrname"] = txtBoxUsername.Text;
                composite["Pwd"] = passwordBox.Password.ToString();
                composite["Authority"] = 1;
                ApplicationDataContainer localSettings = ApplicationData.Current.LocalSettings;
                if (localSettings.Values["UsrNum"] == null)
                    localSettings.Values["UsrNum"] = 0;
                localSettings.Values["U" + localSettings.Values["UsrNum"].ToString()] = composite;
                localSettings.Values["UsrNum"] = Convert.ToInt32(localSettings.Values["UsrNum"].ToString()) + 1;
                Frame.Navigate(typeof(MainPage));
            }
        }

        private void bttnReset_Click(object sender, RoutedEventArgs e)
        {
            txtBoxUsername.Text = "";
            passwordBox.Password = "";
            passwordBoxComfirm.Password = "";
        }
    }
}