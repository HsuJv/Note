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

namespace NotesApp
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {

        public MainPage()
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
                int lastIndex = Convert.ToInt32(localSettings.Values["NoteNum"].ToString());
                NotesCollection.Notes.Clear();
                for (int i = 0; i < lastIndex; i++)
                {
                    try
                    {
                        if (localSettings.Values[i.ToString()] != null)
                        {
                            ApplicationDataCompositeValue noteValue = localSettings.Values[i.ToString()] as ApplicationDataCompositeValue;
                            string title = noteValue["Title"].ToString();
                            string content = noteValue["Content"].ToString();
                            NotesCollection.Notes.Add(new Note(title, content));
                        }
                    }
                    catch { }
                }
            }
            catch { }
            lstBoxNotes.ItemsSource = NotesCollection.Notes;
            if (lstBoxNotes.Items.Count == 0)
                txtBlkNoNoteExists.Visibility = Windows.UI.Xaml.Visibility.Visible;
            else
                txtBlkNoNoteExists.Visibility = Windows.UI.Xaml.Visibility.Collapsed;

        }

        private void bttnAdd_Tapped(object sender, TappedRoutedEventArgs e)
        {
            Frame.Navigate(typeof(AddNote));
        }

        private async void lstBoxNotes_RightTapped(object sender, RightTappedRoutedEventArgs e)
        {
            PopupMenu pMenu = new PopupMenu();
            UICommand addCommand = new UICommand();
            addCommand.Label = "Add";
            pMenu.Commands.Add(addCommand);
            var chosenCommand = await pMenu.ShowForSelectionAsync(new Rect(e.GetPosition(null), e.GetPosition(null)));
            if (chosenCommand != null)
            {
                Frame.Navigate(typeof(AddNote));
            }
        }

        private void lstBoxNotes_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            Frame.Navigate(typeof(NoteDetails), lstBoxNotes.SelectedItem);
        }
    }
}
