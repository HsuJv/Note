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
    public sealed partial class Admin : Page
    {
        public Admin()
        {
            this.InitializeComponent();
        }
        /// <summary>
        /// Invoked when this page is about to be displayed in a Frame.
        /// </summary>
        /// <param name="e">Event data that describes how this page was reached.  The Parameter
        /// property is typically used to configure the page.</param>
        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            try
            {
                ApplicationDataContainer localSettings = ApplicationData.Current.LocalSettings;
                int lastIndex = Convert.ToInt32(localSettings.Values["UsrNum"].ToString());
                UserCollection.User.Clear();
                for (int i = 0; i < lastIndex; i++)
                {
                    try
                    {
                        if (localSettings.Values["U" + i.ToString()] != null)
                        {
                            ApplicationDataCompositeValue UserValue = localSettings.Values["U" + i.ToString()] as ApplicationDataCompositeValue;
                            string Usrname = UserValue["Usrname"].ToString();
                            string Pwd = UserValue["Pwd"].ToString();
                            string Authority = UserValue["Authority"].ToString();
                            UserCollection.User.Add(new User(Usrname, Pwd, Authority));
                        }
                    }
                    catch { }
                }
            }
            catch { }
            lstBoxNotes.ItemsSource = UserCollection.User;
            if (lstBoxNotes.Items.Count == 0)
                txtBlkNoNoteExists.Visibility = Windows.UI.Xaml.Visibility.Visible;
            else
                txtBlkNoNoteExists.Visibility = Windows.UI.Xaml.Visibility.Collapsed;

        }

        private void bttnBak_Tapped(object sender, TappedRoutedEventArgs e)
        {
            Frame.Navigate(typeof(MainPage));
        }

        private void bttnRm_Tapped(object sender, TappedRoutedEventArgs e)
        {
            ApplicationDataContainer localSettings = ApplicationData.Current.LocalSettings;
            ApplicationDataCompositeValue composite;
            int lastIndex = Convert.ToInt32(localSettings.Values["UsrNum"].ToString());
            for (int i = 0; i < lastIndex; i++)
            {
                try
                {
                    string usrname;
                    composite = localSettings.Values["U" + i.ToString()] as ApplicationDataCompositeValue;
                    usrname = composite["Usrname"].ToString();
                    if (Convert.ToInt32(composite["Authority"].ToString()) == 1)
                    {
                        int lastIndex2 = Convert.ToInt32(localSettings.Values[usrname + "NoteNum"].ToString());
                        for (int j = 0; j < lastIndex2; j++)
                        {
                            try
                            {
                                composite = localSettings.Values[usrname + "N" + j.ToString()] as ApplicationDataCompositeValue;
                                localSettings.DeleteContainer("composite");
                                localSettings.Values[usrname + "NoteNum"] = Convert.ToInt32(localSettings.Values[usrname + "NoteNum"].ToString()) - 1;

                            }
                            catch { }
                        }
                        lastIndex2 = Convert.ToInt32(localSettings.Values[usrname + "ClassNum"].ToString());
                        for (int j = 0; j < lastIndex2; j++)
                        {
                            try
                            {
                                composite = localSettings.Values[usrname + "C" + j.ToString()] as ApplicationDataCompositeValue;
                                localSettings.DeleteContainer("composite");
                                localSettings.Values[usrname + "ClassNum"] = Convert.ToInt32(localSettings.Values[usrname + "ClassNum"].ToString()) - 1;

                            }
                            catch { }
                        }
                    }
                    else
                    {
                        int lastIndex2 = Convert.ToInt32(localSettings.Values[usrname + "ClassNum"].ToString());
                        for (int j = 0; j < lastIndex2; j++)
                        {
                            try
                            {
                                composite = localSettings.Values[usrname + "C" + j.ToString()] as ApplicationDataCompositeValue;
                                localSettings.DeleteContainer("composite");
                                localSettings.Values[usrname + "ClassNum"] = Convert.ToInt32(localSettings.Values[usrname + "ClassNum"].ToString()) - 1;
                                if (Convert.ToInt32(localSettings.Values[usrname + "ClassNum"].ToString()) == 0)
                                {
                                    localSettings.Values[usrname + "ClassNum"] = null;
                                }
                            }
                            catch { }
                        }
                    }


                    composite = localSettings.Values["U" + i.ToString()] as ApplicationDataCompositeValue;
                    localSettings.DeleteContainer("composite");
                    localSettings.Values["UsrNum"] = Convert.ToInt32(localSettings.Values["UsrNum"].ToString()) - 1;
                }
                catch { }
            }


            Frame.Navigate(typeof(Admin));
        }
    }
}
