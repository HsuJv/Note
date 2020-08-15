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
    public sealed partial class TotalClass : Page
    {
        string usrname;
        int auth;
        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            usrname = e.Parameter as string;
            ApplicationDataContainer ls = ApplicationData.Current.LocalSettings;
            int l = Convert.ToInt32(ls.Values["UsrNum"].ToString());
            for (int i = 0; i < l; i++)
            {
                try
                {
                    if (ls.Values["U" + i.ToString()] != null)
                    {
                        ApplicationDataCompositeValue UserValue = ls.Values["U" + i.ToString()] as ApplicationDataCompositeValue;
                        if (usrname == UserValue["Usrname"].ToString())
                        {
                            auth = Convert.ToInt32(UserValue["Authority"].ToString());
                        }

                    }
                }
                catch { }
            }
            if (auth == 2)
            {
                bttnHomeworknote.IsEnabled = false;
                bttnAdd.IsEnabled = false;
            }//屏蔽button


            foreach (var t in grd.Children)
            {
                if (t is TextBox)
                {
                    TextBox tbox = t as TextBox;
                    tbox.Text = "";
                }
            }
            ApplicationDataContainer localSettings = ApplicationData.Current.LocalSettings;
            if (localSettings.Values[usrname+"ClassNum"] != null)
            {
                int lastIndex = Convert.ToInt32(localSettings.Values[usrname + "ClassNum"].ToString());
                for (int i = 0; i < lastIndex; i++)
                {
                    ApplicationDataCompositeValue ClassInfo = localSettings.Values[usrname + "C" + i.ToString()] as ApplicationDataCompositeValue;
                    string CourseName = ClassInfo["Coursename"].ToString();
                    string TeacherName = ClassInfo["Teachername"].ToString();
                    string ClassRoom = ClassInfo["Classroom"].ToString();
                    int StartWeek = Convert.ToInt32(ClassInfo["Startweek"].ToString());
                    int EndWeek = Convert.ToInt32(ClassInfo["Endweek"].ToString());
                    int ClassTime = Convert.ToInt32(ClassInfo["Classtime"].ToString());
                    int WeekTime = Convert.ToInt32(ClassInfo["Weektime"].ToString());
                    if (WeekTime == 0) WeekTime = 7;
                    int DuelOrSingle = Convert.ToInt32(ClassInfo["DuelOrSingle"].ToString());
                    foreach (var t in grd.Children)
                    {
                        if (t is TextBox)
                        {
                            TextBox tbox = t as TextBox;
                            if (Grid.GetColumn(tbox) == WeekTime && Grid.GetRow(tbox) == ClassTime + 1)
                            {
                                if (String.IsNullOrEmpty(tbox.Text))
                                {
                                    string tt = CourseName + "@" + TeacherName + "(" + ClassRoom + ")";
                                    if (DuelOrSingle != 3)
                                    {
                                        if (DuelOrSingle == 1)
                                        {
                                            tt += "Single";
                                        }
                                        else
                                        {
                                            tt += "Duel";
                                        }
                                    }
                                    tbox.Text = tt;
                                }
                                else
                                {
                                    string tt = tbox.Text;
                                    tt = tt + "\n" + CourseName + "@" + TeacherName + "(" + ClassRoom + ")";
                                    if (DuelOrSingle != 3)
                                    {
                                        if (DuelOrSingle == 1)
                                        {
                                            tt += "Single";
                                        }
                                        else
                                        {
                                            tt += "Duel";
                                        }
                                    }
                                    tbox.Text = tt;
                                }
                            }
                        }
                    }
                }
            }
        }

        public TotalClass()
        {
            this.InitializeComponent();
        }

        private void bttnBack_Click(object sender, RoutedEventArgs e)
        {
            if (auth == 1)
            {
                Frame.Navigate(typeof(StudentPage), usrname);
            }
            else
            {
                Frame.Navigate(typeof(TeacherPage), usrname);
            }
        }

        private void bttnHomeworknote_Click(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(Note), usrname);
        }

        private void bttnAdd_Click(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(AddClass), usrname);
        }

        private async void grd_RightTapped(object sender, RightTappedRoutedEventArgs e)
        {
            if (auth == 1)
            {
                UIElement control = e.OriginalSource as UIElement;
                while (control != null && control != sender as UIElement)
                {
                    if (control is TextBox)
                    {
                        TextBox tbox = control as TextBox;
                        if (!String.IsNullOrEmpty(tbox.Text))
                        {
                            PopupMenu pMenu = new PopupMenu();
                            UICommand deleteCommand = new UICommand();
                            deleteCommand.Label = "DELETE";
                            pMenu.Commands.Add(deleteCommand);
                            var chosenCommand = await pMenu.ShowForSelectionAsync(new Rect(e.GetPosition(null), e.GetPosition(null)));
                            if (chosenCommand != null)
                            {
                                MessageDialog msg = new MessageDialog("Are you sure to delete this course?", "Delete Confirmation");
                                UICommand noCommand = new UICommand();
                                noCommand.Label = "No";
                                noCommand.Id = 1;
                                msg.Commands.Add(noCommand);
                                UICommand yesCommand = new UICommand();
                                yesCommand.Label = "Yes";
                                yesCommand.Id = 2;
                                msg.Commands.Add(yesCommand);
                                IUICommand selectedCommand = await msg.ShowAsync();
                                if (selectedCommand != null)
                                {
                                    if ((int)selectedCommand.Id == 2)
                                    {

                                        ApplicationDataContainer localSettings = ApplicationData.Current.LocalSettings;
                                        ApplicationDataCompositeValue composite;
                                        int lastIndex = Convert.ToInt32(localSettings.Values[usrname + "ClassNum"].ToString());
                                        for (int i = 0; i < lastIndex; i++)
                                        {
                                            try
                                            {
                                                if (localSettings.Values[usrname + "C" + i.ToString()] != null)
                                                {
                                                    composite = localSettings.Values[usrname + "C" + i.ToString()] as ApplicationDataCompositeValue;
                                                    if (Grid.GetColumn(tbox) == Convert.ToInt32(composite["Weektime"].ToString()) && Grid.GetRow(tbox) == Convert.ToInt32(composite["Classtime"].ToString()) + 1)
                                                    {
                                                        int j = i;
                                                        while ((j + 1) < lastIndex)
                                                        {
                                                            localSettings.Values[usrname + "C" + j.ToString()] = localSettings.Values[usrname + "C" + (j + 1).ToString()];
                                                            j++;
                                                        }
                                                        composite = localSettings.Values[usrname + "C" + (lastIndex - 1).ToString()] as ApplicationDataCompositeValue;
                                                        localSettings.DeleteContainer("composite");
                                                        localSettings.Values[usrname + "ClassNum"] = Convert.ToInt32(localSettings.Values[usrname + "ClassNum"].ToString()) - 1;

                                                        break;
                                                    }
                                                }
                                            }
                                            catch { }
                                        }
                                        Frame.Navigate(typeof(TotalClass), usrname);
                                    }
                                }
                            }
                        }
                        break;
                    }
                    control = VisualTreeHelper.GetParent(control) as UIElement;
                }
            }
        }


    }
}
//作业备忘录