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
using System.Text.RegularExpressions;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

namespace ClasstableTable
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class EditNote : Page
    {
        Homework selectedNote;
        string usrname;
        public EditNote()
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

        private async void tboxNoteContent_RightTapped(object sender, RightTappedRoutedEventArgs e)
        {
            PopupMenu pMenu = new PopupMenu();
            UICommand SelectAllCommand = new UICommand();
            SelectAllCommand.Label = "SelectAll";
            pMenu.Commands.Add(SelectAllCommand);
            var chosenCommand = await pMenu.ShowForSelectionAsync(new Rect(e.GetPosition(null), e.GetPosition(null)));
            if (chosenCommand != null)
            {
                tboxNoteContent.SelectAll();
            }
        }

        private void bttnCancel_Tapped(object sender, TappedRoutedEventArgs e)
        {
            Frame.Navigate(typeof(Note), usrname);
        }

        private async void bttnSave_Click(object sender, RoutedEventArgs e)
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
                ApplicationDataCompositeValue composite_old = new ApplicationDataCompositeValue();
                composite["Title"] = tboxNoteTitle.Text;
                composite["Content"] = tboxNoteContent.Text;
                composite["Deadline"] = tboxNoteDeadline.Text;
                composite["Usrname"] = usrname;
                ApplicationDataContainer localSettings = ApplicationData.Current.LocalSettings;
                int lastIndex = Convert.ToInt32(localSettings.Values[usrname+"NoteNum"].ToString());
                for (int i = 0; i < lastIndex; i++)
                {
                    try
                    {
                        if (localSettings.Values[usrname+"N"+i.ToString()] != null)
                        {
                            composite_old = localSettings.Values[usrname+"N"+i.ToString()] as ApplicationDataCompositeValue;
                            if (selectedNote.Title == composite_old["Title"] as string && selectedNote.Content == composite_old["Content"] as string)
                            {
                                localSettings.Values[usrname+"N"+i.ToString()] = composite;
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

