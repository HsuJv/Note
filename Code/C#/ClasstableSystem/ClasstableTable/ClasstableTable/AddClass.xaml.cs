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
    public sealed partial class AddClass : Page
    {
        string usrname;
        int S_D = 0;

        public AddClass()
        {
            this.InitializeComponent();
        }

        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            usrname = e.Parameter as string;
        }

        private void bttnBack_Click(object sender, RoutedEventArgs e)
        {
            Frame.GoBack();
        }

        private async void bttnAdd_Click(object sender, RoutedEventArgs e)
        {
            if (string.IsNullOrEmpty(txtBoxCoursename.Text))
            {
                MessageDialog msg = new MessageDialog("The coursename cannot be empty", "Warning");
                UICommand CancelCommand = new UICommand();
                CancelCommand.Label = "Cancel";
                msg.Commands.Add(CancelCommand);
                IUICommand selectedCommand = await msg.ShowAsync();
            }
            else if (string.IsNullOrEmpty(txtBoxTeachername.Text))
            {
                MessageDialog msg = new MessageDialog("The teacher's name cannot be empty", "Warning");
                UICommand CancelCommand = new UICommand();
                CancelCommand.Label = "Cancel";
                msg.Commands.Add(CancelCommand);
                IUICommand selectedCommand = await msg.ShowAsync();
            }
            else if (string.IsNullOrEmpty(txtBoxClassroom.Text))
            {
                MessageDialog msg = new MessageDialog("The classroom info cannot be empty", "Warning");
                UICommand CancelCommand = new UICommand();
                CancelCommand.Label = "Cancel";
                msg.Commands.Add(CancelCommand);
                IUICommand selectedCommand = await msg.ShowAsync();
            }
            else if (comboBoxClassTime.SelectedIndex == -1)
            {
                MessageDialog msg = new MessageDialog("The classtime cannot be empty", "Warning");
                UICommand CancelCommand = new UICommand();
                CancelCommand.Label = "Cancel";
                msg.Commands.Add(CancelCommand);
                IUICommand selectedCommand = await msg.ShowAsync();
            }
            else if (comboBoxStartweek.SelectedIndex == -1)
            {
                MessageDialog msg = new MessageDialog("The startweek cannot be empty", "Warning");
                UICommand CancelCommand = new UICommand();
                CancelCommand.Label = "Cancel";
                msg.Commands.Add(CancelCommand);
                IUICommand selectedCommand = await msg.ShowAsync();
            }
            else if (comboBoxEndweek.SelectedIndex == -1)
            {
                MessageDialog msg = new MessageDialog("The endweek cannot be empty", "Warning");
                UICommand CancelCommand = new UICommand();
                CancelCommand.Label = "Cancel";
                msg.Commands.Add(CancelCommand);
                IUICommand selectedCommand = await msg.ShowAsync();
            }
            else if (comboBoxWeektime.SelectedIndex == -1)
            {
                MessageDialog msg = new MessageDialog("The weekday cannot be empty", "Warning");
                UICommand CancelCommand = new UICommand();
                CancelCommand.Label = "Cancel";
                msg.Commands.Add(CancelCommand);
                IUICommand selectedCommand = await msg.ShowAsync();
            }
            else if (S_D == 0)
            {
                MessageDialog msg = new MessageDialog("The single or duel info cannot be empty", "Warning");
                UICommand CancelCommand = new UICommand();
                CancelCommand.Label = "Cancel";
                msg.Commands.Add(CancelCommand);
                IUICommand selectedCommand = await msg.ShowAsync();
            }
            else if (Convert.ToInt32(comboBoxStartweek.SelectedIndex.ToString()) > Convert.ToInt32(comboBoxEndweek.SelectedIndex.ToString()))
            {
                MessageDialog msg = new MessageDialog("The endweek must be after startweek", "Warning");
                UICommand CancelCommand = new UICommand();
                CancelCommand.Label = "Cancel";
                msg.Commands.Add(CancelCommand);
                IUICommand selectedCommand = await msg.ShowAsync();
            }
            else
            {
                ApplicationDataCompositeValue composite = new ApplicationDataCompositeValue();
                composite["Coursename"] = txtBoxCoursename.Text;
                composite["Teachername"] = txtBoxTeachername.Text;
                composite["Classroom"] = txtBoxClassroom.Text;
                composite["Startweek"] = comboBoxStartweek.SelectedIndex + 1;
                composite["Endweek"] = comboBoxEndweek.SelectedIndex + 1;
                composite["Classtime"] = comboBoxClassTime.SelectedIndex + 1;
                composite["Weektime"] = comboBoxWeektime.SelectedIndex;
                composite["DuelOrSingle"] = S_D;
                ApplicationDataContainer localSettings = ApplicationData.Current.LocalSettings;
                if (localSettings.Values[usrname+"ClassNum"] == null)
                    localSettings.Values[usrname+"ClassNum"] = 0;
                localSettings.Values[usrname + "C" + localSettings.Values[usrname+"ClassNum"].ToString()] = composite;
                localSettings.Values[usrname+"ClassNum"] = Convert.ToInt32(localSettings.Values[usrname+"ClassNum"].ToString()) + 1;
                string teacher = txtBoxTeachername.Text;
                if (localSettings.Values[teacher + "ClassNum"] == null)
                {
                    localSettings.Values[teacher + "ClassNum"] = 0;
                    ApplicationDataCompositeValue comp = new ApplicationDataCompositeValue();
                    comp["Usrname"] = teacher;
                    comp["Pwd"] = "888888";
                    comp["Authority"] = 2;
                    localSettings.Values["U" + localSettings.Values["UsrNum"].ToString()] = comp;
                    localSettings.Values["UsrNum"] = Convert.ToInt32(localSettings.Values["UsrNum"].ToString()) + 1;
                }
                localSettings.Values[teacher + "C" + localSettings.Values[teacher + "ClassNum"].ToString()] = composite;
                localSettings.Values[teacher + "ClassNum"] = Convert.ToInt32(localSettings.Values[teacher + "ClassNum"].ToString()) + 1;
                Frame.Navigate(typeof(StudentPage), usrname);
            }
        }

        private void bttnReset_Click(object sender, RoutedEventArgs e)
        {
            txtBoxCoursename.Text = "";
            txtBoxTeachername.Text = "";
            txtBoxClassroom.Text = "";
            comboBoxStartweek.SelectedIndex = -1;
            comboBoxEndweek.SelectedIndex = -1;
            comboBoxClassTime.SelectedIndex = -1;
            comboBoxWeektime.SelectedIndex = -1;
            radioBttnDuel.IsChecked = false;
            radioBttnSingle.IsChecked = false;
            S_D = 0;
        }

        private void radioBttnSingle_Checked(object sender, RoutedEventArgs e)
        {
            S_D = 1;
        }

        private void radioBttnDuel_Checked(object sender, RoutedEventArgs e)
        {
            S_D = 2;
        }

        private void radioBttnBoth_Checked(object sender, RoutedEventArgs e)
        {
            S_D = 3;
        }
    }
}
//课程名、开课地点、开课时间、开课周、是否单双周