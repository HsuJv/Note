using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
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

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

namespace ClasstableTable
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class NoteDetails : Page
    {
        Homework selectedNote;
        string usrname;
        public NoteDetails()
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
            if (e.Parameter != null && e.Parameter is Homework)
            {
                selectedNote = e.Parameter as Homework;
                tboxNoteContent.DataContext = selectedNote;
                tboxNoteTitle.DataContext = selectedNote;
                tboxNoteDeadline.DataContext = selectedNote;
                usrname = selectedNote.Usrname;
            }

        }

        private void bttnEdit_Tapped(object sender, TappedRoutedEventArgs e)
        {
            Frame.Navigate(typeof(EditNote), selectedNote);
        }

        private void bttnCancel_Tapped(object sender, TappedRoutedEventArgs e)
        {
            Frame.Navigate(typeof(Note), usrname);
        }

        private async void bttnDelete_Tapped(object sender, TappedRoutedEventArgs e)
        {
            MessageDialog msg = new MessageDialog("Are you sure to delete this note?", "Delete Confirmation");
            UICommand noCommand = new UICommand();
            noCommand.Label = "No";
            noCommand.Id = 1;
            msg.Commands.Add(noCommand);
            UICommand yesCommand = new UICommand();
            yesCommand.Label = "Yes";
            yesCommand.Id = 2;
            msg.Commands.Add(yesCommand);
            IUICommand selectedCommand = await msg.ShowAsync();
            if(selectedCommand != null)
            {
                if ((int)selectedCommand.Id == 2)
                {
                    ApplicationDataContainer localSettings = ApplicationData.Current.LocalSettings;
                    ApplicationDataCompositeValue composite;
                    int lastIndex = Convert.ToInt32(localSettings.Values[usrname+"NoteNum"].ToString());
                    for (int i = 0; i < lastIndex; i++)
                    {
                        try
                        {
                            if (localSettings.Values[usrname+"N"+i.ToString()] != null)
                            {
                                composite = localSettings.Values[usrname+"N"+i.ToString()] as ApplicationDataCompositeValue;
                                if(selectedNote.Title == composite["Title"] as string && selectedNote.Content == composite["Content"] as string)
                                {
                                    int j = i;
                                    while((j + 1) < lastIndex)
                                    {
                                        localSettings.Values[usrname + "N" + j.ToString()] = localSettings.Values[usrname + "N" + (j + 1).ToString()];
                                        j++;     
                                    }
                                    composite = localSettings.Values[usrname + "N" + (lastIndex - 1).ToString()] as ApplicationDataCompositeValue;
                                    localSettings.DeleteContainer("composite");
                                    localSettings.Values[usrname+"NoteNum"] = Convert.ToInt32(localSettings.Values[usrname+"NoteNum"].ToString()) - 1;

                                    break;
                                }
                            }
                        }
                        catch { }
                    }
                    Frame.Navigate(typeof(Note), usrname);
                }
            }
        }
    }
}
