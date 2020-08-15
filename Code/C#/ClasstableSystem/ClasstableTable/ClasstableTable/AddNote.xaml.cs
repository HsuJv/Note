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
using Windows.Storage;
using System.Text.RegularExpressions;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

namespace ClasstableTable
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class AddNote : Page
    {
        string usrname;

        public AddNote()
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
            usrname = e.Parameter as string;
        }

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
                tboxNoteDeadline.Text = "yyyy-mm-dd";
            }
        }

        private void bttnCancel_Tapped(object sender, TappedRoutedEventArgs e)
        {
            Frame.Navigate(typeof(Note), usrname);
        }

        private async void bttnSave_Tapped(object sender, TappedRoutedEventArgs e)
        {
            bool c = true;
            Regex reg = new Regex("^(?:(?!0000)[0-9]{4}-(?:(?:0[1-9]|1[0-2])-(?:0[1-9]|1[0-9]|2[0-8])|(?:0[13-9]|1[0-2])-(?:29|30)|(?:0[13578]|1[02])-31)|(?:[0-9]{2}(?:0[48]|[2468][048]|[13579][26])|(?:0[48]|[2468][048]|[13579][26])00)-02-29)$");
            if (string.IsNullOrEmpty(tboxNoteTitle.Text))
            {
                MessageDialog msg = new MessageDialog("You ought to type in the subject", "Warning");
                UICommand CancelCommand = new UICommand();
                CancelCommand.Label = "Cancel";
                msg.Commands.Add(CancelCommand);
                IUICommand selectedCommand = await msg.ShowAsync();
                c = false;
            }
            else if (string.IsNullOrEmpty(tboxNoteContent.Text))
            {
                MessageDialog msg = new MessageDialog("You ought to type in the content of the assignment", "Warning");
                UICommand CancelCommand = new UICommand();
                CancelCommand.Label = "Cancel";
                msg.Commands.Add(CancelCommand);
                IUICommand selectedCommand = await msg.ShowAsync();
                c = false;
            }
            else if (string.IsNullOrEmpty(tboxNoteDeadline.Text))
            {
                MessageDialog msg = new MessageDialog("You ought to type in the Deadline", "Warning");
                UICommand CancelCommand = new UICommand();
                CancelCommand.Label = "Cancel";
                msg.Commands.Add(CancelCommand);
                IUICommand selectedCommand = await msg.ShowAsync();
                c = false;
            }
            else if (!reg.IsMatch(tboxNoteDeadline.Text))
            {
                MessageDialog msg = new MessageDialog("The Deadline should follow the form : yyyy-mm-dd, and must be a valid value", "Warning");
                UICommand CancelCommand = new UICommand();
                CancelCommand.Label = "Cancel";
                msg.Commands.Add(CancelCommand);
                IUICommand selectedCommand = await msg.ShowAsync();
                c = false;
            }
            if (c)
            {
                ApplicationDataCompositeValue composite = new ApplicationDataCompositeValue();
                composite["Title"] = tboxNoteTitle.Text;
                composite["Content"] = tboxNoteContent.Text;
                composite["Deadline"] = tboxNoteDeadline.Text;
                composite["Usrname"] = usrname;
                ApplicationDataContainer localSettings = ApplicationData.Current.LocalSettings;
                if (localSettings.Values[usrname+"NoteNum"] == null)
                    localSettings.Values[usrname+"NoteNum"] = 0;
                localSettings.Values[usrname+"N"+localSettings.Values[usrname+"NoteNum"].ToString()] = composite;
                localSettings.Values[usrname+"NoteNum"] = Convert.ToInt32(localSettings.Values[usrname+"NoteNum"].ToString()) + 1;
                Frame.Navigate(typeof(Note), usrname);
            }
        }


        private void tboxNoteDeadline_GotFocus(object sender, RoutedEventArgs e)
        {
            if (tboxNoteDeadline.Text == "yyyy-mm-dd")
            {
                tboxNoteDeadline.Text = "";
            }
            
        }
    }
}
