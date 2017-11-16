using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.Storage;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using Windows.UI.Popups;
using System.Text.RegularExpressions;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

namespace NotesApp
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class AddNote : Page
    {

        public AddNote()
        {
            this.InitializeComponent();
        }

        /// <summary>
        /// Invoked when this page is about to be displayed in a Frame.
        /// </summary>
        /// <param name="e">Event data that describes how this page was reached.  The Parameter
        /// property is typically used to configure the page.</param>

        private async void grd_RightTapped(object sender, RightTappedRoutedEventArgs e)
        {
            PopupMenu pMenu = new PopupMenu();
            UICommand UndoCommand = new UICommand();
            UndoCommand.Label = "Undo";
            pMenu.Commands.Add(UndoCommand);
            var chosenCommand = await pMenu.ShowForSelectionAsync(new Rect(e.GetPosition(null), e.GetPosition(null)));
            if (chosenCommand != null)
            {
                tboxNoteTitle.Text = "";
                tboxNoteContent.Text = "";
            }
        }

        private void bttnCancel_Tapped(object sender, TappedRoutedEventArgs e)
        {
            Frame.Navigate(typeof(MainPage));
        }

        private void bttnSave_Tapped(object sender, TappedRoutedEventArgs e)
        {
            ApplicationDataCompositeValue composite = new ApplicationDataCompositeValue();
            composite["Title"] = tboxNoteTitle.Text;
            composite["Content"] = tboxNoteContent.Text;
            ApplicationDataContainer localSettings = ApplicationData.Current.LocalSettings;
            if (localSettings.Values["NoteNum"] == null)
                localSettings.Values["NoteNum"] = 0;
            localSettings.Values[localSettings.Values["NoteNum"].ToString()] = composite;
            localSettings.Values["NoteNum"] = Convert.ToInt32(localSettings.Values["NoteNum"].ToString()) + 1;
            Frame.Navigate(typeof(MainPage));
        }
    }
}
